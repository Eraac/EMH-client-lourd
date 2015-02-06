#ifndef FORM_HPP
#define FORM_HPP

#include <QString>
#include <QColor>
#include "Entity.hpp"

namespace Entity
{
    class Form : public Entity
    {
        public:
        Form();             // Consstructeur par défaut
        virtual ~Form();    // Destructeur

        static const int weight;    // Utilisé pour trier

        // TODO s'aliner par rapport à Symfony
        enum class Status {NONE, TEST, PUBLIC};             // Le statut du formulaire

        Entity::ErrorType load(unsigned int id);            // Charge l'entité depuis la base de données
        virtual int getWeight() const;                      // Retourne le poids

        virtual void persist() override;                    // Persiste l'entité en base de données
        virtual void remove() override;                     // Supprime de la base de données
        virtual bool isValid() const;                       // Retourne si l'entité est valide pour le persiste

        void setName(QString const& name);                  // Change le nom
        void setDescription(QString const& description);    // Change la description
        void setInfo(QString const& info);                  // Change le texte d'information
        void setImportant(QString const& important);        // Change le texte important
        void setStatus(Form::Status status);                // Change le statut du formulaire
        void setIdAuthor(unsigned const int id);            // Change l'id du créateur
        void setColor(QColor const& color);                 // Change la couleur

        QString getName() const;                            // Retourne le nom du formulaire
        QString getDescription() const;                     // Retoure la description du formulaire
        QString getInfo() const;                            // Retourne le texte d'information
        QString getImportant() const;                       // Retourne le texte important
        Form::Status getStatus() const;                     // Retourne le statut du formulaire
        unsigned int getIdAuthor() const;                   // Retourne l'id du createur
        QString getColor() const;                           // Retoune la couleur

        private:
        QString m_name;
        QString m_description;
        QString m_info;
        QString m_important;
        QString m_color;
        Form::Status m_status;
        unsigned int m_idAuthor;
    };
}

#endif // FORM_HPP
