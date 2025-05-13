#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "Point.h"

class GeoIntersection {
public:
    static std::vector<Point> intersectLineCircle(Point P0, Point direction, Point center, double radius);
    static void saveToFile(double k, double b, Point center, double radius, const std::vector<Point>& intersections);
};
