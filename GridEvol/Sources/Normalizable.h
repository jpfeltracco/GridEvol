class Normalizable {

public:
    Normalizable(double value,
                 double min,
                 double max);
    Normalizable(double value);
    
    double get_value() const;

    void set_range(double min, double max, bool update_val = true);
    void set_value(double new_value);

private:
    double min;
    double max;
    double value;
};
