//
// Created by Psy.C on 2026/10/2.
//
/**
读入 n-1 条边，建立无向树，节点编号 1..n，邻接表存储
从根 1 出发 dfs(1,0)，st 表示当前节点到根的距离（层数/深度）。

按 st 的奇偶把节点分到两类：

st 为偶数 → 累加到 a2（注意 root 在 dfs(1,0) 前 a1=1, a2=0，root 本身 st=0 计入 a2）；
st 为奇数 → 累加到 a1。
初始 a1=1, a2=0：根节点 1（st=0，偶数）已经计入 a2，但从代码看 a1=1 而 root 算到 a2…这里注意实际分配：

初始 a1 = 1（预置1个），a2 = 0；
进入 dfs(1,0)：root 的邻居 i，若 !vis[i] 则 vis[i]=1，此时 st=0 为偶数 → a2++，dfs(i,1)；
下一层 st=1 奇数 → a1++；
… 依此类推。
所以 a1 实际累计奇数层（深度为奇数）的节点总数，a2 累计偶数层（含根）的节点总数。预置 a1=1 不过是把某种计数初始化（实际含义随题而定）。

树上任意两点的距离奇偶 = 两点深度奇偶异同。深度同为偶或同为奇 → 距离偶数；一奇一偶 → 距离奇数。
异色（一奇一偶）点对总数为 even * odd（每对深度奇偶不同的节点距离为奇数）。
在这 even*odd 对中，去掉相邻（距离为 1）‍的 n-1 对（即树的边），剩下的就是距离为 3,5,7,… 的奇数距离点对。
所以 ans = even*odd - (n-1) = 距离为奇数的点对总数（不包括直接相邻的边所代表的距离1）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

vector<int> v[N];
int vis[N];
ll a1, a2;
void dfs(int x, int st) {
    for (int i : v[x]) {
        if (!vis[i]) {
            vis[i] = 1;
            if (st&1) a1++; else a2++;
            dfs(i, st+1);
        }
    }
}

int main() {
    fast;
    int n; cin >> n; a1 = 1, a2 = 0;
    for (int i = 0, x, y; i < n-1; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
    }
    vis[1] = 1; dfs(1, 0);
    cout << a1*a2-(n-1) << '\n';
    return 0;
}