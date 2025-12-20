#include "BallSpec.h"
#include <string> // for std::getline()

#ifdef _MSC_VER // Visual C++ ?
#define strcasecmp _stricmp // then use the function _stricmp() 
#else
#include <strings.h> // for strcasecmp() function in POSIX C++
#endif


std::ostream & operator<<(std::ostream & os, BallSpec::Colour colour)
{
    return os << BallSpec::Colour_str[static_cast<size_t>(colour)];

}

std::ostream & operator<<(std::ostream & os, BallSpec::Type type)
{
    return os << BallSpec::Type_str[static_cast<size_t>(type)];
}

std::ostream & operator<<(std::ostream & os, const BallSpec& spec)
{
    spec.send_to(os);
    return os;
}

void BallSpec::send_to(std::ostream& os) const {
    os  << _colour << csv_delimiter
        << _type << csv_delimiter
        << _diameter
        << _perimeter;
}

std::istream& operator>>(std::istream& is, BallSpec::Colour& colour)
{
    if (is)
    {
        std::string tmp;
        std::getline(is, tmp, csv_delimiter);
        if (is)
        {
            bool found{ false };

            for (size_t i{ 0 }; i < sizeof(BallSpec::Type_str) / sizeof(BallSpec::Type_str[0]); i++)
            {
                if (tmp.length() == BallSpec::Type_str[i].length()
                    && 0 == strcasecmp(tmp.c_str(), std::string(BallSpec::Type_str[i]).c_str())) // case insensitive comparison
                {
                    colour = static_cast<BallSpec::Colour>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                colour = BallSpec::Colour::ANY;
        }
    }

    return is;
}

std::istream& operator>>(std::istream& is, BallSpec::Type& type)
{
    if (is)
    {
        std::string tmp;
        std::getline(is, tmp, csv_delimiter);
        if (is)
        {
            bool found{ false };

            for (size_t i{ 0 }; i < sizeof(BallSpec::Type_str) / sizeof(BallSpec::Type_str[0]); i++)
            {
                if (tmp.length() == BallSpec::Type_str[i].length()
                    && 0 == strcasecmp(tmp.c_str(), std::string(BallSpec::Type_str[i]).c_str())) // case insensitive comparison
                {
                    type = static_cast<BallSpec::Type>(i);
                    found = true;
                    break;
                }
            }

            if (!found)
                type = BallSpec::Type::ANY;
        }
    }

    return is;
}

std::istream& operator>>(std::istream& is, BallSpec& item)
{
    item.recv_from(is);
    return is;
}


void BallSpec::recv_from(std::istream& is)
{
    // Must be in the same order as in BicycleSpec::send_to(..)!

    if (is)
        is >> _colour; // operator>>() processed csv_delimiter

    if (is)
        is >> _type; // operator>>() processed csv_delimiter

    if (is)
        (is >> _diameter).ignore(); // call ignore() to skip csv_delimiter

    if (is)
        (is >> _perimeter).ignore();
}



bool BallSpec::matches(const BallSpec& otherSpec) const
{
    if (this == &otherSpec) // if comparing to self
        return true;

    auto result{ true };

    // Check each specification property, e.g.:

    if (result && 0 != otherSpec._diameter &&
        _diameter != otherSpec._diameter)
    {
        result = false;
    }

    if (result && 0 != otherSpec._perimeter &&
        _perimeter != otherSpec._perimeter)
    {
        result = false;
    }

    return result;
}