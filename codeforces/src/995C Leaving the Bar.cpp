//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
inf = 2.25e12：期望的最终长度平方上限（2.25e12 = 1.5e6 的平方）。
node：存每个向量的 x、y 和原始编号 id。
ans[i]：第 i 个向量分配的符号（+1 / -1）。
sx, sy：当前累加的总向量
读入 n 个向量的坐标，并记录原始编号 id
每轮开始把累加向量清零。
用 random_shuffle 把 n 个向量随机打乱顺序（每轮的贪心顺序不同）
对打乱后的每个向量 v[i]：

计算两种选择后的长度平方：
t1 = |S + v_i|²（加）
t2 = |S - v_i|²（减）
选长度更小的那一种：
若加更大（t1 > t2），选"减"：sx-=x, sy-=y, ans=-1；
否则选"加"：sx+=x, sy+=y, ans=+1
累加完一整轮后，判断最终向量长度平方是否 ≤ inf。
是 → 跳出循环，输出结果；
否 → while 继续，重新洗牌再跑一轮
按原始编号顺序输出每个向量的符号（1 或 -1）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr ll N = 1e5+5, inf = 2.25e12;

struct node { ll x, y; int id; } v[N];

int n, i, ans[N];
ll sx, sy;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> v[i].x >> v[i].y; v[i].id = i; }
    while (true) {
        sx = 0, sy = 0;
        random_shuffle(v+1, v+n+1);
        rep(i,n) {
            ll t1 = (sx+v[i].x)*(sx+v[i].x)+(sy+v[i].y)*(sy+v[i].y),
            t2 = (sx-v[i].x)*(sx-v[i].x)+(sy-v[i].y)*(sy-v[i].y);
            if (t1 > t2) sx -= v[i].x, sy -= v[i].y, ans[v[i].id] = -1;
            else sx += v[i].x, sy += v[i].y, ans[v[i].id] = 1;
        }
        if (sx*sx+sy*sy <= inf) break;
    }
    rep(i,n) cout << ans[i] << ' ';
    return 0;
}