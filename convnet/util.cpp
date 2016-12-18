#include "util.h"

#include <cmath>
#include <cstdlib>

double gaussRandom() {
    static double v1, v2, s;
    static int phase = 0;
    double x;

    if (phase == 0) {
        do {
            double u1 = (double)rand() / RAND_MAX;
            double u2 = (double)rand() / RAND_MAX;

            v1 = 2 * u1 - 1;
            v2 = 2 * u2 - 1;
            s = v1 * v1 + v2 * v2;
        } while (s >= 1 || s == 0);

        x = v1 * sqrt(-2 * log(s) / s);
    } else
        x = v2 * sqrt(-2 * log(s) / s);

    phase = 1 - phase;

    return x;
}

double gaussRandom(double mu, double std) {
    return mu + gaussRandom() * std;
}
