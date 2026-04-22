//
// Created by Psy.C on 2026/4/21.
//
/**
求解ax+by=gcd(a,b)的解
siz[]：子树大小
all：当前分治块总大小
rt：重心
v[]：邻接表存储图
vis[]：访问标记
寻找重心：使用点分治思想找到树的重心
w<<1 <= all判断是否为重心
收集路径信息：存储深度、正向数值、反向数值
d1：正向拼接的数值（如1->2->3变成123）
d2：反向拼接的数值（如1->2->3变成321）
d1: (d1*10 + 当前边权) % mod （正向构建数字）
d2: (d2 + base[dep] * 当前边权) % mod （反向构建数字）
 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define tp3 tuple<int, int, int>
#define ll long long
using namespace std;
constexpr int N = 1e5+7;

void ex_gcd(int a, int b, int& x, int& y) {
    if (!b) return x = 1, y = 0, void();
    ex_gcd(b, a%b, y, x);
    y -= a/b*x;
}

int siz[N], all, rt;
vector<ii> v[N];
bool vis[N];
void dfs(int p, int fa) {
    siz[p] = 1;//当前节点子树大小为1
    int w = 0;//最大子树大小
    for (const auto &key: v[p] | views::keys)//遍历p的所有邻居节点
        if (!vis[key] && key != fa)//未访问且不是父节点 递归并更新信息
            dfs(key, p), siz[p] += siz[key], w = max(w, siz[key]);
    w = max(w, all - siz[p]);//删除当前节点后剩余部分的大小
    if (w<<1 <= all) rt = p;//最大子树不超过总数一半
}

vector<tp3> g;
int mod, base[N];
void get(int p, int fa, int dep, int d1, int d2) {
    g.emplace_back(dep, d1, d2);//将当前状态加入g向量
    for (const auto&[fst, snd] : v[p])//遍历当前节点的所有邻接点
        if (!vis[fst] && fst != fa)
            get(fst, p, dep+1, (d1*10ll+snd)%mod,//递归，更新正向数值
                (d2+1ll*base[dep]*snd)%mod);//递归，更新反向数值
}

map<int, int> mp;
ll ans;
int inv[N];
void solve(int p) {
    mp.clear(); ++mp[0];//包含0的出现次数为1
    //第一遍遍历所有子树
    for (const auto&[fst, snd] : v[p]) {
        if (vis[fst]) continue;//已访问则跳过
        g.clear();//清空临时存储
        get(fst, p, 1, snd, snd);//获取从p到fst的路径信息
        //检查是否有匹配的路径
        for (const auto& j : g) {
            //检查是否存在路径使得正向路径值相加为0 (mod mod)
            if (mp.contains((mod-1ll*get<1>(j)*inv[get<0>(j)]%mod)%mod))
                ans += mp[(mod-1ll*get<1>(j)*inv[get<0>(j)]%mod)%mod];
        }
        //将当前路径的反向值加入哈希表
        for (const auto& j : g) ++mp[get<2>(j)];
    }
    ans += mp[0] - 1;//加上经过根节点的路径 减去自身重复计算的部分
    //第二遍遍历（翻转边顺序再次计算）
    ranges::reverse(v[p]); mp.clear();
    for (const auto&[fst, snd] : v[p]) {
        if (vis[fst]) continue;
        g.clear();
        get(fst, p, 1, snd, snd);
        for (const auto& j : g) {
            if (mp.contains((mod-1ll*get<1>(j)*inv[get<0>(j)]%mod)%mod))
                ans += mp[(mod-1ll*get<1>(j)*inv[get<0>(j)]%mod)%mod];
        }
        for (const auto& j : g) ++mp[get<2>(j)];
    }
    //递归处理子树
    vis[p] = true; dfs(p, 0);//标记当前节点已访问，并重新计算子树大小
    for (const auto &key: v[p] | views::keys) {
        if (vis[key]) continue;//跳过已访问的子树
        all = siz[key];//设置当前子树大小
        dfs(key, p);//在子树中寻找新的重心
        solve(rt);//递归解决子树问题
    }
}

int n;
int main() {
    fast;
    cin >> n >> mod; base[0] = 1;
    //预计算10的幂次：base[i] = 10^i % mod
    for (int i = 1; i <= n; ++i) base[i] = base[i-1]*10ll%mod;
    ex_gcd(10, mod, inv[1], inv[0]);//10*x + mod*y = gcd(10,mod)
    //确保逆元为正 base[0]的逆元为1
    inv[1] = (inv[1]%mod + mod)%mod; inv[0] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = 1ll*inv[i-1]*inv[1]%mod;//预计算所有逆元
    for (int i = 1, x, y, z; i < n; ++i)
        cin >> x >> y >> z, ++x, ++y, z %= mod, v[x].emplace_back(y, z),
            v[y].emplace_back(x, z);
    all = n; dfs(1, 0); solve(rt);
    cout << ans << '\n';
    return 0;
}