// Main.cpp
#include <iostream>
#include <algorithm>
#include "Ball.h"
#include "Log.h"
#include <iomanip>
#include <fstream>

using namespace std;

class Average
{
public:
    Average() : _sum{ 0.0 }, _count{ 0 } { }
    void operator()(const Ball & item)
    {
        _sum += item.get_price();
        _count++;
    }
    double result() const {  return _count ? _sum / _count : 0.0;  }
    
private:
    double _sum;   // the accumulated sum
    size_t _count; // the count of items accumulated
};

double avg_price(const Log & log)
{
    return std::for_each(log.begin(), log.end(), Average()).result();
}

// outputs abstraction object properties to the console window
template <typename T>
void show(const T & item)
{
    cout << item << "\n";
}

bool is_less(const Ball & item1, const Ball & item2)
{
    return item1.get_price() < item2.get_price();
}

Ball max_price(const Log & log)
{
    if (log.begin() == log.end()) // alternatively this condition can be used: log.begin() == log.end()
        throw std::range_error("There are no items");

    return *std::max_element(log.begin(), log.end(), is_less);
}

// Function to show all items in the log
void show_all(const Log & log)
{
    std::for_each(log.begin(), log.end(), show<Ball>);
}

// solution entry function
int main()
{
    Log log;

    // specification is constructed separately
    using spcBallSpec = shared_ptr<BallSpec>;
    spcBallSpec spec_soccer{ new BallSpec(BallSpec::Colour::RED, BallSpec::Type::SOCCER, 15, 30) };

    Ball b1(23, 4.3, 2.0, spec_soccer);
    cout << b1 << "\n";

    auto filename{ "b1.csv" };
    ofstream ofs(filename);
    if (ofs)
        ofs << b1 << "\n";
    ofs.close();
    cout << "Saved...\n";

    Ball b2;
    ifstream ifs(filename);
    if (ifs)
        ifs >> b2;
    ifs.close();
    cout << "Read...\n"
         << b2 << "\n----\n";

    log.add_item(2, 4.54, 1.1, spec_soccer);

    // V2: the specification object is constructed during passing of an argument
    log.add_item(10, 2.56, 3.4, std::make_shared<BallSpec>(BallSpec::Colour::BLUE, BallSpec::Type::BASKETBALL, 16, 32));

    // V3: constructing and using of the same specification for several
    spcBallSpec spec_tennis{ new BallSpec(BallSpec::Colour::GREEN, BallSpec::Type::TENNIS, 2, 4) };
    log.add_item(1, 2.4, 3.2, spec_tennis);
    log.add_item(2, 4.3, 1.1, spec_soccer);

    // Show all items in the log
    cout << "All items in the log:\n";
    show_all(log);

    // Save the log to a file
    log.save("log.csv");
    cout << "Log saved to log.csv\n";

    // Load the log from a file
    Log new_log;
    new_log.load("log.csv");
    cout << "Log loaded from log.csv\n";

    // Show all items in the new log
    cout << "All items in the new log:\n";
    show_all(new_log);

    // test with another query values
    show(log.find_item(*spec_soccer));
    show(log.find_item(Ball{ 15, 0.2, 2.7, std::make_shared<BallSpec>() }));

    // testing for non-matching criterion
    show(log.find_item(BallSpec{ BallSpec::Colour::ANY, BallSpec::Type::ANY, 15, 0 }));
    show(log.find_item(BallSpec{ BallSpec::Colour::GREEN, BallSpec::Type::BASKETBALL, 20, 40 }));

    return 0;
}
