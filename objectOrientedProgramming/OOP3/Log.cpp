#include "Log.h"
#include <cmath>

// The parameters must match with the class declaration
void Log::add_item(int size, double price, double weight, spcBallSpec spec)
{
    if (_count < Log::MAX_SIZE)
    {
        Ball new_item(size, price, weight, spec);
        _items[_count] = new_item;
        _count++;
    }
}

Ball Log::find_item(const Ball& query) const
{
    const double epsil = 0.0001; // Define a small epsilon value for comparison

    // temporary pointer to the specification
    auto query_spec_p{ query.get_spec() };
    for (size_t i = 0; i < _count; i++)
    {
        if (query.get_size() != 0 && query.get_size() != _items[i].get_size())
            continue;

        if (query.get_price() != 0.0 && std::abs(query.get_price() - _items[i].get_price()) > epsil)
            continue;

        if (query.get_weight() != 0.0 && std::abs(query.get_weight() - _items[i].get_weight()) > epsil)
            continue;

        auto item_spec_p{ _items[i].get_spec() };

        if (query_spec_p && item_spec_p && item_spec_p->matches(*query_spec_p))
        {
            return _items[i];
        }
    }

    return Ball{}; // return the 'default' object
}

Ball Log::find_item(const BallSpec& query_spec) const
{
    for (size_t i = 0; i < _count; i++)
    {
        auto item_spec_p{ _items[i].get_spec() };

        if (item_spec_p && item_spec_p->matches(query_spec))
        {
            return _items[i]; // the first object with matching specification
        }
    }

    return Ball{}; // return the 'default' object
}
