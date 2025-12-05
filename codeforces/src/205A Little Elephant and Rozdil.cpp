//
// Created by Psy.C on 2025/12/5.
//
/*
*mn = 1e9: 最小值，初始化为很大的数(10亿)
cnt = 0: 计数器，记录最小值出现的次数
t = 0: 计数器，记录处理的元素个数
pos = 0: 位置，记录最小值第一次出现的位置
 *
*t++: 计数器递增
如果当前元素小于已知最小值：
更新最小值为当前元素
重置计数器为1
记录当前位置(加1是因为题目可能要求从1开始计数)
否则如果当前元素等于最小值：
计数器递增
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> dis(n);
    for (auto& i : dis) cin >> i;

    int mn = 1e9, cnt = 0, t = 0, pos = 0;
    for (int i = 0; i < n; ++i) {
        t++;
        if (dis[i] < mn) {
            mn = dis[i];
            cnt = 1;
            pos = i + 1;
        } else if (dis[i] == mn) cnt++;
    }
    if (t == 1) { cout << 1 << '\n'; return 0; }//只有一个元素
    if (cnt == 1) cout << pos << '\n';//最小值只出现一次
    else cout << "Still Rozdil" << '\n';
    return 0;
}