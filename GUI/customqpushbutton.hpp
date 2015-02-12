#ifndef CUSTOMQPUSHBUTTON_HPP
#define CUSTOMQPUSHBUTTON_HPP

#include <QPushButton>
#include <QString>

class CustomQPushButton : public QPushButton
{
    Q_OBJECT

    public:
        CustomQPushButton(QString const& name, int id);

        void reduceId();

        int getId() const;

    public slots:
        void click();

    signals:
        void customClicked(int id);

    private:
        int m_id;
};

#endif // CUSTOMQPUSHBUTTON_HPP

