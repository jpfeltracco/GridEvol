#include <gtest/gtest.h>

#include "GridSimulation.h"

TEST (Entity, live_movement)
{
    Entity e;
    e.row = 10;
    e.col = 15;
    e.move(POS, NEG);
    EXPECT_EQ(11, e.row);
    EXPECT_EQ(14, e.col);
}

TEST (Entity, live_movement_2)
{
    Entity e;
    e.row = 10;
    e.col = 15;
    e.move(POS, NONE);
    EXPECT_EQ(11, e.row);
    EXPECT_EQ(15, e.col);
}

TEST (Entity, dead_movement)
{
    Entity e;
    e.row = 10;
    e.col = 15;
    e.dead = true;
    e.move(POS, NEG);
    EXPECT_EQ(10, e.row);
    EXPECT_EQ(15, e.col);
}
