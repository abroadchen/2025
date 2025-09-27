//
// Created by Psy.C on 2025/9/26.
//
/*
 *整数点结构体 (ipoint)
*成员变量x和y表示坐标
构造函数用于初始化
get()从输入读取坐标并加1（可能是为了处理边界）
重载减法运算符计算两点间向量
重载乘法运算符计算向量叉积
 *浮点点结构体 (point)
*支持从整数点转换
==运算符用于判断两点是否相等（考虑浮点误差）
up()判断点是否在上半平面
len()计算点到原点距离的平方
<运算符用于极角排序
 *
 *整数线段结构体 (iseg)
*sign()判断点相对于线段的方向
on()判断点是否在线段上
xx()判断两线段是否相交
xp()计算两线段的交点
 *
 *浮点线段结构体 (seg)
 *
 *并查集结构体 (DSU)
*init()初始化并查集
dsu()查找根节点（路径压缩）
merge()合并两个集合
build()构建并查集结果
 *
 *面结构体 (T)
*adj存储相邻面的索引
area存储面积
color存储颜色
 *
 *id函数
 *通过二分查找找到点p在points数组中的索引。
 *
 *bfs函数
 *使用广度优先搜索将连通区域的颜色改为cl。
 *
 *读取输入，添加垂直和水平边界线段。
 *计算所有线段的端点和交点，去重后得到所有关键点。
 *将线段按交点分割成更小的线段，构建边集合。
 *构建邻接表和环结构，使用并查集合并属于同一线段的边。
 *通过遍历环来构建面，计算面积并建立面之间的邻接关系。
 *处理颜色查询，通过点在线段上或射线法判断点在哪个面内，然后改变该面的颜色。
*统计各种颜色的面积并输出结果。

这是一个复杂的计算几何问题，主要解决平面分割和区域着色问题。
 *
 *
 *w(宽度)、h(高度)、n(线段数)、m(边数)、sz(大小)、q(查询数)
 *
*线段索引 i → 对应的两条边索引为 2*i 和 2*i+1
边索引 k → 对应的线段索引为 k>>1（即 k/2）


k^1 表示对k和1进行异或运算：

当 k 是偶数时（如 0, 2, 4, 6...），k^1 的结果是 k+1
当 k 是奇数时（如 1, 3, 5, 7...），k^1 的结果是 k-1


每条无向线段被表示为两条有向边
索引 2*i 和 2*i+1 表示同一条线段的两个相反方向
其中：
2*i 是正向边
2*i+1 是反向边


k^1 就是与边k方向相反的边
如果k是正向边，k^1就是对应的反向边
如果k是反向边，k^1就是对应的正向边
 */
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <set>
#include <numeric>
#include <queue>
#define mp make_pair
#define pb emplace_back
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
#define F first
#define S second
using namespace std;
const double eps = 1e-12;
int w, h, n, m, sz, q;


struct ipoint {
    int x, y;
    ipoint() {}
    ipoint(int x, int y) : x(x), y(y) {}
    void get() { cin >> x >> y; ++x, ++y; }
    ipoint operator-(const ipoint& o) const { return ipoint(x - o.x, y - o.y); }
    ll operator*(const ipoint& o) const { return 1ll * x * o.y - 1ll * y * o.x; }
};

struct point {
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    point(ipoint p) : x(p.x), y(p.y) {}//从整数点转换为浮点点的构造函数。
    void get() { cin >> x >> y; ++x, ++y; }
    point operator-(const point& o) const { return point(x - o.x, y - o.y); }
    double operator*(const point& o) const { return x * o.y - y * o.x; }
    bool operator==(const point& o) const { return abs(x - o.x) < eps && abs(y - o.y) < eps; }
    bool up() const { return (x > 0 && y >= 0) || (x <= 0 && y > 0); }
    double len() const { return x * x + y * y; }
    bool operator<(const point& o) const { return up() != o.up() ? up() : abs((*this)*o) < eps ? len() < o.len() : (*this)*o > 0; }
};

struct iseg {
    ipoint a, b;//线段的两个端点
    iseg() {}
    iseg(ipoint a, ipoint b) : a(a), b(b) {}//用给定的两点初始化线段
    void get() { a.get(), b.get(); }//从标准输入读取线段两个端点的坐标
    int sign(ipoint o) {//判断点o相对于线段的方向
        ll val = (o - a) * (o - b);//计算叉积来判断点相对于线段的位置
        return val > 0 ? 1 : val == 0 ? 0 : -1;//1表示点在线段左侧，0表示在线段上，-1表示在线段右侧
    }
    bool on(ipoint o) {//判断点o是否在线段上
        if (o.x < min(a.x, b.x) || o.x > max(a.x, b.x)) return 0;//检查x坐标是否在线段范围内
        if (o.y < min(a.y, b.y) || o.y > max(a.y, b.y)) return 0;//检查y坐标是否在线段范围内
        return sign(o) == 0;//如果点在线段上则返回true
    }
    bool xx(iseg o) {//判断当前线段与线段o是否相交
        if (on(o.a) || on(o.b) || o.on(a) || o.on(b)) return 1;//如果任一线段的端点在另一线段上，则相交
        if (sign(o.a) == 0 || sign(o.b) == 0 || o.sign(a) == 0 || o.sign(b) == 0) return 0;//如果有端点在线段上但不满足前一个条件，则不相交
        return sign(o.a) == -sign(o.b) && o.sign(a) == -o.sign(b);//通过叉积符号判断是否相交
    }
    point xp(iseg o) {//计算当前线段与线段o的交点。
        assert(xx(o));//断言两线段确实相交。
        if (on(o.a)) return o.a;//如果o.a在线段上，返回o.a。
        if (on(o.b)) return o.b;
        if (o.on(a)) return a;//如果a在o线段上，返回a。
        if (o.on(b)) return b;
        ll A = abs((o.a - a) * (o.a - b)), B = abs((o.b - a) * (o.b - b));//使用叉积计算比例系数
        ll ux = o.a.x * B + o.b.x * A, uy = o.a.y * B + o.b.y * A;//计算交点坐标的分子
        ll gx = gcd(ux, A + B), gy = gcd(uy, A + B);//计算最大公约数用于约分
        point res;
        if (ux % (A + B) == 0) res.x = ux / (A + B);//如果能整除，则直接计算整数坐标
        else res.x = (double)(ux / gx) / ((A + B) / gx);//否则计算浮点坐标
        if (uy % (A + B) == 0) res.y = uy / (A + B);
        else res.y = (double)(uy / gy) / ((A + B) / gy);
        return res;//返回交点
    }
};

struct seg {
    point a, b;
    seg() {}
    seg(point a, point b) : a(a), b(b) {}
    seg(iseg o) : a(o.a), b(o.b) {}//从整数线段转换为浮点线段的构造函数
    void get() { a.get(), b.get(); }
    int sign(point o) {
        double val = (o - a) * (o - b);
        return abs(val) < eps ? 0 : val > 0 ? 1 : -1;//考虑浮点误差返回符号
    }
    bool on(point o) {
        if (o.x + eps < min(a.x, b.x) || o.x - eps > max(a.x, b.x)) return 0;
        if (o.y + eps < min(a.y, b.y) || o.y - eps > max(a.y, b.y)) return 0;
        return sign(o) == 0;
    }
    bool xx(seg o) {
        if (on(o.a) || on(o.b) || o.on(a) || o.on(b)) return 1;
        if (sign(o.a) == 0 || sign(o.b) == 0 || o.sign(a) == 0 || o.sign(b) == 0) return 0;
        return sign(o.a) == -sign(o.b) && o.sign(a) == -o.sign(b);
    }
    bool operator==(const seg& o) const { return a == o.a && b == o.b; }
    bool operator<(const seg& o) const { return a == o.a ? b < o.b : a < o.a; }
};

struct DSU {
    int n, sz;//n表示元素总数，sz表示集合数量
    vector<int> to, g, id;//to存储父节点，g存储集合编号，id存储集合代表元素
    void init(int n_) {
        n = n_;
        to.resize(n);
        g.resize(n, 0);
        iota(to.begin(), to.end(), 0);//将to数组初始化为0,1,2,...,n-1。
    }
    int dsu(int x) { return x == to[x] ? x : (to[x] = dsu(to[x])); }//查找x的根节点，采用路径压缩优化
    void merge(int a, int b) {//合并包含a和b的两个集合
        a = dsu(a), b = dsu(b);//找到a和b的根节点
        if (a == b) return;//如果已在同一集合则直接返回
        to[b] = a;//将b所在集合合并到a所在集合
    }
    int build() {//构建并查集结果
        sz = 0;
        rep (i, 0, n - 1) if (i == dsu(i)) g[i] = sz++, id.pb(i);//为每个根节点分配集合编号，并记录代表元素
        rep (i, 0, n - 1) g[i] = g[dsu(i)];//为每个元素分配所属集合的编号
        return sz;//返回集合数量
    }
} dg;

struct T {
    vector<int> adj;//存储相邻面的索引
    double area = 0;
    string color;
};


vector<pair<iseg, bool>> isegs;//存储整数线段及其类型（true表示输入线段，false表示边界线段）
vector<point> points;//存储所有关键点
vector<pair<seg, bool>> e;//存储分割后的线段及其类型
vector<vector<pair<int, int>>> adj;//存储邻接表，每个点的邻接点及对应的边索引
vector<int> nxt, face;//nxt存储边的下一条边，face存储边所属的面
vector<T> G;//存储所有面的信息
vector<vector<int>> eid;//存储每个面包含的边索引
map<string, double> ans;//存储每种颜色的总面积

int id(point p) {//查找点p在points数组中的索引
    int i = lower_bound(points.begin(), points.end(), p) - points.begin();//第一个不小于p的点的位置
    assert(i < n && p == points[i]);//断言找到的点确实存在且等于p
    return i;//返回索引
}

void bfs(int s, string cl) {//将连通区域的颜色改为cl
    string c = G[s].color;//获取起始面的当前颜色
    if (c == cl) return;//如果颜色相同则直接返回
    queue<int> q;
    q.push(s), G[s].color = cl;//将起始面入队并改变其颜色
    while (q.size()) {//当队列非空时继续搜索
        int pos = q.front(); q.pop();//取出队首元素
        for (int np : G[pos].adj) if (G[np].color == c) {//遍历相邻面，如果颜色相同则处理
            q.push(np);//将相邻面入队
            G[np].color = cl;//改变相邻面的颜色
        }
    }
}

void solve() {
    cin >> h >> w >> n;//读取高度、宽度和线段数
    h++, w++;//将高度和宽度加1（处理边界）
    {
        vector<int> xs, ys;//存储所有x坐标和y坐标
        xs.pb(1), xs.pb(h);//添加左右边界坐标
        ys.pb(1), ys.pb(w);//添加上下边界坐标
        rep (i, 0, n - 1) {//循环读取所有输入线段
            iseg sg;
            sg.get();//读取线段坐标
            isegs.pb(sg, 1);//将线段添加到isegs中，标记为输入线段
            xs.pb(sg.a.x);//记录线段a端点的x坐标
            xs.pb(sg.b.x);
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());//去除重复的x坐标
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        for (int x : xs) isegs.pb(iseg(ipoint(x, 1), ipoint(x, w)), 0);//添加所有垂直边界线段
        for (int y : ys) isegs.pb(iseg(ipoint(1, y), ipoint(h, y)), 0);//添加所有水平边界线段
    }
    {
        for (int i = 0; i < isegs.size(); ++i) {//遍历所有线段
            points.pb(isegs[i].F.a);//添加线段a端点
            points.pb(isegs[i].F.b);
            for (int j = i + 1; j < isegs.size(); ++j) {//检查与其他线段的交点
                if (isegs[i].F.xx(isegs[j].F))//如果两线段相交
                    points.pb(isegs[i].F.xp(isegs[j].F));//添加交点
            }
        }
        sort(points.begin(), points.end());//对所有点排序
        points.erase(unique(points.begin(), points.end()), points.end());
        n = points.size();//更新点的数量
    }
    {
        for (auto [sg, ty] : isegs) {//遍历所有整数线段
            vector<point> v;//存储在线段上的所有关键点
            for (auto [sg2, ty2] : isegs) {//检查与其他线段的关系
                if (sg.on(sg2.a)) v.pb(sg2.a);//如果sg2的a端点在sg上，添加到v
                if (sg.on(sg2.b)) v.pb(sg2.b);
                if (sg.xx(sg2)) v.pb(sg.xp(sg2));//如果sg与sg2相交，添加交点到v
            }
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            for (int i = 0; i + 1 < v.size(); ++i) {//将线段分割成小段
                point a = v[i], b = v[i + 1];//获取相邻两点
                if (b < a) swap(a, b);//确保a < b
                e.pb(seg(a, b), ty);//添加分割后的线段
            }
        }
        sort(e.begin(), e.end());//对所有线段排序
        e.erase(unique(e.begin(), e.end()), e.end());
        vector<pair<seg, bool>> tmp;//临时存储去重后的线段
        for (auto [sg, ty] : e) {//遍历所有线段
            if (tmp.size() && sg == tmp.back().F) tmp.pop_back();//如果与上一条线段相同，则删除上一条
            tmp.pb(sg, ty);//添加当前线段
        }
        e = tmp;//更新e为去重后的线段
    }
    {
        m = e.size();//获取线段数量
        adj.resize(n);//调整邻接表大小
        rep (i, 0, m - 1) {//遍历所有线段
            auto [sg, ty] = e[i];//获取线段及其类型
            int j = id(sg.a), k = id(sg.b);//获取线段两端点的索引
            adj[j].pb(k, 2*i);//添加从j到k的有向边
            adj[k].pb(j, 2*i+1);//添加从k到j的有向边
        }
        nxt.resize(2*m);
        dg.init(m);//初始化并查集
        rep (i, 0, n - 1) {//遍历所有点
            sort(adj[i].begin(), adj[i].end(), [&](auto a, auto b) {
                return points[a.F] - points[i] < points[b.F] - points[i];
            });//按极角对邻接点排序
            int l(-1);//记录上一条输入线段
            for (int j = 0; j < adj[i].size(); ++j) {//遍历所有邻接点
                int lj = (j ? j - 1 : adj[i].size() - 1), k = adj[i][j].S;//获取前一个邻接点和当前边索引
                auto [sg, ty] = e[k>>1];//获取边对应的线段
                nxt[k^1] = adj[i][lj].S;//设置边的下一条边
                if (ty) {//如果是输入线段
                    if (l != -1) dg.merge(l, k>>1);//合并上一条输入线段与当前线段
                    l = k>>1;//更新上一条输入线段
                }//k>>1的作用就是将有向边的索引转换回原始无向线段的索引，从而获取该边对应的线段信息
            }
        }
    }
    {
        sz = dg.build();
        vector<int> vs(2*m, 0);//标记边是否已访问
        face.resize(2*m, -1);//初始化face数组
        G.resize(sz);
        rep (i, 0, sz - 1) {//遍历所有并查集代表元素
            int j = dg.id[i];//获取代表元素索引
            G[i].color = (e[j].S ? "black" : "white");
        }
        rep (i, 0, 2*m-1) if (vs[i] == 0) {//遍历所有未访问的边
            int pos = i;//设置当前位置
            vector<int> v;//存储环中的边
            double area(0);//计算环的有向面积
            while (vs[pos] == 0) {//当边未访问时继续
                v.pb(pos);//添加边到环中
                if (pos % 2 == 0) area += e[pos>>1].F.a * e[pos>>1].F.b;//如果是正向边，累加面积
                else area += e[pos>>1].F.b * e[pos>>1].F.a;
                vs[pos] = 1;//标记边已访问
                pos = nxt[pos];//移动到下一条边
            }
            if (area < -eps) continue;//如果面积为负则跳过
            for (int j : v) face[j] = sz;//为环中的边分配面索引
            T x;//创建新面
            x.area = area;
            x.color = "white";
            G.pb(x);//将面添加到G中
            sz++;//增加面的数量
        }
        eid.resize(sz);
        rep (i, 0, 2*m-1) {//遍历所有边
            int j = face[i], k = dg.g[i>>1];//获取边所属的面和线段的集合
            if (j == -1) continue;//如果边不属于任何面则跳过
            G[j].adj.pb(k);//在面之间添加邻接关系
            G[k].adj.pb(j);
            eid[j].pb(i>>1);//记录面包含的线段
        }
        rep (i, 0, sz - 1) {//遍历所有面
            sort(G[i].adj.begin(), G[i].adj.end());//对面的邻接点排序
            G[i].adj.erase(unique(G[i].adj.begin(), G[i].adj.end()), G[i].adj.end());
        }
    }

    cin >> q;//读取查询数量
    while (q--) {
        point p;//声明查询点
        string cl;//声明目标颜色
        p.get();//读取查询点坐标
        cin >> cl;
        bool f(0);//标记是否找到点所在的线段
        rep (i, 0, m - 1) {//遍历所有输入线段
            auto [sg, ty] = e[i];//获取线段及其类型
            if (ty == 0) continue;//如果是边界线段则跳过
            if (sg.on(p)) {//如果点在线段上
                bfs(dg.g[i], cl);//改变线段所在集合的颜色
                f = 1;//标记已找到
                break;
            }
        }
        if (f) continue;//如果已处理则继续下一个查询
        rep (i, 0, m - 1) {//遍历所有边界线段
            auto [sg, ty] = e[i];
            if (ty == 1) continue;//如果是输入线段则跳过
            if (sg.on(p)) {
                bfs(dg.g[i], cl);
                f = 1;
                break;
            }
        }
        if (f) continue;
        seg s(p, point(1e9, p.y + 1));//创建从查询点向右的射线
        rep (i, dg.sz, sz - 1) {//遍历所有面
            int cnt(0);//初始化交点计数器
            for (int j : eid[i]) cnt += e[j].F.xx(s);//计算射线与面的边的交点数
            if (cnt & 1) {//如果交点数为奇数
                bfs(i, cl);
                break;
            }
        }
    }

    rep (i, 0, dg.sz - 1) {//遍历所有线段集合
        int j = dg.id[i];//获取集合代表元素
        if (e[j].S) ans[G[i].color] = 0;//如果是输入线段，则对应颜色面积为0
    }
    rep (i, dg.sz, sz - 1) ans[G[i].color] += G[i].area;//累加各颜色面的面积

    cout << fixed << setprecision(12);//设置输出格式为固定小数点后12位
    for (auto [cl, area] : ans) {//遍历所有颜色及其面积
        cout << cl << ' ' << area / 2 << '\n';//面积除以2是因为叉积计算的是两倍面积
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}