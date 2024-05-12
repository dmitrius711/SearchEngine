#include <exception>

class ConfigFileIsEmpty : public std::exception
{
public:
    const char *what() const noexcept
    {
        return "Config file is empty.";
    }
};

class ConfigFileIsMissing : public std::exception
{
public:
    const char *what() const noexcept
    {
        return "Config file is missing.";
    }
};
