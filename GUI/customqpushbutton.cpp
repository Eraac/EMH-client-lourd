#include "customqpushbutton.hpp"

CustomQPushButton::CustomQPushButton(const QString &name, int id) : QPushButton(name), m_id(id)
{
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(click()));
}

void CustomQPushButton::click()
{
    emit customClicked(m_id);
}
