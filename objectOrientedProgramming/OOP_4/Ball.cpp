#include "Ball.h"
#include <string> // for std::getline()


Ball::Ball(int size, double price, double weight, spcBallSpec spec)
{

	_size = size;
	_price = price;
	_weight = weight;
	_spec = spec;

}

std::ostream& operator<<(std::ostream& os, const Ball& item)
{
    item.send_to(os);
    return os;
}

void Ball::send_to(std::ostream& os) const
{
    os << _size << csv_delimiter
        << _price << csv_delimiter
        << _weight;
        
    if (_spec)
    {
        os << csv_delimiter;
        _spec->send_to(os);
    }
}

std::istream& operator>>(std::istream& is, Ball& item)
{
    item.recv_from(is);
    return is;
}

void Ball::recv_from(std::istream& is)
{
    if (is)
        (is >> _size).ignore(); // calling ignore() to skip csv_delimiter

    if (is)
        (is >> _price).ignore();

    if (is)
        (is >> _weight).ignore();

    auto temp_spec{ std::make_shared<BallSpec>() };
    is >> *temp_spec; // alternatively: temp_spec->recv_from(is);
    _spec = temp_spec; // replace the specification
}


