#include "BallSpec.h"

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