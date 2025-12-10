//
// Created by Psy.C on 2025/12/9.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 50;

int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j)//遍历字符串的每个字符，将其转换为数字
            a[i][j] = s[j] - '0';
    }
    int n2, m2; cin >> n2 >> m2;
    vector<vector<int>> b(n2, vector<int>(m2));
    for (int i = 0; i < n2; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m2; ++j)
            b[i][j] = s[j] - '0';
    }
    ll ans = -1;//最大的匹配值
    pair<int, int> p;//最优偏移量(x, y)
    for (int x = -N; x <= N; ++x) {
        for (int y = -N; y <= N; ++y) {
            ll cur = 0;//当前偏移量下的匹配值
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (i + x >= 0 && i + x < n2 && j + y >= 0 && j + y < m2)
                        cur += a[i][j] * b[i + x][j + y];
                }
            }
            if (cur > ans) p = {x, y};
            ans = max(ans, cur);
        }
    }
    cout << p.first << ' ' << p.second << '\n';
    return 0;
}