#include <gtest/gtest.h>

#include "Normalizable.h"

const double EPSILON = 0.00000000001;

TEST (Normalizable, TestActualToNorm) { 
    Normalizable n(-5, 10);
    n.set_actual(0);
    ASSERT_NEAR(n.normalized(), -1.0 / 3.0, EPSILON);
}

TEST (Normalizable, TestNormToActual) {
    Normalizable n(-5, 10);
    n.set_normalized(-1.0 / 3.0);
    ASSERT_NEAR(n.actual(), 0, EPSILON);
}
