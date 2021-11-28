#ifndef EXPECPTIONS_H
#define EXPECPTIONS_H

#include <exception>
#include <typeinfo>
#include <string>
#include <cstring>

class Exception : public std::exception
{
    char *error_msg;

public:
    explicit Exception(std::string name)
    {
        std::string msg = "An error has occurred: " + name;
        this->error_msg = new char[msg.length() + 1];
        std::strcpy(this->error_msg, msg.c_str());
        this->error_msg[msg.length()] = '\0';
    };
    const char *what() const noexcept override
    { 
        return this->error_msg;
    };
};
//------------------------------------------------------------------------
class Invalid_Input : public Exception
{
public:
    explicit Invalid_Input() : Exception("Invalid input"){};
};
//------------------------------------------------------------------------
class Allocation_Error : public Exception
{
public:
    explicit Allocation_Error() : Exception("Allocation error"){};
};
//------------------------------------------------------------------------
class Failiure : public Exception
{
public:
    explicit Failiure() : Exception("Failiure"){};
};
//------------------------------------------------------------------------
class Empty_Structure : public Exception
{
public:
    explicit Empty_Structure() : Exception("Empty Structure"){};
};
#endif // EXPECPTIONS_H