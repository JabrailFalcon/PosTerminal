#include "framework.h"
//include "Header.h"
#include "User.h"

User::User() : id(0), f_name(""), l_name(""), role(""), mobile(""), email(""), status(""), password("")
{}

User::User(int id, std::string f_name, std::string l_name, std::string role, std::string mobile, std::string email,
    std::string status, std::string password)
    : id(id), f_name(f_name), l_name(l_name), role(role), mobile(mobile), email(email),
    status(status), password(password)
{}



int User::getId()
{
    return id;
}

std::string User::getF_name()
{
    return f_name;
}

std::string User::getL_name()
{
    return l_name;
}

std::string User::getRole()
{
    return role;
}

std::string User::getMobile()
{
    return mobile;
}

std::string User::getEmail()
{
    return email;
}

std::string User::getStatus()
{
    return status;
}

std::string User::getPassword()
{
    return password;
}

void User::setId(int id)
{
    this->id = id;
}

void User::setF_name(std::string f_name)
{
    this->f_name = f_name;
}

void User::setL_name(std::string l_name)
{
    this->l_name = l_name;
}

void User::setRole(std::string role)
{
    this->role = role;
}

void User::setMobile(std::string mobile)
{
    this->mobile = mobile;
}

void User::setEmail(std::string email)
{
    this->email = email;
}

void User::setStatus(std::string status)
{
    this->status = status;
}

void User::setPassword(std::string password)
{
    this->password = password;
}