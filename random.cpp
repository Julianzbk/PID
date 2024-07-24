#include <random>
#include <cstdlib>

#include <iostream>
#include <ctime>
#include <windows.h>

constexpr double LAMBDA = 5;

using std::cout, std::endl;

class Randomizer
{
/*
    PDF: λe^(-λx) {x <= 0}
          λe^(λx) {x >= 0}
*/
    std::exponential_distribution<double> distr;
    std::mt19937 gen;
public:
    Randomizer(int seed = time(nullptr))
        :distr(LAMBDA), gen(seed)
    {
    }

    double operator() ()
    {
        bool is_positive = std::rand() / ((RAND_MAX + 1u) / 2);

        if (is_positive)
            return distr(gen);
        else
            return -distr(gen);
    }
};

/*
#include <map>
#include <iomanip>

constexpr int RAND_MOD = 10;

int main()
{
    Randomizer rand;
    std::map<int, int> hist;
    for (int n = 0; n != 10000; ++n)
        ++hist[floor(2 * rand())];
 
    for (auto const& [x, y] : hist)
        std::cout << std::fixed << std::setprecision(1)
                  << x / 2.0 << '-' << (x + 1) / 2.0 << ' '
                  << std::string(y / 200, '*') << '\n';
    return 0;
}
*/