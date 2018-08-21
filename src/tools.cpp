#include <tools.hpp>
#include <cstdlib>

double Uniform() {
    return (double)rand() / (double)(RAND_MAX+1.0);
}

int UniformInt(int min, int max) {
    return Uniform()*(max-min) + min;
}
