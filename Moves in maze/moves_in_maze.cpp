#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// ������� ���������, ����������� ���� �����
// � �������� ���������� � ��������� ����� ������������ '.'
struct cell {
    int x, y;
};

// �������� - ����������� ������������� BFS
void trace_maze(string *maze, int width, int height, cell c) {
    // ������� �������, ���� ����� ���������� ������ ��� ���������
    queue<cell> q;
    maze[c.y][c.x] = '0'; // ����� �������� ��������� �������
    q.push(c); // ���������� �� � ������� ��� ���������

    // ������������ �������� � ������� ������
    while(!q.empty()) {
        // �������� �� ������� �������� �������
        cell curr = q.front();
        q.pop(); // ������� ��� �� �������

        // ��������� ��� ��������� ���� � ���������
        vector<cell> steps = {{(curr.x + 1)%width, curr.y}, // ����������� �� ������, �������� ����������� �� ������� ����� ������ ��������
                              {(curr.x - 1) >= 0 ? (curr.x - 1) : (width - 1), curr.y},
                              {curr.x, (curr.y - 1) >= 0 ? (curr.y - 1) : (height - 1)}, // ����������� �� ������
                              {curr.x, (curr.y + 1)%height}}; 

        // ������� ��������� ���
        for (cell step : steps) {
            // ���� ������ �������� ��� ����
            if (maze[step.y][step.x] == '.') {
                // �������� ����� ����
                maze[step.y][step.x] = maze[curr.y][curr.x] + 1;
                if (maze[curr.y][curr.x] == '9') {
                    maze[step.y][step.x] = 'A';
                }
                // ���������� ��� ������ � ������� ��� ���������
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
    // ������
    for (int i = 0; i < h; i++) {
        getline(cin, maze[i]);
        // ����� ������� ��������� ������� 
        if (start.x < 0) {
            auto startX = maze[i].find('S');
            if (startX != string::npos) {
                start.x = startX;
                start.y = i;
            }
        }
    }

    // ������� ��������
    trace_maze(maze, w, h, start);
    for (int i = 0; i < h; i++) {
        cout << maze[i] << endl;
    }
}