//
// Created by Psy.C on 2026/9/18.
//
/**
a[i]：序列值。
c[i]：某种代价/权值数组。
la[i]：值 i 上一次出现的位置（last occurrence）
对每个位置 i，ans += c[a[i]]（基础权值全累加）。
若 a[i] 之前出现过（la[a[i]] != 0），则生成一个"区间"：左端点 = 该值上一次出现位置，右端点 = 本次位置 i，权值 = c[a[i]]。
更新 la[a[i]] = i。
即：vec 收集了所有"同一值相邻两次出现之间"的区间（左闭右开式的 [la, i]）
维护一棵区间加、区间查最大值的线段树 Tr，表示"每个位置当前被多少个已选择的区间内部覆盖"。
遍历（当前经过随机交换重排后的）vec：
若区间有内部空隙（l+1 <= r-1，即区间长度 ≥ 2 有内部点）：
先查区间 [l+1, r-1] 当前最大覆盖深度，若 <= m-2 才"接受"这个区间：把 sum += u.w，并把区间 [l+1, r-1] 整体 +1（占一个槽）。
若区间无内部空隙（相邻，长度 2 之类）：直接 sum += u.w（不需要查，也不占用槽）。
m-2：容量上限。m 是主存的某种容量参数，最多允许区间内部覆盖深度不超过 m-2，超了就不能再选。
s = vec.size()。
模拟退火：温度 T=10，降温系数 delta=0.99，终止条件 t<eps，时间预算 tl=0.95 秒。
每次随机交换 vec 中两个元素，重算 calc()（贪心价值）：
若更优 → 更新 mx（历史最优）。
若更差 → 按概率 (mx-now)*T > rand()/RAND_MAX 决定是接受（保留交换）还是回退（再换回来）。
反复迭代直到时间耗尽。
注意：calc() 的结果依赖 vec 的顺序（因为贪心从左到右看覆盖深度是否超限）。所以"交换重排 + 贪心"构成了邻域搜索，用模拟退火在高维空间找好的排列，最大化能贪心选出的总权值 mx
先 ans = sum(c[a[i]])（所有元素权值之和）。
模拟退火得到最多可"选出的区间权值和" mx。
输出 ans - mx——即原始总和减去最优能保留/节省的部分 = 最小化目标
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 85;
struct edge { int l, r, w; };

struct sgt {
    int tr[N<<2], tag[N<<2];
    void clear() {
        memset(tr, 0, sizeof(tr));
        memset(tag, 0, sizeof(tag));
    }
    void get(int u, int t) { tr[u] += t, tag[u] += t; }
    void push_up(int u) {
        tr[u] = max(tr[u<<1], tr[u<<1|1]);
    }
    void pushdown(int u) {
        if (tag[u]) {
            get(u<<1, tag[u]);
            get(u<<1|1, tag[u]);
            tag[u] = 0;
        }
    }
    void insert(int u, int l, int r, int L, int R) {
        if (l >= L && r <= R) return get(u, 1), void(0);
        int mid = (l+r)>>1;
        pushdown(u);
        if (L <= mid) insert(u<<1, l, mid, L, R);
        if (mid+1 <= R) insert(u<<1|1, mid+1, r, L, R);
        push_up(u);
    }
    int query(int u, int l, int r, int L, int R) {
        if (l >= L && r <= R) return tr[u];
        int mid = (l+r)>>1;
        pushdown(u);
        int s = 0;
        if (L <= mid) s = query(u<<1, l, mid, L, R);
        if (mid+1 <= R) s = max(s, query(u<<1|1, mid+1, r, L, R));
        push_up(u);
        return s;
    }
} Tr;

vector<edge> vec;
int n, m;
ll calc() {
    ll sum = 0; Tr.clear();
    for (auto u : vec) {
        if (u.l + 1 <= u.r - 1) {
            if (Tr.query(1, 1, n, u.l+1, u.r-1) <= m-2)
                sum += u.w, Tr.insert(1, 1, n, u.l+1, u.r-1);
        } else sum += u.w;
    }
    return sum;
}
constexpr double T = 10, eps = 1e-15, delta = 0.99, tl = 0.95;
mt19937 rd(random_device{}());
int s;
ll mx;
void sa() {
    double t = T;
    while (t > eps) {
        int x = rd()%s, y = rd()%s;
        swap(vec[x], vec[y]);
        ll now = calc();
        if (now > mx) mx = now;
        else if (1.0*(mx-now)*T > rand()/RAND_MAX)
            swap(vec[x], vec[y]);
        t *= delta;
    }
}

int a[N], c[N], la[N];
ll ans;
int main() {
    fast;
    clock_t st = clock();
    srand(time(0)); cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) {
        ans += c[a[i]];
        if (la[a[i]])
            vec.push_back({.l = la[a[i]], .r = i, .w = c[a[i]]});
        la[a[i]] = i;
    }
    s = vec.size();
    while (clock() - st < tl*CLOCKS_PER_SEC) sa();
    cout << ans-mx << '\n';
    return 0;
}