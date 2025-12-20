#pragma once
#ifndef TASK_H
#define TASK_H

#include <chrono>
#include <string>

using datetime = std::chrono::system_clock::time_point;

class Task
{
public:
    enum class PRIORITY { LOW, NORMAL, HIGH };
    Task(std::string description, PRIORITY priority, datetime due_time);
    bool is_done() const;
    void toggle_done();
    bool is_due() const;
    operator std::string() const;

private:
    std::string _description;
    PRIORITY _priority;
    datetime _due_time;
    bool _done;
};

#endif