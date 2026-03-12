//
// Created by Psy.C on 2026/3/12.
//
/**
定义line结构体表示直线方程ax+by+c=0
声明line数组l，存储n条直线

存储分组信息
s[i][2]存储第i组的两个直线编号（最多两组，每组最多两条线）
num[i]记录第i组已有直线数
o1为初始状态，o为最终状态

判断三条直线是否交于一点（即三线共点）
首先检查系数矩阵的行列式是否为0（避免退化情况）
第二个条件是使用齐次坐标下的三线共点判断公式
如果三条直线交于一点返回true，否则返回false

n：直线总数
k：分组数上限
尝试将第now条直线分组
如果已处理完所有直线（now=n+1），更新结果并返回true
尝试将当前直线now放入第i组
如果当前组还没满2条线，直接添加
如果当前组已有2条线，检查新加入的直线是否与组内两直线交于一点
如果不交于一点，跳过此分组方案
递归处理下一条直线
如果找到可行方案返回true
否则尝试其他分组方案

统计实际使用的分组数ans
输出分组数
输出每个分组的直线编号
如果组内只有1条线，第二位置输出-1
如果组内有2条线，输出两个编号
如果无解，输出NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

struct line { ll a, b, c; } l[N];
struct node { int s[5][2], num[5]; } o1, o;

bool ok(const line &u, const line &v, const line &w) {
    if (v.a*w.b-v.b*w.a == 0 && u.b*w.a-u.a*w.b == 0) return false;
    if (u.c*(v.a*w.b-v.b*w.a)+v.c*(u.b*w.a-u.a*w.b)+w.c*(u.a*v.b-u.b*v.a) == 0)
        return true;
    return false;
}

int n, k;
bool dfs(const int now, const node& d) {
    if (now == n + 1) { o = d; return true; }
    for (int i = 0; i < k; ++i) {
        node x = d;
        if (x.num[i] != 2) x.s[i][x.num[i]++] = now;
        else if (!ok(l[x.s[i][0]], l[x.s[i][1]], l[now])) continue;
        if (dfs(now + 1, x)) return true;
    }
    return false;
}

int main() {
    fast;
    cin>>n>>k;
    for (int i = 1; i <= n; ++i) cin>>l[i].a>>l[i].b>>l[i].c;
    if (dfs(1, o1)) {
        cout << "YES\n";
        int ans = 0;
        for (int i = 0; i < k; ++i)
            if (o.num[i] > 0) ans++;
        cout << ans << '\n';
        for (int i = 0; i < ans; ++i) {
            cout << o.s[i][0] << ' ';
            if (o.s[i][1] == 0) cout << "-1\n";
            else cout << o.s[i][1] << '\n';
        }
    } else cout << "NO\n";
    return 0;
}