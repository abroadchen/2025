//
// Created by Psy.C on 2026/9/25.
//
/**
siz：当前回文自动机节点总数。
lst：上次插入后所在节点（last）。
fail[N]：回文自动机的 fail 指针（最长真回文后缀）。
len[N]：节点 u 代表的回文串长度。
bd[N]：节点 u 的 half-fail / series 链接（最长长度 ≤ len[u]/2 的回文 border 对应的节点），用于 O(log n) 求周期
a[N]：字符串（处理后为 1..26 的小写数字）。
son[N][26]：字典树转移（每条边一个字符）。
dp[N]：记录"该回文串能由几个相同的短回文重复得到"的层数（详见 insert）。
sz[N]：回文节点在 fail 树上的子树大小（该回文串在原串中的出现次数统计，通过拓扑累计）
建立两个初始节点：
节点 0：偶回文根，len[0]=0。
节点 1：奇回文根，len[1]=-1（方便处理单字符回文）。
fail[0]=fail[1]=1：两个根的 fail 都指向奇根（奇根是"空"的通用根）。
bd[0]=0, bd[1]=1：half 链接初值

id 是当前字符在串中的下标
从 lst 开始，沿 fail 找最长的回文后缀 p，使得在其两边各加 a[id] 能构成新回文：
检查 a[id] == a[id - len[p] - 1]（即新字符与回文左边对应位置字符相等），不满足就 p = fail[p] 跳到更短的后缀回文。
找到 p 后，若转移 son[p][a[id]] 不存在，说明要新建节点；否则沿用已有节点
新建节点 u。
求新节点 u 的 fail：从 fail[p] 出发找能扩展出回文的节点 v，fail[u] = son[v][a[id]]。
len[u] = len[p]+2：新回文比 p 长的回文左右各加 1 个字符。
长度 ≤2 时，bd[u] = fail[u]。
否则，参照论文回文自动机 half 链构造：从 bd[p] 开始，不断沿 fail 调整，保证 bd[u] 是长度不超过 len[u]/2 的最长回文 border（series link），然后一步转移到 son[bd[u]][a[id]]
如果 bd[u] 的长度恰好等于 len[u]/2，说明 u 可拆成两个相同的半串（回文 square/palindromic period 结构），则 dp[u] = dp[bd[u]] + 1（在上层基础上再叠一层）。
否则 dp[u] = 1（自己算第一层）。
dp[u] 的物理意义：u 代表的回文串，按"长度对半分"的方式，最多能迭代拆出多少个相同的更短回文——即该回文串是某个短回文串重复 2^dp 层（这里其实是按二分的 board 结构近似，但常用作 Codeforces 17E 类题中统计"一个串由某个全回文重复"的计数）
让该回文节点出现次数 sz 增加（出现位置计数，后面沿 fail 树累加得到出现次数）。
lst 更新到当前节点

读入字符串（下标从 1 开始）。
a[i] -= 96：把字符 'a'..'z' 转成 1..26 的数字（'a'=97 → 1）。
逐个字符 insert(i) 构建回文自动机
回文自动机的 fail 树中，父节点（更短的回文）长度严格小于子节点，因此按 len 排序即得 fail 树的拓扑序。
用计数排序（桶 buc 按长度）把所有节点按长度从大到小排到 ord[]。
ord[0]=1, ord[1]=0：把两个根放前面（便于后面按序处理时跳过根)
按拓扑序（长度从大到小），sz[fail[u]] += sz[u]。
累加后，sz[u] 表示节点 u 代表的回文串在整个字符串中的出现次数（每个节点 + 它的所有 fail 后代）
ans[dp[j]] += sz[j]：把每个回文节点按其 dp 层数归类，累加出现次数。
从大到小做后缀和，ans[j] += ans[j+1]。
这样 ans[i] 表示"所有 dp ≥ i 的回文节点出现次数之和"。
逐行输出 ans[1..n]
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e6+5, M = 26;

int siz, lst, fail[N], len[N], bd[N];
void init() {
    siz = lst = 1;
    fail[0] = fail[1] = 1;
    len[1] = -1; len[0] = 0;
    bd[0] = 0; bd[1] = 1;
}

char a[N];
int son[N][M+1], dp[N], sz[N];
void insert(int id) {
    int p = lst;
    while (a[id] != a[id-len[p]-1]) p = fail[p];
    if (!son[p][a[id]]) {
        siz++;
        int u = siz, v = fail[p];
        while (a[id] != a[id-len[v]-1]) v = fail[v];
        fail[u] = son[v][a[id]];
        son[p][a[id]] = u;
        len[u] = len[p] + 2;
        if (len[u] <= 2) bd[u] = fail[u];
        else {
            bd[u] = bd[p];
            while (a[id] != a[id-len[bd[u]]-1] ||
                (len[bd[u]]+2)*2 > len[u]) bd[u] = fail[bd[u]];
            bd[u] = son[bd[u]][a[id]];
        }
        if (len[bd[u]] == len[u]>>1) dp[u] = max(0, dp[bd[u]]) + 1;
        else dp[u] = 1;
    }
    sz[son[p][a[id]]]++;
    lst = son[p][a[id]];
}

int buc[N], ord[N];
ll ans[N];
int main() {
    init();
    scanf ("%s", a+1);
    int n = strlen(a+1);
    for (int i = 1; i <= n; i++) a[i] -= 96;
    for (int i = 1; i <= n; i++) insert(i);
    for (int i = 2; i <= siz; i++) buc[len[i]]++;
    for (int i = 1; i <= n; i++) buc[i] += buc[i-1];
    for (int i = siz; i >= 2; i--) ord[(buc[len[i]]--)+1] = i;
    ord[0] = 1; ord[1] = 0;
    for (int j = siz; j >= 2; j--) {
        int u = ord[j];
        sz[fail[u]] += sz[u];
    }
    for (int j = 2; j <= siz; j++) ans[dp[j]] += sz[j];
    for (int j = 22; j >= 1; j--) ans[j] += ans[j+1];
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
    return 0;
}