//
// Created by Psy.C on 2025/9/13.
//

#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, P1, P2, P3, T1, T2;
    cin >> n >> P1 >> P2 >> P3 >> T1 >> T2;

    vector<pair<int, int>> periods(n);
    for (int i = 0; i < n; i++) cin >> periods[i].first >> periods[i].second;

    long long total_power = 0;
    int last_end_time = 0;

    for (int i = 0; i < n; i++) {
        int start = periods[i].first;
        int end = periods[i].second;

        total_power += (end - start) * P1;

        if (i > 0) {
            int idle_time = start - last_end_time;
            int remainint_time = idle_time;

            int time_in_normal = min(remainint_time, T1);
            total_power += time_in_normal * P1;
            remainint_time -= time_in_normal;

            if (remainint_time > 0) {
                int time_in_screensaver = min(remainint_time, T2);
                total_power += time_in_screensaver * P2;
                remainint_time -= time_in_screensaver;

                if (remainint_time > 0) total_power += remainint_time * P3;
            }
        }
        last_end_time = end;
    }

    cout << total_power << endl;


    return 0;
}