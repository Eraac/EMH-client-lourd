#ifndef CUSTOMQPUSHBUTTON_HPP
#define CUSTOMQPUSHBUTTON_HPP

#include <QPushButton>
#include <QString>

class CustomQPushButton : public QPushButton
{
    Q_OBJECT

    public:
        CustomQPushButton(QString const& name, int id);

    public slots:
        void click();

    signals:
        void customClicked(int id);

    private:
        int m_id;
};

#endif // CUSTOMQPUSHBUTTON_HPP

