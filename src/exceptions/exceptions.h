
#include <exception>
#include <string>

class ContainerException: public std::exception
{
    public:
        enum ExceptionType{INDEX_OUT_OF_BOUNDS,INDEX_NULL_POINTER};
        ContainerException(ExceptionType type,std::string message);
        const char* what() const noexcept;
        ExceptionType type;
    private:
        std::string message;
        
};

class FileException: public std::exception
{
    public:
        enum ExceptionType{BAD_FILE_FORMAT};
        FileException(ExceptionType type,std::string message);
        const char* what() const noexcept;
        ExceptionType type;
    private:
        std::string message;
        
};