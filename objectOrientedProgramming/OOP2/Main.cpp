#include <iostream>
#include <cassert>
#include "Ball.h"
#include "Log.h"

using namespace std;

// outputs abstraction object properties to the console window
void show(Ball item)
{
    cout << item.get_size() << " "
        << "'" << item.get_colour() << "' "
        << "'" << item.get_type() << "' "
        << item.get_price() << " "
        << item.get_weight() << " "
        << endl;
}

// solution entry function
int main()
{
    Log log;

    log.init();

    // Test 1: Add several different abstraction objects to the log
    log.add_item(13, "Blue", "Bowling Ball", 309.953, 7.082);
    log.add_item(5, "Brown and White", "Rugby Ball", 392.695, 0.462);
    log.add_item(4, "Yellow", "Volleyball", 289.738, 0.382);

    // Test 2: Query for an existing item and assert the result for size
    Ball qry1;
    qry1.init(13, "", "", 0.0, 0.0);
    Ball foundBall1 = log.find_item(qry1);
    show(foundBall1);
    assert(foundBall1.get_size() == 13);

    // Test 3: Query for a non-matching item and assert the default-initialized result
    Ball qry2;
    qry2.init(0, "Star", "", 0.0, 0.0);
    Ball foundBall2 = log.find_item(qry2);
    show(foundBall2);
    assert(foundBall2.get_price() == 0.0);

    // Test 4: Query for an existing item based on weight and assert the result
    Ball qry3;
    qry3.init(0, "", "", 0.0, 0.462);
    Ball foundBall3 = log.find_item(qry3);
    show(foundBall3);
    assert(foundBall3.get_weight() == 0.462);

    // Test 5: Query for an existing item based on price and assert the result
    Ball qry4;
    qry4.init(0, "", "", 289.738, 0.0);
    Ball foundBall4 = log.find_item(qry4);
    show(foundBall4);
    assert(foundBall4.get_price() == 289.738);
    
    return 0;
}