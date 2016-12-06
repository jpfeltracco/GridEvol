class Normalizable {
public:
    Normalizable(double min, double max);
    double actual();
    double normalized();

    void set_actual(double value);
    void set_normalized(double value);

private:
    double normed; // value between -1 and 1
    double min;
    double max;
};
