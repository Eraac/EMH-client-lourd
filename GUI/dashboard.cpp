#include "dashboard.hpp"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::loadUser(Entity::User const& user)
{
    m_user = user;

    ui->footer->setText("EMH v1.0 - " + m_user.getEmail());
}

void Dashboard::clickDisconnect()
{
    emit disconnect();
}

void Dashboard::addUser()
{
    CreateUser createUser;
        createUser.exec();
}

void Dashboard::editUser()
{

}

void Dashboard::addGroup()
{

}

void Dashboard::editGroup()
{

}

void Dashboard::addForm()
{

}

void Dashboard::editForm()
{

}
