#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

double Uniform();
int UniformInt(int min, int max);

template<typename T>
bool inRange(const T &x, const T &min, const T &max) {
    return x >= min && x <= max;
}

#endif
