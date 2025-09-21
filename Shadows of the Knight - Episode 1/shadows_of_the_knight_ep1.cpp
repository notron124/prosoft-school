#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int w; // width of the building.
    int h; // height of the building.
    int end_x, end_y;
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();
    int x1 = 0, x2 = w - 1, y1 = 0, y2 = h - 1;
    /* x1, y1 - нижние границы
       x2, y2 - верхние границы */

    // game loop
    while (1) {
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bomb_dir; cin.ignore();
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // Бомба выше текущей точки, уменьшаем верхнюю границу 
        if (bomb_dir.find("U") != string::npos) {
            y2 = y0 - 1;
        } else if (bomb_dir.find("D") != string::npos) { // Бомба ниже, увеличиваем нижнюю границу
            y1 = y0 + 1;
        }

        // Аналогично с границами слева и справа
        if (bomb_dir.find("L") != string::npos) {
            x2 = x0 - 1;
        } else if (bomb_dir.find("R") != string::npos) {
            x1 = x0 + 1;
        }

        // Каждый раз прыгаем в центр диапазона
        x0 = x1 + (x2 - x1)/2;
        y0 = y1 + (y2 - y1)/2;

        cout << x0 << " " << y0 << endl;         
    }
}