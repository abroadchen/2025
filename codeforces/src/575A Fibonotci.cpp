//
// Created by Psy.C on 2026/3/14.
//
/**
k: 查询次数
m: 修改操作数
v: 存储修改操作
v0: 事件列表 {时间戳, {操作类型, 操作值}}

构建事件列表，包括修改操作和边界处理
按块大小分组排序
分块处理修改操作
对同一块内的操作批量处理
先应用修改，查询结果，再恢复原值
处理剩余的完整块
应用最后块的修改
查询最终结果

重载下标运算符[]，使得可以通过matrix[i]访问第i行
返回指向第x行的指针
允许传入4个参数初始化矩阵
参数有默认值0，可以不传参创建单位矩阵
友元函数，可以访问私有成员（这里其实没有私有成员）
执行标准2×2矩阵乘法：C = A × B
每个结果元素都要对mod取模

n：数组长度
s[N]：存储原始数组
左边界l、右边界r、矩阵v
将左子树和右子树的矩阵相乘，更新当前节点的值
p=1：当前节点在线段树中的位置（根节点为1）

x：要更新的位置
y：矩阵行号（0或1）
v_val：要设置的值
p：当前节点位置
如果是叶子节点，更新矩阵中指定位置的值
计算中点
递归更新对应的子树（根据x在左半还是右半决定走哪边）
更新完成后向上更新

查询函数
l_q, r_q：查询区间
p：当前节点
如果查询区间无效，返回单位矩阵
如果当前节点完全包含在查询区间内，返回当前节点的矩阵
计算中点
初始化结果为单位矩阵
如果左半区间有交集，查询左子树并与结果相乘
如果右半区间有交集，查询右子树并与结果相乘

读入m个修改操作
添加边界条件，确保处理的完整性
将修改操作转换为事件格式加入v0
如果操作位置不为0，还添加一个辅助事件

lst记录上一个处理的块
d指向当前块的最后一个元素
寻找当前块的所有元素（按n分块）
如果当前块超出查询范围，记录并退出
将中间完整的块通过快速幂计算并乘入结果
应用当前块内的所有修改操作
查询当前状态并乘入结果
恢复修改操作，撤销刚才的更新
处理剩余的完整块
应用最后一块的修改操作
查询最后的区间结果
输出矩阵[1][0]位置的值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 5e4, inf = 0x3f3f3f3f3f3f3f3f;
int mod;
struct node {
    int a[2][2]{};
    int *operator[](int x) { return a[x]; }
    node(int x=0, int y=0, int z=0, int v=0) {
        a[0][0]=x, a[0][1]=y, a[1][0]=z, a[1][1]=v;
    }
    friend node operator*(node x, node y) {
        return {(x[0][0]*y[0][0] + x[0][1]*y[1][0]) % mod,
            (x[0][0]*y[0][1] + x[0][1]*y[1][1]) % mod,
            (x[1][0]*y[0][0] + x[1][1]*y[1][0]) % mod,
            (x[1][0]*y[0][1] + x[1][1]*y[1][1]) % mod
        };
    }
};

///时间复杂度O(log y)
node ksm(node x, int y) {
    node res(1, 0, 0, 1);
    while (y) {
        if (y&1) res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}

int n, s[N];
struct sgt {
    struct node2 { int l{}, r{}; node v; } tr[N<<2];
#define l(p) tr[p].l
#define r(p) tr[p].r
#define v(p) tr[p].v
    void push_up(int p) { v(p) = v(p<<1)*v(p<<1|1); }
    void build(int l=0, int r=n-1, int p=1) {
        l(p) = l, r(p) = r;
        if (l == r) return v(p) = {0, s[l], 1, s[(l+1)%n]}, void();
        int mid = (l+r)>>1;
        build(l, mid, p<<1), build(mid+1, r, p<<1|1);
        push_up(p);
    }
    void init() { build(); }
    void update(int x, bool y, int v, int p=1) {
        if (l(p) == r(p)) return v(p)[y][1] = v, void();
        int mid = (l(p)+r(p))>>1;
        update(x, y, v, p<<1|(x>mid));
        push_up(p);
    }
    node query(int l=0, int r=n-1, int p=1) {
        if (l > r) return {1, 0, 0, 1};
        if (l <= l(p) && r >= r(p)) return v(p);
        int mid = (l(p)+r(p))>>1;
        node res(1, 0, 0, 1);
        if (l <= mid) res = res*query(l, r, p<<1);
        if (r > mid) res = res*query(l, r, p<<1|1);
        return res;
    }
} st;

int k, m;
ii v[N+1];
vector<pair<int, pair<bool, int>>> v0;
signed main() {
    fast;
    cin >> k >> mod >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> v[i].first >> v[i].second;
    v0.push_back({-n, {0, 0}}); v0.push_back({inf, {0, 0}});
    for (int i = 1; i <= m; ++i) {
        v0.push_back({v[i].first, {0, v[i].second}});
        if (v[i].first)
            v0.push_back({v[i].first-1, {1, v[i].second}});
    }
    ranges::sort(v0); st.init();
    node res(1, 0, 0, 1);
    int lst = 0;
    for (int i = 1, d; i < v0.size(); i = d+1) {
        d = i;
        while (d + 1 < v0.size() && v0[d + 1].first/n == v0[i].first/n) d++;
        if (v0[i].first/n >= k/n) { lst = v0[i-1].first/n; break; }
        res = res * ksm(st.query(), v0[i].first/n - 1 - v0[i-1].first/n);
        for (int j = i; j <= d; ++j) st.update(v0[j].first%n, v0[j].second.first, v0[j].second.second);
        res = res * st.query();
        for (int j = i; j <= d; ++j) st.update(v0[j].first%n, v0[j].second.first, v0[j].second.first ?
            s[(v0[j].first+1)%n] : s[v0[j].first%n]);
    }
    res = res * ksm(st.query(), k/n-1-lst);
    for (auto &[fst, snd] : v0)
        if (fst/n == k/n) st.update(fst%n, snd.first, snd.second);
    res = res * st.query(0, k%n-1);
    cout << res[1][0];
    return 0;
}