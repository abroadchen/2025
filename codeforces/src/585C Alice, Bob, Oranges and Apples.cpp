//
// Created by Psy.C on 2026/3/17.
//
/**
检查x和y是否互质
如果不互质，则无解，输出"Impossible"
如果x == y且都等于1，说明到达目标(1,1)，返回
如果x == y但不等于1，说明无法继续，输出"Impossible"
A操作：(x, y) -> (x-y, y)，即从(x,y)通过A操作得到(x-y,y)

当x > y时，计算需要多少次A操作
k = x/y（但如果整除则减1）
输出k和"A"
递归处理(x-k*y, y)
B操作：(x, y) -> (x, y-x)，即从(x,y)通过B操作得到(x,y-x)

当y > x时，计算需要多少次B操作
k = y/x（但如果整除则减1）
输出k和"B"
递归处理(x, y-k*x)

O(log(min(x,y)))，类似于欧几里得算法的时间复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

void dfs(ll x, ll y) {
    if (__gcd(x, y) != 1) { cout << "Impossible\n"; return; }
    if (x == y) {
        if (x == 1 && y == 1) return;
        cout << "Impossible\n";
        return;
    }
    if (x > y) {
        ll k = x/y;
        if (x%y == 0) k--;
        cout << k << "A";
        dfs(x - k*y, y);
    } else {
        ll k = y/x;
        if (y%x == 0) k--;
        cout << k << "B";
        dfs(x, y - k*x);
    }
}

ll x, y;
int main() {
    fast;
    cin >> x >> y; dfs(x, y);
    return 0;
}