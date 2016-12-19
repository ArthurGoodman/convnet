#pragma once

#include "ilayer.h"
#include "tensor3.h"

class ALossLayer : public ILayer {
public:
    std::vector<double> y;
    double loss;
};
