#ifndef FIELD_HPP
#define FIELD_HPP

#include <QString>
#include <QColor>
#include "Entity.hpp"

namespace Entity
{
    class Field : public Entity
    {
        public:
        Field();            // Constructeur par défaut
        virtual ~Field();   // Destructeur

        static const int weight; // Utilisé pour trier

        enum class Type {NONE, DATE, DATETIME,
                         EMAIL, NUMBER, TEXT,
                         TIME, URL, RADIO, TEXTAREA, PASSWORD};       // Type HTML du champs

        void setType(Field::Type const type);               // Change le type
        void setLabel(QString const& label);                // Change le label
        void setPlaceholder(QString const& placeholder);    // Change le placeholder
        void setHelpText(QString const& helpText);          // Change le texte d'aide
        void setIsMultiple(bool multiple);  // Change la valeur de m_isMultiple
        void setIsRequired(bool required);  // Change la valeur de m_isRequired
        void setFormId(unsigned int id);    // Change l'id du formulaire

        Field::Type getType() const;    // Retourne le type
        QString getTypeReadable() const;// Retourne le type lisable par un humain
        QString getLabel() const;       // Retourne le label
        QString getPlaceholder() const; // Retourne le placeholder
        QString getHelpText() const;    // Retourne le texte d'aide
        bool getIsMultiple() const;     // Retourne si le champs est multiple ou pas
        bool getIsRequired() const;     // Retourne si le champs est requis ou pas
        unsigned int getFormId() const; // Retourne l'id du formulaire associé
        QString getDefaultValue();      // Retourne la valeur par défaut du champs

        Entity::ErrorType load(unsigned int id);    // Charge l'entité depuis la base de données
        virtual int getWeight() const;              // Retourne le poids

        virtual void persist() override;            // Persiste l'entité dans le base de données
        virtual bool isValid() const;               // Retourne si l'entité est valide pour le base de données
        virtual void remove() override;             // Supprime l'entité de la base de données

        private:
        Field::Type m_type;
        bool m_isMultiple;
        bool m_isRequired;
        QString m_label;
        QString m_placeholder;
        QString m_helpText;
        unsigned int m_idForm;
    };
}

#endif // FIELD_HPP
