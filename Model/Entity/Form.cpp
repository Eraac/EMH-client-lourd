#include "Form.hpp"

const int Entity::Form::weight = 1;

Entity::Form::Form() : Entity(), m_name(""), m_description(""), m_info(""),
                       m_important(""), m_status(Form::Status::NONE),                                             
                       m_idAuthor(0)
{

}

Entity::Form::~Form()
{

}

bool Entity::Form::formExist(const QString &name)
{
    // TODO
    return ("morphine" == name);
}

Entity::Entity::ErrorType Entity::Form::load(unsigned int id)
{
    // TODO
    m_id        = id;
    m_name      = "Demande de béquilles";
    m_description = "Pour faire une demande de béquilles";
    m_info      = "Un médecin va venir les chercher";
    m_important = "Il faut rentre les béquilles dès que possible";
    m_status    = Form::Status::DEMAND;
    m_idAuthor  = 1;

    return Entity::ErrorType::NONE;
}

int Entity::Form::getWeight() const
{
    return Form::weight;
}

void Entity::Form::persist()
{
    // TODO
}

void Entity::Form::remove()
{
    // TODO
}

bool Entity::Form::isValid() const
{
    return (!m_name.isEmpty() && !m_description.isEmpty() &&
            m_status != Form::Status::NONE);
}

void Entity::Form::setName(const QString &name)
{
    if (!name.isEmpty())
        m_name = name;
}

void Entity::Form::setDescription(const QString &description)
{
    if (!description.isEmpty())
        m_description = description;
}

void Entity::Form::setInfo(const QString &info)
{
    m_info = info;
}

void Entity::Form::setImportant(const QString &important)
{
    m_important = important;
}

void Entity::Form::setStatus(Form::Status status)
{
    if (status != Form::Status::NONE)
        m_status = status;
}

void Entity::Form::setIdAuthor(const unsigned int id)
{
    if (id != 0)
        m_idAuthor = id;
}

void Entity::Form::setColor(const QColor &color)
{
    m_color = color.name().remove(0, 1);
}

QString Entity::Form::getName() const
{
    return m_name;
}

QString Entity::Form::getDescription() const
{
    return m_description;
}

QString Entity::Form::getInfo() const
{
    return m_info;
}

QString Entity::Form::getImportant() const
{
    return m_important;
}

Entity::Form::Status Entity::Form::getStatus() const
{
    return m_status;
}


unsigned int Entity::Form::getIdAuthor() const
{
    return m_idAuthor;
}

QString Entity::Form::getColor() const
{
    return m_color;
}
