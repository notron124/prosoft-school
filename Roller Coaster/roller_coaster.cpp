#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


long long calculate_earnings(queue<int> &coaster_queue, const int capacity, const int rides_per_day) {
    long long total_earnings = 0;
    
    for (int ride = 0; ride < rides_per_day; ride++) {
        int cap = capacity;
        while (cap > 0) {
            int group = coaster_queue.front();
            cap -= group;
            
            if (cap >= 0) {
                coaster_queue.pop();
                total_earnings += group;
                coaster_queue.push(group);
            }

            cerr << "cap: " << cap << " group: " << group << endl;
        }

    }

    return total_earnings;
}

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