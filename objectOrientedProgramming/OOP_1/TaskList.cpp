// TASKLIST.CPP

#include "TaskList.h"

void TaskList::add_task(Task task)
{
    _tasks.push_back(task);
}

void TaskList::complete_task(size_t i)
{
    if (!_tasks[i].is_done())
        _tasks[i].toggle_done();
}

bool TaskList::task_is_due(size_t i) const
{
    return _tasks[i].is_due();
}

void TaskList::send_to(std::ostream& out, std::function<bool(const Task&)> filter) const
{
    for (auto&& task : _tasks)
        if (filter(task))
            out << (std::string)task << "\n";
}

void TaskList::remove_done_tasks()
{
    _tasks.erase(
        std::remove_if(_tasks.begin(), _tasks.end(), [](const Task& task) { return task.is_done(); }),
        _tasks.end()
    );
}
