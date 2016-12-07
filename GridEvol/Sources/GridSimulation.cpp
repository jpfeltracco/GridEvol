#include <random>
#include <exception>

#include "GridSimulation.h"

Grid::Grid(int rows, int cols)
{
    for (int row = 0; row < rows; ++row) {
        grid.push_back(Col());
        for (int col = 0; col < cols; ++col) {
            grid[row].push_back(Spot());
        }
    }
}

int Grid::num_rows() {
    return grid.size();
}

int Grid::num_cols() {
    return grid[0].size();
}

void Grid::clear() {
    for (auto v : grid) {
        v.clear();
    }
}

void Grid::add(std::shared_ptr<Entity> entity)
{
    // Don't even bother adding it if it's already dead
    if (entity->dead) return;

    int row = entity->row;
    int col = entity->col;

    if (!is_in_range(entity->row, entity->col)) {
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


void Grid::get_surrounding(int row, int col, std::vector<spot_state>& v)
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

spot_state Grid::get_spot_state(int row, int col)
{
    if (!is_in_range(row, col)) return BLOCKED;
    if (is_spot_full(row, col)) return BLOCKED;
    return EMPTY;
}

bool Grid::is_in_range(int row, int col)
{
    return (row >= 0 && row < num_rows()) && (col >= 0 && col < num_cols());
}

bool Grid::is_spot_full(int row, int col)
{
    return grid[row][col].size() != 0;
}

GridSimulation::GridSimulation(std::size_t num_entities, std::size_t rows, std::size_t cols)
    : grid(rows, cols)
{
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

std::unique_ptr<Outputs> GridSimulation::step(const Inputs& inputs)
{
    if (inputs.size() != get_entity_num()) {
        throw std::invalid_argument("Input size doesn't match entity count.");
    }

    grid.clear();

    // Move the entities to their new positions
    for (std::size_t entity_id = 0; entity_id < get_entity_num(); ++entity_id) {
        const Input& input = inputs[entity_id];
        auto directions = direction_from_input(input);

        //Entity& entity = entities[entity_id];
        auto entity_ptr = entities[entity_id];
        
        entity_ptr->move(std::get<0>(directions), std::get<1>(directions));
    }
    
    // Check for overlaps and marks entities dead as needed
    for (auto& e : entities) {
        grid.add(e);
    }

    // Build our outputs and update fitnesses
    for (auto& e : entities) {
        if (!e->dead) {
            e->fitness++;
        } 
    }

    auto output_ptr = std::make_unique<Outputs>();
    for (std::size_t i = 0; i < entities.size(); ++i) {
        auto entity_ptr = entities[i];
        
    }
    
    return output_ptr;
}


std::size_t GridSimulation::get_entity_num() const
{
    return 10;
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
    return false;
}

std::unique_ptr<Fitnesses> GridSimulation::get_fitnesses() const
{
    return nullptr;
}

