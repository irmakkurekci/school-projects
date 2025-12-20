#pragma once

#include <string>
#include <string_view>
#include "BallSpec.h"
#include <iostream>

#ifndef BALL
#define BALL

using namespace std;

class Ball
{
public:
    Ball() = default;
    Ball(int size, double price, double weight, spcBallSpec spec);

    int get_size() const { return _size; }
    double get_price() const { return _price; }
    double get_weight() const { return _weight; }
    spcBallSpec get_spec() const { return _spec; }

    void send_to(std::ostream& os) const;
    void recv_from(std::istream& is);
    friend std::istream& operator>>(std::istream& is, Ball& item);


private:
    int _size;
    double _price;
    double _weight;
    spcBallSpec _spec;

};

std::ostream& operator<<(std::ostream& os, const Ball& item);
#endif