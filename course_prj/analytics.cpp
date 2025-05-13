#include "analytics.h"

std::vector<Point> Analytics::intersectLineCircle(double k, double b,
    double cx, double cy, double r) {
    std::vector<Point> result;

    // Прямая: y = kx + b
    // Окружность: (x - cx)^2 + (y - cy)^2 = r^2

    // Подставляем y = kx + b в уравнение окружности:
    // Получаем квадратное уравнение: Ax^2 + Bx + C = 0
    double A = 1 + k * k;
    double B = 2 * (k * (b - cy) - cx);
    double C = cx * cx + (b - cy) * (b - cy) - r * r;

    double D = B * B - 4 * A * C;

    if (D < 0) {
        // Нет пересечений
        return result;
    }
    else if (D == 0) {
        // Одно касание
        double x = -B / (2 * A);
        double y = k * x + b;
        result.push_back({ x, y });
    }
    else {
        // Два пересечения
        double sqrtD = std::sqrt(D);
        double x1 = (-B + sqrtD) / (2 * A);
        double y1 = k * x1 + b;

        double x2 = (-B - sqrtD) / (2 * A);
        double y2 = k * x2 + b;

        result.push_back({ x1, y1 });
        result.push_back({ x2, y2 });
    }

    return result;
}