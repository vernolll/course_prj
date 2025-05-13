#include "scanning__line.h"



SweepLine::SweepLine(Point line_point, Point direction, Point circle_center, double r)
    : p0(line_point), dir(direction), center(circle_center), radius(r) {
}

std::vector<Point> SweepLine::findIntersections() {
    std::vector<Point> intersections;

    // Прямая: y = kx + b
    double k = dir.y / dir.x;
    double b = p0.y - k * p0.x;

     // Окружность: (x - cx)^2 + (y - cy)^2 = r^2
    double cx = center.x;
    double cy = center.y;

    // Определим диапазон x, в котором потенциально возможны пересечения
    double startX = cx - radius;
     double endX = cx + radius;

    // Используем set для "событий" (x-координат)
    std::set<double> sweepPoints = { startX, endX };

    // Попробуем найти корни уравнения пересечения
    // Подставим y = kx + b в уравнение окружности:
    // (x - cx)^2 + (kx + b - cy)^2 = r^2
    // Решаем это как квадратное уравнение

    double A = 1 + k * k;
    double B = 2 * (k * (b - cy) - cx);
    double C = cx * cx + (b - cy) * (b - cy) - radius * radius;

    double D = B * B - 4 * A * C;

    if (D < 0)
        return intersections;  // нет пересечений

    double sqrtD = std::sqrt(D);
    double x1 = (-B - sqrtD) / (2 * A);
    double x2 = (-B + sqrtD) / (2 * A);

    for (double x : {x1, x2}) {
        double y = k * x + b;
        intersections.emplace_back(x, y);
    }

    return intersections;
}

void SweepLine::saveToFile(const std::vector<Point>& intersections, double k, double b, Point center, double r) {
    std::ofstream fout("input.txt");
    fout << k << " " << b << "\n";
    fout << center.x << " " << center.y << " " << r << "\n";
    fout << intersections.size() << "\n";
    for (const auto& p : intersections) {
    fout << p.x << " " << p.y << "\n";
    }
    fout.close();
}
