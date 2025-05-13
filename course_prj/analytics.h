#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "Point.h"

class Analytics {
public:
    // Метод: пересечение прямой и окружности
    static std::vector<Point> intersectLineCircle(double k, double b,
        double cx, double cy, double r);
};
