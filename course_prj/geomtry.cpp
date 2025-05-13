#include "geomtry.h"

std::vector<Point> GeoIntersection::intersectLineCircle(Point P0, Point direction, Point center, double radius) {
    std::vector<Point> result;

    // ������ �� ������ � ����� �� ������
    double dx = direction.x;
    double dy = direction.y;

    double fx = P0.x - center.x;
    double fy = P0.y - center.y;

    // ����������� ��������� ������ � ��������� ���������� � �������� ��. ��-� ������������ t:
  // a*t^2 + b*t + c = 0
    double a = dx * dx + dy * dy;  // ����������� ��� t^2.
    double b = 2 * (fx * dx + fy * dy); // ����������� ��� t.
    double c = fx * fx + fy * fy - radius * radius; // ��������� ����.

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        // ��� �����������
        return result;
    }

    double sqrtD = std::sqrt(discriminant);

    // ���� ��� ��� ��������� t (����������� �� ������)
    double t1 = (-b + sqrtD) / (2 * a);
    double t2 = (-b - sqrtD) / (2 * a);

    // ������ �����
    result.push_back({ P0.x + t1 * dx, P0.y + t1 * dy });

    if (discriminant > 0) {
        // ������ �����, ���� �� ���������
        result.push_back({ P0.x + t2 * dx, P0.y + t2 * dy });
    }

    return result;
}

void GeoIntersection::saveToFile(double k, double b, Point center, double radius, const std::vector<Point>& intersections) {
    std::ofstream fout("input.txt");
    fout << k << " " << b << "\n";
    fout << center.x << " " << center.y << " " << radius << "\n";
    fout << intersections.size() << "\n";
    for (const Point& p : intersections) {
        fout << p.x << " " << p.y << "\n";
    }
    fout.close();
}