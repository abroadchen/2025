//
// Created by Psy.C on 2026/3/22.
//
/**
计算直线与圆的交点函数
c：将直线方程ax+by+c1=0代入点(x0,y0)
sa, sb, sc, sr：各项的平方
如果b不为0，使用解析几何方法求解直线与圆的交点
d：判别式，小于0表示无交点
计算两个交点坐标(px1,py1)和(px2,py2)
将直角坐标转换为极坐标角度
确保返回的角度区间是[l,r]

定义树状数组结构体
v：存储数据的向量
构造函数初始化数组大小
在位置x添加y的值
利用lowbit操作更新所有相关节点
查询前缀和[1,x]
查询区间[x,y]的和

m：有效区间的数量
n：输入点的数量
len：离散化后的长度
k：目标数量
a,b,c：直线方程系数
lsh：离散化数组
tmp：临时存储区间
pos：离散化后的位置

检查半径mid是否满足条件
遍历所有直线，计算与圆的交点区间
将所有区间端点存入离散化数组
按左端点排序区间
使用树状数组统计有多少个区间有重叠
返回重叠次数是否达到k

计算两条直线的交点
如果平行（系数比相等）则返回无穷
解二元一次方程组求交点坐标

将两点转换为直线方程参数
如果两点x坐标相同，返回垂直线
计算斜率k和截距b，返回直线方程的参数形式

线段树单点修改
在位置k添加值v到对应区间
使用二进制位运算优化
线段树区间查询
查找区间[l,r]内的所有元素

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db long double
#define dd pair<db,db>
#define ii pair<int,int>
#define eps 1e-9
using namespace std;
constexpr int N = 50005, M = 1e5+5, A = 4e5+5, inf = 1011451423;

db sqr(db x) { return x * x; }
db dis(db ax, db ay, db bx, db by) {
    return sqrt(sqr(ax - bx) + sqr(ay - by));
}
db dis(dd a, dd b) {
    return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}

db x0, y_0;///目标点坐标
dd get(db a, db b, db c1, db R) {
    db c = a*x0 + b*y_0 + c1, sa = sqr(a), sb = sqr(b), sc = sqr(c), sr = sqr(R);
    db px1 = 0, px2 = 0, py1 = 0, py2 = 0;
    if (fabs(b) > eps) {
        db d = (sa + sb) * sb * sr - sb * sc;
        if (d < 0) return {inf, inf};
        px1 = (-a*c + sqrt(d))/(sa + sb); px2 = (-a*c - sqrt(d))/(sa + sb);
        py1 = -(a*px1 + c)/b; py2 = -(a*px2 + c)/b;
    }
    db l = atan2(px1, py1), r = atan2(px2, py2);
    if (l > r) swap(l, r);
    return {l, r};
}

struct bit {
    int n; vector<int> v;
    bit(int _n = 100000) : v(_n+5) { n = _n; }
    void add(int x, int y) {
        for (; x <= n; x += x&-x) v[x] += y;
    }
    int query(int x) const {
        int ret = 0;
        for (; x; x -= x&-x) ret += v[x];
        return ret;
    }
    int query(int x, int y) const { return query(y) - query(x-1); }
};


int m, n, len, k;
db a[N], b[N], c[N], lsh[M];
dd tmp[N];
ii pos[N];
bool ok(db mid) {
    m = 0;
    for (int i = 1; i <= n; ++i) {
        auto ret = get(a[i], b[i], c[i], mid);
        if (ret.first != inf || ret.second != inf) {
            ++m; tmp[m] = ret;
            lsh[(m<<1)-1] = ret.first; lsh[m<<1] = ret.second;
        }
    }
    sort(lsh + 1, lsh + (m<<1) + 1);
    len = unique(lsh + 1, lsh + (m<<1) + 1) - lsh - 1;
    //将区间端点映射到离散化后的位置
    for (int i = 1; i <= m; ++i) {
        pos[i].first = lower_bound(lsh + 1, lsh + len + 1, tmp[i].first) - lsh;
        pos[i].second = lower_bound(lsh + 1, lsh + len + 1, tmp[i].second) - lsh;
    }
    sort(pos + 1, pos + m + 1);
    bit T(len);
    int cnt = 0;
    for (int i = 1; i <= m; ++i) {
        cnt += T.query(pos[i].first, pos[i].second);
        T.add(pos[i].second, 1);
    }
    return cnt >= k;
}

dd get(db a0, db b0, db c0, db a1, db b1, db c1) {
    if (fabs(a0*b1 - a1*b0) < eps)
        return {inf, inf};
    db x, y;
    if (fabs(a0) > eps) {
        y = (a1*c0 - a0*c1)/(a0*b1 - a1*b0);
        x = -(b0*y + c0)/a0;
    } else {
        y = -c0/b0;
        x = (-c1 - y*b1)/a1;
    }
    return {x, y};
}

pair<db, dd> get_p(db p, db q, db r, db s) {
    if (fabs(p - r) < eps)
        return {1., {0., -p}};
    db k = (q - s)/(p - r), b = q - k*p;
    return {k, {-1., b}};
}

vector<int> tr[A];
void modify(int k, int v, int x, int L, int R) {
    tr[x].push_back(v);
    if (L == R) return;
    int mid = (L+R)>>1;
    k <= mid ? modify(k, v, x<<1, L, mid) : modify(k, v, x<<1|1, mid+1, R);
}

vector<int> res;
void query(int l, int r, int x, int L, int R) {
    if (l <= L && R <= r) {
        for (auto i : tr[x]) res.push_back(i);
        return;
    }
    int mid = (L+R)>>1;
    if (l <= mid) query(l, r, x<<1, L, mid);
    if (r > mid) query(l, r, x<<1|1, mid+1, R);
}
void query(int l, int r) {
    res.clear();
    query(l, r, 1, 1, len);
}

pair<db, dd> t[N];
int main() {
    fast;
    cin >> n >> x0 >> y_0 >> k; x0/=1000, y_0/=1000;//缩放坐标以减少浮点误差
    //读取直线方程系数，标准化处理
    for (int i = 1; i <= n; ++i)
        cin >> a[i] >> c[i], a[i]/=1000, b[i] = -1, c[i]/=1000;
    db l = eps, r = 3e9;
    while (r - l > eps) {//找到最小半径
        if (db mid = (l+r)/2; ok(mid)) r = mid;
        else l = mid;
    }
    if (l <= eps) return cout << 0 << '\n', 0;//半径很小
    ok(l);//获取区间信息
    //将弧度转换为圆上的点，并计算直线方程
    for (int i = 1; i <= m; ++i)
        t[i] = get_p(l*cos(lsh[pos[i].first]), l*sin(lsh[pos[i].first]),
            l*cos(lsh[pos[i].second]), l*sin(lsh[pos[i].second]));
    int cnt = 0; db ans = 0;
    for (int i = 1; i <= m; ++i) {//统计所有相交的区间对的距离和
        if (pos[i].first + 1 > pos[i].second - 1) continue;
        query(pos[i].first + 1, pos[i].second - 1);
        for (auto j : res) {
            db ret = dis({0., 0.}, get(t[i].first, t[i].second.first,
                t[i].second.second, t[j].first, t[j].second.first, t[j].second.second));
            ans += ret, ++cnt;
        }
        modify(pos[i].second, i, 1, 1, len);
    }
    //包含剩余未计算的k-cnt个点的距离
    cout << fixed << setprecision(12) << ans + l*(k-cnt) << '\n';
    return 0;
}