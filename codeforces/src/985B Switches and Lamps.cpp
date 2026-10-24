//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
n、m 是行列数（≤2000）。
v[] 记录每一列中 1 的总个数。
s[] 存矩阵每一行（字符串，'1'/'0'）
遍历所有行所有列，统计每一列 j 中 1 的个数存入 v[j]
对当前行 i，做"临时删掉这一行"的模拟：

遍历每一列 j：
if (s[i][j] == '1') v[j]--;：若当前行该列是 1，则暂时把该列的总数 -1（模拟删行）。
if (v[j] == 0) t = true;：若删掉后某列变成 0，说明这一列就没有任何 1 了，标记 t=true（表示存在某一列会全为 0）。
if (!t) f = true;：如果整行遍历下来没有任何一列变 0（即 t==false），说明删掉这行后每列仍都有 1，满足条件，置 f=true。
rep(j,m) if (s[i][j] == '1') v[j]++;：还原刚才减掉的值，恢复每列计数，继续尝试下一行
f==true：说明至少有一行满足"删掉后每列都有 1" → 输出 Yes。
否则 No
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<(n); i++)
using namespace std;

constexpr int N = 2e3+5;

int n, m, v[N];
string s[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> s[i];
    rep(i,n) rep(j,m) if (s[i][j] == '1') v[j]++;
    bool f = false;
    rep(i,n) {
        bool t = false;
        rep(j,m) {
            if (s[i][j] == '1') v[j]--;
            if (v[j] == 0) t = true;
        }
        if (!t) f = true;
        rep(j,m) if (s[i][j] == '1') v[j]++;
    }
    if (f) cout << "Yes\n"; else cout << "No\n";
    return 0;
}