#include "tensor3.h"

#include <cmath>

#include "util.h"

Tensor3::Tensor3(int sx, int sy, int depth)
    : sx(sx), sy(sy), depth(depth) {
    int n = sx * sy * depth;

    w.resize(n);
    dw.resize(n);

    double scale = sqrt(1.0 / n);

    for (int i = 0; i < n; i++)
        w[i] = gaussRandom(0.0, scale);

    std::fill_n(dw.data(), n, 0.0);
}

Tensor3::Tensor3(const std::vector<double> &w)
    : sx(1), sy(1), depth(w.size()), w(w), dw(w.size()) {
}

Tensor3::Tensor3(const Tensor3 &t) {
    *this = t;
}

Tensor3::Tensor3(Tensor3 &&t) {
    *this = std::move(t);
}

Tensor3 &Tensor3::operator=(const Tensor3 &t) {
    sx = t.sx;
    sy = t.sy;
    depth = t.depth;
    w = t.w;

    return *this;
}

Tensor3 &Tensor3::operator=(Tensor3 &&t) {
    sx = t.sx;
    sy = t.sy;
    depth = t.depth;
    w = std::move(t.w);

    return *this;
}
