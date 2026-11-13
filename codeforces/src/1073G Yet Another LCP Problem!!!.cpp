//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
node：x 是位置，tp 是该位置属于哪个集合（A=0 / B=1），k 是排序方向标记（用于正向/反向两次扫描方向相反）。
h[]：实际要排序的后缀位置数组
x[]：当前轮的"排名数组"（第一关键字）。
y[]：按第二关键字排好的序号（或暂存）。
cnt[]：基数排序计数数组。
sa[]：后缀数组
第一轮：按单个字符排序
j 是当前处理的子串半长（每次倍增，比较长度为 2j 的前缀）。
tot 记录本轮产生的不同排名个数，m = tot 更新桶数；当 tot > n（排名全不同）或 tot == n 时循环结束。
第二关键字：长度溢出（后缀不足 j）的那些空后缀排最前；其余按上一轮 sa 顺序生成 y。
基数排序：以第二关键字为序，对第一关键字做稳定排序。cnt[t[i]] 是次数，前缀和定区间，i 从 n 倒序保证稳定。
重新编号：cmp(y, a, b, j) 判断两个排名 (sa) 的前 2j 个字符是否相同，相同则同类 tot-1，否则 tot++ 分配新区号。tot 从 2 起（占 1 个起点
经典的 H[i] >= H[i-1]-1 线性求 height：

从 i=1 到 n 依次求每个后缀的 height（利用 height[rk[i]]）。
k 复用上一位的 height，若上一位非零则 k-1 起步，然后暴力比对 s[i+k] 与 s[j+k] 扩展 k。
j = sa[rk[i]-1] 是排在前一名的后缀位置。
结果是 ht[rk[i]] = k（长度为 k 的公共前缀）
标准 ST 表构建在 ht[] 上，g[i][j] 表示 [i, i+2^j-1] 的 min
后缀数组中，LCP(suffix(x), suffix(y)) = min(ht[x+1], ..., ht[y])（排名相邻区间的 height 最小值）。这里用 ST 表 O(1) 查询。

x 从排名加1开始（因为 ht[rk] 记录的是 sa[rk-1] 与 sa[rk] 的 LCP，区间要覆盖 (x, y]）
0：sum 是单调栈维护的"当前高度贡献"，ans 是答案累加，top 是栈顶。
把所有 A、B 位置放进 h[]，然后按后缀排名排序（node::operator< 按 rk[x] 比，tp 作次级）。
排序后，按排名顺序扫描相邻后缀，相邻的 LCP = tmp。
单调栈维护：栈 q[top] 存高度，p[top] 存前缀计数。栈保持高度单调递增。
当新高度 tmp 不大于栈顶高度，把栈顶弹出并撤销其贡献（sum -= (p[top]-p[top-1])*q[top]），保持单调性。
压入新高度：sum += tmp*(j-p[top])，其中 j = 到目前为止 B 的个数（或某种累计标记）。
p[top]=j 记录新栈顶对应"已到第 j 个元素"。
若当前 h[i] 属于 A 集合（!h[i].tp），则把当前 sum（即"与之前所有 B 后缀的 LCP 相关贡献"）累加进 ans。
j += h[i].tp：每遇到一个 B 元素 j 加 1（tp 累加），用于计数。
单调栈要点：由于 LCP 满足 lcp(i,k) = min(lcp(i,j), lcp(j,k))（区间可合并），从小到大维护高度，可把"每个 A 与之前所有 B 的 LCP 求和"在线性时间内求出。sum 实际上等价于"当前元素与前面所有同类集合元素 LCP 的某种加权和"

每次询问读入两组位置 a[]（A）、b[]（B）。
做两次 solve：正向一次（tp=1），反转后反向一次（tp=0）。
两次方向不同，是因为本题需要统计的 LCP 贡献分顺、逆两个方向（例如"子串匹配"既有从左向右也有从右向左的匹配），两方向的结果相加才是完整答案。
b[0]=1, b[l2+1]=n 是给 B 集合加边界位置（可能是解决"覆盖/区间"型需求的标记）。
reverse(a, a+l1+2)：因为 a 从下标 1 开始，l1+1 之后那一位为 0，反转范围 [0..l1+1] 包含边界空位，用来配合 node 排序方向的切换。
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int rk[N];
struct node {
    int x, tp, k;
    bool operator<(const node &o) const {
        if (k) return rk[x] < rk[o.x] || (x == o.x && tp > o.tp);
        return rk[x] > rk[o.x] || (x == o.x && tp < o.tp);
    }
} h[N<<1];
//比较函数：两段长度为 l 的子串是否完全相等，即第一、第二关键字都相等
bool cmp(int *g, int a, int b, int l) { return g[a] == g[b] && g[a+l] == g[b+l]; }

int m, n, cnt[N], x[N], sa[N], y[N], t[N];
char s[N];
void get_sa() {
    m = 128;//初始桶数 = 字符集大小（假设ASCII）
    rep(i,n) cnt[x[i]=s[i]]++;//第一轮：把每个字符的ASCII码作为初始排名
    rep(i,m) cnt[i] += cnt[i-1];//前缀和（确定每个桶的排名区间）
    for (int i = n; i; i--) sa[cnt[x[i]]--] = i;//稳定排序得到第一轮 sa
    for (int j = 1, tot = 0; tot <= n; m = tot, j <<= 1) {
        tot = 0;
        for (int i = n-j+1; i <= n; i++) y[++tot] = i;//第二关键字为0(空后缀)的排最前
        rep(i,n) if (sa[i] > j) y[++tot] = sa[i] - j;//其余按 sa 顺序取 sa[i]-j 作为第二关键
        rep(i,n) t[i] = x[y[i]];//取第一关键字
        memset(cnt, 0, sizeof(cnt));
        rep(i,n) cnt[t[i]]++;
        rep(i,m) cnt[i] += cnt[i-1];
        for (int i = n; i; i--) sa[cnt[t[i]]--] = y[i];//按第一关键字稳定排序，合并第二关键字
        tot = 2; swap(x, y); x[sa[1]] = 1;
        for (int i = 2; i <= n; i++)
            x[sa[i]] = cmp(y, sa[i], sa[i-1], j) ? tot-1 : tot++;//重新分配排名
    }
}

int ht[N];//ht[i] = LCP(sa[i-1], sa[i])，即排名相邻两个后缀的最长公共前缀
void geth() {
    rep(i,n) rk[sa[i]] = i;//由 sa 逆推 rk（排名）
    for (int i = 1, j, k = 0; i <= n; ht[rk[i++]] = k)
        for (k = k ? k-1 : 0, j = sa[rk[i]-1]; s[i+k] == s[j+k]; k++) {}
}

int g[N][20];//ST表，存区间最小值（height 的 min）
void rmq() {
    memset(g, 127, sizeof(g));
    rep(i,n) g[i][0] = ht[i];//第0级：每个位置的height
    for (int j = 1; 1<<j <= n; j++) rep(i,n-(1<<j)+1)
        g[i][j] = min(g[i][j-1], g[i+(1<<(j-1))][j-1]);
}
int lcp(int x, int y) {
    if (x == y) return n-x+1;//同一后缀，LCP 是其完整长度
    x = rk[x]; y = rk[y];//转为排名
    if (x > y) swap(x,y); x++;//区间取 (x, y]，because 需比对 ht[x+1..y]
    int p = log2(y-x+1);
    return min(g[x][p], g[y-(1<<p)+1][p]);
}

int a[N], b[N], q[N], p[N];
ll solve(int l1, int l2, int tp) {
    ll sum = 0, ans = 0; int tot = 0, top = 0;
    rep(i,l1) h[++tot] = {a[i], 0, tp};//A的位置，tp=0标记
    rep(i,l2) h[++tot] = {b[i], 1, tp};//B的位置，tp=1标记
    sort(h+1, h+tot+1);
    for (int i = 2, j = h[1].tp; i <= tot; i++) {
        int tmp = lcp(h[i-1].x, h[i].x);
        while (top && tmp <= q[top]) sum -= (p[top]-p[top-1])*q[top], top--;
        sum += tmp*(j-p[top]); q[++top] = tmp; p[top] = j;
        if (!h[i].tp) ans += sum;
        j += h[i].tp;
    }
    return ans;
}

int Q;
ll ans;
int main() {
    int l1, l2;//l1: A集合大小, l2: B集合大小
    scanf("%d%d %s",&n,&Q,s+1); get_sa(); geth(); rmq();
    while (Q--) {
        scanf("%d%d",&l1,&l2); ans = 0;
        rep(i,l1) cin >> a[i];//读入 A 集合的位置
        rep(i,l2) cin >> b[i];
        b[0] = 1; b[l2+1] = n;//边界：B 集合两端补 1 和 n（原串范围）
        ans += solve(l1, l2, 1);//正向扫描，tp=1
        reverse(a, a+l1+2); reverse(b, b+l2+2);//反转（处理反向，如对 b 集合内部顺序）
        ans += solve(l1, l2, 0);
        printf("%lld\n", ans);
    }
    return 0;
}