//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
mod 质数 998244353；inv3 = 332748118 = 3 在模 mod 下的乘法逆元（用于 S2 中的 /3）；inf = 1e9 作无穷大哨兵
对 x 做一次"向 mod 回折"：过大减一次 mod，过小（负）加一次 mod。用于累积式加减时的取模修正
f(x,y,i)：计算 max(0, 2i - x + 1) * max(0, 2i - y + 1) % mod——形如一个以 i 为界的"面积/边长贡献"。
S1(x)=x(x+1)/2：1..x 的和（模）。
S2(x)=x(x+1)(2x+1)/6：1²+2²+...+x²（平方和公式，/6 = /2 再 /3，inv3 处理除 3）。
这三个合起来用于批量求和（等差、平方和）
把"到 t 为止的和"拆成：

起点贡献 t*f(x,y,t)；
对 i 从 l=(max(x,y)+1)/2 到 r=t-1 求和，用 平方和 S2、等差和 S1、常数项 三种闭合公式分别累计。
三项修正系数：-4·S2、+2(x+y-2)·S1、-(x-1)(y-1)·(r-l+1)。最终得到的是某个 以 (x,y) 为参数的"区间积分/面积"的闭合表达式，避免 O(t) 循环而做到 O(1)。

结合 f(x,y,i)=max(0,2i-x+1)*max(0,2i-y+1)，这里其实在统计二维平面中满足 u+i>=x、v+i>=y 这类不等式的整数点数量，calc 在求"字典序小/面积差"的计数
a[i] 保存第 i 个点的 (x,y) 坐标对。
s 是一个有序集合，用来动态维护"已处理点的 y 值集合"，借助 upper_bound/lower_bound 找最近邻
dx 是两点的 x 坐标差。
交换 i,j 保证 a[i][1] <= a[j][1]（y 有序），后续处理方便。
p、q 初始 infinite，用于记录左右最近的"邻居 y"
关键判断：只有 [a[i].y, a[j].y] 区间内没有其他已存在点时才会被处理（it1==it2 即区间空）。若区间内有其他点，说明这一对不是"最小/有效贡献对"，直接跳过（保证最终统计的是"相邻点对"的贡献，避免重复）。
这相当于题目要求枚举的点对之间不能夹有其他点（几何学中的"按 y 相邻"限制
先从 ans 减掉以该 y 差为参数的贡献（calc(dx, dy)）
it1 存在（在集合末尾之前）→ 右邻居 y 为 *it1，贡献 calc(dx, *it1 - a[i].y)，记录 p=*it1。
it2 向前退一位（--it2）得左邻居 y，贡献 calc(dx, a[j].y - *it2)，记录 q=*it2。
即：为"恰好夹着该点对"的两侧邻居分别加入贡献
若左右邻居都真实存在，则要减掉"从 p 到 q 整区间"的贡献（calc(dx, p-q)）——这是容斥思想：加左、加右、减去重叠部分，保证不重复计数。
solve(i,j) 本质是对一对点 (i,j)，用三个区间（自身 dy、右侧到邻居、左侧到邻居、以及邻居跨段）做容斥加加减减，得到该点对"独有"的 calc 贡献。
初始答案 = n * calc(0,0)（所有点与原点基准的贡献之和）。
按坐标排序所有点。
对每个起点 i：清空 set，然后遍历所有 j>i，先 solve(i,j)（基于当前 set 中已有的 y 判断有效点对并容斥累加），再把 a[j][1]（j 点的 y）插入 set。
这样 s 始终保存"i 之后、当前 j 之前"已处理点的 y，配合 solve 里的 upper_bound/lower_bound 判断相邻关系，实现 O(n² log n) 的总复杂度

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ar(x) array<int,x>
using namespace std;

constexpr int N = 2e3+1e2, mod = 998244353, inv3 = 332748118, inf = 1e9;

inline void add(int &x) {
    if (x >= mod) x -= mod;
    if (x < 0) x += mod;
}

int f(int x, int y, int i) { return 1ll*max(0,2*i-x+1)*max(0,2*i-y+1)%mod; }
int S1(int x) { return 1ll*x*(x+1)/2%mod; }
int S2(int x) { return 1ll*x*(x+1)/2%mod*(2*x+1)%mod*inv3%mod; }

int t;
int calc(int x, int y) {
    int res = 1ll*t*f(x,y,t)%mod, l = (max(x,y)+1)/2, r = t-1;
    if (l > r) return res;
    add(res -= 4ll*(S2(r)-S2(l-1))%mod);
    add(res += 2ll*(x-1+y-1)*(S1(r)-S1(l-1))%mod);
    add(res -= 1ll*(x-1)*(y-1)%mod*(r-l+1)%mod);
    return res;
}

ar(2) a[N];
set<int> s;
int ans;
void solve(int i, int j) {
    int dx = a[j][0]-a[i][0], p = inf, q = inf;
    if (a[i][1] > a[j][1]) swap(i,j);
    auto it1 = s.upper_bound(a[j][1]);
    auto it2 = s.lower_bound(a[i][1]);
    if (it1 != it2) return;
    add(ans -= calc(dx,a[j][1]-a[i][1]));
    if (it1 != s.end()) add(ans += calc(dx,*it1-a[i][1])), p = *it1;
    if (it2 != s.begin()) --it2, add(ans += calc(dx,a[j][1]-*it2)), q = *it2;
    if (p != inf && q != inf) add(ans -= calc(dx, p-q));
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n;
void solve() {
    n = rd(), t = rd(); ans = 1ll*n*calc(0,0)%mod;//基准：n*calc(0,0)
    rep(i,n) a[i] = {rd(), rd()};//读入 n 个点 (x,y)
    sort(a+1, a+n+1);//按 (x,y) 排序
    rep(i,n) {
        s.clear();// 每个起点 i 重置有序集合
        for (int j = i+1; j <= n; ++j)//枚举 j>i，处理点对并插入其 y
            solve(i,j), s.insert(a[j][1]);
    }
    cout << ans << '\n';
}


int main() {
    fast;
    solve();
    return 0;
}