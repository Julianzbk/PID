#include "random.cpp"

#include <iomanip>
#include <fstream>
//#include <format>
using std::to_string;

Randomizer random;
double d = 0;

constexpr double target = 15;
constexpr int step_ms = 100;

double err_sum = 0;

double err()
{
    double err = target - d;
    err_sum += err;
    return err;
}

double MAX_ERROR = 0;

void print()
{
    double abs_err = abs(err());
    if (MAX_ERROR == 0)
        MAX_ERROR = __DBL_MIN__;
    else
    {
        if (abs_err > abs(MAX_ERROR))
            MAX_ERROR = err();
    }

    cout << std::setw(8) << "d= " << to_string(d).substr(0, 7) << ", "
         << "err= " << to_string(err()).substr(0, 7) << ", "  << "esum= " << to_string(err_sum).substr(0, 7) <<  ", "
         << "max= "<< to_string(MAX_ERROR).substr(0, 7) <<'\n';
}

constexpr double Kp = 0.6;

double prop(double d)
{
    return err() * Kp;
}

constexpr double Ki = 0.001;

double integ(double d)
{
    return err_sum * Ki;
}

double old_d = 0;

constexpr double Kd = 0.05;

double deriv(double d)
{
    return (old_d - d) * Kd;
}

double pid(double d)
{
    return d + prop(d) + integ(d) + deriv(d);
}

std::ofstream file("data.txt");

void step() 
{
    print();
    file << d << '\n';
    old_d = d;
    d += random();
    //file << d << '\n';
    d = pid(d) + (random() / 8);
}

int main()
{
    //file << std::format("Kp={}, Ki={}, Kd={}\n", Kp, Ki, Kd);
    file << "Kp=" << Kp << ", Ki=" << Ki << ", Kd=" << Kd << '\n';
    file << target << '\n';
    for (int i = 0; i < 75; ++i)
    {
        step();
        Sleep(step_ms);
    }
    file.close();
    //return system("python plot.py");
}