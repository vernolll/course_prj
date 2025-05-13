#pragma once
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <fstream>

#include "Point.h"

class SweepLine {
public:
    SweepLine(Point line_point, Point direction, Point circle_center, double r);

    std::vector<Point> findIntersections();

    static void saveToFile(const std::vector<Point>& intersections, double k, double b, Point center, double r);

private:
    Point p0;
    Point dir;
    Point center;
    double radius;
};
