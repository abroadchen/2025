//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
a[i]：存读入的每个数。
tp：当前堆的下标，初值 1。
st[1], st[2], ...：若干栈，分别代表"第 1 组、第 2 组……"
st[tp].empty()：如果当前堆是空的，说明这是当前堆的第一个元素，直接 push，不加组。
否则看 st[tp].top()（当前堆最上面的数）与 a[i] 的关系：
若栈顶 ≥ 当前数：tp++，意思是开一组新的堆，然后把这个数放进新堆。
若栈顶 < 当前数：不换堆，直接放进当前堆（栈顶依然是原来的数，新数压在上面）
输出用了多少组
输出每组的大小
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e3+1;

int n, i, a[N], tp(1);
stack<int> st[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) {
        if (st[tp].empty()) st[tp].push(a[i]);
        else {
            if (st[tp].top() >= a[i]) tp++;
            st[tp].push(a[i]);
        }
    }
    cout << tp << '\n';
    rep(i,tp) cout << st[i].size() << ' ';
    return 0;
}