//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
动态开点单点插入：把位置 pos 插入线段树，节点不存在则新建（cnt 编号）。用于记录某个 SAM 状态的 endpos 位置
区间查询：判断该线段树（某个 SAM 状态）在 [L, R] 范围内是否存在 endpos。空节点直接返回 0。两半区间结果用 |=（有任一即真）
线段树合并：把两棵树（两个子节点的 endpos 集）合并成新树，都为空则返回非空那棵，否则新建节点递归合并左右子树。用于把 SAM 的 endpos 集合自底向上汇总
lst：最近一次插入的位置（last）。
tot：SAM 节点总数（1 为根/初始状态）。
len[i]：状态 i 对应子串的最长长度。
ch[i][c]：转移边。
pa[i]：后缀链接（parent）。
e[i]：状态 i 关联的 endpos 位置（仅终止状态有）。
rt[i]：状态 i 的线段树根。
G[i]：parent 树上以 i 为父节点的子节点列表
标准在线 SAM 构建：
新建 np 表示新前缀。
沿后缀链接补齐转移边。
若无祖先转移则直连根；否则引入/复用 clone 节点 nq（处理"分裂"情况）
后序遍历 parent 树。每次把子节点的线段树合并到父节点，父节点 endpos 集 = 自身 + 所有子孙的并集。这样 rt[x] 就是状态 x 的完整 endpos 集合。
把所有非根节点的父子关系建图，从根 1 开始 dfs 合并 endpos
打印答案字符串
从状态 now 出发，找第一个大于字符 c、且其 endpos 落在 [l+len-1, r] 区间内的转移字符（字典序最小的可行后继）。返回该字符；找不到返回 '#'

读入模式串 s（长度 sl），目标：求按字典序紧跟 s 之后、且是 s[l..r] 子串的最小字符串
now：SAM 中当前匹配到的状态（从根开始）。
path：记录走过状态的路径（含根）。
ans：构造出的答案字符序列。
len：当前匹配的公共长度
对模式串每个字符：
从 当前字符 s[i] 开始向后扫描字符 pos（即找字典序 ≥ 该字符的第一可能转移）。
条件：SAM 有转移且该状态的 endpos 落在合法区间 [l+len, r]（下标对得上）。
若找到，推进；若该字符恰好等于模式串字符，继续匹配下一个；若找到更大字符（pos != s[i]），说明此处已可构造出更大字符串，直接输出 ans 结束。
若整轮没找到（ck == 0），标记 tag=1，说明模式串本身无法完全匹配，跳到第二阶段"回退找更大前缀"
从字符串尾部向前尝试：每回退一步，就用 check 找"当前前缀状态下，能替换成的下一个更大合法字符"。若找到就输出；全部失败输出 -1（无解
模式串能完全匹配时，尝试在末尾追加一个可行字符（从 a 起找最小合法），成功即输出。
追加失败则同样回退替换（逻辑同第二阶段）

读入母串，构建 SAM。
二次遍历母串，沿正确转移找到每个前缀的终止状态，把位置 i 记为 e[now]（endpos）。
build()：合并 endpos 集合
对每次询问：读入母串区间 [l, r] 和模式串 s，调用 solve 输出答案（或 -1）




len[i]：状态 i 中最长子串的长度。状态内的子串长度形成一个连续区间 [len[pa[i]]+1, len[i]]。
pa[i]（后缀链接）：指向另一个状态，其代表的最长子串是状态 i 里最短子串的一个后缀。所有后缀链接构成一棵 parent 树，根是 1。
lst：当前自动机的"最新状态"，即最长整个串所在的状态。
ch[p][c]：从状态 p 读入字符 c 后的转移

p 记录旧 last，np 是新增状态，代表插入新字符后形成的新完整前缀。
len[np] = len[old_last] + 1：新前缀只比旧前缀长 1。
把 lst 更新为 np（下次插入由此继续）
从当前节点 p 开始，沿后缀链接向上走，只要遇到"没有字符 c 转移"的祖先，就给它补上指向 np 的转移。
这样保证：从这些状态出发也能识别"以新字符结尾"的子串（它们原本没有 c 的定义，现在补到 np）。
循环在第一个已有 c 转移的祖先处停下（或到根 p=0 停）
情况 A：跑到根了（!p）‍
说明根到所有祖先都不认识字符 c，新字符是全新开头。新状态 np 的后缀链接直接连到根 1
情况 B：在祖先 p 处发现了已存在的转移 q = ch[p][c]

这里要判断：q 能否直接作为 np 的后缀链接？分两小种：

情况 B1：len[q] == len[p] + 1
含义：状态 q 的最长子串长度就等于 len[p]+1（即 p 加一个 c）。
这说明 q 代表的子串区间正好能与 np 平滑衔接，q 直接就是 np 的一个合法后缀状态，直接连即可。
情况 B2：len[q] > len[p] + 1（q 太长，需要克隆）‍
为什么需要 clone？因为 q 里包含的子串长度区间过大，np 只需要其中"长度为 len[p]+1、以 c 结尾"的那一段。直接让 np 连 q、让 q 作为 suffix link 会破坏状态划分的简洁性。
解决办法：造一个新状态 nq，它的最长子串长度正好是 len[p]+1，作为 q 和 np 共同的"更靠近前缀"的代表。
把 q 的全部转移复制给 nq（因为 nq 代表 q 的子集，继承同样的后缀转移）。
最后回头把所有"本应走到 q、但实际正好命中 this c 前缀"的祖先转移重定向到 nq，保持自动机正确性。

*/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 4e6+10, M = 3e5+10;

namespace SGT {
    int ls[N], rs[N], cnt;
    void change(int &x, const int &l, const int &r, const int &pos) {
        if (!x) x = ++cnt;
        if (l == r) return;
        int mid = (l+r)>>1;
        if (pos <= mid) change(ls[x], l, mid, pos);
        else change(rs[x], mid+1, r, pos);
    }
    bool query(const int &x, const int &l, const int &r, const int &L, const int &R) {
        if (!x) return 0;
        if (l >= L && r <= R) return 1;
        int mid = (l+r)>>1, res = 0;
        if (L <= mid) res = query(ls[x], l, mid, L, R);
        if (mid < R) res |= query(rs[x], mid+1, r, L, R);
        return res;
    }
    int merge(const int &x, const int &y) {
        if (!x || !y) return x|y;
        int p = ++cnt;
        ls[p] = merge(ls[x], ls[y]);
        rs[p] = merge(rs[x], rs[y]);
        return p;
    }
}
using namespace SGT;

int al;
namespace SAM {
    int lst(1), tot(1), len[M], ch[M][26], pa[M], e[M], rt[M];
    vector<int> G[M];
    void insert(const int &c) {
        int p = lst, np = ++tot;//p=上一个last节点，np=新建节点
        lst = tot; len[np] = len[p] + 1;//更新last，np表示的新前缀长度+1
        for (; p && !ch[p][c]; p = pa[p]) ch[p][c] = np;//补齐转移边
        if (!p) pa[np] = 1;//一直回溯到根都没转移→直连根
        else {//找到了有转移的祖先
            int q = ch[p][c];//q是祖先p经c到达的节点
            if (len[q] == len[p] + 1) pa[np] = q;//可直接使用q
            else {//需要clone一个nq
                int nq = ++tot; len[nq] = len[p] + 1;
                pa[nq] = pa[q]; pa[q] = pa[np] = nq;//更新后缀链接
                memcpy(ch[nq], ch[q], sizeof ch[q]);//复制q的全部转移
                for (; p && ch[p][c] == q; p = pa[p]) ch[p][c] = nq;//重定向
            }
        }
    }
    void dfs(int x) {
        if (e[x]) change(rt[x], 1, al, e[x]);
        for (auto v : G[x]) {
            dfs(v);
            rt[x] = merge(rt[x], rt[v]);
        }
    }
    void build() {
        for (int i = 2; i <= tot; ++i) G[pa[i]].push_back(i);
        dfs(1);
    }
}
using namespace SAM;

inline void out(const vector<char> &c) {
    for (auto i : c) putchar(i);
    putchar('\n');
}
char check(int now, char c, int len, int l, int r) {
    int v = c - 'a';
    for (int i = v+1; i < 26; ++i)
        if (ch[now][i] && query(rt[ch[now][i]], 1, al, l+len-1, r))
            return i + 'a';
    return '#';
}

int sl;
char s[M];
void solve(int l, int r) {
    int now = 1;
    vector<int> path; vector<char> ans; path.push_back(1);
    int len = 0, tag = 0;
    for (int i = 1, pos, ck; i <= sl; ++i) {
        ck = 0;
        for (pos = s[i]-'a'; pos < 26; ++pos)
            if (ch[now][pos] && query(rt[ch[now][pos]], 1, al, l+len,r)) {
                ck = 1; break;
            }
        if (!ck) { tag = 1; break; }
        ans.push_back(pos+'a');
        if (pos != s[i]-'a') { out(ans); return; }
        path.push_back(ch[now][pos]);
        len++;
        now = ch[now][pos];
    }
    if (tag) {
        int pl = (int)path.size();
        for (int i = pl-2; ~i; --i) {
            char lst = check(path[i], s[len-pl+1+i+1], len-pl+1+i+1, l, r);
            ans.pop_back();
            if (lst == '#') continue;
            ans.push_back(lst); out(ans); return;
        }
        puts("-1");
        return;
    }
    for (int nxt = 0; nxt < 26; ++nxt)
        if (ch[now][nxt] && query(rt[ch[now][nxt]], 1,al, l+len, r)) {
            ans.push_back(nxt+'a');
            out(ans); return;
        }
    int pl = (int)path.size();
    for (int i = pl-2; ~i; --i) {
        char lst = check(path[i], s[len-pl+1+i+1], len-pl+1+i+1, l, r);
        ans.pop_back();
        if (lst == '#') continue;
        ans.push_back(lst); out(ans); return;
    }
    puts("-1");
}

int n;
int main() {
    scanf("%s", s+1); sl = strlen(s+1); al = sl;
    for (int i = 1; i <= sl; ++i) insert(s[i]-'a');
    for (int i = 1, now = 1; i <= sl; ++i) {
        int v = s[i]-'a'; now = ch[now][v]; e[now] = i;
    }
    build();
    scanf("%d", &n);
    while (n--) {
        int l, r; scanf("%d%d", &l, &r);
        scanf("%s", s+1); sl = strlen(s+1);
        solve(l, r);
    }
    return 0;
}