#include <iostream>
#include "Ball.h"
#include "Log.h"
#include <iomanip>
using namespace std;

// outputs abstraction object properties to the console window
void show(Ball item)
{
    auto is = item.get_spec();

    if (!is)
        is.reset(new BallSpec());

    cout << item.get_size()
        << " " << item.get_price()
        << " " << item.get_weight()
        << " " << is->get_diameter()
        << " " << is->get_perimeter()
        << " '" << is->get_colour_str() << "'"
        << " '" << is->get_type_str() << "'"
        << endl;
}

// solution entry function
int main()
{
    Log log;

    using spcBallSpec = shared_ptr<BallSpec>;
    spcBallSpec spec_soccer{ new BallSpec(BallSpec::Colour::RED,BallSpec::Type::SOCCER,15, 30) };
    log.add_item(24, 3.3, 2.2, spec_soccer);

    log.add_item(10, 2, 4, std::make_shared<BallSpec>(BallSpec::Colour::GREEN, BallSpec::Type::BASKETBALL, 16, 32));

    spcBallSpec spec_tennis{ new BallSpec(BallSpec::Colour::GREEN,BallSpec::Type::TENNIS, 2, 4) };

    log.add_item(1, 2, 3, spec_tennis);
    log.add_item(2, 4, 1.1, spec_soccer);

    show(log.find_item(*spec_soccer));

    show(log.find_item(Ball{ 15, 0, 2, std::make_shared<BallSpec>() }));

    show(log.find_item(BallSpec{ BallSpec::Colour::ANY,BallSpec::Type::ANY, 15, 0 }));

    show(log.find_item(BallSpec{ BallSpec::Colour::GREEN,BallSpec::Type::BASKETBALL, 20, 40 }));

    return 0;
}
