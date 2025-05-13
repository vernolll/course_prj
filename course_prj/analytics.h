#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "Point.h"

class Analytics {
public:
    // �����: ����������� ������ � ����������
    static std::vector<Point> intersectLineCircle(double k, double b,
        double cx, double cy, double r);
};
