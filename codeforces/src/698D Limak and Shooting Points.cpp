//
// Created by Psy.C on 2026/4/17.
//
/**
a[i]: 镜子的坐标 (最多8面镜子)
b[i]: 点的坐标 (最多1000个点)
l[i][j] 表示第i面镜子上，从点j能看到的其他点集合
m: 镜子数量
n: 点的数量
p: 镜子的排列数组
q: BFS队列

共线判断
(b[j].x-a[i].x)*(b[k].y-a[i].y) == (b[j].y-a[i].y)*(b[k].x-a[i].x)
判断点b[j]、镜子a[i]、点b[k]三点共线
使用叉积为0判断共线
方向判断
(a[i].x-b[k].x)*(b[j].x-b[k].x) < 0 || (a[i].x==b[k].x&&(a[i].y-b[k].y)*(b[j].y-b[k].y) < 0)
判断a[i]在b[j]和b[k]之间（线段关系）
确保光线从b[j]经镜子a[i]反射到b[k]

预处理：O(m × n²)
主要计算：O(n × m! × m × n)（排列数 × BFS）
由于m很小（≤8），可以用next_permutation暴力枚举
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;
constexpr int N = 1e3+5;

struct node { int x, y; } a[9], b[N];

int m, n, p[9], q[N];
vector<int> l[9][N];
bool vis[N];
int main() {
    fast;
    cin >> m >> n;
    rep(i,m) cin >> a[i].x >> a[i].y;
    rep(i,n) cin >> b[i].x >> b[i].y;
    rep(i,m) rep(j,n) rep(k,n) if (k != j) {
        if (1ll*(b[j].x-a[i].x)*(b[k].y-a[i].y) == 1ll*(b[j].y-a[i].y)*(b[k].x-a[i].x) &&
            (1ll*(a[i].x-b[k].x)*(b[j].x-b[k].x) < 0 || (a[i].x==b[k].x&&1ll*(a[i].y-b[k].y)*(b[j].y-b[k].y) < 0)))
            l[i][j].push_back(k);
    }
    int ans = 0;
    rep(j,n) {//尝试每个点作为起点
        rep(i,m) p[i] = i;// 初始化镜子顺序
        bool flag = false;
        do {
            rep(i,n) vis[i] = false;//清空访问标记
            bool cur = true;
            int hd = 1, tl = 1;
            q[tl] = j; vis[j] = true;//BFS起点
            while (hd <= tl) {
                int u = q[hd];
                for (int i = 0; i < l[p[hd]][u].size(); ++i) {
                    if (vis[l[p[hd]][u][i]]) continue;
                    q[++tl] = l[p[hd]][u][i];//加入BFS队列
                    vis[l[p[hd]][u][i]] = true;
                    if (tl > m) {//访问的点超过m个（镜子数）
                        cur = false;
                        break;
                    }
                }
                if (!cur) break;
                hd++;//移动BFS指针
            }
            if (cur) { flag = true; break; }//找到合法路径
        } while (next_permutation(p+1, p+m+1));//尝试所有镜子排列
        if (flag) ans++;//如果从点j能找到合法路径，答案+1
    }
    cout << ans << '\n';
    return 0;
}