#ifndef TAG_HPP
#define TAG_HPP

#include <QString>
#include <QStringList>
#include "Entity.hpp"

namespace Entity
{
    class Tag : public Entity
    {

        public:
            Tag();  // Constructeur par défaut
            ~Tag(); // Destructeur

            static const int weight;    // Utilisé pour trier

            void setName(QString const& name);          // Change le nom

            QString getName() const;                    // Retourne le nom

            Entity::ErrorType load(unsigned int id);    // Charge l'entité depuis la base de données

            static QStringList getAll();                // Retourne le nom de tous les tags
            virtual int getWeight() const;              // Retourne le poids

            virtual void persist() override;            // Persiste l'entité en base de données
            virtual void remove() override;             // Supprime l'entité de la base de données
            virtual bool isValid() const;               // Retourne si l'entité est valide pour le persiste

        private:
            QString m_name;

    };
}

#endif // TAG_HPP
