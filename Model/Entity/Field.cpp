#include "Field.hpp"

const int Entity::Field::weight = 1;

Entity::Field::Field() : Entity(), m_type(Field::Type::NONE), m_isMultiple(false),
                         m_label(""), m_placeholder(""), m_helpText(""), m_isRequired(true),
                         m_idForm(0)
{

}

Entity::Field::~Field()
{

}

void Entity::Field::setType(const Field::Type type)
{
    m_type = type;
}

void Entity::Field::setLabel(const QString &label)
{
    m_label = label;
}

void Entity::Field::setPlaceholder(const QString &placeholder)
{
    m_placeholder = placeholder;
}

void Entity::Field::setHelpText(const QString &helpText)
{
    m_helpText = helpText;
}

void Entity::Field::setIsMultiple(bool multiple)
{
    m_isMultiple = multiple;
}

void Entity::Field::setIsRequired(bool required)
{
    m_isRequired = required;
}

void Entity::Field::setFormId(unsigned int id)
{
    m_idForm = id;
}

Entity::Field::Type Entity::Field::getType() const
{
    return m_type;
}

QString Entity::Field::getTypeReadable() const
{
    QString type;

    switch(m_type)
    {
        case Field::Type::DATE:
            type = "Date";
        break;

        case Field::Type::DATETIME:
            type = "Date et heure";
        break;

        case Field::Type::EMAIL:
            type = "Email";
        break;

        case Field::Type::NUMBER:
            type = "Nombre";
        break;

        case Field::Type::RADIO:
            type = "Choix multiple";
        break;

        case Field::Type::TEXT:
            type = "Texte";
        break;

        case Field::Type::TIME:
            type = "Heure";
        break;

        case Field::Type::URL:
            type = "Url";
        break;

        case Field::Type::PASSWORD:
            type = "Caché";
        break;

        case Field::Type::TEXTAREA:
            type = "Long texte";
        break;

        default:
            type = "Texte";
    }

    return type;
}

QString Entity::Field::getLabel() const
{
    return m_label;
}

QString Entity::Field::getPlaceholder() const
{
    return m_placeholder;
}

QString Entity::Field::getHelpText() const
{
    return m_helpText;
}

bool Entity::Field::getIsMultiple() const
{
    return m_isMultiple;
}

bool Entity::Field::getIsRequired() const
{
    return m_isRequired;
}

unsigned int Entity::Field::getFormId() const
{
    return m_idForm;
}

QString Entity::Field::getDefaultValue()
{
    QString defaultValue;

    if (!initDB() || m_id == 0)
        return defaultValue;

    QSqlQuery query = m_db.exec("SELECT defaultValue.value \
                                FROM defaultValue WHERE field_id = ?");

    query.bindValue(0, m_id);
    query.exec();

    while (query.next())
    {
        defaultValue.append(query.value(0).toString() + "\n");
    }

    return defaultValue;
}

QList<Entity::Constraint> Entity::Field::getConstraints()
{
    QList<Constraint> listConstraints;

    if (!initDB())
        return listConstraints; // TODO Add exception ?

    QSqlQuery query = m_db.exec("SELECT fieldConstraint.id FROM fieldConstraint \
                                WHERE fieldConstraint.fields_id = ?");

    query.bindValue(0, m_id);
    query.exec();

    while (query.next())
    {
        Constraint constraint;
            constraint.load(query.value(0).toInt());

        listConstraints.append(constraint);
    }

    return listConstraints;
}

Entity::Entity::ErrorType Entity::Field::load(unsigned int id)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM field WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id            = id;
    m_isMultiple    = query.value("multiple").toBool();
    m_label         = query.value("label").toString();
    m_placeholder   = query.value("placeholder").toString();
    m_helpText      = query.value("helpText").toString();
    m_type          = static_cast<Field::Type> (query.value("type").toInt());
    m_isRequired    = query.value("isRequired").toBool();
    m_idForm        = query.value("form_id").toInt();

    return Entity::ErrorType::NONE;
}

int Entity::Field::getWeight() const
{
    return Field::weight;
}

void Entity::Field::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec(
                    "UPDATE field SET multiple = ?, label = ?, placeholder = ?, helpText = ?, \
                    type = ?, isRequired = ?, form_id = ? WHERE id = ?"
                    );

        query.bindValue(0, m_isMultiple);
        query.bindValue(1, m_label);
        query.bindValue(2, m_placeholder);
        query.bindValue(3, m_helpText);
        query.bindValue(4, static_cast<int> (m_type));
        query.bindValue(5, m_isRequired);
        query.bindValue(6, m_idForm);
        query.bindValue(7, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec(
                    "INSERT INTO field (multiple, label, placeholder, helpText, type, isRequired, form_id) \
                    VALUES(?, ?, ?, ?, ?, ?, ?)"
                    );

        query.bindValue(0, m_isMultiple);
        query.bindValue(1, m_label);
        query.bindValue(2, m_placeholder);
        query.bindValue(3, m_helpText);
        query.bindValue(4, static_cast<int> (m_type));
        query.bindValue(5, m_isRequired);
        query.bindValue(6, m_idForm);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();

        qDebug() << query.lastError().text();
    }
}

void Entity::Field::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM field WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::Field::isValid() const
{
    return (m_type != Field::Type::NONE && !m_label.isEmpty());
}
