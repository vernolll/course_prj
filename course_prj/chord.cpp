#include "chord.h"

Secant::Secant(Point line_point, Point direction, Point circle_center, double r)
    : line_point(line_point), direction(direction), circle_center(circle_center), r(r) {
}

std::vector<Point> Secant::solve() {
    std::vector<Point> intersections;

    const double epsilon = 1e-6;
    const int max_iter = 1000;

    // ѕр€ма€: y = kx + b
    double k = direction.y / direction.x;
    double b = line_point.y - k * line_point.x;

    // f(x) = (x - cx)^2 + (kx + b - cy)^2 - r^2
    auto f = [&](double x) {
        double y = k * x + b;
        return (x - circle_center.x) * (x - circle_center.x) +
            (y - circle_center.y) * (y - circle_center.y) - r * r;
        };

    // ѕопробуем найти два корн€ с разных стартов (лева€ и права€ границы)
    double a1 = circle_center.x - r - 5;
    double a2 = circle_center.x + r + 5;

    double x0 = a1, x1 = a2;
    for (int i = 0; i < max_iter; ++i) {
        double fx0 = f(x0);
        double fx1 = f(x1);
        // ≈сли разница мала, то последовательность сошлась
        if (std::fabs(fx1 - fx0) < epsilon) break;

        // —ледующее приближение
        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        if (std::fabs(f(x2)) < epsilon) { // ≈сли близко к 0, значит это корень
            double y2 = k * x2 + b;
            intersections.push_back(Point(x2, y2));
            break;
        }
        x0 = x1;
        x1 = x2;
    }

    // ѕытаемс€ найти второй корень на другом интервале (в обратном направлении)
    x0 = a2; x1 = a1;
    for (int i = 0; i < max_iter; ++i) {
        double fx0 = f(x0);
        double fx1 = f(x1);
        if (std::fabs(fx1 - fx0) < epsilon) break;

        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        if (std::fabs(f(x2)) < epsilon) {
            double y2 = k * x2 + b;
            Point pt(x2, y2);

            // ѕроверим, не записали ли мы уже эту точку
            bool duplicate = false;
            for (const auto& p : intersections) {
                if (std::fabs(p.x - pt.x) < epsilon && std::fabs(p.y - pt.y) < epsilon) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate)
                intersections.push_back(pt);
            break;
        }
        x0 = x1;
        x1 = x2;
    }

    return intersections;
}

void Secant::saveToFile(const std::vector<Point>& intersections, double k, double b, Point circle_center, double r) {
    std::ofstream fout("input.txt");

    fout << k << " " << b << "\n";
    fout << circle_center.x << " " << circle_center.y << " " << r << "\n";
    fout << intersections.size() << "\n";
    for (const auto& pt : intersections) {
        fout << pt.x << " " << pt.y << "\n";
    }

    fout.close();
}

