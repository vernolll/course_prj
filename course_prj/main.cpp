#include <iostream>
#include <windows.h>
#include <fstream>

#include "analytics.h"
#include "bisection.h"
#include "chord.h"
#include "geomtry.h"
#include "newton.h"
#include "scanning__line.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "КУРСОВОЙ ПРОЕКТ НА ТЕМУ: \"ПЕРЕСЕЧЕНИЕ ГЕОМЕТРИЧЕСКИХ ОБЪЕКТОВ\"" << std::endl;

    bool running = true;
    int choice = 0;

    while (running)
    {
        std::cout << "\nМеню" << std::endl;
        std::cout << "1. Аналитический метод" << std::endl;
        std::cout << "2. Геометрический подход" << std::endl;
        std::cout << "3. Метод Ньютона" << std::endl;
        std::cout << "4. Метод хорд" << std::endl;
        std::cout << "5. Метод сканирующей прямой" << std::endl;
        std::cout << "6. Метод бисекций" << std::endl;
        std::cout << "7. Выход" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            double k, b, cx, cy, r;

            std::cout << "Введите коэффициенты прямой (k и b): ";
            std::cin >> k >> b;

            std::cout << "Введите координаты центра окружности (cx, cy): ";
            std::cin >> cx >> cy;

            std::cout << "Введите радиус окружности: ";
            std::cin >> r;

            std::vector<Point> intersections = Analytics::intersectLineCircle(k, b, cx, cy, r);

            if (intersections.empty()) {
                std::cout << "Пересечений нет.\n";
            }
            else {
                std::cout << "Точки пересечения:\n";
                for (size_t i = 0; i < intersections.size(); ++i) {
                    std::cout << " (" << intersections[i].x << ", " << intersections[i].y << ")\n";
                }
            }

            std::ofstream fout("input.txt");
            fout << k << " " << b << "\n";
            fout << cx << " " << cy << " " << r << "\n";
            fout << intersections.size() << "\n";
            for (const Point& p : intersections) {
                fout << p.x << " " << p.y << "\n";
            }
            fout.close();

            system("python draw_line_circle.py");

            break;
        }
        case 2:
        {
            Point line_point, direction, circle_center;
            double r;

            std::cout << "Введите точку на прямой (x0 y0): ";
            std::cin >> line_point.x >> line_point.y;

            std::cout << "Введите вектор направления прямой (dx dy): ";
            std::cin >> direction.x >> direction.y;

            std::cout << "Введите центр окружности (cx cy): ";
            std::cin >> circle_center.x >> circle_center.y;

            std::cout << "Введите радиус окружности: ";
            std::cin >> r;

            std::vector<Point> pts = GeoIntersection::intersectLineCircle(line_point, direction, circle_center, r);

            if (pts.empty()) {
                std::cout << "Пересечений нет.\n";
            }
            else {
                std::cout << "Точки пересечения:\n";
                for (const auto& p : pts)
                    std::cout << " (" << p.x << ", " << p.y << ")\n";
            }

            // Вычисляем k и b из направления
            if (direction.x == 0) {
                std::cerr << "Вертикальная прямая: отрисовка невозможна (нужна доработка скрипта).\n";
            }
            else {
                double k = direction.y / direction.x;
                double b = line_point.y - k * line_point.x;

                GeoIntersection::saveToFile(k, b, circle_center, r, pts);

                system("python draw_line_circle.py");
            }

            break;
        }

        case 3:
        {
            Point line_point, direction, circle_center;
            double r;

            // Ввод точки на прямой
            std::cout << "Введите точку на прямой (x0 y0): ";
            std::cin >> line_point.x >> line_point.y;

            // Ввод вектора направления
            std::cout << "Введите вектор направления прямой (dx dy): ";
            std::cin >> direction.x >> direction.y;

            // Ввод центра окружности и радиуса
            std::cout << "Введите центр окружности (cx cy): ";
            std::cin >> circle_center.x >> circle_center.y;

            std::cout << "Введите радиус окружности: ";
            std::cin >> r;

            // Создаем объект класса Newton и решаем задачу
            try {
                Newton newton(line_point, direction, circle_center, r);
                std::vector<Point> intersections = newton.solve();

                // Сохраняем результаты в файл
                Newton::saveToFile(intersections, direction.y / direction.x, line_point.y - direction.y / direction.x * line_point.x, circle_center, r);

                // Выводим точки пересечения
                std::cout << "Точки пересечения:\n";
                for (const auto& p : intersections) {
                    std::cout << "(" << p.x << ", " << p.y << ")\n";
                }

                system("python draw_line_circle.py");
            }
            catch (const std::exception& ex) {
                std::cout << "Ошибка: " << ex.what() << "\n";
            }

            break;
        }
        case 4:
        {
            Point line_point, direction, circle_center;
            double r;

            std::cout << "Введите точку на прямой (x0 y0): ";
            std::cin >> line_point.x >> line_point.y;

            std::cout << "Введите вектор направления прямой (dx dy): ";
            std::cin >> direction.x >> direction.y;

            std::cout << "Введите центр окружности (cx cy): ";
            std::cin >> circle_center.x >> circle_center.y;

            std::cout << "Введите радиус окружности: ";
            std::cin >> r;

            double k = direction.y / direction.x;
            double b = line_point.y - k * line_point.x;

            Secant secant(line_point, direction, circle_center, r);
            std::vector<Point> intersections = secant.solve();

            std::cout << "Найдено пересечений: " << intersections.size() << "\n";
            for (const auto& p : intersections)
                std::cout << "(" << p.x << ", " << p.y << ")\n";

            Secant::saveToFile(intersections, k, b, circle_center, r);

            system("python draw_line_circle.py");
            break;
        }
        case 5:
        {
            Point line_point, direction, circle_center;
            double r;

            std::cout << "Введите точку на прямой (x0 y0): ";
            std::cin >> line_point.x >> line_point.y;

            std::cout << "Введите вектор направления прямой (dx dy): ";
            std::cin >> direction.x >> direction.y;

            std::cout << "Введите центр окружности (cx cy): ";
            std::cin >> circle_center.x >> circle_center.y;

            std::cout << "Введите радиус окружности: ";
            std::cin >> r;

            double k = direction.y / direction.x;
            double b = line_point.y - k * line_point.x;

            SweepLine sl(line_point, direction, circle_center, r);
            std::vector<Point> result = sl.findIntersections();

            std::cout << "Найдено пересечений: " << result.size() << "\n";
            for (const auto& p : result) {
                std::cout << "(" << p.x << ", " << p.y << ")\n";
            }

            SweepLine::saveToFile(result, k, b, circle_center, r);

            system("python draw_line_circle.py");
            break;
        }
        case 6:
        {
            Point line_point, direction, circle_center;
            double r;

            std::cout << "Введите точку на прямой (x0 y0): ";
            std::cin >> line_point.x >> line_point.y;

            std::cout << "Введите вектор направления прямой (dx dy): ";
            std::cin >> direction.x >> direction.y;

            std::cout << "Введите центр окружности (cx cy): ";
            std::cin >> circle_center.x >> circle_center.y;

            std::cout << "Введите радиус окружности: ";
            std::cin >> r;

            double k = direction.y / direction.x;
            double b = line_point.y - k * line_point.x;

            BisectionIntersection solver(line_point, direction, circle_center, r);
            std::vector<Point> intersections = solver.findIntersections();

            std::cout << "Точки пересечения:\n";
            for (const auto& p : intersections)
                std::cout << "(" << p.x << ", " << p.y << ")\n";

            BisectionIntersection::saveToFile(intersections, k, b, circle_center, r);

            system("python draw_line_circle.py");
            break;
        }
        case 7:
        {
            std::cout << "Завершение программы..." << std::endl;
            running = false;
            break;
        }
        default:
            std::cout << "Неверный ввод." << std::endl;
            break;
        }
    }

    return 0;
}
