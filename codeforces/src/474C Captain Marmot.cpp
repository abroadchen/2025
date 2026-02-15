//
// Created by Psy.C on 2026/2/15.
//
/**
坐标(x,y)、旋转中心(a,b)、时间和步数t
h[5]: 存储原始四边形顶点信息
tt[5][5]: 存储每个顶点经过不同旋转次数后的位置
c[5]: 记录每个顶点的旋转次数

绕点(h[j].a, h[j].b)逆时针旋转90°的变换公式：
新x = -(原y-中心y) + 中心x
新y = (原x-中心x) + 中心y
 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define inf 0x3f3f3f3f
#define rep(i,n) for (int i=0;i<n;++i)
using namespace std;

struct node { int x, y, a, b, t; } h[5], tt[5][5];
int c[5];

int get(const int tm) {
    map<ll, int> mp;
    rep(i,3) {
        const int e = c[i];
        for (int j = i + 1; j < 4; ++j) {
            const int p = c[j], t1 = tt[i][e].x - tt[j][p].x,
            t2 = tt[i][e].y - tt[j][p].y, tmp = t1*t1 + t2*t2;//所有点对之间的距离平方
            mp[tmp]++;
        }
    }
    if (mp.size() == 2) {//两种不同的距离（边长和对角线）
        int a[2], cnt = 0;//存入元素的个数
        for (const auto &key: mp | views::keys) {
            a[cnt++] = key;
            if (key == 0) return inf;
        }
        //正方形条件（对角线² = 2×边长²）
        if (a[0]*2 == a[1] || a[1]*2 == a[0]) return tm;
    }
    return inf;
}

int res;
void dfs(const int cnt, const int tm) {
    if (cnt == 4) {
        if (const int tmp = get(tm); tmp < res) res = tmp;
        return;
    }
    rep(i,4) {
        c[cnt] = i;
        dfs(cnt + 1, tm + tt[cnt][i].t);//之前操作数 + 当前顶点旋转所需操作数
    }
}

int n;
int main() {
    fast;
    cin>>n;
    rep(i,n) {
        rep(j,4) {
            cin >> h[j].x >> h[j].y >> h[j].a >> h[j].b;
            tt[j][0].x = h[j].x, tt[j][0].y = h[j].y;
            tt[j][0].t = 0;
        }
        rep(j,4) for (int k = 1; k < 4; ++k) {
            auto& e = tt[j][k];
            const auto &p = tt[j][k-1];
            const int tx = p.x - h[j].a, ty = p.y - h[j].b;
            e.x = -ty + h[j].a, e.y = tx + h[j].b;
            e.t = k;
        }
        res = inf; dfs(0, 0);
        if (res == inf) cout << "-1\n"; else cout << res << '\n';
    }
    return 0;
}