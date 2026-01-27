//
// Created by Psy.C on 2026/1/26.
//

#include <iostream>
#include <deque>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    deque<int> q;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; q.push_back(x);
    }
    int s1 = 0, s2 = 0;//玩家1和玩家2的分数
    for (int i = 1; i <= n; ++i) {
        const int l = q.front(), r = q.back();
        if (i&1) {
            //从两端取较大的数字
            if (l > r) { s1 += l; q.pop_front(); }//从队列中移除已取的数字
            else { s1 += r; q.pop_back(); }
        } else {
            if (l > r) { s2 += l; q.pop_front(); }
            else { s2 += r; q.pop_back(); }
        }
    }
    cout << s1 << ' ' << s2 << '\n';
    return 0;
}