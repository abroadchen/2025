//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin>>t;
    while (t--) {
        long long n, m, x1, y1, x2, y2;
        cin >> n >> m >> x1 >> y1 >> x2 >> y2;

        long long dx = x2 - x1, dy = y2 - y1;
        long long min1_i = max(1LL, 1LL - dx);
        long long max1_i = min(n, n - dx);
        long long min1_j = max(1LL, 1LL - dy);
        long long max1_j = min(m, m - dy);

        long long count1 = max(0LL, max1_i - min1_i + 1) * max(0LL, max1_j - min1_j + 1);

        long long min2_i = max(1LL, 1LL + dx);
        long long max2_i = min(n, n + dx);
        long long min2_j = max(1LL, 1LL + dy);
        long long max2_j = min(m, m + dy);

        long long count2 = max(0LL, max2_i - min2_i + 1) * max(0LL, max2_j - min2_j + 1);

        long long inter_x_min = max(min1_i, min2_i);
        long long inter_x_max = min(max1_i, max2_i);
        long long inter_y_min = max(min1_j, min2_j);
        long long inter_y_max = min(max1_j, max2_j);

        long long intersection = max(0LL, inter_x_max - inter_x_min + 1) * max(0LL, inter_y_max - inter_y_min + 1);

        long long reachable = count1 + count2 - intersection;
        long long unreachable = n * m - reachable;
        cout << unreachable << "\n";
    }
    
    return 0;
}