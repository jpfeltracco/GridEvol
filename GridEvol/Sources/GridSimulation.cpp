#include <random>
#include <exception>
#include <iostream>

#include "GridSimulation.h"

int Entity::ID = 0;

Grid::Grid(int rows, int cols)
{
    for (int row = 0; row < rows; ++row) {
        grid.push_back(Col());
        for (int col = 0; col < cols; ++col) {
            grid[row].push_back(Spot());
        }
    }
}

int Grid::num_rows() const
{
    return grid.size();
}

int Grid::num_cols() const
{
    return grid[0].size();
}

void Grid::clear() {
    for (auto& v : grid) {
        for (auto& s : v) {
            s.clear();
        }
    }
}

void Grid::add(std::shared_ptr<Entity> entity)
{
    // Don't even bother adding it if it's already dead
    if (entity->dead) return;

    int row = entity->row;
    int col = entity->col;

    if (!is_in_range(row, col)) {
        entity->dead = true;
    } else {
        grid[row][col].push_back(entity);    

        // If there was an overlap, mark all as dead
        if (grid[row][col].size() > 1) {
            for (auto& e : grid[row][col]) {
                e->dead = true;
            }
        }
    }
}


void Grid::get_surrounding(int row, int col, std::vector<spot_state>& v) const
{
    // bottom left
    v.push_back(get_spot_state(row - 1, col - 1));
    // left
    v.push_back(get_spot_state(row, col - 1));
    // top left
    v.push_back(get_spot_state(row + 1, col - 1));
    // top
    v.push_back(get_spot_state(row + 1, col));
    // top right
    v.push_back(get_spot_state(row + 1, col + 1));
    // right
    v.push_back(get_spot_state(row, col + 1));
    // bottom right
    v.push_back(get_spot_state(row - 1, col + 1));
    // bottom
    v.push_back(get_spot_state(row - 1, col));
}

spot_state Grid::get_spot_state(int row, int col) const
{
    if (!is_in_range(row, col)) return BLOCKED;
    if (is_spot_full(row, col)) return BLOCKED;
    return EMPTY;
}

bool Grid::is_in_range(int row, int col) const
{
    return (row >= 0 && row < num_rows()) && (col >= 0 && col < num_cols());
}

bool Grid::is_spot_full(int row, int col) const
{
    return grid[row][col].size() != 0;
}

GridSimulation::GridSimulation(std::size_t num_entities, std::size_t rows, std::size_t cols)
    : grid(rows, cols), alive_entity_count(num_entities)
{
    // hack, remove this later
    Entity::ID = 0;
    if (num_entities > rows * cols) {
        throw std::invalid_argument("Inputted number of entities cannot fit in specified rows/cols");
    }

    // Seed with a real random value, if available
    std::random_device r;
 
    // Choose a random position in rows and cols
    std::default_random_engine e1(r());

    std::uniform_int_distribution<int> row_selector(0, rows - 1);
    std::uniform_int_distribution<int> col_selector(0, cols - 1);


    for (std::size_t i = 0; i < num_entities; ++i) {
        auto entity_ptr = std::make_shared<Entity>();
        entities.push_back(entity_ptr);

        do {
            std::size_t row_val = row_selector(e1);
            std::size_t col_val = col_selector(e1);

            entity_ptr->row = row_val;
            entity_ptr->col = col_val;
        } while (grid.is_spot_full(entity_ptr->row, entity_ptr->col));

        grid.add(entity_ptr);
    }
}

auto GridSimulation::direction_from_input(const Input& input)
{
    double x_input = input[HORIZ].get_value();
    double y_input = input[VERT].get_value();

    direction x_dir = NONE;
    direction y_dir = NONE;

    if (x_input > 0.5) {
        x_dir = POS;
    } else if (x_input < -0.5) {
        x_dir = NEG;
    }

    if (y_input > 0.5) {
        y_dir = POS;
    } else if (y_input < -0.5) {
        y_dir = NEG;
    }
    
    return std::make_tuple(x_dir, y_dir); 
}

#include <iostream>
void GridSimulation::step(const Inputs& inputs)
{
    //std::cout << "got input: " << std::endl;
    //for (const Input& b : inputs) {
    //    for (const auto& val : b) {
    //        std::cout << val.get_value() << " " << std::endl;
    //    }
    //}
    if (inputs.size() != get_entity_num()) {
        throw std::invalid_argument("Input size doesn't match entity count.");
    }

    grid.clear();

    // Move the entities to their new positions
    for (std::size_t entity_id = 0; entity_id < get_entity_num(); ++entity_id) {
        const Input& input = inputs[entity_id];
        auto directions = direction_from_input(input);

        auto entity_ptr = entities[entity_id];
        
        entity_ptr->move(std::get<0>(directions), std::get<1>(directions));
    }
    
    // Check for overlaps and marks entities dead as needed
    for (auto& e : entities) {
        grid.add(e);
    }

    alive_entity_count = get_entity_num();

    // update fitnesses and our alive counter
    for (auto& e_ptr : entities) {
        if (!e_ptr->dead) {
            e_ptr->fitness++;
        }  else {
            alive_entity_count--;
        }
    }
}

std::unique_ptr<Outputs> GridSimulation::get_outputs() const
{
    auto output_ptr = std::make_unique<Outputs>();

    for (auto& e_ptr : entities) {
        std::vector<spot_state> surround;
        std::vector<Norm> single_out;

        grid.get_surrounding(e_ptr->row, e_ptr->col, surround);

        for (spot_state s : surround) {
            switch(s) {
                case EMPTY:
                    single_out.push_back(Norm(-1));
                    break;
                case BLOCKED:
                    single_out.push_back(Norm(1));
                    break;
            }
        }

        output_ptr->push_back(single_out);
    }
    
    return output_ptr;
}


std::size_t GridSimulation::get_entity_num() const
{
    return entities.size();
}

int GridSimulation::get_inputs_per_entity() const
{
    return 8;
}

int GridSimulation::get_outputs_per_entity() const
{
    return 2;
}

bool GridSimulation::is_finished() const 
{
    return alive_entity_count == 0;
}

std::unique_ptr<Fitnesses> GridSimulation::get_fitnesses() const
{
    auto fit_ptr = std::make_unique<Fitnesses>();

    for (auto& e : entities) {
        fit_ptr->push_back(e->fitness);
    }
    return fit_ptr;
}

std::ostream& operator<<(std::ostream& os, const GridSimulation& g)
{
    os << g.grid; 
    return os;
}

std::ostream& operator<<(std::ostream& os, const Grid& g)  
{
    for (int row = g.num_rows() - 1; row >= 0; --row) {
        for (int col = 0; col < g.num_cols(); ++col) {
            if (g[row][col].size() == 0) {
                os << " ";
            } else {
                for (auto& e : g[row][col]) { 
                    os << e->currentID << " ";
                }
            }
            os << "\t";
        }
        os << "\n";
    }
    return os;  
}  
