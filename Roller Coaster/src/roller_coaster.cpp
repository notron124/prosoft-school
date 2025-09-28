#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// Определяем метод хеша для std:vercotr<int>, чтобы можно было использовать его в качестве ключа в unordered_map
namespace std {
    struct vector_hash {
        std::size_t operator()(const std::vector<int>& v) const {
            std::size_t seed = v.size();
            for (int i : v) {
                // 0x9e3779b9 - константа, связанная с золотым сечением
                seed ^= std::hash<int>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

long long calculate_earnings(queue<int> &coaster_queue, const int capacity, const int rides_per_day) {
    long long total_earnings = 0;
    long long earnings_per_ride = 0;
    const int queue_size = coaster_queue.size();
    int group_cntr = 0;
    int total_group_cntr = 0;
    int cap = 0;

    int rides_earnings_prev_size = 0;
    unordered_map<vector<int>, int, vector_hash> group_rides;
    bool is_cycle_established = false;
    bool track_queues = true;
    int rides_to_simulate = 0;

    
    for (int ride = rides_per_day; ride > 0; ride--) {
        vector<int> current_ride_queue;
        cap = capacity;
        earnings_per_ride = 0;
        group_cntr = 0;

        if (is_cycle_established && rides_to_simulate > 0) { // если замечен цикл, завершаем текущий до конца
            rides_to_simulate--;
        } else if (is_cycle_established && total_group_cntr >= queue_size) { // Даем время алгоритму хотя бы раз полностью пройти 1 группу, иначе возможны сработки на неполные данные
            long long cyclic_earnings = 0;
            int cyclic_groups_cntr = 0;
            for (const auto &[q, v] : group_rides) {
                if (v >= 2) {
                    cyclic_groups_cntr++;
                    for (int gr : q) {
                        cyclic_earnings += gr;
                    }
                }
            }

            if (cyclic_groups_cntr > 0) {
                total_earnings += (ride / cyclic_groups_cntr) * cyclic_earnings;
                ride = ride % cyclic_groups_cntr;
                if (ride == 0) {
                    return total_earnings;
                }
                is_cycle_established = false;
                track_queues = false;
            }
        }

        // пытаемся заполнить весь аттракицон
        while (cap > 0) {
            int group = coaster_queue.front();
            cap -= group;
            group_cntr++;

            if (cap >= 0) {
                current_ride_queue.push_back(group);
                coaster_queue.pop();
                earnings_per_ride += group;
                coaster_queue.push(group);
            }

            // Больше никого нет в очереди
            if (group_cntr >= queue_size) {
                break;
            }
        }

        
        total_group_cntr += group_cntr;

        // В случае, если вся очередь влезает на аттракцион, просто возвращаем поездки умноженные на выручку с одной поездки
        if (group_cntr >= queue_size) {
            return earnings_per_ride * ride;
        } else {
            total_earnings += earnings_per_ride;
        }

        if (!track_queues) {
            continue;
        }

        group_rides[current_ride_queue]++;
        
        int curr_re_size = group_rides.size();

        if (curr_re_size > rides_earnings_prev_size) {
            rides_earnings_prev_size = curr_re_size;
        } else if (!is_cycle_established){
            is_cycle_established = true;
            rides_to_simulate = curr_re_size;
        }
    }

    return total_earnings;
}

// BUILD_TEST определяется при сборке с помощью CMake, #ifndef нужен для избежания ошибки с множественными main
#ifndef BUILD_TESTS
int main()
{
    queue<int> coaster_queue;
    int l;
    int c;
    int n;
    cin >> l >> c >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi; cin.ignore();
        coaster_queue.push(pi);

    }

    long long total_earnings = calculate_earnings(coaster_queue, l, c);

    cout << total_earnings << endl;
}
#endif