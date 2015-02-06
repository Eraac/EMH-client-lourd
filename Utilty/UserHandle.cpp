/*
#include "UserHandle.hpp"

UserHandle::UserHandle() : QWidget()
{
    // === Init pointer ===
    m_loginWidget   = nullptr;
    m_dashboard     = nullptr;
}

UserHandle::~UserHandle()
{
}

void UserHandle::run()
{
    // Init login window
    m_loginWidget   = new GUI::LoginWidget();
        // Display login window
        m_loginWidget->show();

    // === Make connection between button connect and connect method ===
    QObject::connect(m_loginWidget, SIGNAL(connect(Entity::User)), this, SLOT(connect(Entity::User)));
}

void UserHandle::connect(Entity::User const& user)
{
    // Pointer as delete, you need to break the connect
    QObject::disconnect(m_loginWidget, SIGNAL(connect(Entity::User)), this, SLOT(connect(Entity::User)));

    // Delete login window
    delete m_loginWidget;

    // Init dashboard window
    m_dashboard = new GUI::Dashboard(user);
        // Display dashboard window
        m_dashboard->show();

    // Make connection between disconnect button and disconnect method
    QObject::connect(m_dashboard, SIGNAL(disconnect()), this, SLOT(disconnect()));
}

void UserHandle::disconnect()
{
    // Pointer as delete, you need to break the connect
    QObject::disconnect(m_dashboard, SIGNAL(disconnect()), this, SLOT(disconnect()));

    // Delete dashboard window
    delete m_dashboard;

    // Init login window
    m_loginWidget = new GUI::LoginWidget{};
        // Display login window
        m_loginWidget->show();

    // === Make connection between button connect and connect method ===
    QObject::connect(m_loginWidget, SIGNAL(connect(Entity::User)), this, SLOT(connect(Entity::User)));
}
*/
