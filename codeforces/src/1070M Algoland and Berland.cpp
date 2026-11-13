//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
n 是全局，m 是另一个全局。node 同时容纳两类"点"：前 n 个（id ≤ n，r=0，作为划分的"锚点/容器"）和后 m 个（id > n，有输入给的 r，是要"放进容器"的元素）
统计当前点集里锚点（id ≤ n）有几个。若只剩一个：
递归出口：当前集合只剩 1 个锚点 p，则把集合内所有"叶点"（id>n）全部归属给锚点 p，输出 叶点编号-n 锚点编号，返回。这就是"每个点被分给唯一锚点"
在反点（id>n）里找一个 r 最大的换到 a[0]。a[0] 成为分治的"支点"（通常选成最外侧/权重最大点）
以 a[0] 为原点，把其余点按极角排序，形成一圈锋良好的环
w 累积"净权重"，1-a[p].r 别：反点贡献 1-r。
p 指向当前窗口右端。
循环条件判断极角跨度是否超过 180°（+pi）——保证后续划分是"凸角/半平面可分离"。这个 while 在窗口跨度超过 π 前不断扩展 p，w += 1-a[p].r
i 是窗口左端，p 是右端，w 是窗口内净重，cnt 是窗口内点数
每次尝试以当前窗口 [i, p) 为一个"半平面"，看净重 w 是否落在区间 [1, a[0].r-1]。若落在，就把集合沿窗口切成两半，a[0] 同时分给两半（左半拿 w，右半拿 a[0].r-w），各自递归 → 分治完成。
否则右端 p 继续前进扩展窗口（条件是用极角判断窗口是否还能保持 ≤π 的连续性）。
窗口右端到头后，左端 i 前进（w -= 1-a[i].r; cnt--），继续下一轮扫描
前 n 个是锚点（r=0），后 m 个是带权重 r 的点。输出固定 "YES"（单测多组 T）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define pi acos(-1)
using namespace std;

struct node {
    int x, y, id, r;// 点坐标 点编号，1..n+m 某个权重（小于 n 的点 r=0，输入的后 m 个点由题目给 r）
    double val;//用于排序的角度
    bool operator<(const node &o) const { return val < o.val; }
};

int n;//第一类点个数（"固定点"）
void solve(vector<node> a) {
    int cnt = 0, p = 0;
    rep(i,0,a.size()-1) if (a[i].id <= n) cnt++, p = a[i].id;
    if (cnt == 1) {
        rep(i,0,a.size()-1) if (a[i].id > n) cout << a[i].id-n << ' ' << p << '\n';
        return;
    }
    rep(i,1,a.size()-1) if (a[i].id > n && a[i].r > a[0].r) swap(a[i], a[0]);
    rep(i,1,a.size()-1) a[i].val = atan2(a[i].y-a[0].y, a[i].x-a[0].x);
    sort(a.begin()+1, a.end());//除 a[0] 外按极角升序排
    int w = 0; cnt = 0, p = 1;
    while (cnt < a.size()-1 && a[p].val + pi <= a.back().val) {
        w += 1-a[p].r; cnt++; p++;
        if (p == a.size()) p = 1;
    }
    rep(i,1,a.size()-1) {
        while (1) {
            if (w >= 1 && w < a[0].r) {
                vector<node> b;
                int u = i;
                do {
                    b.push_back(a[u]); u++;
                    if (u == a.size()) u = 1;
                } while (u != p);
                //递归左半
                node t = a[0]; t.r = w; b.push_back(t); solve(b); b.clear(); u = p;
                while (u != i) {
                    b.push_back(a[u]); u++;
                    if (u == a.size()) u = 1;
                }
                t = a[0]; t.r = a[0].r-w; b.push_back(t); solve(b);//递归右半
                return;
            }
            if (!(cnt < a.size()-1 && (p >= i && a[p].val <= a[i].val + pi ||
                a[p].val + pi <= a[i].val))) break;
            w += 1-a[p].r; cnt++; p++;
            if (p == a.size()) p = 1;
        }
        w -= 1-a[i].r; cnt--;
    }
}

int m;
void solve() {
    cin >> n >> m;
    vector<node> a; a.resize(n+m);
    rep(i,0,m-1) cin >> a[i+n].r;
    rep(i,0,n+m-1) {
        cin >> a[i].x >> a[i].y; a[i].id = i+1;
        if (i < n) a[i].r = 0;
    }
    cout << "YES\n";
    solve(a);
}


int main() {
    fast;
    int T; cin >> T;
    while (T--) solve();
    return 0;
}