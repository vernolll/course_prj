#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#include "Point.h"

class BisectionIntersection {
public:
    BisectionIntersection(Point linePoint, Point dir, Point circleCenter, double radius);

    std::vector<Point> findIntersections(double t_min = -1e3, double t_max = 1e3, double eps = 1e-6);

    static void saveToFile(const std::vector<Point>& intersections, double k, double b, Point center, double r);

private:
    Point p0, dir, center;
    double r;
};
