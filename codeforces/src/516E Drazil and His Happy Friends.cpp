//
// Created by Psy.C on 2026/2/28.
//
/**
扩展欧几里得算法，求ax + by = gcd(a,b)的解
当b=0时，x=1, y=0
递归求解，返回x=yy, y=xx-a/b*yy

计算v在模mod下的逆元
使用扩展欧几里得算法
返回正数结果

n, m：两个参数
c：n和m的最大公约数
ans：答案，初始化为-1
pos：按余数分组存储数值的映射

解决余数为id的组
如果该组为空，输出-1并退出
t：(m/c)在模(n/c)下的逆元
mod = n/c：模数
计算每个元素相对于首个元素的位置差
dt：标准化后的间隔
排序后处理，更新最大间隔

读入n, m，计算gcd(n,m)作为c
读入b个蓝色元素，按v%c分组存储，加入B数组
读入g个绿色元素，同样处理，加入G数组
如果n < m，交换n和m以及对应的数组
对每个余数类[0, c-1]进行处理
检查绿色数组中缺失的最小值
检查蓝色数组中缺失的最小值
更新答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;

void dfs(const int a, const int b, int& x, int& y) {
    if (!b) return x = 1, y = 0, void();
    int xx, yy;
    dfs(b, a%b, xx, yy);
    return x = yy, y = xx - a/b*yy, void();
}

int inv(const int v, const int mod) {
    int x, y;
    dfs(v, mod, x, y);
    return (x%mod + mod)%mod;
}

int n, m, c, ans=-1;
map<int, set<int>> pos;
void solve(const int id) {
    const auto st = pos[id];
    if (st.empty()) return cout << -1, exit(0), void();
    const int t = inv(m/c, n/c), mod = n/c;
    int lst = 0, p0 = *st.begin();
    vector<ii> v;
    for (auto x : st) {
        int dt = (((x-p0)/c)%mod+mod)%mod*t%mod;
        if (dt == 0) dt = mod;
        v.push_back({dt, x});
    }
    ranges::sort(v);
    for (auto [fst, snd] : v) {
        const int a = fst, b = snd;
        if (a-lst-1) ans = max(ans, p0+(a-lst-1)*m);
        lst = a, p0 = b;
    }
}

int b, g;
vector<int> B, G;
signed main() {
    fast;
    cin >> n >> m, c = __gcd(n, m);
    cin >> b;
    for (int i = 1, v; i <= b; ++i) {
        cin >> v;
        pos[v%c].insert(v); B.push_back(v);
    }
    cin >> g;
    for (int i = 1, v; i <= g; ++i) {
        cin >> v;
        pos[v%c].insert(v); G.push_back(v);
    }
    if (n < m) swap(n, m), swap(B, G);
    for (int i = 0; i <= c-1; ++i) solve(i);
    set<int> st;
    for (auto id : G) st.insert(id);
    for (int i = m; i >= 1; --i)
        if (!st.contains(i-1)) {
            ans = max(ans, i-1);
            break;
        }
    st.clear();
    for (auto id : B) st.insert(id);
    for (int i = n; i >= 1; --i)
        if (!st.contains(i-1)) {
            ans = max(ans, i-1);
            break;
        }
    st.clear();
    cout << ans;
    return 0;
}