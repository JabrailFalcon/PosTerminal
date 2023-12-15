#pragma once

class User
{
    int id;
    std::string f_name;
    std::string l_name;
    std::string role;
    std::string mobile;
    std::string email;
    std::string status;
    std::string password;
public:
    User();
    User(int id, std::string f_name, std::string l_name, std::string role, 
        std::string mobile, std::string email, std::string status, std::string password);
    int getId() const;
    std::string getF_name() const;
    std::string getL_name() const;
    std::string getRole() const;
    std::string getMobile() const;
    std::string getEmail() const;
    std::string getStatus() const;
    std::string getPassword() const;
    void setId(int id);
    void setF_name(std::string f_name);
    void setL_name(std::string l_name);
    void setRole(std::string role);
    void setMobile(std::string mobile);
    void setEmail(std::string email);
    void setStatus(std::string status);
    void setPassword(std::string password);
};
