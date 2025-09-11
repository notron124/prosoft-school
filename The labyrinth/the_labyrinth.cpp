#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <stack>

using namespace std;

inline const bool IGNORE_CONSOLE = true;

// ��� �������� ����� �� ����� �������� �� ��� ���������� �������
unordered_map<string, string> opposite_steps = {
    {"RIGHT", "LEFT"},
    {"LEFT", "RIGHT"},
    {"UP", "DOWN"},
    {"DOWN", "UP"}
};

// �������� �������
void reverse_queue(queue<string>& q)
{
    stack<string> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}

// ������������ ������������ ������� ��� �������� � ����������
template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
                    std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

// ������� ���������, ����������� ���� �����
// � �������� ���������� � ��������� ����� ������������ '.'
struct cell {
    int x, y;
};

// ������������� hash ��� cell ��� ����������� �������� ������������ � unordered_set
namespace std {
    template <> struct hash<cell> {
        std::size_t operator()(const cell& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 16));
        }
    };
}


// ��������� ��� ��������� cell 
bool operator == (cell a, cell b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (cell a, cell b) {
  return !(a == b);
}

bool operator < (cell a, cell b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

// �������� ���, �������� ����������� ���� �����
string get_step(cell curr, cell next) {
    if (next.x > curr.x) {
        return "RIGHT";
    } else if (next.x < curr.x) {
        return "LEFT";
    } else if (next.y > curr.y) {
        return "DOWN";
    } else {
        return "UP";
    }
}

// �������� �������� ������
vector<cell> neighbors(string *maze, cell current, bool ignore_console = false) {
    vector<cell> possible_steps = {
        {1, 0}, // right
        {-1, 0}, // left
        {0, -1}, // up
        {0, 1} // down
    };

    vector<cell> neighbors;

    for (cell step : possible_steps) {
        cell next_cell = {current.x + step.x, current.y + step.y};
        char next_char = maze[next_cell.y][next_cell.x];
        if (next_char == 'C' && !ignore_console) {
            neighbors.push_back(next_cell);
            continue;
        }
        
        if (next_char == '.' || next_char == 'T') {
            neighbors.push_back(next_cell);
        }
    }

    return neighbors;
}

// �������, ������������ ����������������� "���" �� ������ �� ������
inline int heuristic(cell a, cell b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// ����� ���������� ���� ������-������
void find_shortest_way(string *maze, cell start, cell goal, unordered_map<cell, cell> &came_from, unordered_map<cell, int> &cost_so_far) {
    // ������� ������������ �������, ���� ����� ���������� ������ ��� ���������
    PriorityQueue<cell, int> q;
    q.put(start, 0);
    cost_so_far[start] = 0;

    // ������������ �������� � ������� ������
    while(!q.empty()) {
        // �������� �� ������� �������� �������
        cell curr = q.get();

        // ��������� ����� �� �����, ���� ����� �� ����
        if (curr == goal) {
            break;
        }

        // ������� ��������� ���
        for (cell next : neighbors(maze, curr)) {
            int new_cost = cost_so_far[curr] + 1;
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                int priority = new_cost + heuristic(next, goal);
                came_from[next] = curr;
                q.put(next, priority);
            }
        }
    }
}

void explore_maze(string *maze, cell start, unordered_map<cell, string> &came_from) {
    // ������� ������������ �������, ���� ����� ���������� ������ ��� ���������
    queue<cell> q;
    q.push(start); // ���������� �� � ������� ��� ���������

    // ������������ �������� � ������� ������
    while(!q.empty()) {
        // �������� �� ������� �������� �������
        cell curr = q.front();
        q.pop(); // ������� ��� �� �������

        // ������� ��������� ���
        for (cell next : neighbors(maze, curr, IGNORE_CONSOLE)) {
            if (!came_from.contains(next)) {
                string step = get_step(curr, next);

                came_from[next] = step;
                q.push(next);
            }
        }
    }
}

int main()
{
    int r; // number of rows.
    int c; // number of columns.
    int a; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    cin >> r >> c >> a; cin.ignore();

    cerr << "ROWS: " << r << " COLUMNS: " << c << endl;

    bool maze_explored = false;

    string maze[r];
    queue<string> steps;

    cell console_pos = {
        .x = -1,
        .y = -1,
    };

    cell rick_start_pos = {
        .x = -1,
        .y = -1,
    };

    cell rick_pos = {
        .x = -1,
        .y = -1,
    };

    unordered_map<cell, string> current_path;

    // game loop
    while (1) {

        cell goal;
        unordered_map<cell, cell> came_from;
        unordered_map<cell, string> possible_steps;
        unordered_map<cell, int> cost_so_far;

        int kr; // row where Rick is located.
        int kc; // column where Rick is located.
        cin >> kr >> kc; cin.ignore();
        
   

        if (rick_start_pos.x == -1) {
            rick_start_pos.x = kc;
            rick_start_pos.y = kr;
        }

        rick_pos.x = kc;
        rick_pos.y = kr;

        cerr << "RICK POS: " << rick_pos.x << " " << rick_pos.y << endl;


        for (int i = 0; i < r; i++) {
            string row; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> row; cin.ignore();
            cerr << row << endl;
            maze[i] = row;

            if (console_pos.x == -1) {
                auto x = row.find('C');
                if (x != string::npos) {
                    console_pos.x = x;
                    console_pos.y = i;
                }
            }
        }

        // ������, ���� ������ � ������ �� ��������
        if (!steps.empty()) {
            if (rick_pos != console_pos) {
                cout << steps.front() << endl;
                steps.pop();
                continue;
            } else {
                steps.pop();
            }
        }

        explore_maze(maze, rick_pos, possible_steps);

        // �������
        //for (const auto &[key, value]: possible_steps) {
            //cerr << "This: " << key.x << " " << key.y << " Came from: " << value << endl;
        //}

        // �������� ����������, ��������� ���� �� ������ �������
        if (current_path.size() == possible_steps.size() - 1) {
            maze_explored = true;
            goal.x = console_pos.x;
            goal.y = console_pos.y;
        }

        if (!maze_explored) {
            cell best_step = {
                .x = -1,
                .y = -1,
            };

            // �������� �� ���������� �������� ������ ��� ����
            for (auto next : neighbors(maze, rick_pos, IGNORE_CONSOLE)) {
                cerr << "next: " << next.x << " " << next.y << endl;
                if (current_path.find(next) == current_path.end()) {
                    best_step = next;
                    break;
                }   
            }

            // ���� ������������ �������� ������ ���, �� ������������
            if (best_step.x == -1) {
                cout << current_path[rick_pos] << endl;
            } else {
                // ��������, ��� ��� ������ ��������
                cout << possible_steps[best_step] << endl;
                current_path[best_step] = opposite_steps[possible_steps[best_step]];
            }

            continue;
        }

        // ��������� �� ������, ��������� ���� �� �����
        if (console_pos == rick_pos) {
            goal.x = rick_start_pos.x;
            goal.y = rick_start_pos.y; 
        }

        // ����� ���������� ����
        find_shortest_way(maze, rick_pos, goal, came_from, cost_so_far);

        cell cur = goal;

        // �������
        //for (const auto &[key, value]: came_from) {
            //cerr << "This: " << key.x << " " << key.y << " Came from: " << value.x << " " << value.y << endl;
        //}

        // ��������� ������ ������ � �������� �������
        while (cur != rick_pos) {
            steps.push(get_step(came_from[cur], cur));
            cur = came_from[cur];
        }

        // �������� �������
        reverse_queue(steps);

        // ����� ������� 1 ���, ����� ���� ����� ���������
        cout << steps.front() << endl;
        steps.pop();
    }
}