#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <limits>
#include <functional>
#include <vector>

#include "Point.h"

class Newton {
public:
    // Конструктор, принимающий параметры прямой и окружности
    Newton(Point line_point, Point direction, Point circle_center, double r);
    // Метод для вычисления пересечений
    std::vector<Point> solve();
    static void saveToFile(const std::vector<Point>& intersections, double k, double b, Point circle_center, double r);

private:
    Point line_point;  // Точка на прямой
    Point direction;   // Направление прямой
    Point circle_center;  // Центр окружности
    double r;  // Радиус окружности
};