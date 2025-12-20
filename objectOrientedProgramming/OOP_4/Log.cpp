#include "Log.h"
#include <cmath>
#include <fstream>
void Log::add_item(int size, double price, double weight, spcBallSpec spec)
{
    if (_count < Log::MAX_SIZE)
    {
        Ball new_item(size, price, weight, spec);

        if (price != find_item(new_item).get_price())
        {
            _items[_count] = new_item;
            _count++;
        }
    }
}

Ball Log::find_item(const Ball& query) const
{
    auto query_spec_p{ query.get_spec() };

    for (size_t i = 0; i < _count; i++)
    {
        if (query.get_size() != 0 && query.get_size() != _items[i].get_size())
            continue;

        constexpr double epsil{ 0.005 };

        if (query.get_price() != 0.0 && (epsil < std::abs(query.get_price() - _items[i].get_price())))
            continue;
        
        if (query.get_weight() != 0.0 && (epsil < std::abs(query.get_weight() - _items[i].get_weight())))
            continue;

        auto item_spec_p{ _items[i].get_spec() };

        if (query_spec_p && item_spec_p && item_spec_p->matches(*query_spec_p))
        {
            return _items[i];
        }
    }

    return Ball{};
}

Ball Log::find_item(const BallSpec& query_spec) const
{
    for (size_t i = 0; i < _count; i++)
    {
        auto item_spec_p{ _items[i].get_spec() };

        if (item_spec_p && item_spec_p->matches(query_spec))
        {
            return _items[i];
        }
    }

    return Ball{};
}

// Implementation of save method
void Log::save(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (ofs) {
        for (size_t i = 0; i < _count; ++i) {
            ofs << _items[i] << std::endl;
        }
        ofs.close();
        std::cout << "Log saved to " << filename << std::endl;
    } else {
        std::cerr << "Failed to open file " << filename << " for writing." << std::endl;
    }
}

// Implementation of load method
void Log::load(const std::string& filename) {
    std::ifstream ifs(filename);
    if (ifs) {
        _count = 0;

        Ball item;
        while (ifs >> item) {
            if (_count < MAX_SIZE) {
                _items[_count++] = item;
            } else {
                std::cerr << "Log is full, cannot load more items." << std::endl;
                break;
            }
        }

        ifs.close();
        std::cout << "Log loaded from " << filename << std::endl;
    } else {
        std::cerr << "Failed to open file " << filename << " for reading." << std::endl;
    }
}
