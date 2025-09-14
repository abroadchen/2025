//
// Created by Psy.C on 2025/9/13.
//

#include <ios>
#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n; cin >> n;
    queue<long long> q; q.push(1);

    int count = 0;
    while (!q.empty()) {
        long long current = q.front(); q.pop();
        if (current > n) break;
        count++;

        q.push(current * 10);
        q.push(current * 10 + 1);
    }

    cout << count << endl;
    
    return 0;
}