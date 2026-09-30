//
// Created by Psy.C on 2026/9/30.
//
/**
这里的图由"字符串前缀哈希"构造，点最多 N=2e6 个，但每个串只贡献前缀长度那么多个点，实际节点数 tot 通常远小于 N。
dp[x][1]=1 表示选节点 x（在最大独立集里）价值为 1，dp[x][0]=0 表示不选
经典树上最大独立集：每个节点两状态，父节点决定子节点能否选。这里对无向图做 DFS 转成树后，dp[x][1]=选 x、dp[x][0]=不选 x 的最大贡献
用 f[j]（233 的 j 次幂）对字符串做前缀哈希，从而每个前缀用一个大整数 x 唯一表示（概率性去重，靠大质数抗碰撞）。
mp：哈希值 → 节点编号 tot 的映射，保证每个不同前缀只对应一个图节点
对每个串 ss[i]，扫描其每个前缀：

x = 当前前缀哈希(含第 j 个字符)
y = 去掉首字符后的前缀哈希(即从位置 1..j 的子串哈希)
if (mp 里存在 y 且 vis 未标记 x) {
    在节点 mp[x] 与 mp[y] 之间连无向边;
    标记 vis[mp[x]]=1;   // 防止同一节点被重复建边
}
逻辑：若串 A 的某个前缀 等于 串 B 去掉首字符后的某个前缀，说明 A 与 B 间存在"错位前缀重合"关系，就在对应哈希节点间连边。
vis[mp[x]]=1 用于防止同一节点被多次连边（保证建图去重）。
连边的具体语义（"前缀等于去掉首字符的前缀"）对应原题某种"串的重叠/包含冲突"，最终使得冲突关系转为图上的边，求最大独立集即求最多不冲突的选取。
第一遍把所有前缀哈希塞进 mp 获得节点总数 tot。
第二遍按"前缀 == 去首字符前缀"规则连边。
第三遍每棵连通树分别求最大独立集并累加，ans 即为最终答案
哈希映射 mp O(N)。
建图 O(总字符数)。
树形 DP O(tot)，tot 为不同前缀总数

clear() 只会把 size 设为 0，但 capacity 不会改变，内存并没有真正释放；而 shrink_to_fit() 能回收多余容量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e6, M = 1e6+5;
constexpr ll mod = 1e16+61;
int dp[N+5][2];
bool vis[N+5];
vector<int> s[N+5];
inline void dfs(int x, int fa) {
    dp[x][1] = 1, dp[x][0] = 0;
    vis[x] = 1;
    for (int i = 0; i < s[x].size(); ++i) {
        int y = s[x][i];
        if (vis[y]) continue;
        dfs(y, x);
        dp[x][1] += dp[y][0];//选 x，则儿子不能选
        dp[x][0] += max(dp[y][0], dp[y][1]);//不选 x，儿子可选可不选
    }
}

ll f[N+5];
int n, tot, ans;
unordered_map<ll, int> mp;
string ss[M];
int main() {
    fast;
    f[0] = 1;
    for (int i = 1; i <= N; ++i) f[i] = f[i-1]*233%mod;
    int t; cin >> t;
    while (t--) {
        cin >> n; tot = 0; ans = 0; mp.clear();
        for (int i = 1; i <= n; ++i) {//第一遍：读入每个串，把每个前缀映射成哈希值并分配到节点编号
            ll x = 0; ss[i].clear(); cin >> ss[i];
            for (int j = 0; j < ss[i].size(); ++j) {
                x = (x + f[j]*(ss[i][j]-'a'+1)%mod) % mod;
                if (!mp.contains(x)) mp[x] = ++tot;//新前缀 → 新节点
            }
        }
        //第二遍：建冲突边
        for (int i = 1; i <= n; ++i) {
            ll x = 0, y = 0;//x = 前缀哈希;  y = 去掉首字符的前缀哈希;
            for (int j = 0; j < ss[i].size(); ++j) {
                x = (x + f[j]*(ss[i][j]-'a'+1)%mod) % mod;
                if (j != 0) y = (y+f[j-1]*(ss[i][j]-'a'+1)%mod) % mod;
                if (mp.contains(y) && !vis[mp[x]]) {
                    int p = mp[x], q = mp[y];
                    s[p].push_back(q); s[q].push_back(p);
                    vis[p] = 1;
                }
            }
        }
        //第三遍：对每个连通分量做树形 DP 求最大独立集
        for (int i = 1; i <= tot; ++i) vis[i] = 0;
        for (int i = 1; i <= tot; ++i) {
            if (!vis[i]) {
                dfs(i, 0);
                ans += max(dp[i][0], dp[i][1]);
            }
        }
        //清理
        for (int i = 0; i <= tot; ++i)
            s[i].clear(), s[i].shrink_to_fit(), vis[i] = 0;
        cout << ans << '\n';
    }
    return 0;
}