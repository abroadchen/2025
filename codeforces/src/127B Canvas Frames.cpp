//
// Created by Psy.C on 2025/11/18.
//

#include <vector>
#include <iostream>
#include <map>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    int res(0);
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    map<int, int> fr;//键为整数(表示数值)，值为整数(表示该数值出现的频次)
    for (const int& num : v) fr[num]++;
    for (const auto& p : fr) res += p.second / 2;//能组成多少对相同的数字
    cout << res / 2 << '\n';//每对相同数字需要两个才能组成一对
    return 0;
}