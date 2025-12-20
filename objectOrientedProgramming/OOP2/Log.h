#pragma once
#ifndef LOG
#define LOG

#include "Ball.h" 

class Log
{
public:
    
    void init() { _count = 0; }
    size_t get_count() { return _count; }
    Ball get_item(size_t i) { return (i < _count) ? _items[i] : Ball{}; }

    void add_item(int size, string colour, string type, double price, double weight);
    Ball find_item(Ball query);

private:
  
    static const size_t MAX_SIZE{ 10 };

    Ball _items[Log::MAX_SIZE];
    size_t _count;
};

#endif

