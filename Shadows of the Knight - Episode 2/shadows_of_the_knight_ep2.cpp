#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 // Функция для аналитического определения следующих границ
 // Основана на геометрических неравенствах и не является "правильным" решением данной задачи
tuple<int, int, int, int> get_new_borders(int x0, int y0, int x, int y, int min_x, int max_x, int min_y, int max_y, const string_view info) {
    cerr << "narrow: x0=" << x0 << ", y0=" << y0 << ", x=" << x << ", y=" << y << ", info=" << info << endl;
    if (min_x != max_x) {
        if (info == "UNKNOWN") {
            // Ничего не делаем
        } else if (info == "SAME") {
            int mid = (x0 + x) / 2;
            if ((x0 + x) % 2 == 0 && min_x <= mid && mid <= max_x) {
                min_x = max_x = mid;
            } else {
                min_x = max(min_x, mid);
                max_x = min(max_x, mid + 1);
            }
        } else if (info == "WARMER") {
            double mid = (x0 + x) / 2.0;
            if (x > x0) {
                min_x = max(min_x, static_cast<int>(ceil(mid)));
            } else {
                max_x = min(max_x, static_cast<int>(floor(mid)));
            }
        } else { // COLDER
            double mid = (x0 + x) / 2.0;
            if (x > x0) {
                max_x = min(max_x, static_cast<int>(floor(mid)));
            } else {
                min_x = max(min_x, static_cast<int>(ceil(mid)));
            }
        }
    } else {
        if (info == "UNKNOWN") {
            // Ничего не делаем
        } else if (info == "SAME") {
            int mid = (y0 + y) / 2;
            if ((y0 + y) % 2 == 0 && min_y <= mid && mid <= max_y) {
                min_y = max_y = mid;
            } else {
                min_y = max(min_y, mid);
                max_y = min(max_y, mid + 1);
            }
        } else if (info == "WARMER") {
            double mid = (y0 + y) / 2.0;
            if (y > y0) {
                min_y = max(min_y, static_cast<int>(ceil(mid)));
            } else {
                max_y = min(max_y, static_cast<int>(floor(mid)));
            }
        } else { // COLDER
            double mid = (y0 + y) / 2.0;
            if (y > y0) {
                max_y = min(max_y, static_cast<int>(floor(mid)));
            } else {
                min_y = max(min_y, static_cast<int>(ceil(mid)));
            }
        }
    }
    cerr << "min_x=" << min_x << ", max_x=" << max_x << ", min_y=" << min_y << ", max_y=" << max_y << endl;
    return {min_x, max_x, min_y, max_y};
}

int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();

    int min_x = 0, max_x = w - 1;
    int min_y = 0, max_y = h - 1;
    int next_x = x0;
    int next_y = y0;

    // game loop
    while (1) {
        string bomb_dir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bomb_dir; cin.ignore();

        auto [new_min_x, new_max_x, new_min_y, new_max_y] = get_new_borders(x0, y0, next_x, next_y, min_x, max_x, min_y, max_y, bomb_dir);
        min_x = new_min_x;
        max_x = new_max_x;
        min_y = new_min_y; 
        max_y = new_max_y;

        x0 = next_x;
        y0 = next_y;

        // Выбор наиболее оптимального деления плоскости по 1 оси
        if (min_x != max_x) {
            if (x0 == 0 && max_x - min_x + 1 != w) {
                next_x = (min_x + max_x) / 2;
            } else if (x0 == w - 1 && max_x - min_x + 1 != w) {
                next_x = (min_x + max_x) / 2 - x0;
            } else {
                next_x = min_x + max_x - x0;
            }
            if (next_x == x0) {
                next_x += 1;
            }
            next_x = min(max(next_x, 0), w - 1);
        } else {
            if (next_x != min_x) {
                next_x = x0 = min_x;
                cout << next_x << " " << next_y << endl;
                continue;
            }
            if (min_y == max_y) {
                next_y = min_y;
            } else {
                if (y0 == 0 && max_y - min_y + 1 != h) {
                    next_y = (min_y + max_y) / 2;
                } else if (y0 == h - 1 && max_y - min_y + 1 != h) {
                    next_y = (min_y + max_y) / 2 - y0;
                } else {
                    next_y = min_y + max_y - y0;
                }
                next_y = min(max(next_y, 0), h - 1);
            }
        }
        cout << next_x << " " << next_y << endl;  
    }
}