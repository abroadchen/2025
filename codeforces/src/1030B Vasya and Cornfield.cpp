//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
顶点依次为
(
0
,
d
)
(0,d)、
(
d
,
0
)
(d,0)、
(
n
,
n
−
d
)
(n,n−d)、
(
n
−
d
,
n
)
(n−d,n)，即一个中心在
(
n
/
2
,
n
/
2
)
(n/2,n/2)、对角线长为
n
n、轴旋转 45°的菱形。
这对应经典题：满足
∣
x
−
y
∣
≤
d
∣x−y∣≤d 且
∣
x
+
y
−
n
∣
≤
d
∣x+y−n∣≤d 的菱形（
n
n 为一半对角线长）
对四条边依次计算叉积 (边向量) × (顶点到点向量)。
点在凸多边形内 ⟺ 对所有边叉积同号（全非负或全非正）‍。
代码用 pre 保存上一轮叉积，累乘判断是否出现异号（. < 0），一旦变号即点在外部。
全部同号 → YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, d, m, u[4], v[4];
int main() {
    fast;
    cin >> n >> d >> m;
    u[0] = 0, u[1] = d, u[2] = n, u[3] = n - d;
    v[0] = d, v[1] = 0, v[2] = n - d, v[3] = n;
    while (m--) {
        int x, y; cin >> x >> y;
        int pre = 1; bool f = 1;
        for (int i = 0; i < 4; i++) {
            int a = u[(i+1)%4] - u[i], b = v[(i+1)%4] - v[i];//边向量
            int c = x - u[i], d = y - v[i];//点到顶点的向量
            int res = a*d - b*c;//叉积
            if (i) pre = res*pre;
            if (pre < 0) f = 0;//出现负号 → 在外部
            pre = res;
        }
        if (f) cout << "YES\n"; else cout << "NO\n";
    }
    return 0;
}