#include <gtest/gtest.h>
#include <stdexcept>

#include "Norm.h"

const double EPSILON = 0.00000000001;

TEST (Norm, real_range_to_normal)
{
    Norm n(0, -5, 10);
    n.set_range(-1.0, 1.0);
    EXPECT_NEAR(n.get_value(), -1.0 / 3.0, EPSILON);
}

TEST (Norm, norm_range_to_real)
{
    Norm n(-1.0 / 3.0);
    n.set_range(-5, 10);
    EXPECT_NEAR(n.get_value(), 0, EPSILON);
}

TEST (Norm, constructor_min_max_exception)
{
    EXPECT_THROW(Norm n(3, 5, 0), std::invalid_argument);
}

TEST (Norm, range_exception)
{
    Norm n(3, 0, 10);
    EXPECT_THROW(n.set_range(4, -10), std::invalid_argument);
}

TEST (Norm, value_min_max_exception)
{
    Norm n(0, -10, 10);
    EXPECT_THROW(n.set_value(-11), std::invalid_argument);
    EXPECT_THROW(n.set_value(11), std::invalid_argument);
}

TEST (Norm, typical_usage)
{
    Norm n(-1); // shouldn't throw anything even if we are at limit
}
