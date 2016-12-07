#include <vector>
#include <memory>

#include "Norm.h"

using NetInput = std::vector< Norm >;
using NetInputs = std::vector< NetInput >;
using NetOutput = std::vector< Norm >;
using NetOutputs = std::vector< NetOutput >;
using Fitnesses = std::vector< double >;

class Nets {
public:
    Nets(int num_nets, int num_inputs_per_net, int num_outputs_per_net)
        : num_nets(num_nets), num_inputs_per_net(num_inputs_per_net), num_outputs_per_net(num_outputs_per_net) {};

    virtual std::unique_ptr<NetOutputs> process(std::unique_ptr<NetInputs>) = 0;
    virtual void update_generation(std::unique_ptr<Fitnesses>) = 0;

private:
    const int num_nets;
    const int num_inputs_per_net;
    const int num_outputs_per_net;
};
