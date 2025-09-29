#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;



/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// Планировщик по минимальному времени до дедлайна
// SRTF - Shortest remaining time first 
class SRTF_Scheduler {
    public:
    SRTF_Scheduler() {
        last_day = 0;
    }

    void add_task(int start, int duration) {
        int end = start + duration;
        tasks.push_back({start, end});
        if (end > last_day) {
            last_day = end;
        }
    }

    int maximum_tasks_in_period() {
        int maximum_tasks_in_period = 0;
        // Создаем временной отрезок, каждый отсчет в котором будет изначально не занят (=flase)
        vector<bool> period(last_day, false);

        // Сортируем по возрастанию дедлайна, для обработки задачь с ближайшим дедлайном в первую очередь
        std::sort(tasks.begin(), tasks.end(), [](const std::pair<int, int>& t1, const std::pair<int, int>& t2) {
            return t1.second < t2.second;
        });

        // Проходимся по задачам 
        for (int idx = 0; auto task : tasks) {
            idx++;
            auto start = period.begin() + task.first;
            auto end = period.begin() + task.second;

            // проверяем, есть ли занятые отрезки на периоде задачи, если есть, пропускаем задачу
            if (find(start, end, true) != end) {
                continue;
            } else { // если период свободен, занимаем его
                fill(start, end, true);
                maximum_tasks_in_period++;
            }
        }

        return maximum_tasks_in_period;
    }

    private:
    vector<pair<int, int>> tasks;
    int last_day;
};

int main()
{
    int n;
    cin >> n; cin.ignore();
    SRTF_Scheduler scheduler;

    for (int i = 0; i < n; i++) {
        int j;
        int d;
        cin >> j >> d; cin.ignore();
        scheduler.add_task(j, d);
    }

    cout << scheduler.maximum_tasks_in_period() << endl;
}