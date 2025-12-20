#pragma once
#ifndef TASKLIST_H
#define TASKLIST_H

#include <ostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "Task.h"

class TaskList
{
public:
    void add_task(Task task);
    Task get_task(size_t i) const { return _tasks[i]; }
    void complete_task(size_t i);
    bool task_is_due(size_t i) const;
    void send_to(std::ostream& out, std::function<bool(const Task&)> filter = [](const Task&) { return true; }) const;
    size_t get_tasks_count() const { return _tasks.size(); }
    void remove_done_tasks();

private:
    std::vector<Task> _tasks;
};

#endif
