import matplotlib.pyplot as plt
import numpy as np

def draw(k, b, cx, cy, r, intersections):
    fig, ax = plt.subplots()

    # Окружность
    circle = plt.Circle((cx, cy), r, color='blue', fill=False, linewidth=2)
    ax.add_patch(circle)

    # Прямая
    x_vals = np.linspace(cx - r - 5, cx + r + 5, 1000)
    y_vals = k * x_vals + b
    ax.plot(x_vals, y_vals, label="Прямая", color='green')

    # Точки пересечения
    if intersections:
        for pt in intersections:
            ax.plot(pt[0], pt[1], 'ro')
            ax.text(pt[0], pt[1], f'({pt[0]:.2f}, {pt[1]:.2f})', fontsize=9, ha='left', va='bottom')

    # Выставление границ и пропорций
    padding = r + 5
    ax.set_xlim(cx - padding, cx + padding)
    ax.set_ylim(cy - padding, cy + padding)
    ax.set_aspect('equal', adjustable='box')

    ax.grid(True)
    ax.set_title("Пересечение прямой и окружности")
    ax.legend()
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.show()


if __name__ == "__main__":
    # Чтение из файла
    with open("input.txt", "r") as fin:
        k, b = map(float, fin.readline().split())
        cx, cy, r = map(float, fin.readline().split())
        n = int(fin.readline())
        intersections = [tuple(map(float, fin.readline().split())) for _ in range(n)]

    draw(k, b, cx, cy, r, intersections)
