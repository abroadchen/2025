//
// Created by Psy.C on 2026/3/5.
//
/**
f[N]: DP状态数组
奇数层：f[x] = min(f[x], f[v[i]]) (取最小值)
偶数层：f[x] = f[x] + f[v[i]] (求和)
叶子节点：f[x] = 1, lv++

偶数层：取最小值
奇数层：求和
叶子节点：f[x] = 1

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 4e5+1;


int head[N], tot, nxt[N], v[N];
void add(const int x, const int y) {
    tot++; nxt[tot] = head[x]; head[x] = tot; v[tot] = y;
    tot++; nxt[tot] = head[y]; head[y] = tot; v[tot] = x;
}

int dep[N], f[N], n, lv;
void dfs(const int x, const int fa) {
    dep[x] = dep[fa] + 1;
    bool flag = false;
    if (dep[x]&1) {
        f[x] = n;
        for (int i = head[x]; i; i = nxt[i]) {
            if (v[i] == fa) continue;
            dfs(v[i], x);
            f[x] = min(f[x], f[v[i]]);
            flag = true;
        }
    } else {
        for (int i = head[x]; i; i = nxt[i]) {
            if (v[i] == fa) continue;
            dfs(v[i], x);
            f[x] = f[x] + f[v[i]];
            flag = true;
        }
    }
    if (!flag) f[x] = 1, lv++;
}

void dfs2(const int x, const int fa) {
    bool flag = false;
    if (!(dep[x]&1)) {
        f[x] = n;
        for (int i = head[x]; i; i = nxt[i]) {
            if (v[i] == fa) continue;
            dfs2(v[i], x);
            f[x] = min(f[x], f[v[i]]);
            flag = true;
        }
    } else {
        f[x] = 0;
        for (int i = head[x]; i; i = nxt[i]) {
            if (v[i] == fa) continue;
            dfs2(v[i], x);
            f[x] = f[x] + f[v[i]];
            flag = true;
        }
    }
    if (!flag) f[x] = 1;
}



int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y; add(x, y);
    }
    dfs(1, 0); cout << lv - f[1] + 1 << ' ';
    dfs2(1, 0); cout << f[1] << '\n';
    return 0;
}