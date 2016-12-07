#include "Norm.h"
#include <stdexcept>

/**
 * Initializes the object with a custom range.
 *
 * @param value Value to store
 * @param min Minimum value in the range
 * @param Max Maximum value in the range
 */
Norm::Norm(double value, double min, double max)
{
    set_range(min, max, false); 
    set_value(value);
}

/**
 * Initializes the object with a default range of -1 to 1
 * (This is what I'm calling 'normalized')
 *
 * @param norm_value Value to store
 */
Norm::Norm(double norm_value)
    : Norm::Norm(norm_value, -1.0, 1.0) {}

/**
 * Returns the current value this object encapsulates.
 *
 * @return value held by this object.
 */
double Norm::get_value() const
{
    return value;
}

/**
 * Remaps the value from its current range to a new range.
 *
 * @param new_min New min value of the range
 * @param new_max New max value of the range
 * @param update_val Flags whether to do a set_value, can be disabled for
 * constructing the initial Norm
 */
void Norm::set_range(double new_min, double new_max, bool update_val)
{
    if (new_min >= new_max) {
        throw std::invalid_argument("Min must be less than max."); 
    }

    // only used if update_val is true
    double value_normed = (value - min) / (max - min);
    
    min = new_min;
    max = new_max;

    if (update_val) {
        set_value(value_normed * (new_max - new_min) + new_min);
    }
}

/**
 * Sets a new value to be encapsulated by this object.
 *
 * @param new_value Value to store.
 */
void Norm::set_value(double new_value)
{
    if (new_value < min || new_value > max) {
        throw std::invalid_argument("Input must be in range [min, max].");
    }
    value = new_value;
}
