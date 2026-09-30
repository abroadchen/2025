//
// Created by Psy.C on 2026/9/30.
//
/**
node：存储拐点/事件，a 是用 double 存的投影截距（y - kx），用于按方向排序；x,y 是坐标，id 用于区分是点(0)还是查询(正负 id)；比较时用 eps 做浮点相等的容差。
cmp：为 pair<int,int>（分数 a/b）做有理数比较（a.second*b.first < b.second*a.first），用于把向量按极角排序（避免了除法精度问题）。
Fenwick tr：离散化后的一维 BIT
k 方向数, n 点, q 查询
读 v[1..k]，规约到第一象限（把每向量翻到非负方向），累加 sx,sy
sort(v, cmp) 按极角排序
读 n 个点 (x[i],y[i],a[i])，把 x 放入 val 离散化

对每个非垂直方向 v[i]，把点和查询点都投影到该方向的垂线（用截距 y-kx 排序）‍，用扫描线 BIT 统计"落在方向带内的点权和/点计数"，从而逐段累加贡献。每处理完一个方向，把查询点位置向前推进到下一个方向起点，形成闭环多边形扫描
第二遍从最后一个方向反向扫回来，把贡献加回（第一遍减、第二遍加），最终抵消单程，得到净结果（类似"去程减、返程加"的双向覆盖校正）

w[j].x-(i<2) / w[j].y-(i>1) 这类 (i<2)/(i>1) 的 ±1 微调，是处理方向带端点开闭边界（首个/末个方向避免重复计）的边界校正。id=0 是点、id<0 是第一遍查询（减贡献）、id>0 是第二遍查询（加贡献）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define eps 1e-7
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+10;

struct node {
    double a; int x, y, id;
    node(double a=0, int x=0, int y=0, int id=0) : a(a), x(x), y(y), id(id) {}
    bool operator<(const node& o) const {
        return fabs(a-o.a) < eps ? id < o.id : a < o.a;
    }
} w[N<<1];
bool cmp(const ii& a, const ii& b) {
    if (!b.first) return a.first || a.second < b.second;
    return a.second*b.first < b.second*a.first;
}
ll tr[N];
void update(int p, int v) { for (; p < N; p += p&-p) tr[p] += v; }
ll query(int p) {
    ll r = 0;
    for (; p; p -= p&-p) r += tr[p];
    return r;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ii v[11];
int sx, sy, x[N], y[N], a[N], px[N], py[N], t[N];
vector<int> val;
ll ans[N];

int pos(int x) {
    return upper_bound(val.begin(), val.end(), x) - val.begin();
}
int main() {
    fast;
    int k = rd(), n = rd(), q = rd();
    for (int i = 1; i <= k; ++i) {
        v[i].first = rd(), v[i].second = rd();
        if (v[i].first < 0) {
            v[i].first = -v[i].first; v[i].second = -v[i].second;
        } else if (!v[i].first && v[i].second < 0) {
            v[i].second = -v[i].second;
        }
        sx += v[i].first, sy += v[i].second;
    }
    sort(v+1, v+k+1, cmp);
    for (int i = 1; i <= n; ++i) {
        val.push_back(x[i] = rd());
        y[i] = rd(); a[i] = rd();
    }
    ranges::sort(val);
    val.erase(ranges::unique(val).begin(), val.end());
    for (int i = 1; i <= q; ++i) {
        px[i] = rd(), py[i] = rd(); t[i] = rd();
        px[i] -= sx*t[i], py[i] -= sy*t[i];//把查询点按合力方向"回退" t 步
        t[i] <<= 1;//时长翻倍
    }
    for (int i = 1; i <= k; ++i) {
        if (!v[i].first) {//v[i]垂直(无x分量)
            for (int j = 1; j <= q; ++j)
                py[j] += v[i].second*t[j];//只沿y平移
            continue;
        }
        double k = 1.*v[i].second/v[i].first;
        for (int j = 1; j <= n; ++j)//生成 n 个点的截距事件 w[j] = {y-k x, x, a, 0}
            w[j] = {y[j]-k*x[j], x[j], a[j], 0};
        for (int j = 1; j <= q; ++j) {
            w[n+j] = {py[j]-k*px[j], px[j], px[j]+v[i].first*t[j], -j};//生成 q 个查询事件 w[n+j] = {py-k px, px, px+v.x*t, -j}
            px[j] += v[i].first*t[j], py[j] += v[i].second*t[j];//事后把 px,py 沿该方向前进 t 步（移动到下一个方向的起点）
        }
        sort(w+1, w+n+q+1);
        memset(tr, 0, sizeof(tr));
        for (int j = 1; j <= n+q; ++j) {
            if (w[j].id) ans[-w[j].id] -= query(pos(w[j].y)) - query(pos(w[j].x-(i<2)));
            else update(pos(w[j].x), w[j].y);
        }
    }
    for (int i = 1; i <= k; ++i) {
        if (!v[i].first) break;
        double k = 1.*v[i].second/v[i].first;
        for (int j = 1; j <= n; ++j)
            w[j] = {y[j]-k*x[j], x[j], a[j], 0};
        for (int j = 1; j <= q; ++j) {
            w[n+j] = {py[j]-k*px[j], px[j]-v[i].first*t[j], px[j], j};
            px[j] -= v[i].first*t[j], py[j] -= v[i].second*t[j];
        }
        sort(w+1, w+n+q+1);
        memset(tr, 0, sizeof(tr));
        for (int j = 1; j <= n+q; ++j) {
            if (w[j].id) ans[w[j].id] += query(pos(w[j].y-(i>1))) - query(pos(w[j].x-1));
            else update(pos(w[j].x), w[j].y);
        }
    }
    for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
    return 0;
}