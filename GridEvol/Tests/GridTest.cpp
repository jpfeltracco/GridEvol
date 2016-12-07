#include <gtest/gtest.h>
#include <stdexcept>
#include <memory>

#include "GridSimulation.h"

class GridTest : public ::testing::Test {
public:
    GridTest() : grid(10, 15) {}
protected:
    virtual void SetUp() {
        out_of_range_e = std::make_shared<Entity>();
        out_of_range_e->row = 10;
    }
    
    Grid grid;

    std::shared_ptr<Entity> out_of_range_e;
    std::shared_ptr<Entity> zero_zero_e;
};

TEST_F(GridTest, test_num_rows_and_cols)
{
    EXPECT_EQ(10, grid.num_rows());
    EXPECT_EQ(15, grid.num_cols());
}

TEST_F(GridTest, test_spot_full)
{
    auto e = std::make_shared<Entity>();
    e->row = 5;
    e->col = 3;
    grid.add(e);

    EXPECT_TRUE(grid.is_spot_full(5, 3));
}

TEST_F(GridTest, test_out_of_range)
{
    grid.add(out_of_range_e);
    EXPECT_TRUE(out_of_range_e->dead);
}

TEST_F(GridTest, test_get_surrounding)
{
    auto e_above_ptr = std::make_shared<Entity>();
    e_above_ptr->row = 1;
    auto e_top_right_ptr = std::make_shared<Entity>();
    e_top_right_ptr->row = 1;
    e_top_right_ptr->col = 1;

    grid.add(e_above_ptr);
    grid.add(e_top_right_ptr);

    // surroundings
    std::vector<spot_state> sur;

    std::vector<spot_state> act;
    act.push_back(BLOCKED);
    act.push_back(BLOCKED);
    act.push_back(BLOCKED);
    act.push_back(BLOCKED);
    act.push_back(BLOCKED);
    act.push_back(EMPTY);
    act.push_back(BLOCKED);
    act.push_back(BLOCKED);
    

    grid.get_surrounding(0, 0, sur); 

    EXPECT_EQ(act, sur);

    sur.clear();
    act.clear();

    act.push_back(BLOCKED);
    act.push_back(EMPTY);
    act.push_back(EMPTY);
    act.push_back(EMPTY);
    act.push_back(EMPTY);
    act.push_back(EMPTY);
    act.push_back(EMPTY);
    act.push_back(EMPTY);
}

