#include <tuple>
#include <vector>
#include <memory>

#include "Simulation.h"

class Entity;

using Spot = std::vector< std::shared_ptr<Entity> >;
using Col = std::vector<Spot>;

enum direction {
    NONE, POS, NEG
};

enum input_dir {
    HORIZ = 0, VERT
};

enum spot_state {
    EMPTY, BLOCKED
};

class Grid {
public:
    Grid(int rows, int cols);

    void get_surrounding(int row, int col, std::vector<spot_state>& v);
    spot_state get_spot_state(int row, int col);
    
    int num_rows();
    int num_cols();
    
    bool is_in_range(int row, int col);
    bool is_spot_full(int row, int col);
    void add(std::shared_ptr<Entity> entity);

    Col& operator[](int row) {
        return grid[row];
    }

    void clear();

private:
    std::vector< std::vector<Spot> > grid;
};

class Entity {
public:
    Entity() : row(0), col(0), fitness(0), dead(false) {};

    void move(direction row_dir, direction col_dir) {
        if (dead) return;

        if (row_dir == POS) row++;
        if (row_dir == NEG) row--;
        if (col_dir == POS) col++;
        if (col_dir == NEG) col--;
    }


    int row;
    int col;

    int fitness;
    bool dead;
};

class GridSimulation : public Simulation {
public:
    GridSimulation(std::size_t num_entities, std::size_t rows, std::size_t cols); 
    virtual std::unique_ptr<Outputs> step(const Inputs& inputs);

    virtual std::size_t get_entity_num() const;
    
    virtual int get_inputs_per_entity() const;
    virtual int get_outputs_per_entity() const;

    virtual bool is_finished() const;

    virtual std::unique_ptr<Fitnesses> get_fitnesses() const;
private:
    Grid grid;
    std::vector< std::shared_ptr<Entity> > entities;

    auto direction_from_input(const Input& input);

};
