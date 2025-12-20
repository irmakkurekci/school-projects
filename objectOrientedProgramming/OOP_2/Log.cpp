#include "Log.h"
#include <cmath>

    
    void Log::add_item(int size, string colour, string type, double price, double weight)
{
    if (_count < Log::MAX_SIZE)
    {
        Ball new_item;
        new_item.init(size, colour, type, price, weight);
        _items[_count] = new_item;
        _count++;
    }
}

    Ball Log::find_item(Ball query)
{
    for (size_t i = 0; i < _count; i++)
    {
        // for integer or boolean type property
        if (query.get_size() != 0
            && query.get_size() != _items[i].get_size())
            continue;

        // for string type property
        if (query.get_colour() != ""
            && query.get_colour() != _items[i].get_colour())
            continue;

        // for string type property
        if (query.get_type() != ""
            && query.get_type() != _items[i].get_type())
            continue;


        // for other types as I saw in the demo solution for double we use:
        constexpr double epsil_price{ 0.005 };
        if (query.get_price() != 0.0
            && epsil_price < std::abs(query.get_price() - _items[i].get_price()))
            continue;

        constexpr double epsil_weight{ 0.003 };
        if (query.get_weight() != 0.0
            && epsil_weight < std::abs(query.get_weight() - _items[i].get_weight()))
            continue;


        return _items[i];
    }

    return Ball{}; // return the 'default' object
}
