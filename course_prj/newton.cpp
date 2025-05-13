#include "newton.h"

Newton::Newton(Point line_point, Point direction, Point circle_center, double r)
    : line_point(line_point), direction(direction), circle_center(circle_center), r(r) {
}

// Метод для вычисления пересечений с использованием аналитического решения
std::vector<Point> Newton::solve() {
    std::vector<Point> intersections;

    double k = direction.y / direction.x;  // Уклон прямой
    double b = line_point.y - k * line_point.x;  // Смещение прямой

    // Подставляем уравнение прямой в уравнение окружности
    double A = 1 + k * k;
    double B = 2 * (k * (b - circle_center.y) - circle_center.x);
    double C = (circle_center.x * circle_center.x + (b - circle_center.y) * (b - circle_center.y)) - r * r;

    // Находим дискриминант
    double discriminant = B * B - 4 * A * C;

    if (discriminant < 0) {
        return intersections;  // Нет пересечений
    }

    // Находим корни
    double x1 = (-B - sqrt(discriminant)) / (2 * A);
    double x2 = (-B + sqrt(discriminant)) / (2 * A);

    // Находим y для каждого x
    double y1 = k * x1 + b;
    double y2 = k * x2 + b;

    intersections.push_back(Point(x1, y1));
    intersections.push_back(Point(x2, y2));

    // Теперь уточним точки пересечения с помощью метода Ньютона
    const int max_iterations = 1000;
    const double epsilon = 1e-6;

    for (auto& pt : intersections) {
        double x = pt.x;
        double y = pt.y;

        // Применяем метод Ньютона для уточнения решения
        for (int i = 0; i < max_iterations; ++i) {
            // Вычисляем f(x) и f'(x)
            double f = (x - circle_center.x) * (x - circle_center.x) + (y - circle_center.y) * (y - circle_center.y) - r * r;
            double f_prime = 2 * (x - circle_center.x) + 2 * (y - circle_center.y) * (direction.y / direction.x);

            // Если производная слишком мала, прекращаем
            if (std::fabs(f_prime) < epsilon) {
                break;
            }

            // Обновляем x с использованием метода Ньютона
            x -= f / f_prime;
            y = direction.y / direction.x * (x - line_point.x) + line_point.y;  // Обновляем y

            // Вычисляем новую точку пересечения
            f = (x - circle_center.x) * (x - circle_center.x) + (y - circle_center.y) * (y - circle_center.y) - r * r;
            if (std::fabs(f) < epsilon) {
                pt = Point(x, y);  // Обновляем точку пересечения
                break;
            }
        }
    }

    return intersections;
}

// Метод для записи данных в файл
void Newton::saveToFile(const std::vector<Point>& intersections, double k, double b, Point circle_center, double r) {
    std::ofstream fout("input.txt");

    // Записываем параметры прямой
    fout << k << " " << b << "\n";

    // Записываем параметры окружности
    fout << circle_center.x << " " << circle_center.y << " " << r << "\n";

    // Записываем количество точек пересечения
    fout << intersections.size() << "\n";

    // Записываем координаты точек пересечения
    for (const auto& pt : intersections) {
        fout << pt.x << " " << pt.y << "\n";
    }

    fout.close();
}