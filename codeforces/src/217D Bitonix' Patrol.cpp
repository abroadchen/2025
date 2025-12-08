//
// Created by Psy.C on 2025/12/7.
//
/*
*cnt[N]：计数数组，统计不同值的出现次数
x[N]：数组，存储当前选择的值
v[N+N+N]：数组，存储模m的循环值
ans：结果变量
s[8]：位集数组，用于状态压缩和快速查找
vis[N]：访问标记数组
 *
*计算当前选择方案的权重：
参数d表示当前深度
初始化返回值ret为1
循环计算从第1到第d-1个选择的乘积
使用static_cast<int>确保类型安全
每次乘法后取模防止溢出
 *
*d：当前搜索深度
lst：上一次选择的值
首先计算当前方案的权重
如果深度不超过6，继续搜索：
遍历从lst+1到m/2的所有可能值
如果该值不存在或已被使用，跳过
记录当前选择
更新状态位集（表示已使用的值及其对称值）
递归搜索下一层
累加结果并处理模运算
 *
 */
#include <iostream>
#include <bitset>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 122
#define mod 1000000007
using namespace std;

int n, m, k, cnt[N], x[N], v[N+N+N], ans;
bitset<N<<1> s[8];
bool vis[N];

int get(const int d) {
    int ret = 1;
    for (int i = 1; i < d; ++i) ret =
        static_cast<int>(1ll * ret * cnt[x[i]] % mod);
    return ret;
}

int dfs(const int d, const int lst) {
    int ret = get(d);
    if (d <= 6) {
        for (int i = lst + 1; i <= m / 2; ++i) {
            if (!cnt[i]) continue;
            if (s[d-1][i] || s[d-1][m-i]) continue;//检查值 i 或其对称值 m-i 是否已经在当前状态下被使用
            x[d] = i;
            if (d <= 5) {
                s[d] = s[d-1];//复制上一状态
                s[d] |= s[d-1] << i;
                s[d] |= s[d-1] >> i;
                s[d] |= s[d-1] >> (m-i);
                s[d] |= s[d-1] << m-i;
            }
            ret += dfs(d + 1, i);
            if (ret >= mod) ret -= mod;
        }
    }
    return ret;
}

int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 0; i < 3 * N; ++i) v[i] = i % m;//存储0到3*N-1模m的值
    for (int i = 1; i <= k; ++i) {
        int t; cin >> t;
        t %= m;
        t = min(t, m - t);//取与对称值中的较小值
        vis[t] = true;
        cnt[t]++;
    }
    s[0][0] = true;//标记0位置为已使用
    ans = dfs(1, 0);
    cout << ans << '\n';
    return 0;
}