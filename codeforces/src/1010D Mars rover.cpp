//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
N = 1e6+10：节点数量上限，约一百万。
M = 100：装操作名字符串的缓冲长度。
op[u]：节点类型。0=输入变量（IN），1=NOT，2=AND，3=OR，4=XOR。
l[u], r[u]：左右孩子编号。NOT 只用左孩子；AND/OR/XOR 用左右。
val[u]：该节点在当前输入下的布尔值（0/1）。
f[u]：标记数组，1 表示"翻转 u 这个子树的输出会导致根最终输出翻转"，0 表示不影响。
s：读取每一行操作词的缓冲区
只取操作词的首字母判断类型：

NOT → N → 1
AND → A → 2
OR → O → 3
XOR → X → 4
其它（IN）→ 0
这样无需整串比较，快
读入 n 个节点：
若是门（op[i]!=0）：先读左孩子 x；若是 AND/OR/XOR（op[i]>1）再读右孩子 y。
若是 IN（op[i]==0）：直接读入该输入的初始值 val[i]（0 或 1）。
然后 dfs(1) 求所有节点值，dfs2(1) 做敏感性分析。
最后遍历所有 IN 叶子，输出 f[i] ^ val[1]：
val[1] 是当前根输出。
若该输入翻转会影响根（f[i]=1），则结果变为 1 ^ val[1] = !val[1]；
若不影响（f[i]=0），结果仍为 0 ^ val[1] = val[1]。
输出 0/1 连成一个字符串（原题要求每行拼起来输出全部答案）
后序遍历：先递归求出所有孩子值，再计算本节点值。

if (!op[u]) return;：输入叶子本身有初值，直接返回。
对门节点：
NOT：val = 1 - val[l]（取反）。
AND：左右相与。
OR：左右相或。
XOR：左右相异或。
结束后 val[1] 就是根节点的当前输出
f[u]=1 的含义："把 u 这个子树整体取反"会连带使根输出取反。从根往下传播这个"敏感性"，只有能一路传到叶子，该叶子翻转才真正影响最终输出。判断规则如下。
翻转唯一孩子 → 本节点必然翻转 → 孩子继续继承敏感性
左=0、右=1（结果0）：翻转左→1，结果变1；翻转右→0，结果仍0。只看左。
左=1、右=0（结果0）：翻转右会改变，只看右。
都=1（结果1）：翻转任何一个变0，结果都变0 → 两者都可影响，都走。
都=0（结果0）：翻转任一仍为0（最多 AND 变 0&1=0）→ 都不走
左=1、右=0（结果1）：翻转左→0，结果变0；翻转右仍1。只看左。
左=0、右=1：翻转右→0 会改变，走右。
都=0：翻转任一个→1，OR 变1，都走。
都=1：翻转任一仍为1，都不走。
异或对两输入完全对称：翻转任意一个输入都会令异或结果取反 → 左右都继承敏感性（本例子树都会翻转）
只对 IN 叶子输出。
f[i]^val[1]：
若 f=1（翻转该输入会改变根）→ 1^val[1] = 翻转后的根值；
若 f=0（不影响）→ 0^val[1] = 当前根值。
所有字符连成一串输出，即为题目要求的所有答案


#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6 + 10, M = 100;

char s[M];
int get(char ch) {
    if (ch == 'N') return 1;
    if (ch == 'A') return 2;
    if (ch == 'O') return 3;
    if (ch == 'X') return 4;
    return 0;
}

int op[N], l[N], r[N], val[N];
int f[N];

// ---- 迭代后序求全部节点的 val ----
// 用显式栈模拟递归后序："先左后右，结算在出栈时"
void dfs_iter() {
    int stk[N], top = 0;        // 手写栈
    int vis[N] = {0};           // 标记是否已处理完孩子
    stk[++top] = 1;
    while (top) {
        int u = stk[top];
        if (!vis[u]) {
            vis[u] = 1;         // 第一次见到：先压入孩子（顺序：左、右）
            if (op[u] == 0) { --top; continue; }   // 叶子，无需处理孩子
            if (op[u] == 1) { stk[++top] = l[u]; } // NOT 只压左
            else { stk[++top] = l[u]; stk[++top] = r[u]; } // 压左、压右
        } else {                // 孩子都已处理完，此时结算本节点
            --top;
            if (op[u] == 1) val[u] = 1 - val[l[u]];
            else if (op[u] == 2) val[u] = val[l[u]] & val[r[u]];
            else if (op[u] == 3) val[u] = val[l[u]] | val[r[u]];
            else if (op[u] == 4) val[u] = val[l[u]] ^ val[r[u]];
        }
    }
}

// ---- 迭代先序传播 f（自顶向下）----
void dfs2_iter() {
    int stk[N], top = 0;
    stk[++top] = 1;
    while (top) {
        int u = stk[top--];
        f[u] = 1;
        if (!op[u]) continue;                    // 叶子
        if (op[u] == 1) { stk[++top] = l[u]; continue; }  // NOT：唯一孩子
        if (op[u] == 2) {                        // AND
            if (val[l[u]] ^ val[r[u]]) {
                if (!val[l[u]]) stk[++top] = l[u];
                else stk[++top] = r[u];
            } else if (val[l[u]]) { stk[++top] = l[u]; stk[++top] = r[u]; }
        } else if (op[u] == 3) {                 // OR
            if (val[l[u]] ^ val[r[u]]) {
                if (val[l[u]]) stk[++top] = l[u];
                else stk[++top] = r[u];
            } else if (!val[l[u]]) { stk[++top] = l[u]; stk[++top] = r[u]; }
        } else if (op[u] == 4) {                 // XOR：左右都走
            stk[++top] = l[u]; stk[++top] = r[u];
        }
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> s; op[i] = get(s[0]);
        if (op[i]) {
            cin >> x; l[i] = x;
            if (op[i] > 1) cin >> y, r[i] = y;
        } else cin >> val[i];
    }
    dfs_iter();      // 后序求值
    dfs2_iter();     // 先序传敏感性
    string ans;
    for (int i = 1; i <= n; i++)
        if (!op[i]) ans += char('0' + (f[i] ^ val[1]));
    cout << ans;
    return 0;
}


*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+10, M = 100;

char s[M];
int get(char ch) {
    if (ch == 'N') return 1;
    if (ch == 'A') return 2;
    if (ch == 'O') return 3;
    if (ch == 'X') return 4;
    return 0;
}

int op[N], l[N], r[N], val[N];
void dfs(int u) {
    if (!op[u]) return;
    dfs(l[u]);
    if (op[u] > 1) dfs(r[u]);
    if (op[u] == 1) val[u] = 1 - val[l[u]];
    else if (op[u] == 2) val[u] = val[l[u]]&val[r[u]];
    else if (op[u] == 3) val[u] = val[l[u]]|val[r[u]];
    else val[u] = val[l[u]]^val[r[u]];
}

int f[N];
void dfs2(int u) {
    f[u] = 1;
    if (!op[u]) return;
    if (op[u] == 1) { dfs2(l[u]); return; }
    if (op[u] == 2) {
        if (val[l[u]]^val[r[u]]) {
            if (!val[l[u]]) dfs2(l[u]); else dfs2(r[u]);
        } else if (val[l[u]]) dfs2(l[u]), dfs2(r[u]);
    } else if (op[u] == 3) {
        if (val[l[u]]^val[r[u]]) {
            if (val[l[u]]) dfs2(l[u]); else dfs2(r[u]);
        } else if (!val[l[u]]) dfs2(l[u]), dfs2(r[u]);
    } else if (op[u] == 4) dfs2(l[u]), dfs2(r[u]);
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> s; op[i] = get(s[0]);
        if (op[i]) {
            cin >> x; l[i] = x;
            if (op[i] > 1) cin >> y, r[i] = y;
        } else cin >> val[i];
    }
    dfs(1), dfs2(1);
    for (int i = 1; i <= n; i++)
        if (!op[i]) cout << (f[i]^val[1]);
    return 0;
}