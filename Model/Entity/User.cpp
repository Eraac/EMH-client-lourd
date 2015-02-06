#include "User.hpp"

const int Entity::User::weight = 1;

Entity::User::User() : Entity(), m_name(""), m_password(""), m_hasEncryptedPassword(false), m_isAdmin(false)
{
}

Entity::User::~User()
{

}

bool Entity::User::emailExist(QString const& email)
{
    // TODO

    return ("kevin@labesse.me" == email); // valeur de test
}

Entity::Entity::ErrorType Entity::User::loadUserByLogin(QString const& email, QString const& password)
{
    // TODO Requete SQL here pour charger user
    m_id = 2;
    m_name = email;
    m_password = password;
    m_isAdmin = true;

    return Entity::ErrorType::NONE;
}

Entity::Entity::ErrorType Entity::User::loadUserByEmail(const QString &email)
{
    // TODO SQL
    m_id = 2;
    m_name = email;
    m_password = "kevin";
    m_isAdmin = true;

    return Entity::ErrorType::NONE;
}

Entity::Entity::ErrorType Entity::User::load(unsigned int id)
{
    m_id = id;
    m_name = "kevin@labesse.me";
    m_password = "kevin";
    m_isAdmin = true;

    return Entity::ErrorType::NONE;
}

QString Entity::User::getName() const
{
    return m_name;
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

    // TODO requete SQL

    groupsNameOfUser.append("Suisse");
    groupsNameOfUser.append("Paris");

    return groupsNameOfUser;
}

void Entity::User::setName(const QString &name)
{
    if (!name.isEmpty()) // If name is empty do not replace m_name
        m_name = name;
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
    // TODO Si mdp deja crypte on crypte pas (sinon crypter + mettre boolen a true)
    //QCryptographicHash hash(QCryptographicHash::Sha512);

    //hash.addData(&m_password, m_password.length()); // Erreur il ne doit pas recevoir un QString mais un char*

   // m_password = hash.result();
}

void Entity::User::persist()
{
    // TODO
    // TMP
    m_id = 5;
}

void Entity::User::remove()
{
    // TODO
}

void Entity::User::prePersist()
{
    if (!m_hasEncryptedPassword) // Encrypte password if is necessary
        encryptePassword();
}

bool Entity::User::isValid() const
{
    return !m_name.isEmpty() && !m_password.isEmpty();
}
