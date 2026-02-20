//
// Created by Psy.C on 2026/2/19.
//
/**
f[i][j]: 从位置i开始，长度为2^j的区间的最大值
b[i]: 预计算的log2(i)值 floor(log2(i))

l, r: 查询区间
mx: 区间内的最大值
p: 概率值
m: 查询数量
mx: 数组最大值
mm: 辅助变量
g[x]: 节点x的子节点列表
f[x][j]: 节点x在j个事件下的概率


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1, Q = 5e3+1, M = 1e4+1;

int n, a[N];
namespace rmq {
    constexpr int M = 17;//2^17=131072
    int f[N][M], b[N];
    void build() {
        for (int i = 2; i <= n; ++i) b[i] = b[i>>1]+1;
        for (int i = 1; i <= n; ++i) f[i][0] = a[i];//长度为1的区间最大值就是元素本身
        for (int j = 1; j < M; ++j)//f[i][j] = max(f[i][j-1], f[i+2^(j-1)][j-1])
            for (int i = 1; i <= n; ++i) {
                const int x = i + (1<<(j-1));
                f[i][j] = f[i][j-1];
                if (x <= n && f[x][j-1] > f[i][j])
                    f[i][j] = f[x][j-1];
            }
    }
    inline int query(const int l, const int r) {//将[l,r]分解为两个长度为2^x的重叠区间
        const int x = b[r-l+1];
        return max(f[l][x], f[r-(1<<x)+1][x]);
    }
}

struct node {
    int l, r, mx; double p;
    bool operator<(const node& o) const {
        return l != o.l ? l < o.l : r > o.r;
    }
} q[Q];

int m, mx, mm;
namespace tree {
    vector<int> g[Q];
    double f[Q][M];
    inline void add(const int x, const int y) { g[x].push_back(y); }
    void build() {
        sort(q + 1, q + m + 1);
        static int sta[Q], top;//初始化栈
        q[sta[top=0]=0] = {1, n, min(mx, m), 0};//创建根节点
        ///构建区间树：使用单调栈处理区间嵌套关系
        for (int i = 1; i <= m; ++i) {
            ///当前区间的左端点超过栈顶区间的右端点时，连接父子关系
            for (const auto& p = q[i]; top > 0 && p.l > q[sta[top]].r; --top)
                add(sta[top-1], sta[top]);
            sta[++top] = i;
        }
        for (; top; --top) add(sta[top-1], sta[top]);//处理栈中剩余元素
    }
    void dfs(const int x) {
        if (g[x].empty()) {//基础概率设置
            f[x][0] = 1 - q[x].p;
            for (int i = 1; i <= mm; ++i) f[x][i] = 1;
            return;
        }
        for (const int& v : g[x]) dfs(v);
        for (int j = 0; j <= m; ++j) {
            double t1 = j ? q[x].p : 0, t2 = 1 - q[x].p;
            for (const int& v : g[x]) {
                const int t = q[x].mx - q[v].mx + j;
                t1 *= f[v][t-1];
                t2 *= f[v][t];
            }
            f[x][j] = t1 + t2;
        }
        for (int j = m+1; j <= mm; ++j) f[x][j] = f[x][j-1];//延拓概率值
    }
    double get() {
        double res = mx;
        for (int i = 1; i <= m; ++i) res += (f[0][i] - f[0][i-1])*i;
        return res;//期望值
    }
}

inline void mxx(int& x, const int y) { x = max(x, y); }

int main() {
    fast;
    cin >> n >> m; mm = m<<1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mxx(mx, a[i]);
    }
    if (mx > m)
        for (int i = 1; i <= n; ++i)
            a[i] = max(0, a[i]+m-mx);//标准化
    rmq::build();
    for (int i = 1; i <= m; ++i) {
        cin >> q[i].l >> q[i].r >> q[i].p;
        q[i].mx = rmq::query(q[i].l, q[i].r);//每个区间的最大值
    }
    tree::build(); tree::dfs(0);
    const double ans = tree::get();
    printf("%.10lf\n", ans);
    return 0;
}