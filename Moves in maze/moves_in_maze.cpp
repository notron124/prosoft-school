#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Создаем структуру, описывающую нашу ячеку
// в качестве индикатора о посещении будем использовать '.'
struct cell {
    int x, y;
};

// Алгоритм - стандартная интерпретация BFS
void trace_maze(string *maze, int width, int height, cell c) {
    // создаем очередь, куда будем складывать ячейки для обработки
    queue<cell> q;
    maze[c.y][c.x] = '0'; // сразу отмечаем стартовую позицию
    q.push(c); // отправляем ее в очередь для обработки

    // обрабатываем попавшие в очередь ячейки
    while(!q.empty()) {
        // забираем из очереди передний элемент
        cell curr = q.front();
        q.pop(); // удаляем его из очереди

        // описываем все возможные шаги в лабиринте
        vector<cell> steps = {{(curr.x + 1)%width, curr.y}, // ограничение по ширине, учитывая ограничения по рамерам такой способ подойдет
                              {(curr.x - 1) >= 0 ? (curr.x - 1) : (width - 1), curr.y},
                              {curr.x, (curr.y - 1) >= 0 ? (curr.y - 1) : (height - 1)}, // ограничения по высоте
                              {curr.x, (curr.y + 1)%height}}; 

        // пробуем совершить шаг
        for (cell step : steps) {
            // если ячейка доступна для шага
            if (maze[step.y][step.x] == '.') {
                // отмечаем номер шага
                maze[step.y][step.x] = maze[curr.y][curr.x] + 1;
                if (maze[curr.y][curr.x] == '9') {
                    maze[step.y][step.x] = 'A';
                }
                // отправляем эту ячейку в очередь для обработки
                q.push(step);
            }
        }
    }
}

int main()
{
    int w, h;
    cell start = {
        .x = -1,
        .y = -1,
    };
    cin >> w >> h; cin.ignore();
    string maze[h];
    // читаем
    for (int i = 0; i < h; i++) {
        getline(cin, maze[i]);
        // сразу находим стартовую позицию 
        if (start.x < 0) {
            auto startX = maze[i].find('S');
            if (startX != string::npos) {
                start.x = startX;
                start.y = i;
            }
        }
    }

    // обходим лабиринт
    trace_maze(maze, w, h, start);
    for (int i = 0; i < h; i++) {
        cout << maze[i] << endl;
    }
}