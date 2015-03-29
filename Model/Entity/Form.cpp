#include "Form.hpp"

const int Entity::Form::weight = 1;

Entity::Form::Form() : Entity(), m_name(""), m_description(""), m_info(""),
                       m_important(""), m_status(Form::Status::NONE),                                             
                       m_idAuthor(0)
{

}

Entity::Form::~Form()
{

}

bool Entity::Form::formExist(const QString &name)
{
    initDB();

    QSqlQuery query = m_db.exec("SELECT COUNT(*) FROM form WHERE name = ?");

    if (name.isEmpty() && !m_name.isEmpty())
        query.bindValue(0, m_name);
    else if (!name.isEmpty())
        query.bindValue(0, name);
    else
        return false;

    query.exec();
    query.next();

    int count = query.value(0).toInt();

    return (count > 0) ? true : false;
}

Entity::Entity::ErrorType Entity::Form::load(unsigned int id)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM form WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id            = id;
    m_name          = query.value("name").toString();
    m_description   = query.value("description").toString();
    m_info          = query.value("info").toString();
    m_important     = query.value("important").toString();
    m_color         = query.value("color").toString();
    m_status        = static_cast<Form::Status> (query.value("status").toInt());
    m_idAuthor      = query.value("author_id").toInt();


    return Entity::ErrorType::NONE;
}

int Entity::Form::getWeight() const
{
    return Form::weight;
}

void Entity::Form::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec(
                    "UPDATE form SET \
                        author_id = ?, \
                        name = ?, \
                        description = ?, \
                        info = ?, \
                        important = ?, \
                        status = ?, \
                        color = ? \
                    WHERE id = ?");

        query.bindValue(0, m_idAuthor);
        query.bindValue(1, m_name);
        query.bindValue(2, m_description);
        query.bindValue(3, m_info);
        query.bindValue(4, m_important);
        query.bindValue(5, static_cast<int> (m_status));
        query.bindValue(6, m_color);
        query.bindValue(7, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec(
                    "INSERT INTO form (author_id, name, description, info, important, status, color) \
                    VALUES(?, ?, ?, ?, ?, ?, ?)"
                    );

        query.bindValue(0, m_idAuthor);
        query.bindValue(1, m_name);
        query.bindValue(2, m_description);
        query.bindValue(3, m_info);
        query.bindValue(4, m_important);
        query.bindValue(5, static_cast<int> (m_status));
        query.bindValue(6, m_color);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::Form::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM form WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::Form::isValid() const
{
    return (!m_name.isEmpty() && !m_description.isEmpty() &&
            m_status != Form::Status::NONE);
}

void Entity::Form::setName(const QString &name)
{
    if (!name.isEmpty())
        m_name = name;
}

void Entity::Form::setDescription(const QString &description)
{
    if (!description.isEmpty())
        m_description = description;
}

void Entity::Form::setInfo(const QString &info)
{
    m_info = info;
}

void Entity::Form::setImportant(const QString &important)
{
    m_important = important;
}

void Entity::Form::setStatus(Form::Status status)
{
    if (status != Form::Status::NONE)
        m_status = status;
}

void Entity::Form::setIdAuthor(const unsigned int id)
{
    if (id != 0)
        m_idAuthor = id;
}

void Entity::Form::setColor(const QColor &color)
{
    m_color = color.name().remove(0, 1);
}

QString Entity::Form::getName() const
{
    return m_name;
}

QString Entity::Form::getDescription() const
{
    return m_description;
}

QString Entity::Form::getInfo() const
{
    return m_info;
}

QString Entity::Form::getImportant() const
{
    return m_important;
}

Entity::Form::Status Entity::Form::getStatus() const
{
    return m_status;
}


unsigned int Entity::Form::getIdAuthor() const
{
    return m_idAuthor;
}

QString Entity::Form::getColor() const
{
    return m_color;
}
