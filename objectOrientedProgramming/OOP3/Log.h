#pragma once
#ifndef LOG
#define LOG

#include "Ball.h" 
#include "BallSpec.h"
#include <memory>
#include <string>
using namespace std;

class Log
{
public:
    // Initializes the log
    Log()
        : _count{ 0 }
    { }


    // Returns the current number of abstraction objects
    size_t get_count() const { return _count; }

    // Returns stored abstraction object by its index or default object if index is invalid
    Ball get_item(size_t i) const { return (i < _count) ? _items[i] : Ball{}; }

    // From passed property values, creates and adds new abstraction object in an array _items
    // (replace parameters to match your property types and identifiers)
    void add_item(int size, double price, double weight, spcBallSpec spec);



    // Looks for a matching abstraction object and returns the first found or default object
    Ball find_item(const Ball& query) const;
    Ball find_item(const BallSpec& spec_query) const;
private:
    // The maximum number of abstraction objects that can be stored
    static const size_t MAX_SIZE{ 10 };

    // An array for storing abstraction objects
    Ball _items[Log::MAX_SIZE];

    // The number of currently stored abstraction objects in the array _items
    size_t _count;
};

#endif