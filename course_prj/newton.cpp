#include "newton.h"

Newton::Newton(Point line_point, Point direction, Point circle_center, double r)
    : line_point(line_point), direction(direction), circle_center(circle_center), r(r) {
}

// ����� ��� ���������� ����������� � �������������� �������������� �������
std::vector<Point> Newton::solve() {
    std::vector<Point> intersections;

    double k = direction.y / direction.x;  // ����� ������
    double b = line_point.y - k * line_point.x;  // �������� ������

    // ����������� ��������� ������ � ��������� ����������
    double A = 1 + k * k;
    double B = 2 * (k * (b - circle_center.y) - circle_center.x);
    double C = (circle_center.x * circle_center.x + (b - circle_center.y) * (b - circle_center.y)) - r * r;

    // ������� ������������
    double discriminant = B * B - 4 * A * C;

    if (discriminant < 0) {
        return intersections;  // ��� �����������
    }

    // ������� �����
    double x1 = (-B - sqrt(discriminant)) / (2 * A);
    double x2 = (-B + sqrt(discriminant)) / (2 * A);

    // ������� y ��� ������� x
    double y1 = k * x1 + b;
    double y2 = k * x2 + b;

    intersections.push_back(Point(x1, y1));
    intersections.push_back(Point(x2, y2));

    // ������ ������� ����� ����������� � ������� ������ �������
    const int max_iterations = 1000;
    const double epsilon = 1e-6;

    for (auto& pt : intersections) {
        double x = pt.x;
        double y = pt.y;

        // ��������� ����� ������� ��� ��������� �������
        for (int i = 0; i < max_iterations; ++i) {
            // ��������� f(x) � f'(x)
            double f = (x - circle_center.x) * (x - circle_center.x) + (y - circle_center.y) * (y - circle_center.y) - r * r;
            double f_prime = 2 * (x - circle_center.x) + 2 * (y - circle_center.y) * (direction.y / direction.x);

            // ���� ����������� ������� ����, ����������
            if (std::fabs(f_prime) < epsilon) {
                break;
            }

            // ��������� x � �������������� ������ �������
            x -= f / f_prime;
            y = direction.y / direction.x * (x - line_point.x) + line_point.y;  // ��������� y

            // ��������� ����� ����� �����������
            f = (x - circle_center.x) * (x - circle_center.x) + (y - circle_center.y) * (y - circle_center.y) - r * r;
            if (std::fabs(f) < epsilon) {
                pt = Point(x, y);  // ��������� ����� �����������
                break;
            }
        }
    }

    return intersections;
}

// ����� ��� ������ ������ � ����
void Newton::saveToFile(const std::vector<Point>& intersections, double k, double b, Point circle_center, double r) {
    std::ofstream fout("input.txt");

    // ���������� ��������� ������
    fout << k << " " << b << "\n";

    // ���������� ��������� ����������
    fout << circle_center.x << " " << circle_center.y << " " << r << "\n";

    // ���������� ���������� ����� �����������
    fout << intersections.size() << "\n";

    // ���������� ���������� ����� �����������
    for (const auto& pt : intersections) {
        fout << pt.x << " " << pt.y << "\n";
    }

    fout.close();
}