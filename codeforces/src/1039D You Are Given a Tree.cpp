//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
根为 1，把无根树 g 转成有根树 t（每节点存其子节点）。
dfn[cnt] = q 在子树全部访问完后记录，即后序遍历，父节点编号总在子节点之后
树形贪心 DP，目标是统计"长度 ≥ q 的不相交路径"数量：

mx[i]：节点 i 最长的一条向下延伸链长度（从 i 到某叶子的最大深度）。
cx[i]：节点 i 次长链长度。
对每个节点 i，收集其所有儿子：
若儿子链长大于当前最长，把原最长降为次长，更新最长；否则只更新次长（即维护 mx 和 cx 两个最大）。
若 mx[i] + cx[i] + 1 >= q：说明过节点 i 能拼出一条长度 ≥ q 的路径（最长链 + 次长链 + 自身），贪心取掉这条路径（res++），并把 mx[i] 重置为 0，让该节点的链不再向上贡献（保证路径不相交）。
否则 mx[i]++：把 i 纳入向上延伸的链中，继续向上贡献。
核心贪心：一旦能在节点处凑出 ≥ q 的路径就"截断"，使路径互不共享节点，最大化数量。
返回 res = 长度 ≥ q 的路径数
利用单调性（ans[k] 随 k 增大而单调不增）批量填答案：

len：一个分块阈值（sqrt(n log n) 量级），小 k 直接暴力。
前半段 i <= len：直接 check(i) 算出。
后半段按答案值（n/len 个不同值）分块：由于答案随 k 单调，具有同样答案 i 的 k 连成一段。用二分在 [l, r] 里找出 check(mid)==i 的最大 mid，把整段 k 都填成 i。这是"对答案相同区间二分定界" 的技巧
逐行输出每个 k 的答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define per(i,n) for(int i=n;i>=1;i--)
using namespace std;

constexpr int N = 1e5+10;

vector<int> g[N], t[N];
int cnt, dfn[N];
inline void dfs(int q, int w) {
    for (int i = 0; i < g[q].size(); i++)
        if (g[q][i] != w) {
            t[q].push_back(g[q][i]);
            dfs(g[q][i], q);
        }
    cnt++; dfn[cnt] = q;
}

int res, n, mx[N], cx[N];
int check(int q) {
    res = 0;
    rep(x,n) {
        int i = dfn[x]; //按后序遍历顺序取节点
        mx[i] = cx[i] = 0;
        for (int j = 0; j < t[i].size(); j++) {
            if (mx[t[i][j]] > mx[i]) {
                cx[i] = mx[i];
                mx[i] = mx[t[i][j]];
            } else cx[i] = max(cx[i], mx[t[i][j]]);
        }
        if (mx[i] + cx[i] + 1 >= q) { res++; mx[i] = 0; }
        else mx[i]++;
    }
    return res;
}

int x, y, len, ans[N], l, r, L, R;
int main() {
    fast;
    cin >> n;
    rep(i,n-1) { cin >> x >> y; g[x].push_back(y); g[y].push_back(x); }
    dfs(1, 0); len = sqrt(n*log2(n)); len = min(len, n);
    rep(i,len) ans[i] = check(i);//前 len 个 k 暴力算
    r = len;
    per(i,n/len) {//对答案值 i 从大到小分块
        l = r+1; r = l-1; L = l; R = n;
        while (L <= R) {
            int mid = (L+R)/2;
            if (check(mid) == i) { r = mid; L = mid+1; } else R = mid-1;
        }
        for (int j = l; j <= r; j++) ans[j] = i;
    }
    rep(i,n) cout << ans[i] << '\n';
    return 0;
}