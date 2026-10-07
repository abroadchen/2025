//
// Created by Psy.C on 2026/10/7.
//
/**
a>>31 在有符号 int 中，如果 a 为负数则得到 -1（全 1），否则 0。a>>31&mod：

若 a<0：(-1)&mod = mod，则 a += mod，把负数修正进 [0, mod)。
若 a≥0：加 0。
所以 update(a) 等价于 把 a 归一化到非负（若为负则加 mod）‍，用于处理减法/可能为负的结果
t[0]=1。
t[i] = (2*t[i-1] - mod) mod-mod-norm = 2^i mod mod。
即 t[i] 存储 2^i 的模 mod 值（用于快速幂式的乘法，因为这里多次出现 <<（×2）操作）。*t = 1 是 t[0]=1 的写法（*t 即 t[0]）
s[x]：块的数值（上限 inf，看作"天文数字"），相当于把块当作一个二进制数。
L[x]：块的位数（bit length）。
f[x]：块的某个 sum 值（模 mod）。
merge(x, y)：把块 y 拼到块 x 的高位上（x 是低位，y 是高位）：

数值上：s_combined = s[x] + s[y] << L[x]（y 左移 x 的位数，作为高位拼接）。
若结果超过 inf（=2e9），就置为 inf（表示"溢出/大到无法再比较"，用于后续 ≥0 判断时不继续合并）。
f[x] += f[y] * 2^{L[x]}（模 mod）：f 也按同样位权拼接，但用模运算。
L[x] += L[y]：合计位数。
这个 merge 是在把两个二进制块做不进位的二进制连接（按位拼接），保持二进制数字的语义。s 用于真实比较（判断正负/大小），f 是模版本的数值，L 记录位数。

关键判断：L[x] > 30 && s[x] > 0 或数值超 inf → 置 inf。这用于"数字太大时标记为大正数"
pr[i] 存储从位置 i 到 n 的一个"二进制串前缀哈希/数值"
pr[i] = 2*pr[i+1] + a[i]，这是从右往左构造的字符串哈希，把 a[n]...a[i] 看作一个二进制数/数串的高位到低位。

那么 calc(l,r) = (pr[l] - pr[r+1]*2^{r-l+1}) mod，就是从 pr[l] 中"砍掉"位置 r+1 之后的部分，得到子串 a[l..r] 对应的数值模 mod。

pr 的递推方向（从 n 到 1），结合询问前缀和，是标准的哈希前缀和（这里 base=2）


目标问题语义：这应该是：给定一个数组 a[1..n]（每个元素为数位/数值），需要支持某种"把相邻数合并成更大块，确保块的值保持某种单调/非负性质"，然后查询区间 [l,r] 的一个求和值。
并查集的合并条件：while (find(i) > 1 && s[find(i)] >= 0)——从当前位置 i 开始，只要"当前块的非负且还能往左"，就把左边的块并进来。也就是说，每个块被合并直到块值为负（或到边界）‍。这是一种贪心划分数组成若干"最大且前缀符 ≥0"的块（类似"最大子段划分/单调栈"）。因为 a[i] 初值允许为负，合并时 s 是真实数值相加（高位拼接后可能仍为负或正），当 s[find(i)] < 0 时停止——保证每个块的累计值是"最后一次 ≥0 后变负"前能并则并。
实际上这个 while 是：从位置 i 向左，只要 find(i) 表示的最左块还没并到头，并且整合后总块值 ≥0，就继续并入左边的块。这样最终每个块是 "连续右端点 i 的一段前缀，段内任意分割后 ≥0"？核心是保证块的累计值 s 在并入下一个左边块前 ≥0，以控制大小。当块值超过 inf 时报为 inf（巨大正数），于是会一直向左合并到边界——表示一段极大的正数。
find(find(i)-1)：块左边相邻位置的块（因为合并是连续的，find(i)-1 是 i 所在块左边位置的 leader）。
ps[find(i)] = ps[左边块的ps] + f[当前块]：按块顺序的 f 值前缀和（这是把 f 当作该块的一个贡献值累加）


① 并查集合并条件
while (find(i)>1 && s[find(i)]>=0)：

只要当前位置所在的块最左还没到边界，并且整并之后块值仍 ≥0，就把左边相邻的块再并进来。
注意当 s[x]=inf 时 s[x]>=0 恒真，说明一旦出现"大得超限的正数块"，它会一路向左合并直到 find==1。这样 s 的真实值就用于判断块内前缀是否保持非负 / 控制合并终点（一个贪心的"最大合法段"划分）。
② ps：块顺序上的前缀和

find(find(i)-1) 是当前块左侧相邻块的 leader（因为合并是连续的，find(i)-1 必是左侧块的末尾）。
ps[当前块] = ps[左侧块] + f[当前块]（取模）。f 在这里被当作每个块的"整块贡献值"，ps 是按块顺序做的累计和。
③ 询问 [l,r] 的答案构成

从 l 到 r 的整段被并查集切成了若干块，其中 l 位于块的中间、其余是完整块。
答案 = 2 ×（l 所在块之后、直到 r 所在块的各完整块 f 之和）+ l 所在块内"从 l 到该块末尾"的子串值。
ps[find(i)]-ps[find(l)] 给出完整块的和，整体左移一位（×2，与块间的位权有关）；
calc(l, find(l)+L[find(l)]-1) 是 l 在其所在块内的后缀子串哈希值。
这正是"段内分裂求和"的分解：完整块用 ps 前缀和一次算掉，碎的一块用哈希 calc 补上。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 5e5+7, mod = 1e9+7, inf = 2e9+5;

inline void update(int& a) { a += a>>31&mod; }
int t[N];
void init(int n) {
    for (int i = *t = 1; i <= n; ++i)
        update(t[i]=(t[i-1]<<1)-mod);
}
int fa[N], L[N], s[N], f[N];
inline int find(int x) { return x == fa[x]? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
    fa[y] = x;
    if (L[x] > 30 && s[x] > 0 || s[x]+((ll)s[y]<<L[x]) >= inf) s[x] = inf;
    else s[x] += s[y]<<L[x];
    f[x] = (f[x] + (ll)f[y]*t[L[x]])%mod;
    L[x] += L[y];
}

int pr[N];
inline int calc(int l, int r) {
    return (pr[l]-(ll)pr[r+1]*t[r-l+1]%mod+mod)%mod;
}

int a[N], ps[N], ans[N];
vector<ii> v[N];
int main() {
    fast;
    int n, m; cin >> n >> m; init(n);
    for (int i = 1; i <= n; ++i)
        cin >> a[i], update(f[i]=s[i]=a[i]);//初值：单元素块，数值=a
    for (int i = n; i; --i)
        pr[i] = ((ll)(pr[i+1]<<1)+a[i]+mod)%mod;//构建哈希前缀
    for (int i = 1; i <= n; ++i) fa[i] = i, L[i] = 1;//初始每个位置自成一个块
    for (int i = 1, l, r; i <= m; ++i) {
        cin >> l >> r;
        v[r].emplace_back(l, i);//按右端点分组离线存查询
    }
    for (int i = 1; i <= n; ++i) {
        while (find(i) > 1 && s[find(i)] >= 0)//把当前位置 i 向左边"连续合并"，只要左边合并后仍是"非负"值
            merge(find(find(i)-1), find(i));
        //ps：按顺序对已确定块的 f 累加（前缀和）
        update(ps[find(i)]=ps[find(find(i)-1)]+f[find(i)]-mod);
        for (auto [fst, snd] : v[i]) {//处理以 i 为右端点的查询
            int l = fst, id = snd;
            ans[id] = ((ll)(ps[find(i)]-ps[find(l)]+mod)*2+
                calc(l, find(l)+L[find(l)]-1)+mod)%mod;
        }
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}