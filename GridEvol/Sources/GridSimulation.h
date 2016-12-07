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

    void get_surrounding(int row, int col, std::vector<spot_state>& v) const;
    spot_state get_spot_state(int row, int col) const;
    
    int num_rows() const;
    int num_cols() const;
    
    bool is_in_range(int row, int col) const;
    bool is_spot_full(int row, int col) const;
    void add(std::shared_ptr<Entity> entity);
    
    friend std::ostream& operator<<(std::ostream& os, const Grid& g);

    Col& operator[](int row) {
        return grid[row];
    }

    const Col& operator[](int row) const {
        return grid[row];
    }

    void clear();

private:
    std::vector< std::vector<Spot> > grid;
};

class Entity {
public:
    Entity() : row(0), col(0), fitness(0), dead(false), currentID(ID++) {};

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

    const int currentID;
    static int ID;
};
class GridSimulation : public Simulation {
public:
    GridSimulation(std::size_t num_entities, std::size_t rows, std::size_t cols); 
    virtual void step(const Inputs& inputs);

    virtual std::unique_ptr<Outputs> get_outputs() const;

    virtual std::size_t get_entity_num() const;
    
    virtual int get_inputs_per_entity() const;
    virtual int get_outputs_per_entity() const;

    virtual bool is_finished() const;

    virtual std::unique_ptr<Fitnesses> get_fitnesses() const;

    friend std::ostream& operator<<(std::ostream& os, const GridSimulation& g);
private:
    Grid grid;
    std::vector< std::shared_ptr<Entity> > entities;

    auto direction_from_input(const Input& input);

    int alive_entity_count;
};
