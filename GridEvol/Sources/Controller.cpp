#include <memory>
#include <iostream>

#include "Controller.h"
#include "GridSimulation.h"
#include "HippocratesNets.h"

void Controller::run()
{
   


    // need to get neural network component set up using:
    // sim.get_entity_num()
    // sim.get_inputs_per_entity()
    // sim.get_outputs_per_entity()
    
    HippocratesNets neural_nets(5, 8, 2, 1000);

    const std::size_t num_gen = 1000000;

    for (std::size_t generation = 0; generation < num_gen; ++generation) {
        GridSimulation sim(5, 10, 10);


        const std::size_t max_frames = 10;
        for (std::size_t num_frames = 0; num_frames < max_frames; ++num_frames) {
            auto sim_inputs = neural_nets.process(sim.get_outputs());


            sim.step(*sim_inputs);
            if (generation == std::size_t(num_gen - 1)) {
                std::cout << "Frame Count: " << num_frames << std::endl;
                std::cout << sim << std::endl;
            }
            if (sim.is_finished()) break;
        }

        std::cout << "Avg Fitness: " << neural_nets.get_average_fitness() << std::endl;
        neural_nets.update_generation(sim.get_fitnesses());
    }
}
