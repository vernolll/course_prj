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
    // �����������, ����������� ��������� ������ � ����������
    Newton(Point line_point, Point direction, Point circle_center, double r);
    // ����� ��� ���������� �����������
    std::vector<Point> solve();
    static void saveToFile(const std::vector<Point>& intersections, double k, double b, Point circle_center, double r);

private:
    Point line_point;  // ����� �� ������
    Point direction;   // ����������� ������
    Point circle_center;  // ����� ����������
    double r;  // ������ ����������
};