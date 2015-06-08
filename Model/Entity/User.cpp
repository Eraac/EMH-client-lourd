#include "User.hpp"

const int Entity::User::weight = 1;

Entity::User::User() : Entity(), m_name(""), m_email(""), m_firstName(""), m_password(""),
                       m_hasEncryptedPassword(false), m_isAdmin(false)
{
}

Entity::User::~User()
{
}

bool Entity::User::emailExist(QString const& email)
{
    if (!initDB())
        return false;

    QSqlQuery query = m_db.exec("SELECT COUNT(*) FROM user WHERE username = ?");

    if (!email.isEmpty())
        query.bindValue(0, email);
    else if (!m_name.isEmpty())
        query.bindValue(0, m_name);
    else
        return false;    

    query.exec();
    query.next();

    int count = query.value(0).toInt();

    return (count > 0) ? true : false;
}

Entity::Entity::ErrorType Entity::User::loadUserByLogin(QString const& email, QString const& password)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    Utility::EncodePassword encodePassword;
    QString hashed = encodePassword.encodePassword(password);

    QSqlQuery query = m_db.exec("SELECT * FROM user WHERE username = ? AND password = ?");

    query.bindValue(0, email);
    query.bindValue(1, hashed);
    query.exec();

    qDebug() << email;
    qDebug() << hashed;

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id        = query.value("id").toInt();
    m_email     = email;
    m_name      = query.value("name").toString();
    m_firstName = query.value("firstName").toString();
    m_password  = hashed;
    m_isAdmin   = query.value("isAdmin").toBool();
    m_hasEncryptedPassword = true;    

    return Entity::ErrorType::NONE;
}

Entity::Entity::ErrorType Entity::User::loadUserByEmail(const QString &email)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM user WHERE username = ?");

    query.bindValue(0, email);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id        = query.value("id").toInt();
    m_email     = email;
    m_name      = query.value("name").toString();
    m_firstName = query.value("firstName").toString();
    m_password  = query.value("password").toString();
    m_isAdmin   = query.value("isAdmin").toBool();
    m_hasEncryptedPassword = true;

    return Entity::ErrorType::NONE;
}

Entity::Entity::ErrorType Entity::User::load(unsigned int id)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM user WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id        = id;
    m_email     = query.value("username").toString();;
    m_name      = query.value("name").toString();
    m_firstName = query.value("firstName").toString();
    m_password  = query.value("password").toString();
    m_isAdmin   = query.value("isAdmin").toBool();
    m_hasEncryptedPassword = true;

    return Entity::ErrorType::NONE;
}

QString Entity::User::getName() const
{
    return m_name;
}

QString Entity::User::getFirstName() const
{
    return m_firstName;
}

QString Entity::User::getEmail() const
{
    return m_email;
}

QString Entity::User::getPassword() const
{
    return m_password;
}

bool Entity::User::isAdmin() const
{
    return m_isAdmin;
}

bool Entity::User::hasEncryptedPassword() const
{
    return m_hasEncryptedPassword;
}

QStringList Entity::User::getGroupsName() const
{
    QStringList groupsNameOfUser;

    if (!initDB())
        return groupsNameOfUser;

    QSqlQuery query = m_db.exec("SELECT groups.name FROM user JOIN belong ON belong.user_id = user.id JOIN groups ON groups.id = belong.usergroup_id WHERE user.username = ?");

    query.bindValue(0, m_email);
    query.exec();

    while (query.next())
    {
        QString groupname = query.value(0).toString();
        groupsNameOfUser.append(groupname);
    }

    return groupsNameOfUser;
}

QStringList Entity::User::getAllEmail() const
{
    QStringList emailOfUser;

    if (!initDB())
        return emailOfUser;

    QSqlQuery query = m_db.exec("SELECT user.username FROM user");

    query.exec();

    while (query.next())
    {
        QString email = query.value(0).toString();
        emailOfUser.append(email);
    }

    return emailOfUser;
}

void Entity::User::setName(const QString &name)
{
    if (!name.isEmpty()) // Si le nom n'est pas vide on le remplace
        m_name = name;
}

void Entity::User::setFirstName(const QString &firstName)
{
    if (!firstName.isEmpty()) // Si le prénom n'est pas vide on le remplace
        m_firstName = firstName;
}

void Entity::User::setEmail(const QString &email)
{
    if (!email.isEmpty()) // Si l'email n'est pas vide on le change
        m_email = email;
}

void Entity::User::setClearPassword(const QString &clearPassword)
{
    if (!clearPassword.isEmpty()) // If password is empty do not replace m_password
    {
        m_hasEncryptedPassword = false; // The password is now unencrypted
        m_password = clearPassword;
    }
}

void Entity::User::setEncryptedPassword(const QString &encryptedPassword)
{
    if (!encryptedPassword.isEmpty()) // If password is empty do not replace m_password
    {
        m_hasEncryptedPassword = true; // The password is now encrypted
        m_password = encryptedPassword;
    }
}

void Entity::User::setIsAdmin(bool isAdmin)
{
    m_isAdmin = isAdmin;
}

int Entity::User::getWeight() const
{
    return User::weight;
}

void Entity::User::encryptePassword()
{
    Utility::EncodePassword encodePassword;

    m_password = encodePassword.encodePassword(m_password);

    m_hasEncryptedPassword = true;
}

void Entity::User::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec(
                    "UPDATE user SET name = ?, firstName = ?, password = ?, isAdmin = ? WHERE id = ?"
                    );

        query.bindValue(0, m_name);
        query.bindValue(1, m_firstName);
        query.bindValue(2, m_password);
        query.bindValue(3, m_isAdmin);
        query.bindValue(4, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec(
                    "INSERT INTO user (username, name, firstName, password, salt, roles, isAdmin) VALUES(?, ?, ?, ?, ?, ?, ?)"
                    );

        query.bindValue(0, m_email);
        query.bindValue(1, m_name);
        query.bindValue(2, m_firstName);
        query.bindValue(3, m_password);
        query.bindValue(4, "");
        query.bindValue(5, "a:1:{i:0;s:9:\"ROLE_USER\";}");
        query.bindValue(6, m_isAdmin);
        query.exec();

        postInsert();

        qDebug() << query.lastError().text();

        m_id = query.lastInsertId().toInt();        
    }
}

void Entity::User::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM user WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

void Entity::User::prePersist()
{
    if (!m_hasEncryptedPassword) // Encrypte password if is necessary
        encryptePassword();
}

bool Entity::User::isValid() const
{
    return !m_email.isEmpty() && !m_password.isEmpty();
}
