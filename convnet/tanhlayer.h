#pragma once

#include "ilayer.h"

class TanhLayer : public ILayer {
public:
    TanhLayer(int sx, int sy, int depth);

    void forward();
    void backward();
};
