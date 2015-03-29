#ifndef USER_HPP
#define USER_HPP

#include <QString>
#include <QCryptographicHash>
#include <QList>
#include "Entity.hpp"
#include "Group.hpp"

namespace Entity
{
    class User : public Entity
    {
        public:
        User();     // Constructeur par défaut
        virtual ~User();    // Destructeur

        static const int weight;            // Utilisé pour trier

        bool emailExist(QString const& email);   // Retourne true si l'email existe déjà
        Entity::ErrorType loadUserByLogin(QString const& email, QString const& password); // Charge un user par son identifiant
        Entity::ErrorType loadUserByEmail(QString const& email);    // Charge l'utilisateur par son email
        Entity::ErrorType load(unsigned int id);                    // Charge l'entité depuis la base de données

        QString getName() const;            // Retourne le nom de l'utilisateur
        QString getFirstName() const;       // Retourne le prénom de l'utilisateur
        QString getEmail() const;           // Retourne l'email de l'utilisateur
        QString getPassword() const;        // Retourne le mot de passe de l'utilisateur
        bool isAdmin() const;               // Retourne si l'utilisateur est admin
        bool hasEncryptedPassword() const;  // Retourne si le mot de passe est crypté

        QStringList getGroupsName() const;  // Retourne la liste des groupes de l'utilisateur

        void setName(QString const& name);                              // Change le nom de l'utilisateur
        void setFirstName(QString const& firstName);                    // Change le prénom de l'utilisateur
        void setEmail(QString const& email);                            // Change l'email de l'utilisateur
        void setClearPassword(QString const& clearPassword);            // Change le mot de passe (en clair)
        void setEncryptedPassword(QString const& encryptedPassword);    // Change le mot de passe de l'utilisateur (crypté)
        void setIsAdmin(bool isAdmin);                                  // Mets l'user administrateur ou non

        virtual void persist() override;            // Persiste l'entité dans le base de données
        virtual void remove() override;             // Supprime de la base de données
        virtual void prePersist() override;         // Appeler avant le persist pour crypter le mot de passe
        virtual int getWeight() const;              // Retourne le poids

        virtual bool isValid() const;               // Retourne si l'entité est prête pour le persiste

        void encryptePassword();                    // Crypte le mot de passe

        private:
        QString m_name;
        QString m_firstName;
        QString m_email;
        QString m_password;
        bool m_isAdmin;
        bool m_hasEncryptedPassword;

    };
}

#endif // USER_HPP
