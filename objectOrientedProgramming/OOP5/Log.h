#pragma once
#ifndef LOG
#define LOG

#include "Ball.h" 
#include "BallSpec.h"
#include <memory>
#include <string>
#include <stdexcept>
#include <exception>
#include <vector>

using namespace std;

class Log
{
public:
    void add_item(const Ball & new_item);  
    void add_item(int size, double price, double weight, spcBallSpec spec);
    size_t get_count() const { return _items.size(); }
    std::vector<Ball> find_all_items(const BallSpec & otherSpec) const;
    
    const Ball& operator[](size_t i) const { return this->get_item(i); }
    Ball find_item(const Ball& query) const;
    Ball find_item(const BallSpec& spec_query) const;
    
    std::vector<Ball>::const_iterator begin() const { return _items.begin(); }
    std::vector<Ball>::const_iterator end() const { return _items.end(); }
    
    void save(const std::string& filename) const;
    void load(const std::string& filename);

private:
    std::vector<Ball> _items;
    const Ball& get_item(size_t i) const; 
};

#endif
