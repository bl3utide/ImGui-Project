#pragma once

// TODO change app namespace
namespace ImGuiProject
{

extern bool has_error;
extern std::string error_message;
extern bool showing_error_message;

class ContinuableException : public std::exception
{
public:
    enum class Cause : int
    {
    };

    ContinuableException(const Cause cause);

private:
    static const std::unordered_map<Cause, std::string> message_;
};

class UncontinuableException : public std::runtime_error
{
public:
    enum class Cause : int
    {
    };
    UncontinuableException(const Cause cause);

private:
    static const std::unordered_map<Cause, std::string> message_;
};

void setAppError(const std::string& message) noexcept;

} // ImGuiProject
