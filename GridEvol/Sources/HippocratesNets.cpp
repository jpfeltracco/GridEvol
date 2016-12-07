#include "HippocratesNets.h"

#include <stdexcept>

HippocratesNets::HippocratesNets(int num_nets, int num_inputs_per_net, int num_outputs_per_net, int max_fitness)
    : Nets(num_nets, num_inputs_per_net, num_outputs_per_net)
{
    // initialize bodies we'll be using
    for (int i = 0; i < num_nets; ++i) {
        bodies.push_back(Hippocrates::DumbBody(num_inputs_per_net, num_outputs_per_net, 0, max_fitness, false));
    } 

    trainingBodies.insert(trainingBodies.end(), bodies.begin(), bodies.end());

    manager.CreateInitialOrganisms(trainingBodies);

}

std::unique_ptr<NetOutputs> HippocratesNets::process(std::unique_ptr<NetInputs> inputs)
{
    if (inputs->size() != bodies.size()) {
        throw std::invalid_argument("Incorrect input size for num bodies.");
    }

    // update inputs to system
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].update_inputs((*inputs)[i]);
    }

    // processes new outputs
    manager.Update();

    auto output_ptr = std::make_unique<NetOutputs>();
    // return the new outputs
    for (auto& b : bodies) {
        output_ptr->push_back(b.get_outputs());
    }

    return output_ptr;
}

void HippocratesNets::update_generation(std::unique_ptr<Fitnesses> fitnesses)
{
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].set_fitness((*fitnesses)[i]);
    }
    // update bodies with fitnesses
    manager.Repopulate(trainingBodies);
}

double HippocratesNets::get_average_fitness() const
{
    return manager.GetTotalFitness();
}
