#include "exceptions.h"
#include <exception>
#include <string>

ContainerException::ContainerException(ContainerException::ExceptionType type,std::string message):std::exception(),
type(type),message(message)
{

}

const char* ContainerException::what() const noexcept
{
    return message.c_str();
}

FileException::FileException(FileException::ExceptionType type,std::string message):std::exception(),
type(type),message(message)
{

}

const char* FileException::what() const noexcept
{
    return message.c_str();
}