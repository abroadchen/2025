//
// Created by Psy.C on 2026/10/17.
//
/**
a[N]：存储输入的括号表达式字符串（原始输入，含数字、(、)、?）。
N=1e4+10：字符串最大长度。
M=210：dp 第二维的上限（用于"运算符次数/化简次数"），稍后解释。
inf=1e9：表示"不可达/无穷"的标记值。
tot：当前已经建出的树节点个数（节点编号）。
to[i]：位置 i 的括号匹配的另一半的位置（若 a[i] 是 (，则 to[i] = 对应的 ) 下标；若 a[i] 是 )，则 to[i] 指回那个 (）。由后面的栈匹配填充。
val[i]：叶子节点（单个数字）的值。
dp[i][k][0] / dp[i][k][1]：以节点 i 为根的子表达式，使用第 k 次"某操作"后，能得到的最大值 / 最小值。后面细说（[0]=min，[1]=max）。
ls[i]、rs[i]：表达式树节点 i 的左孩子、右孩子节点编号。
把字符串整体右移一位（从 1 开始下标，a[1..n] 存原字符串，a[0] 丢弃）——方便用 1-based 下标处理。
用栈匹配括号：扫描每个位置 i。

若栈顶是 ( 且当前位置是 )：匹配成功，to[st[top]] = i（记下 ( 对应的 ) 位置），栈顶弹出。
否则若 a[i] 是 ( 或 )：压栈（跳过数字和 ?）。
结束后 to[l] 存的就是与左括号 l 匹配的右括号位置
用栈匹配括号：扫描每个位置 i。

now = ++tot：为该区间申请一个新节点。
while (to[l] == r) ++l, --r;：剥掉外层冗余括号。若区间 [l,r] 本身被一对 () 完全包裹（to[l]==r），则把它们去掉，继续检查剥下一层。
叶子情况 l==r：区间就一个数字字符，val[now]=a[l]-'0'；初始 dp：dp[now][0][0]=dp[now][0][1]=val[now]（0 次操作时，min 和 max 都是该数字本身）。
非叶子：区间内有运算（中间有 ? 表示某种二元运算符号）。
若 to[l] 非 0（说明 a[l]=='('，左边是括号子式）：
校验 a[to[l]+1]=='?'（括号闭合后紧跟运算符 ?），否则 exit(1)。
ls[now]=build(l+1, to[l]-1)：左孩子 = 括号内部的表达式。
rs[now]=build(to[l]+2, r)：右孩子 = ? 之后的表达式。
若 to[l]==0（说明 a[l] 是数字，左边是单个数字叶子）：
校验 a[l+1]=='?'（数字后必须有运算符），否则 exit(2)。
ls[now]=build(l,l)：左孩子 = 单个数字。
rs[now]=build(l+2,r)：右孩子 = ? 之后。
这样就把括号表达式建成一棵二叉树：叶子是数字，内部节点是运算符 ?（具体是 + 还是 - 还没定，这正是下面 dp 要决策/枚举的部分）
这里的 X 是题目给定的限制次数（两个操作 + 和 - 各自允许使用的最多次数上限）。sz 是子树大小，用来限定 dp 维度枚举上限（防止无意义循环）。

这段是核心 min-max 树上背包 DP。先展开含义：

假设题意（这类 CF 题的典型）：表达式里 ? 是一个待定运算符。双方玩家（min 方与 max 方）轮流决定每个 ? 是 + 还是 -，其中一方想把整个表达式的值最大，另一方想最小。X 是"×次数里最多能让多少个位置取某操作"之类的上限（实际是每种运算符的使用次数限制）。

dp[x][k][0] = 以 x 为根、使用了 k 个"某种资源（假设是 + 的个数）"时，在最优 min-max 博弈下能取得的最小值（[0] 表示想最小化的一方主导）。
dp[x][k][1] = 同条件下能取得的最大值（[1] 表示想最大化的一方主导）。

转移：左孩子用 i 个资源、右孩子用 j 个资源，合并到父节点：

合并的资源数有两种：若当前位置的运算符决定为 +，则占用 1 个资源位 → 转移到 k = i+j+1；若决定为 -，不占资源 → k = i+j。（具体资源含义依题意，可能是"+号数量上限 X"，所以 + 占用名额。）
状态组合（min-max 语义下求最大 dp[..][1]）‍：

父取 +：left_max(right_max) → 值 = 左加右。但要在 min-max 博弈下，价值来自 dp[ls][i][1] + dp[rs][j][1]（取两子树各自能保证的最大值，因为 + 时想最大化）。
父取 -：left - right 要最大化，max 方希望左大右小 → 用 dp[ls][i][1] - dp[rs][j][0]（左子树最大值、右子树最小值）。
求最小 dp[..][0]：

父取 +：min 方主导 → 左最小 + 右最小 = dp[ls][i][0] + dp[rs][j][0]。
父取 -：要最小化 left-right，min 方希望左小右大 → dp[ls][i][0] - dp[rs][j][1]。
dp[x][k][0]=inf 表示"不可达"（即 k 个资源下这个状态不成立），dp[x][k][1]=-inf 同理（不可达/不存在）。转移时对 !=-inf / !=inf 做可达性判断。

+ 只在 i+j < X 时允许（因为 + 占用名额，不能超过上限 X）。- 不占名额所以无 X 限制。

这和 dfs 结构一模一样，只是 + 与 - 的"资源占用"语义互换了：这里 + 变成不占名额（i+j），- 变成占用名额（i+j+1），且资源上限是 Y。也就是说：dfs 假设"上限是 + 号的个数 = X"（+ 占用名额），dfs2 假设"上限是 - 号的个数 = Y"（- 占用名额）。

其中 min/max 组合也相应调整（- 时用左大-右小来看，+ 时用左大+右大等，语义同前，只是占名额的运算符角色变了）

读入表达式字符串 a、以及两个上限 X 和 Y
把字符串整体右移，让下标从 1 开始
栈匹配括号，填 to[] 数组
选择策略：题目给了+号上限 X、-号上限 Y 两种限制。为了求最大化的最终值，选择更宽松/较小的那个限制来跑 DP：
若 X < Y：+ 号名额更紧张，用 dfs（把 + 当占名额的操作，上限 X）。初始化 dp 全部为 inf/-inf，build 建树，dfs(1) 算 DP，输出 dp[1][X][1]（根节点、+ 用完 X 个、取最大值维度）。
否则（X ≥ Y）：- 号名额更紧张，用 dfs2（把 - 当占名额的操作，上限 Y），输出 dp[1][Y][1]。
之所以取较紧的那个限制来跑，是因为经典转化：在 min-max 博弈下，只要满足限制更小的一方，另一方的个数就自动满足（因为总数里的运算符要么是 + 要么是 -，限制其中之一即可约束全局），所以取 min(X,Y) 对应最紧约束来算答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e4+10, M = 210, inf = 1e9;

int tot, to[N], val[N], dp[N][M][2], ls[N], rs[N];
char a[N];
int build(int l, int r) {
    int now = ++tot;
    while (to[l] == r) ++l, --r;
    if (l == r) {
        val[now] = a[l] - '0';
        dp[now][0][0] = dp[now][0][1] = val[now];
    } else {
        if (to[l]) {
            if (a[to[l]+1] != '?') exit(1);
            ls[now] = build(l+1, to[l]-1);
            rs[now] = build(to[l]+2, r);
        } else {
            if (a[l+1] != '?') exit(2);
            ls[now] = build(l, l);
            rs[now] = build(l+2, r);
        }
    }
    return now;
}

int sz[N], X;
void dfs(int x) {
    if (!ls[x]) return;
    dfs(ls[x]); dfs(rs[x]); sz[x] = 1; sz[x] += sz[ls[x]] + sz[rs[x]];
    rep(i,0,min(sz[ls[x]], X)) rep(j,0,min(X-i, sz[rs[x]])) {
        if(dp[ls[x]][i][1]!=-inf){
            if(i+j<X&&dp[rs[x]][j][1]!=-inf) dp[x][i+j+1][1]=max(dp[x][i+j+1][1],dp[ls[x]][i][1]+dp[rs[x]][j][1]);
            if(dp[rs[x]][j][0]!=inf) dp[x][i+j][1]=max(dp[x][i+j][1],dp[ls[x]][i][1]-dp[rs[x]][j][0]);
        }
        if(dp[ls[x]][i][0]!=inf){
            if(i+j<X&&dp[rs[x]][j][0]!=inf) dp[x][i+j+1][0]=min(dp[x][i+j+1][0],dp[ls[x]][i][0]+dp[rs[x]][j][0]);
            if(dp[rs[x]][j][1]!=-inf) dp[x][i+j][0]=min(dp[x][i+j][0],dp[ls[x]][i][0]-dp[rs[x]][j][1]);
        }
    }
}

int Y;
void dfs2(int x) {
    if (!ls[x]) return;
    dfs2(ls[x]); dfs2(rs[x]); sz[x] = 1; sz[x] += sz[ls[x]] + sz[rs[x]];
    rep(i,0,min(sz[ls[x]], Y)) rep(j,0,min(Y-i, sz[rs[x]])) {
        if(dp[ls[x]][i][1]!=-inf){
            if(i+j<Y&&dp[rs[x]][j][0]!=inf) dp[x][i+j+1][1]=max(dp[x][i+j+1][1],dp[ls[x]][i][1]-dp[rs[x]][j][0]);
            if(dp[rs[x]][j][1]!=-inf) dp[x][i+j][1]=max(dp[x][i+j][1],dp[ls[x]][i][1]+dp[rs[x]][j][1]);
        }
        if(dp[ls[x]][i][0]!=inf){
            if(i+j<Y&&dp[rs[x]][j][1]!=-inf) dp[x][i+j+1][0]=min(dp[x][i+j+1][0],dp[ls[x]][i][0]-dp[rs[x]][j][1]);
            if(dp[rs[x]][j][0]!=inf) dp[x][i+j][0]=min(dp[x][i+j][0],dp[ls[x]][i][0]+dp[rs[x]][j][0]);
        }
    }
}

int st[N], top, n;
int main() {
    fast;
    cin >> a >> X >> Y; n = strlen(a);
    for (int i = n; i; --i) a[i] = a[i-1];
    rep(i,1,n) {
        if (top && a[st[top]] == '(' && a[i] == ')') to[st[top--]] = i;
        else if (a[i] == '(' || a[i] == ')') st[++top] = i;
    }
    if (X < Y) {
        rep(i,1,n) rep(j,0,X) dp[i][j][0] = inf, dp[i][j][1] = -inf;
        build(1, n); dfs(1);
        cout << dp[1][X][1] << '\n';
    } else {
        rep(i,1,n) rep(j,0,Y) dp[i][j][0] = inf, dp[i][j][1] = -inf;
        build(1, n); dfs2(1);
        cout << dp[1][Y][1] << '\n';
    }
    return 0;
}