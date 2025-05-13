#include "bisection.h"


BisectionIntersection::BisectionIntersection(Point linePoint, Point dir, Point circleCenter, double radius)
    : p0(linePoint), dir(dir), center(circleCenter), r(radius) {
}


std::vector<Point> BisectionIntersection::findIntersections(double t_min, double t_max, double eps) {
    std::vector<Point> result; // ��������� �����

    auto f = [&](double t) {
        double x = p0.x + t * dir.x;
        double y = p0.y + t * dir.y;
        return (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y) - r * r;
        // ������� ��. ���������� �� �. (x, y) �� ������ ���. � ��. �������
        };

    // ���� ��� ����� �������� � �������� ����� t_min � t_max � ���������� �� ����
    double prev = t_min;
    double step = 0.1;

    for (double curr = t_min + step; curr <= t_max; curr += step) {
        if (f(prev) * f(curr) < 0) { // ���� ����� ������, �� ���� ������
            double a = prev, b = curr; // ������� ���������
            while (b - a > eps) {
                double mid = (a + b) / 2;
                if (f(a) * f(mid) < 0)
                    b = mid;
                else
                    a = mid;
            }
            double t = (a + b) / 2; // ������

            // ���������� �����������
            double x = p0.x + t * dir.x;
            double y = p0.y + t * dir.y;
            result.emplace_back(x, y);
            if (result.size() == 2) break; // �������� ��� �����������
        }
        prev = curr;
    }

    return result;
}

void BisectionIntersection::saveToFile(const std::vector<Point>& intersections, double k, double b, Point center, double r) {
    std::ofstream fout("input.txt");
    fout << k << " " << b << "\n";
    fout << center.x << " " << center.y << " " << r << "\n";
    fout << intersections.size() << "\n";
    for (const auto& p : intersections) {
        fout << p.x << " " << p.y << "\n";
    }
    fout.close();
}