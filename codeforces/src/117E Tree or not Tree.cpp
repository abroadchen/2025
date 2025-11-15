//
// Created by Psy.C on 2025/11/15.
//
/*
*g：图的邻接表表示
i[1+N]：时间戳数组（用于DFS时间标记）
p[1+N]：父节点数组
r[1+N]：环上节点标记
c：环的大小计数器
q[1+N]：环上前驱数组
t：时间计数器
o[1+N]：结束时间戳数组
k：边的计数器
s：环上特殊计数器
e[1+N]：边的激活状态数组
 *
*使用DFS寻找图中的环
v：当前节点，z：父节点
如果遇到已访问节点，说明找到了环，返回该节点
返回0表示未找到环
 *
*遍历以v为根的子树
i[v]记录进入时间，o[v]记录离开时间
r[w]标记节点属于哪个部分
 *
*如果v和u在同一部分（环或同一子树）：
使用move函数调整路径
 *如果在不同部分，先移动到环上
 *定义move_around函数，沿着环移动并更新状态
*比较两种环向移动方向的距离
选择较短路径进行移动
使用goto语句跳转到相应的处理分支
 *
 *
*定义lambda函数cycle：
h = find()：找到环上的一个节点
接受函数f作为参数
从h开始，沿着父节点遍历整个环
 *
*如果边变为激活(e[w]=true)，k减1
如果边变为非激活(e[w]=false)，k加1
 *
*调整v和u到它们的最近公共祖先
使用DFS时间戳判断祖先关系
 *
 *
*v先被访问，u后被访问
u先完成访问，v后完成访问
这种时间包含关系表明u在v的子树中
 *
返回 q[v] 的值
在C++中，非零值被视为 true，零值被视为 false
所以这个条件函数实际上是在判断：节点v是否在环上*
 *
*顺时针距离：(r[u] + c - r[v]) % c //节点v到节点u
逆时针距离：(r[v] + c - r[u]) % c
 *
*s: 表示当前激活的"特殊边"数量（在环上的边）
c: 表示图中环的总数
k: 表示图中未被删除的有效边数量
代码解释：
s++;
将当前激活的特殊边数量加1
这意味着有一条新的环边被激活（翻转状态）
if (s < c) k--;
如果当前激活的特殊边数量小于环的总数，那么将有效边数量减1
这里的逻辑是：当不是所有的环边都被激活时，新增一条激活边会导致总的可用边减少
 *
 */
#include <vector>
#include <iostream>
using namespace std;

static constexpr uint_fast32_t N = 100'000;
static vector<vector<uint_fast32_t>> g;
static uint_fast32_t i[1 + N] = {}, p[1 + N] = {},
r[1 + N] = {}, c = 0, q[1 + N] = {}, t = 0, o[1 + N], k, s = 0;
static bool e[1 + N] = {};

static uint_fast32_t find(const uint_fast32_t v=1, const uint_fast32_t z=0) noexcept {
    i[v] = true;//标记节点v为已访问
    for (const uint_fast32_t w : g[v]) {//遍历节点v的所有邻居w
        if (w == z) continue;//如果w是父节点z，跳过（避免回溯）
        p[w] = v;//记录w的父节点为v
        if (i[w]) return w;//如果w已被访问，说明找到了环，返回w
        if (const uint_fast32_t h = find(w, v)) return h;//递归搜索w，如果找到环则返回环节点
    }
    return 0;//未找到环返回0
}
//定义遍历函数，参数：v=当前节点，j=部分标记
static void trav(const uint_fast32_t v, const uint_fast32_t j) noexcept {
    i[v] = t++;//记录节点v的进入时间，然后t自增
    for (const uint_fast32_t w : g[v]) {//遍历v的邻居w
        if (r[w]) continue;//如果w已在环上(r[w]非0)，跳过
        r[w] = j;//标记w属于部分j
        p[w] = v;//设置w的父节点为v
        trav(w, j);//递归遍历w
    }
    o[v] = t++;//记录节点v的离开时间，然后t自增
}

//定义lambda函数cycle，用于遍历环上的节点
static inline void preprocess() {
    const auto cycle = [h = find()](const auto& f) noexcept {
        uint_fast32_t y = h;
        do {
            f(y);
            y = p[y];
        } while (y != h);
    };
    //第一次遍历：标记环上节点并建立前驱关系
    cycle([](const uint_fast32_t y) noexcept {
        r[y] = 1 + c++;
        q[p[y]] = y;//建立环上前驱关系
    });
    //第二次遍历：对环上每个节点y进行子树遍历
    cycle([](const uint_fast32_t y) noexcept {
        trav(y, r[y]);
    });
    k = g.size() - 1;//初始化k为边数 节点数-1，对于树而言
}
//w：要移动的节点引用 x：条件函数
template<typename T>//T 可以是任何类型，包括函数类型或可调用对象类型
static inline void move(uint_fast32_t& w, const T& x) noexcept {
    for (; !x(); w = p[w]) {//沿着父节点路径移动，直到条件x()为真 每次将w更新为其父节点
        if ((e[w] = !e[w])) k--;//切换边的状态并更新计数器k
        else k++;
    }
}
//处理从节点v到节点u的路径
static inline void change(uint_fast32_t v, uint_fast32_t u) noexcept {
    if (r[v] == r[u]) {//如果v和u在同一部分（环或同一子树）
        move(v, [&v, &u]() noexcept { return i[v] <= i[u] && o[u] <= o[v]; });
        move(u, [&v, &u]() noexcept { return i[u] <= i[v] && o[v] <= o[u]; });
        return;
    }
    move(v, [&v]() noexcept { return q[v]; });
    move(u, [&u]() noexcept { return q[u]; });
    {//沿着数组d移动，从v到u
        const auto move_around = [&v, u](const uint_fast32_t (&d)[1 + N], const auto& f) noexcept {
            for (; v != u; v = d[v]) {
                const uint_fast32_t w = f(v);
                if ((e[w] = !e[w])) {//切换边状态并更新计数器
                    s++;
                    if (s < c) k--;
                } else {
                    if (s < c) k++;
                    s--;
                }
            }
        };
        //比较两种环向移动方向的距离
        if ((r[u] + c - r[v]) % c < (r[v] + c - r[u]) % c) goto p;
        if ((r[u] + c - r[v]) % c > (r[v] + c - r[u]) % c) goto q;
        if (p[v] < q[v])//选择较短路径进行移动
            p: move_around(p, [](const uint_fast32_t v) noexcept { return v; });
        else
            q: move_around(q, [](const uint_fast32_t v) noexcept { return q[v]; });
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    uint_fast32_t n, m; cin >> n >> m;
    g.resize(n + 1);
    for (; n; --n) {
        uint_fast32_t a, b; cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }
    preprocess();//预处理图结构，识别环和子树
    for (; m; --m) {
        uint_fast32_t v, u; cin >> v >> u;
        change(v, u);
        cout << k << '\n';//输出当前激活边数k
    }
    return 0;
}