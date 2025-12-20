#include "Log.h"
#include <cmath>
#include <fstream>

// The parameters must match with the class declaration
void Log::add_item(const Ball & new_item) {
    auto found = this->find_all_items(*new_item.get_spec());

    for (const auto& found_item : found) {
        
        if (found_item.get_price() == new_item.get_price()) {
            return;
        }
        
        if (found_item.get_weight() == new_item.get_weight()) {
            return;
        }
        
        if (found_item.get_size() == new_item.get_size()) {
            return;
        }
    }

    _items.push_back(new_item);
}

void Log::add_item(int size, double price, double weight, spcBallSpec spec) {
    Ball new_item(size, price, weight, spec);
    this->add_item(new_item); 
}

std::vector<Ball> Log::find_all_items(const BallSpec & otherSpec) const {
    std::vector<Ball> found;

    for (const auto& item : _items) {
        if (item.get_spec()->matches(otherSpec)) {
            found.push_back(item);
        }
    }

    return found;
}

Ball Log::find_item(const BallSpec & otherSpec) const {
    auto found = this->find_all_items(otherSpec);

    if (!found.empty()) {
        return found[0];
    }

    return Ball{};
}

Ball Log::find_item(const Ball &query) const {
    auto spec = query.get_spec();
    if (spec) {
        return find_item(*spec);
    }
    return Ball{};
}

const Ball& Log::get_item(size_t i) const {
    if (i >= _items.size()) {
        throw std::out_of_range("Index out of range");
    }
    return _items[i];
}

// Implementation of save method
void Log::save(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (const auto& item : _items) {
        ofs << item << "\n";
    }
}

void Log::load(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Could not open file for reading");
    }

    _items.clear();
    Ball item;
    while (ifs >> item) {
        _items.push_back(item);
    }
}
