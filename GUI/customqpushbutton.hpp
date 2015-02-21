#ifndef CUSTOMQPUSHBUTTON_HPP
#define CUSTOMQPUSHBUTTON_HPP

#include <QPushButton>
#include <QString>

class CustomQPushButton : public QPushButton
{
    Q_OBJECT

    public:
        CustomQPushButton(QString const& name, int id);

        void reduceId();    // Décrement l'id

        int getId() const;  // Retourne l'id

    public slots:
        void click();   // Lorsque que l'on clique sur le bouton

    signals:
        void customClicked(int id); // Envoi ce signal avec son id lorsque on clique dessus

    private:
        int m_id;
};

#endif // CUSTOMQPUSHBUTTON_HPP

