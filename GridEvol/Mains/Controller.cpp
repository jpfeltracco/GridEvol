#include <iostream>
#include "body/body.hpp"
#include "training/neural_network_trainer.hpp"

class MyBody;

namespace Hippocrates {

class MyBody :  public Hippocrates::Body::IBody {
public:
    auto Reset() -> void {
        //std::cout << "Reset called" << std::endl;
    }
    auto Update(const Type::neuron_values_t& networkOutputs) -> void {
        std::cout << "Update called" << std::endl;
    }
    auto HasFinishedTask() const -> bool {
        std::cout << "has finished?" << std::endl;
        return false;
    }
    auto GetFitness() const -> Type::fitness_t {
        //std::cout << "Get fitness called" << std::endl;
        return 5;
    }

    auto ProvideNetworkWithInputs() const -> Type::neuron_values_t {
        std::cout << "Input called" << std::endl;
        std::vector<float> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        return std::move(vec);
    }

    auto GetInputCount() const -> std::size_t  {
        std::cout << "Input count called" << std::endl;
        return 3;
    }
    auto GetOutputCount() const -> std::size_t {
        std::cout << "Output count called" << std::endl;
        return 5;
    }

    auto GetMaximumFitness() const ->Type::fitness_t {
        //std::cout << "Max called" << std::endl;
        return 10;
    }
};

void start() {
    std::cout << "Ready!" << std::endl;
    srand(static_cast<unsigned>(time(nullptr)));

    //TrainingParameters parameters;
    //parameters.structure.areRecursiveConnectionsAllowed = false;
    std::vector<Hippocrates::MyBody> bodies(100);
    Training::SpeciesManager::Bodies trainingBodies(bodies.begin(), bodies.end());

    Training::SpeciesManager manager;
    manager.CreateInitialOrganisms(trainingBodies);

    manager.Update();

    manager.Repopulate(trainingBodies);
    //Training::NeuralNetworkTrainer trainer;


    //auto champ = trainer.TrainUnsupervised(trainingBodies);
    //std::string s = trainer.GetJSON();
}

}


int main() {
    Hippocrates::start();
    return 0;
}
