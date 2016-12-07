#include <gtest/gtest.h>
#include <stdexcept>
#include <memory>

#include "GridSimulation.h"

class GridSimulationTest : public ::testing::Test {
public:
    GridSimulationTest() : sim(3, 5, 5) {}
protected:
    virtual void SetUp() {
    }
    
    GridSimulation sim;
};

TEST_F(GridSimulationTest, test_num_entities)
{
    EXPECT_EQ(std::size_t(3), sim.get_entity_num());
}

TEST_F(GridSimulationTest, test_step)
{
    Inputs sim_in = {{Norm(-1), Norm(0)}, {Norm(0), Norm(1)}, {Norm(1), Norm(-1)}};
    
    sim.step(sim_in);
    auto output_ptr = sim.get_outputs();
    
    EXPECT_EQ(std::size_t(3), output_ptr->size());
    for (auto& vec : *output_ptr) {
        EXPECT_EQ(std::size_t(8), vec.size());
    }
}

TEST_F(GridSimulationTest, test_kill_all_finished)
{
    Inputs sim_in = {{Norm(-1), Norm(0)}, {Norm(0), Norm(1)}, {Norm(1), Norm(-1)}};

    // No matter the entity positions, moving 5 times same direction should kill
    for (int i = 0; i < 5; ++i) {
        sim.step(sim_in);
    }

    EXPECT_TRUE(sim.is_finished());
}

TEST_F(GridSimulationTest, test_kill_none)
{
    Inputs sim_in = {{Norm(0), Norm(0)}, {Norm(0), Norm(0)}, {Norm(0), Norm(0)}};

    EXPECT_FALSE(sim.is_finished());

    // None should be killed
    for (int i = 0; i < 5; ++i) {
        sim.step(sim_in);
    }

    EXPECT_FALSE(sim.is_finished());
}
