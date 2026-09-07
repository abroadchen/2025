//
// Created by Psy.C on 2026/9/6.
//
/**
s1：第一个位域（低位部分掩码，最多 31 位）
s2：第二个位域（高位部分掩码）
c1、c2：两个计数器（例如"已选中的数量"、"目标差值"之类）
s1 占高 11 位（位移 21，即 s1 需 ≤ (1<<11)）
s2 占中间 11 位（位移 10）
c1 占 5 位（位移 5）
c2 占低 5 位
所以各个分量各自只用有限位（s1、s2 ≤ 2047，c1、c2 ≤ 31

trans 是 get_hash 的逆运算：把打包好的整数拆回四元组。
x>>21 取最高 11 位 → s1
(x & ((1<<21)-1))>>10 取中间 11 位 → s2
(x & ((1<<10)-1))>>5 取 5 位 → c1
x & ((1<<5)-1) 取最低 5 位 → c2

N = 3*10^7：哈希桶数组 head[] 大小
M = 7*10^6：可容纳的条目数（key[]、val[]、pre[]）
p = 1e9+7：模数
K = 5*10^5：d[] 数组大小（n 的上界）
cnt：当前条目数
head[pos]：桶 pos 的第一条链表头
pre[i]：条目 i 的链表前驱
val[i]：条目 i 的累加值（计数）
key[i]：条目 i 的键（打包后的整数）
桶位置取 now % (N-4)。
若键已存在，直接累加 val[i] 并返回；
否则新增条目 i（头插法）
清空整张表（重置计数器、链表、值）
swap：交换两张哈希表的内部分配（整个底层数组整体交换）。用于"滚动交换当前表与下一层表"
声明两个哈希表：f1 当前层、g1 下一层

Popcnt[] 是 0..(2^21-1) 的汉明重量查表。
对一个 64 位 ll x，拆成高 21 位与低 21 位（注意这里只覆盖低 42 位，因为题目里 m 不大，且这里逻辑用低 21 + 次高 21）。
x>>21 取高位段，x & ((1<<21)-1) 取低位段，两者 popcount 相加

mx23：所有 ≤23 的 d 的最大值
m：字符串长度
mn：前半部分位数（≤31 或取 min(实际, 31)）
mx：(1 << (m-mn)) - 1，后半部分对应的掩码
S1：当前状态列表，元素是 {位掩码, 方案数}
Stmp：临时中转列表
s：字符串中所有 0 的位置组成的位掩码（目标集合）
mp：map，用于把相同位掩码累加计数

func(x) 处理小步长 x：
枚举所有同余类起点 i（0..x-1），并把从 i 开始、步长为 x 的所有位置加入掩码 tmp（j=i; j<m; j+=x）。
检查 (tmp & s) == tmp，即 tmp 选中的位置都必须是字符串中的 0（都在目标集 s 内），否则跳过。
若 x 是最大的小步长 mx23，则把状态打包成 4 元组插入哈希表 f1（进入 meet-in-the-middle 的下半场，用 popcount 统计差异）；
否则先把状态累积到 mp（map 去重计数）或 Stmp。
最后把 S1 与 Stmp 交换，准备下一轮
trans(x, y) 在步长变化时对状态进行平移重打包（把位数从 y 压到 x）：
对哈希表 f1 的每个非零条目做变换（这是 DP 的状态转移）。
tmp1、tmp2 截取新的 s1、s2 片段。
delta1、delta2 是位被"移动"造成的差异。
更新 c1、c2 计数器（加入被移动位数的 popcount）。
写入 g1，然后 f1 与 g1 交换
func2(x) 处理中等步长 x 的扩展（在 s1/s2 间、边界处搭桥）：
对每个状态 now，枚举"缺口位置 q"，尝试在左右两侧各放一个新位（str[q]、str[q+x] 都是 0），并检查合法性（(tmp&s)==tmp）。
三种情况：q 和 q+x 都在中间、q+x 超出右界（只放左边）、q < 0（只放右边）。
后面几行是对 c1、c2 两个计数器的"消耗/迁移"型转移（比如用 c1 个已选位做某种组合）。
最后交换 f1/g1
func3(x) 对大步长 d ≥ m（超过字符串长度）做了多项式（生成函数）型 DP：
f2[k] 表示当前"选 k 个目标位"的方案数（多项式系数的 DP）。
转移：对每个大步长，乘上 (x-m) 的系数、加上 i 倍当前项、并向前递推 i+1 项。
本质是在做多项式的"卷积式"递推，把所有大步长 d ≥ 23 的处理合并到多项式系数数组上，避免 2^m 量级的位域爆炸


用递推填好 popcount 查表（Popcnt[i] = Popcnt[i>>1] + (i&1)）
读入字符串 str 与步长个数 n，m = 串长。
把 str 中所有 '0' 的位置置位到目标掩码 s（低位对应位置 0
读入每个步长 d[i] 及其权重 x，累乘 ans *= d[i]^(x-1) mod p（这就是前面 pw 的用途）。
对步长排序；mn = min(m, 31) 决定低位分段位数上限（≤31）
初始状态 S1 = {(0, 1)}（空掩码，方案 1）。
找最大小步长 mx23；对非小步长，收缩 mn（保证分段位数）。
mx 是后半段全 1 掩码
依次对所有小步长调用 func 扩展状态
若根本没有小步长（mx23==0），则直接初始化哈希表 f1 为单个初始状态
处理中步长（>23 且 < m）：先用 trans 做一次维数压缩切换（当步长从 lst 变到 d[i]，且 d[i]≠37 时），再做 func2 扩展。lst 记录上一个中步长。
（d[i]==37 的特殊跳过，可能是题目有特判需求。）
把哈希表 f1 中的每个合法状态的方案数，按 "选中位数"（s1 的 popcount + s2 的 popcount + c1）累加进多项式数组 f2[]，完成 meet-in-the-middle 两半的汇合
cntS 是目标集合 s 中 0 的个数（总需要覆盖的位数）。
对所有大步长（d ≥ m 且 >23）调用 func3 做多项式 DP
最终答案 = f2[cntS]（恰好覆盖所有 0 的方案数）乘上之前累乘的 ans（大步长权重部分），再模 p 输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ud unsigned
#define ll long long
#define pll pair<ll, ll>
using namespace std;

struct quad {
    ud s1, s2, c1, c2;
    quad(int s1, int s2, int c1, int c2) : s1(s1), s2(s2), c1(c1), c2(c2) {}
};
ud get_hash(ud s1, ud s2, ud c1, ud c2) {
    return (s1<<21)|(s2<<10)|(c1<<5)|c2;
}
quad trans(ud x) {
    return quad(x>>21, (x&((1<<21)-1))>>10, (x&((1<<10)-1))>>5, x&((1<<5)-1));
}

constexpr int N = 3e7+5, M = 7e6+5, p = 1e9+7, K = 5e5+5;

struct Hashtable {
    int cnt, pre[M]{}, head[N]{}, val[M]{};
    ud key[M]{};
    Hashtable() {
        cnt = 0;
        memset(pre, -1, sizeof(pre));
        memset(head, -1, sizeof(head));
    }
    void add(ud now, int y) {
        int pos = now % (N-4);
        for (int i = head[pos]; ~i; i = pre[i])
            if (key[i] == now) { (val[i]+=y) %= p; return; }
        pre[++cnt] = head[pos];
        val[cnt] = y;
        key[cnt] = now;
        head[pos] = cnt;
    }
    void clear() {
        cnt = 0;
        memset(pre, -1, sizeof(pre));
        memset(head, -1, sizeof(head));
        memset(val, 0, sizeof(val));
    }
    void swap(Hashtable &o) {
        std::swap(head, o.head);
        std::swap(val, o.val);
        std::swap(pre, o.pre);
        std::swap(key, o.key);
        std::swap(cnt, o.cnt);
    }
} f1, g1;

ll pw(ll x, ll y) {
    ll ans = 1, now = x;
    while (y) {
        if (y&1) ans = ans*now%p;
        now = now*now%p;
        y >>= 1;
    }
    return ans;
}


int Popcnt[1<<21|5];
int popcnt(ll x) {
    return Popcnt[x>>21]+Popcnt[x&((1<<21)-1)];
}

int mx23, m, mn, mx;
vector<pll> S1, Stmp;
ll s;
map<ll, ll> mp;
void func(int x) {
    if (x == mx23) {
        for (auto &[fst, snd] : S1)
            for (int i = 0; i < x; ++i) {
                ll tmp = fst;
                for (int j = i; j < m; j += x) tmp |= 1ll<<j;
                if ((tmp&s) != tmp) continue;
                pll now = {tmp, snd};
                ll mid_now = (now.first&((1ll<<mn)-1))^(now.first&mx),
                mid_goal = (s&((1ll<<mn)-1))^(s&mx),
                lt_now = now.first&mx, rt_now = now.first>>mn, lt_goal = s&mx, rt_goal = s>>mn;
                f1.add(get_hash((int)(lt_now&lt_goal), (int)(rt_now&rt_goal), popcnt(mid_now),
                    popcnt(mid_now^mid_goal)), now.second);
            }
    } else {
        for (auto &[fst, snd] : S1)
            for (int i = 0; i < x; ++i) {
                ll tmp = fst;
                for (int j = i; j < m; j += x) tmp |= 1ll<<j;
                if ((tmp&s) != tmp) continue;
                if (x != 19) (mp[tmp] += snd) %= p;
                else Stmp.emplace_back(tmp, snd);
            }
        for (auto &it : mp) Stmp.emplace_back(it);
        mp.clear();
    }
    S1.swap(Stmp); Stmp.clear();
}

void trans(int x, int y) {
    for (int i = 0; i <= f1.cnt; ++i) if (f1.val[i]) {
        quad now = trans(f1.key[i]);
        int tmp1 = now.s1&((1<<x)-1), tmp2 = now.s2>>(y-x);
        int delta1 = tmp1^now.s1, delta2 = now.s2^(tmp2<<(y-x));
        int d1 = ((s&((1<<y)-1))^(s&((1<<x)-1)))^delta1,
        d2 = ((s>>(m-y))&((1<<(y-x))-1))^delta2;
        g1.add(get_hash(tmp1, tmp2, now.c1+popcnt(delta1)+popcnt(delta2),
            now.c2 + popcnt(d1) + popcnt(d2)), f1.val[i]);
    }
    f1.swap(g1); g1.clear();
}

string str;
void func2(int x) {
    for (int i = 0; i <= f1.cnt; ++i) if (f1.val[i]) {
        quad now = trans(f1.key[i]);
        for (int q = mn - x; q < m - mn; ++q) {
            if (q >= 0 && q + x < m && str[q] == '0' && str[q+x] == '0') {
                ll tmp = ((now.s2|(1ll<<(q+x-mn)))<<mn)+(now.s1|(1<<q));
                if ((tmp&s) == tmp)
                    g1.add(get_hash(now.s1|(1<<q), now.s2|(1<<(q+x-mn)),
                        now.c1, now.c2), f1.val[i]);
            }
            if (q+x >= m && str[q] == '0') {
                ll tmp = ((ll)now.s2<<mn)+(now.s1|(1<<q));
                if ((tmp&s) == tmp)
                    g1.add(get_hash(now.s1|(1<<q), now.s2, now.c1, now.c2), f1.val[i]);
            }
            if (q < 0 && str[q+x] == '0') {
                ll tmp = ((now.s2|(1ll<<(q+x-mn)))<<mn)+now.s1;
                if ((tmp&s) == tmp)
                    g1.add(get_hash(now.s1, now.s2|(1<<(q+x-mn)), now.c1, now.c2), f1.val[i]);
            }
        }
        if (now.c1)
            g1.add(get_hash(now.s1, now.s2, now.c1, now.c2), now.c1*(ll)f1.val[i]%p);
        if (now.c2)
            g1.add(get_hash(now.s1, now.s2, now.c1+1, now.c2-1), now.c2*(ll)f1.val[i]%p);
    }
    f1.swap(g1); g1.clear();
}

ll g2[45], f2[45];
int cntS;
void func3(int x) {
    for (int i = 0; i <= m; ++i) g2[i] = f2[i]*(x-m)%p;
    for (int i = 0; i <= m; ++i) {
        (g2[i] += i*f2[i]) %= p;
        (g2[i+1] += (cntS-i)*f2[i]) %= p;
    }
    memcpy(f2, g2, sizeof(g2));
}

int n, d[K];
ll ans = 1;
int main() {
    fast;
    for (int i = 0; i < (1<<21); ++i) Popcnt[i] = Popcnt[i>>1] + (i&1);
    cin >> str >> n; m = str.size();
    for (int i = 0; i < m; ++i)
        if (str[i] == '0') s |= 1ll<<i;
    for (int i = 1, x; i <= n; ++i) {
        cin >> d[i] >> x;
        (ans *= pw(d[i], x-1)) %= p;
    }
    sort(d+1, d+1+n); mn = min(m, 31);
    S1.emplace_back(0, 1);
    for (int i = 1; i <= n; ++i) {
        if (d[i] <= 23) mx23 = max(mx23, d[i]);
        else mn = min(mn, d[i]);
    }
    mx = (1<<(m-mn))-1;
    for (int i = 1; i <= n; ++i)
        if (d[i] <= 23) func(d[i]);
    if (!mx23) {
        ll mid_goal = (s&((1ll<<mn)-1))^(s&mx);
        f1.add(get_hash(0, 0, 0, popcnt(mid_goal)), 1);
    }
    int lst = 0;
    for (int i = 1; i <= n; ++i) {
        if (d[i] > 23 && d[i] < m) {
            if (lst && d[i] != 37) trans(m-d[i], m-lst), mn = d[i], mx = (1<<(m-mn))-1;
            func2(d[i]);
            lst = d[i];
        }
    }
    for (int i = 0; i <= f1.cnt; ++i) {
        if (f1.val[i]) {
            quad now = trans(f1.key[i]);
            (f2[popcnt(now.s1)+popcnt(now.s2)+now.c1] += f1.val[i]) %= p;
        }
    }
    cntS = popcnt(s);
    for (int i = 1; i <= n; ++i)
        if (d[i] >= m && d[i] > 23) func3(d[i]);
    cout << f2[cntS]*ans%p << '\n';
    return 0;
}