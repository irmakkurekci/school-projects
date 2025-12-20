#include "Task.h"

#ifdef _MSC_VER
#include <format>
#else
#include <sstream>
#include <iomanip>
#endif

Task::Task(std::string description, PRIORITY priority, datetime due_time)
    : _description{ description }, _priority{ priority }, _due_time{ due_time }, _done{ false }
{ }

bool Task::is_done() const
{
    return _done;
}

void Task::toggle_done()
{
    _done = !_done;
}

bool Task::is_due() const
{
    return !_done && ((_due_time - std::chrono::system_clock::now()).count() <= 0);
}

Task::operator std::string() const
{
    // character string representations of the Task::PRIORITY values:
    static const char* PRIORITY_S[]{ "Low", "Normal", "High" };

#ifdef _MSC_VER
    // This is not yet supported by Clang++/G++ compilers:
    return std::format(
        "Subject: {}\n"
        "Priority: {}\n"
        "Due time: {:%F %R}\n" // YYYY-MM-DD HH:MM
        "Due? {}\n"
        "Done? {}\n"
        , _description
        , PRIORITY_S[static_cast<size_t>(_priority)]
        , std::chrono::current_zone()->to_local(_due_time)
        , is_due()
        , is_done()
    );
#else
    std::ostringstream str;
    auto tt{ std::chrono::system_clock::to_time_t(_due_time) };
    auto lt{ *std::localtime(&tt) };

    str << "Subject: " << _description << "\n"
        << "Priority: " << PRIORITY_S[static_cast<size_t>(_priority)] << "\n"
        << "Due date: " << std::put_time(&lt, "%F %R") << "\n"
        << std::boolalpha
        << "Due? " << is_due() << "\n"
        << "Done? " << is_done() << "\n";

    return str.str();
#endif
}