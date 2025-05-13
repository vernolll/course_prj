#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "Point.h"

class Secant {
public:
    Secant(Point line_point, Point direction, Point circle_center, double r);
    static void saveToFile(const std::vector<Point>& intersections, double k, double b, Point circle_center, double r);


    std::vector<Point> solve();
private:
    Point line_point;
    Point direction;
    Point circle_center;
    double r;
};
