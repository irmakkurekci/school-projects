#pragma once
#include <cstddef> // for std::size_t
#include <string>
#include <memory>
class BallSpec
{
public:
    enum class Colour { ANY, RED, BLUE, GREEN };
    enum class Type { ANY, SOCCER, TENNIS, BASKETBALL };

    static constexpr std::string_view Colour_str[]{ "ANY", "RED", "BLUE", "GREEN" };
    static constexpr std::string_view Type_str[]{ "ANY", "SOCCER", "TENNIS", "BASKETBALL" };


    BallSpec()
        : _colour{ Colour::ANY }, _type{ Type::ANY }, _diameter{ 0 }, _perimeter{ 0 }
    { }

    BallSpec(Colour colour, Type type, int diameter, int perimeter)
        : _colour{ colour }
        , _type{ type }
        , _diameter{ diameter }
        , _perimeter{ perimeter }
    { }

    Colour get_colour() const { return _colour; }
    std::string_view get_colour_str() const { return Colour_str[(std::size_t)_colour]; }

    Type get_type() const { return _type; }
    std::string_view get_type_str() const { return Type_str[(std::size_t)_type]; }

    int get_diameter() const { return _diameter; }
    int get_perimeter() const { return _perimeter; }

private:
    Colour _colour;
    Type _type;
    int _diameter;
    int _perimeter;

public:
    bool matches(const BallSpec& otherSpec) const;
};



typedef std::shared_ptr<const BallSpec> spcBallSpec;