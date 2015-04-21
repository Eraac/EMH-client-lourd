#include "Constraint.hpp"

const int Entity::Constraint::weight = 1;

Entity::Constraint::Constraint() : Entity(), m_type(Constraint::Type::NONE), m_fieldId(0)
{

}

Entity::Constraint::~Constraint()
{

}


void Entity::Constraint::setType(const Constraint::Type type)
{
    m_type = type;
}

void Entity::Constraint::setFieldId(unsigned int id)
{
    m_fieldId = id;
}

Entity::Constraint::Type Entity::Constraint::getType() const
{
    return m_type;
}

QString Entity::Constraint::getTypeReadable() const
{
    QString type;

    switch(m_type)
    {
        case Constraint::Type::LENGTH:
            type = "Longueur min et/ou max";
        break;

        case Constraint::Type::BETWEEN:
            type = "Entre X et Y";
        break;

        case Constraint::Type::NOTEQUAL:
            type = "Non égal";
        break;

        case Constraint::Type::LOWER:
            type = "Plus petit que";
        break;

        case Constraint::Type::LOWEROREQUAL:
            type = "Plus petit ou égal à";
        break;

        case Constraint::Type::GREATER:
            type = "Plus grand que";
        break;

        case Constraint::Type::GREATEROREQUAL:
            type = "Plus grand ou égal à";
        break;

        case Constraint::Type::USERPASSWORD:
            type = "Mot de passe de l'utilisateur";
        break;

        case Constraint::Type::REGEX:
            type = "Regex";
        break;
    }

    return type;
}

QStringList Entity::Constraint::getParams()
{
    QStringList listParams;

    if (!initDB())
        return listParams;

    QSqlQuery query = m_db.exec("SELECT value FROM param WHERE fieldConstraint_id = ?");

    query.bindValue(0, m_id);
    query.exec();

    while (query.next())
    {
        listParams << query.value(0).toString();
    }

    return listParams;
}

void Entity::Constraint::removeParams()
{
    if (!initDB())
        return;

   QSqlQuery query = m_db.exec("DELETE FROM param WHERE fieldConstraint_id = ?");

   query.bindValue(0, m_id);
   query.exec();
}

Entity::Entity::ErrorType Entity::Constraint::load(unsigned int id)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM fieldConstraint WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id = query.value("id").toInt();
    m_type = static_cast<Constraint::Type> (query.value("type").toInt());
    m_fieldId = query.value("fields_id").toInt();

    return Entity::ErrorType::NONE;
}

int Entity::Constraint::getWeight() const
{
    return Constraint::weight;
}

void Entity::Constraint::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec("UPDATE fieldConstraint SET type = ?, fields_id = ? WHERE id = ?");

        query.bindValue(0, static_cast<int> (m_type));
        query.bindValue(1, m_fieldId);
        query.bindValue(2, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec("INSERT INTO fieldConstraint (type, fields_id) VALUES(?, ?)");

        query.bindValue(0, static_cast<int> (m_type));
        query.bindValue(1, m_fieldId);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::Constraint::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM fieldConstraint WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::Constraint::isValid() const
{
    return (m_type != Constraint::Type::NONE);
}
