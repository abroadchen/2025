//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
e[i].f 本质上是一个删除标记：为 1 时该边算"存活"。
d[u] = 当前存活边里 u 的度数。
cnt[u] 在 check() 里被临时算出来
统计每个点相邻的叶子邻居数量 cnt[i]。要求：凡是至少连着一个叶子邻居的点 i，其叶子邻居数必须 ≥ 3，否则 fail。这对应一种"每个节点要么不碰叶子、要么必须被至少 3 个叶子保护"的结构约束（很像树的组合/博弈题里的"中心度"条件
每次调用前，根据当前仍存活的边重新计算每个点的度数 d，再跑 check()
一趟扫过所有活边，若任一端点是叶子（度数为1），就把这条边删掉。 这等价于"每次删掉所有与叶子相连的边"，会不断把树"削皮"
约束 k ≤ 12：说明题目深度/轮次有上限，剪枝掉大 k 和单点。
每一轮先 run() 删边，再 chk() 校验结构，检查是否刚好在第 k 轮删光（不能提前、不能超时）。
默认结尾 no()，因为若循环自然结束还没成功就判负
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

struct node { int u, v; bool f; } e[N];

int cnt[N], n, d[N];
bool check() {
    memset(cnt, 0, sizeof(cnt));
    rep(i,n-1) if (e[i].f) {//遍历所有存活边
        if (d[e[i].u] == 1) cnt[e[i].v]++;//u 是叶子 → v 的 cnt++
        if (d[e[i].v] == 1) cnt[e[i].u]++;//v 是叶子 → u 的 cnt++
    }
    rep(i,n) if (cnt[i] != 0 && cnt[i] < 3) return 0;//若有邻居数非0但<3 → 不合法
    return 1;
}
bool chk() {
    memset(d, 0, sizeof(d));
    rep(i,n-1) if (e[i].f) { d[e[i].u]++; d[e[i].v]++; }
    return check();
}
void run() {
    rep(i,n-1) if (e[i].f) {
        if (d[e[i].u] == 1 || d[e[i].v] == 1)//某端是叶子（度=1）
            e[i].f = 0;//删除这条边
    }
}
int calc() {//统计当前还没被删的边数。
    int tot = 0;
    rep(i,n-1) if (e[i].f) tot++;
    return tot;
}
void no() { cout << "No\n"; exit(0); }
void yes() { cout << "Yes\n"; exit(0); }

int k;
int main() {
    fast;
    cin >> n >> k;
    if (k > 12 || n == 1) no();//k太大 或 单点树直接判负
    rep(i,n-1) { cin >> e[i].u >> e[i].v; e[i].f = 1; }
    if (!chk()) no();//初始结构不满足 → 直接失败
    rep(i,k) {
        run();//执行一轮“删叶子邻居边”
        if (!chk()) no();//删完这轮后结构不合法 → 失败
        else if (i == k && calc() == 0) yes();//恰好第k轮删光 → 成功
        if (calc() == 0) no();//提前删光但没到第k轮 → 失败
    }
    no();
    return 0;
}