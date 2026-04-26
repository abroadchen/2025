//
// Created by Psy.C on 2026/4/25.
//
/**
读取起始位置s和持续时间d
计算结束时间e = s + d - 1（包含起始时刻，所以减1）
如果找到了边界或者没有冲突（当前区间与已有区间无交集）
直接输出[s, e]并记录到map中（右端点作为键，左端点作为值）
跳到下一个任务
如果初始位置有冲突，从位置1开始寻找合适的区间
计算新的区间[s, e]
如果没有冲突，则输出区间并记录到map中，退出循环
如果仍有冲突，将起始位置设为冲突区间的右端点+1，继续寻找
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

map<ll, ll> mp;
int n;
int main() {
    fast;
    cin >> n;
    while (n--) {
        ll s, d, e; cin >> s >> d; e = s + d - 1;
        auto it = mp.lower_bound(s);
        if (it == mp.end() || it->second > e) {
            cout << s << ' ' << e << '\n';
            mp[e] = s;
            continue;
        }
        s = 1;
        while (true) {
            e = s + d - 1;
            it = mp.lower_bound(s);
            if (it == mp.end() || it->second > e) {
                cout << s << ' ' << e << '\n';
                mp[e] = s;
                break;
            }
            s = it->first + 1;
        }
    }
    return 0;
}