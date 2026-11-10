//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
n：元素值域大小（编号 1..n）。
m：序列个数。
s：阈值 √n/3。
vis[N]：标记/位置数组，两种用法（见下）。
vec[N]：存储 m 个序列（vec[i] 是第 i 个序列）。
to[N]：邻接表，存"相邻约束边" (u,v)，含义是 u 必须在 v 之前
clear：把 x 和一个临时空对象 y 交换，从而把 x 清空成默认构造的空状态（用于清空 vector）。注意不释放内存，只是逻辑清空
新增的字符串重载（上一轮编译失败就是因为没有它）：逐字符把 string 输出。这才是本段新增、让题目能通过的关键修复
读入 n（的值域大小）、m（序列个数）。
计算阈值 s = √n/3（n 是 int，先变 double 开方再除 3，再截断成 int）。用于区分"短序列 / 长序列"，是分块平衡复杂度的关键参数。
多组数据：把 m 个序列、n 个邻接表全部清空（用上面的 clear），vis[i] 置 0。
vis[i]=0 这里表示"未作标记"（第一轮用 0 表示空
读第 i 个序列的长度 sz，resize 后逐元素读入 v，存进 vec[i]
仅对"短序列"（长度 ≤ 阈值 s）建相邻约束边。
对序列中每个位置 j，对每个更早相邻对 (k, k+1)：在 to[vec[i][j]] 上挂一条边 (vec[i][k], vec[i][k+1])。
语义：vec[i][k] 必须出现在 vec[i][k+1] 之前——这是序列给出的全部"先后"约束。
to 的下标是"后出现的元素"（vec[i][j]），存的是它前面的所有相邻对
遍历每个"后元素" i 的所有入边 (u,v)：
若 vis[u] 非零 且 ≠ 当前 v → 同一个前驱元素 u 被要求排到两个不同后继前 → 矛盾 → 输出 "Human" 并返回。
否则记录 vis[u] = v。
views::keys（来自 <ranges>）取出所有边里第一个元素 u，把它们的 vis[u] 清 0，准备下一段。
作用：在"相邻对"层面检查是否存在某个元素有矛盾的前驱后继
把 vis[] 全部设成 -1（新用途：-1 表示"该元素还没被本序列标记"）。
遍历长序列 i（长度 ≥ 阈值，作为基准）
把 i 中出现的每个元素标记上它在 i 里的下标 j
遍历其他序列 j，只有 j<i（避免重复比对 i↔j 两次）‍或 j 是短序列时才检查——这是去重 + 控制复杂度。
目的：把"长 i"和"其余 j"两两比对相对顺序是否一致。
cur=-1 记录"j 中上一个同时也在 i 里的元素，其在 i 中的最后位置"。
从 j 的末尾往前倒序遍历，只处理那些 vis[元素] ≠ -1（即也在基准序列 i 中出现）的元素。
-k = k != -1；-vis[...] = vis[...] != -1
pos = 该公共元素在 i 中的位置。
若 cur < pos：说明在 j 中靠后的元素，在 i 中的位置也更靠后，顺序一致，更新 cur=pos。
否则（cur >= pos）：j 和 i 的先后顺序发生冲突。此时要求 j 中该元素的后一个元素 vec[j][k+1] 必须等于 i 中对应后一个 vec[i][pos+1]，否则矛盾 → "Human"。
外层每处理完一个长序列 i，把它的元素 vis 全部还原成 -1，供下一个基准 i 复用。
全部检查无冲突 → 存在一致的全局顺序 → 输出 "Robot"
*/
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ii pair<int, int>
using namespace std;

constexpr int N = 3e5+10;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}
template<typename T>
void clear(T &x) {
    T y;
    swap(x, y);
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}
void write(const string& s){ for(char c:s) putchar(c); }
template<class... T>
void println(const T &...x) {
    write(x...), putchar(10);
}

int n, m, s, vis[N];
vector<int> vec[N];
vector<ii> to[N];
void solve() {
    read(n, m); s = sqrt(n)/3;
    rep(i,m) clear(vec[i]);
    rep(i,n) clear(to[i]), vis[i] = 0;
    rep(i,m) {
        int sz; read(sz); vec[i].resize(sz);
        for (int &v : vec[i]) read(v);
        if (sz <= s) {
            for (int j = 0; j < sz; j++)
                for (int k = 0; k+1 <= j; k++)
                    to[vec[i][j]].emplace_back(vec[i][k], vec[i][k+1]);
        }
    }
    rep(i,n) {
        for (auto [u, v] : to[i]) {
            if (vis[u] && vis[u] != v) return println("Human"s);
            vis[u] = v;
        }
        for (auto u: to[i] | views::keys) vis[u] = 0;
    }
    memset(vis, -1, sizeof(vis[0])*(n+2));
    rep(i,m) if (vec[i].size() >= s) {
        for (int j = 0; j < vec[i].size(); j++) vis[vec[i][j]] = j;
        rep(j,m) if (j != i && (j < i || vec[j].size() <= s)) {
            int cur = -1;
            for (int k = vec[j].size()-1; ~k; k--) if (~vis[vec[j][k]]) {
                int pos = vis[vec[j][k]];
                if (cur < pos) cur = pos;
                else {
                    if (vec[j][k+1] != vec[i][pos+1])
                        return println("Human"s);
                }
            }
        }
        for (int j : vec[i]) vis[j] = -1;
    }
    println("Robot"s);
}


int main() {
    fast;
    int T; read(T);
    while (T--) solve();
    return 0;
}