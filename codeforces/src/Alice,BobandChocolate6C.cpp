//
// Created by Psy.C on 2025/9/11.
//


#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector<int> times(n);
    for (int i = 0; i < n; i++) cin >> times[i];

    int alice_bars = 0;
    int bob_bars = 0;
    long long alice_time = 0;
    long long bob_time = 0;

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        if (alice_time + times[left] <= bob_time + times[right]) {
            alice_time += times[left];
            alice_bars++;
            left++;
        } else {
            bob_time += times[right];
            bob_bars++;
            right--;
        }
    }
    cout << alice_bars << " " << bob_bars << endl;

    return 0;
}