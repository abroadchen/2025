//
// Created by Psy.C on 2026/3/2.
//
/**
O(N²)：外层枚举k（N次），内层处理n个数据对（n次）
实际上是O(N×n)，其中N=1001，n是输入规模

const int inf = 0x3f3f3f3f;     // 1061109567 (约1e9)，常用且安全
const int inf = 1e9 + 7;        // 1000000007，经典值
const int inf = 1e10;           // 10000000000，用于更大范围
const int inf = 0x7fffffff;     // 2147483647，int最大值
ans*k 的最大值可能达到 1000 * 10^9 = 10^12
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1001, inf = 100000000000;
int n, a[N], b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    if (n == 1) {
        cout << a[1]*b[1] << '\n';
        return 0;
    }
    ll res = inf;
    for (int k = 1; k <= N; ++k) {
        ll ans = 0; int flag = 0;//状态标记
        for (int i = 1; i <= n && flag != -1; ++i) {//直到flag=-1
            if (a[i] > k && b[i] > k) flag = -1;//标记为无效
            if (a[i] == k || b[i] == k) flag = 1;
        }
        ///存在数据对的两个值都大于k
        ///没有任何数据对包含k值
        if (flag == -1 || flag == 0) continue;//跳过当前k值，尝试下一个k值
        for (int i = 1; i <= n; ++i) {
            if (max(a[i], b[i]) <= k) ans += min(a[i], b[i]);
            else ans += max(a[i], b[i]);
        }
        res = min(res, ans*k);//总成本：ans*k
    }
    cout << res << '\n';
    return 0;
}