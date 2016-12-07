#include <vector>
#include <memory>

#include "Normalizable.h"

using Input = std::vector<Normalizable>;
using Inputs = std::vector<Input>;
using Output = std::vector<Normalizable>;
using Outputs = std::vector<Output>;
using Fitnesses = std::vector< double >;

class Simulation {
public:
    virtual std::unique_ptr<Outputs> step(const Inputs& inputs) = 0;

    virtual std::size_t get_entity_num() const = 0;
    
    virtual int get_inputs_per_entity() const = 0;
    virtual int get_outputs_per_entity() const = 0;

    virtual bool is_finished() const = 0;

    virtual std::unique_ptr<Fitnesses> get_fitnesses() const = 0;
};
