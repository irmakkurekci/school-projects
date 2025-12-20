#include <string>
#ifndef BALL
#define BALL

using namespace std;

class Ball
{
public:
	void init(int size, string colour, string type, double price, double weight);
	int get_size() { return _size; }
	string get_colour() { return _colour; }
	string get_type() { return _type; }
	double get_price() { return _price; }
	double get_weight() { return _weight; }

private:
	int _size;
	string _colour;
	string _type;
	double _price;
	double _weight;

};



#endif