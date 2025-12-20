#include <iostream>
#include "Ball.h"
#include "Log.h"
#include <iomanip>
#include <fstream>

using namespace std;


void show( const Ball & item)
{
    cout << item << "\n";
    
}

// solution entry function
int main()
{
    try {

        Log log;

        // specification is constructed separately
        using spcBallSpec = shared_ptr<BallSpec>;
        spcBallSpec spec_soccer{ new BallSpec(BallSpec::Colour::RED,BallSpec::Type::SOCCER,15, 30) };

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


        log.add_item(2, 4, 1.1, spec_soccer);

        // V2: the specification object is constructed during passing of an argument
        log.add_item(10, 2, 4, std::make_shared<BallSpec>(BallSpec::Colour::GREEN, BallSpec::Type::BASKETBALL, 16, 32));

        // V3: constructing and using of the same specification for several
        spcBallSpec spec_tennis{ new BallSpec(BallSpec::Colour::GREEN,BallSpec::Type::TENNIS, 2, 4) };
        log.add_item(1, 2, 3, spec_tennis);
        log.add_item(2, 4, 1.1, spec_soccer);

        // test with another query values
        show(log.find_item(*spec_soccer));
        show(log.find_item(Ball{ 15, 0, 2, std::make_shared<BallSpec>() }));

        // testing for non-matching criterion
        show(log.find_item(BallSpec{ BallSpec::Colour::ANY,BallSpec::Type::ANY, 15, 0 }));
        show(log.find_item(BallSpec{ BallSpec::Colour::GREEN,BallSpec::Type::BASKETBALL, 20, 40 }));

        auto file_name{ "items.csv" };
        // save all items to file
        log.save(file_name);

        // load into another log object
        Log another_log(file_name);

        // Potential scenario: Invalid arguments for Ball constructor
        try {
            Ball invalid_ball(-5, 4.3, 2.0, spec_soccer); // Assuming negative radius is invalid
        }
        catch (const std::invalid_argument& e) {
            cerr << "Caught exception: " << e.what() << endl;
        }

    }

    catch (const std::exception& e) {
    cerr << "Caught exception: " << e.what() << endl;
    }

    return 0;

}
