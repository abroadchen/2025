//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
node：记录一条直线（或一个"操作点"）。
num：这条线对应的时间戳/编号。
x：这条线的起始位置（在该 x 处插入）。
st[N]：模拟单调栈的数组，维护下凸包的所有候选线，L 是栈顶下标
sgn：整数符号。
mul：判断两个有理数（分数）的大小关系而不丢失精度（避免直接浮点除法误差）。
x1*y2 > y1*x2（作为两个分数比较）即"第一个分数大"。
先用 sgn 判断符号组合避免溢出/符号误判。
(ld) 转 long double 辅助比较，仍保持精确（important for 凸包判定）。
这些用于凸包中"判断三条直线交点的先后"，本质是比较斜率/截距
b[i] / s[i]：前缀累计修正量。每次 type3 操作会对"当前时刻起"直线整体加 x（加到 b）和加 y（加到 s）。
calc(q, w)：计算"直线 q（在时刻 q.num 加入、起点 q.x）在时刻 w 时的函数值"。公式：
b[w] - b[q.num] + (q.x-1)*(s[w]-s[q.num])
含义：当前总修正减去加入时刻之前的修正，得到该线从加入至今的净位移；再乘上位置相关项。这是把"全局线性修改"拆到每条线的净值上
若当前栈顶直线的值此时为 0（避免除零/退化），直接返回。
y = calc({w,x},w)：新候选线在时刻 w 的函数值。
while 弹栈：用 mul（叉积比较）判断"新点是否使 st[L] 成为非凸点"。若三点构成凸包（新线相对 st[L-1]、st[L] 的叉积满足凸性条件）则停止；否则 L--（弹出不再可能最优的中间直线）。
最后把新线 {w,x} 压入栈顶。
这是标准的维护下凸包（斜率单调）‍，保证栈中直线按位置划分最优区间。
当全局发生修改（type3），需要用新的时刻 w 更新：若栈顶的值≤次栈顶（栈顶不再优于栈顶前一），弹掉栈顶。
反复弹出直到栈顶是当前最优。
这是"莫队式的头部淘汰"：随着 w 推进，较早加入的直线可能不再最优，被滑动弹出
初始化：栈顶 {0,1}（时刻0，位置1），n 为初始长度。
每轮先 b[i]=b[i-1]; s[i]=s[i-1]（从前一时刻继承基准值）。
tp == 1（重置）‍：b=s=0（清空累计修正），栈重置为 {i,1}，长度 n += x。即"重新从位置1开始"。
tp == 2（添加直线）‍：add(i, n+1) 在当前时刻 i、位置 n+1 加入新直线，然后 n += x 更新长度。即"新操作插入到序列末尾"。
tp == 3（全局线性修正）‍：读 y，b[i] += x、s[i] += y（给所有当前直线叠加一次位移），然后 del(i) 淘汰不再优的头部。即"所有已存在直线执行一次向右/向上偏移"。
每轮输出：st[L].x（最优直线的起始位置）和 calc(st[L], i)（它在时刻 i 的值）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ld long double
using namespace std;

constexpr int N = 3e5+5;
struct node { int num, x; } st[N];

inline int sgn(ll &x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
inline int mul(ll x1, ll y1, ll x2, ll y2) {
    int w1 = sgn(x1)*sgn(y2), w2 = sgn(y1)*sgn(x2);
    if (w1 != w2) return w1 > w2;
    if (w1 == 0) return 0;
    return (ld)x1*y2 > (ld)y1*x2;
}

ll b[N], s[N];
inline ll calc(node q, int w) { return b[w]-b[q.num]+1ll*(q.x-1)*(s[w]-s[q.num]); }

int L;
void add(int w, int x) {
    if (calc(st[L],w) == 0) return;
    ll y = calc({w,x},w);
    while (L >= 2) {
        if (mul(st[L].x-st[L-1].x,calc(st[L],w)-calc(st[L-1],w),
            x-st[L].x,y-calc(st[L],w))) break;
        L--;
    }
    st[++L] = {w,x};
}
void del(int w) { while (L >= 2 && calc(st[L],w) >= calc(st[L-1],w)) L--; }

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, m;
ll x, y;
int main() {
    fast;
    read(n); read(m);
    st[L=1] = {0,1};
    for (int i = 1, tp; i <= m; i++) {
        b[i] = b[i-1]; s[i] = s[i-1];
        read(tp); read(x);
        if (tp == 1) {
            b[i] = s[i] = 0;
            st[L=1] = {i,1};
            n += x;
        }
        else if (tp == 2) { add(i,n+1); n += x; }
        else { read(y); b[i] += x; s[i] += y; del(i); }
        cout << st[L].x << ' ' << calc(st[L],i) << '\n';
    }
    return 0;
}