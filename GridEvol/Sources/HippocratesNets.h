#include "Nets.h"

#include <vector>

#include "body/body.hpp"
#include "training/neural_network_trainer.hpp"

namespace Hippocrates {

class DumbBody :  public Hippocrates::Body::IBody {
public:
    DumbBody(int in_cnt, int out_cnt, int fitness, int max_fitness, bool finished)
        : input_count(in_cnt), output_count(out_cnt), fitness(fitness), max_fitness(max_fitness),
          finished(finished) {}

    void Reset() {}

    void Update(const Type::neuron_values_t& networkOutputs) { outputs = networkOutputs; }

    bool HasFinishedTask() const { return false; }

    Type::fitness_t GetFitness() const { return fitness; };

    Type::neuron_values_t ProvideNetworkWithInputs() const { return inputs; }

    std::size_t GetInputCount()  const { return input_count; }
    std::size_t GetOutputCount() const { return output_count; }

    Type::fitness_t GetMaximumFitness() const { return max_fitness; }

    void set_input_count(int count) { input_count = count; }
    void set_output_count(int count) { output_count = count; }
    void set_fitness(int fit) { fitness = fit; }
    void set_max_fitness(int fitness) { max_fitness = fitness; }

    void update_inputs(NetInput in)
    {
        inputs.clear();
        for (auto& n : in) {
            n.set_range(-1, 1);
            inputs.push_back(n.get_value());
        }
    }

    NetOutput get_outputs() { 
        return std::vector<Norm>(outputs.begin(), outputs.end() );
    }

private:
    int input_count;
    int output_count;
    int fitness;
    int max_fitness;

    bool finished;

    std::vector<float> inputs;
    std::vector<float> outputs;

};

} // end namespace Hippocrates

class HippocratesNets : public Nets {
public:
    HippocratesNets(int num_nets, int num_inputs_per_net, int num_outputs_per_net, int max_fitness);
    
    virtual std::unique_ptr<NetOutputs> process(std::unique_ptr<NetInputs> inputs);
    virtual void update_generation(std::unique_ptr<Fitnesses>);
    virtual double get_average_fitness() const;
private:
    std::vector<Hippocrates::DumbBody> bodies;
    Hippocrates::Training::SpeciesManager manager;
    Hippocrates::Training::SpeciesManager::Bodies trainingBodies;

    //std::vector<DumbBodies>;
    // num_nets
    // num_inputs_per_net
    // num_outputs_per_net
};
