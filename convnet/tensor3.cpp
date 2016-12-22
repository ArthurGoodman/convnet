#include "tensor3.h"

#include <cmath>

#include "util.h"

Tensor3::Tensor3()
    : sx(0), sy(0), depth(0) {
}

Tensor3::Tensor3(int sx, int sy, int depth)
    : sx(sx), sy(sy), depth(depth) {
    int n = sx * sy * depth;

    w.resize(n);
    dw.resize(n);

    init();
}

Tensor3::Tensor3(int sx, int sy, int depth, double value)
    : sx(sx), sy(sy), depth(depth) {
    int n = sx * sy * depth;

    w.resize(n);
    dw.resize(n);

    std::fill_n(w.data(), n, value);
    std::fill_n(dw.data(), n, 0.0);
}

Tensor3::Tensor3(const std::initializer_list<double> &list)
    : sx(1), sy(1), depth(list.size()), w(list.size()), dw(list.size()) {
    int c = 0;
    for (std::initializer_list<double>::const_iterator i = list.begin(); i != list.end(); ++i)
        w[c++] = *i;
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
    dw = t.dw;

    return *this;
}

Tensor3 &Tensor3::operator=(Tensor3 &&t) {
    sx = t.sx;
    sy = t.sy;
    depth = t.depth;

    w = std::move(t.w);
    dw = std::move(t.dw);

    return *this;
}

void Tensor3::init() {
    int n = sx * sy * depth;

    double scale = sqrt(1.0 / n);

    for (int i = 0; i < n; i++)
        w[i] = gaussRandom(0.0, scale);

    std::fill_n(dw.data(), n, 0.0);
}
