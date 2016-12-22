#pragma once

#include <vector>

class Tensor3 {
public:
    int sx, sy, depth;
    std::vector<double> w, dw;

public:
    Tensor3();
    Tensor3(int sx, int sy, int depth);
    Tensor3(int sx, int sy, int depth, double value);
    Tensor3(const std::vector<double> &w);

    Tensor3(const Tensor3 &t);
    Tensor3(Tensor3 &&t);

    Tensor3 &operator=(const Tensor3 &t);
    Tensor3 &operator=(Tensor3 &&t);
};
