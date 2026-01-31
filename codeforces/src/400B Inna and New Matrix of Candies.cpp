//
// Created by Psy.C on 2026/1/31.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
using namespace std;


int main() {
    fast;
    int n, m, c = 0; cin >> n >> m;
    char str[N]; bool flag = true;//是否满足条件
    for (int i = 0, v[N]={}; i < n; ++i) {//统计不同差值出现次数
        cin >> str;
        int p = -1, q = -1;
        for (int j = 0; j < m; ++j) {//遍历当前行的每个字符
            if (str[j] == 'G') q = j;
            if (str[j] == 'S') p = j;
            if (p >= 0 && q >= 0) break;
        }
        if (const int k = p - q; k < 0) flag = false; else {
            if (v[k] == 0) c++;//v[k]是第一次出现  统计不同的距离差
            v[k]++;//统计该距离差出现的次数
        }
    }
    cout << (flag ? c : -1) << '\n';
    return 0;
}