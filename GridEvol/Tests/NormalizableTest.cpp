#include <gtest/gtest.h>
#include <stdexcept>

#include "Normalizable.h"

const double EPSILON = 0.00000000001;

TEST (Normalizable, real_range_to_normal)
{
    Normalizable n(0, -5, 10);
    n.set_range(-1.0, 1.0);
    ASSERT_NEAR(n.get_value(), -1.0 / 3.0, EPSILON);
}

TEST (Normalizable, norm_range_to_real) {
    Normalizable n(-1.0 / 3.0);
    n.set_range(-5, 10);
    ASSERT_NEAR(n.get_value(), 0, EPSILON);
}

TEST (Normalizable, constructor_min_max_exception) {
    ASSERT_THROW(Normalizable n(3, 5, 0), std::invalid_argument);
}

TEST (Normalizable, range_exception)
{
    Normalizable n(3, 0, 10);
    ASSERT_THROW(n.set_range(4, -10), std::invalid_argument);
}

TEST (Normalizable, value_min_max_exception) {
    Normalizable n(0, -10, 10);
    ASSERT_THROW(n.set_value(-11), std::invalid_argument);
    ASSERT_THROW(n.set_value(11), std::invalid_argument);
}
