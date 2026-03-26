//
// Created by Psy.C on 2026/3/27.
//
/**
n 表示元素个数
c[N] 存储输入的数组
d[7] 临时数组，存储边界值及其相邻值
pr[N] 存储质因数
cnt 记录找到的质因数个数
a, b 两个权重参数
将第一个和最后一个元素以及它们的相邻数字加入候选集
这样做是为了考虑可能影响结果的关键数字

对候选数组d中的每个数字进行质因数分解
内层循环找寻小于等于√d[i]的因数
如果找到因数j，则将其加入pr数组并去除d[i]中的所有j因子
如果剩余的d[i] > 1，则它本身也是一个质因数

对质因数数组排序
去除重复的质因数，只保留不同的质因数

x: 当前位置必须修改的最小代价
y: 当前位置可以选择修改或不修改的最小代价
mn: 利用前面已有的修改机会的最小代价
对每个质因数，检查原数组中的每个元素是否能被整除
如果不能被整除，看是否可以通过±1变为可被整除
根据情况更新状态转移方程
最终ans保存所有可能质因数中的最优解


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define inf (1ll<<60)
using namespace std;
constexpr int N = 1e6+5;
int n, c[N], d[7], pr[N], cnt;
ll a, b;
int main() {
    fast;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    d[0] = c[1] - 1, d[1] = c[1] + 1;
    d[2] = c[n] - 1, d[3] = c[n] + 1;
    d[4] = c[1]; d[5] = c[n];
    for (int i = 0; i < 6; ++i) {
        for (int j = 2; j*j <= d[i]; ++j)
            if (d[i]%j == 0) {
                pr[cnt++] = j;
                while (d[i]%j == 0) d[i] /= j;
            }
        if (d[i] > 1) pr[cnt++] = d[i];
    }
    sort(pr, pr + cnt);
    int m = 0; pr[m++] = pr[0];
    for (int i = 1; i < cnt; ++i)
        if (pr[i] != pr[i-1]) pr[m++] = pr[i];
    ll ans = inf;
    for (int i = 0; i < m; ++i) {
        ll x = 0, y = 0, mn = 0;
        for (int j = 1; j <= n; ++j) {
            ll t = y; y = min(x + a, y + a);
            if (c[j]%pr[i]) {
                if ((c[j]+1)%pr[i] == 0 || (c[j]-1)%pr[i] == 0) {
                    x += b;
                    mn = min(min(mn + b, t + b), t + a);
                } else {
                    x = inf;
                    mn = t + a;
                }
            } else mn = min(t, mn);
        }
        ans = min(ans, min(min(x, y), mn));
    }
    cout << ans << '\n';
    return 0;
}