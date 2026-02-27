//
// Created by Psy.C on 2026/2/27.
//
/**
n：排列的大小
k：目标索引（1基）
a[N]：存储结果的数组
p1 = 0：指向结果数组的开头
p2 = n-1：指向结果数组的末尾

对于从1到n的每个位置i：
x = 2^(n-i)：表示剩余位置的可能排列数
如果i == n（最后一个元素），将其放在前端指针位置

y = x/2 = 2^(n-i-1)：可能排列的一半
情况1：y < k < x → 将i放在后面（p2--）并从k中减去y
情况2：k < x → 将i放在前面（p1++）
情况3：k > x → 从k中减去x并将i放在后面
情况4：k == x → 将i放在后面并从k中减去y
时间复杂度为O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 51;
ll ksm(ll a, ll p) {
    ll ans = 1;
    while (p) {
        if (p&1) ans *= a;
        a *= a;
        p >>= 1;
    }
    return ans;
}

ll n, k;
int a[N];
int main() {
    fast;
    cin >> n >> k;
    int p1 = 0, p2 = n - 1;
    for (int i = 1; i <= n; ++i) {
        const ll x = ksm(2, n-i);
        if (i == n) {
            a[p1++] = i;
            continue;
        }
        if (const ll y = x/2; k < x && k > y) {
            a[p2--] = i;
            k -= y;
        }
        else if (k < x) a[p1++] = i;
        else if (k > x) {
            k -= x;
            a[p2--] = i;
        }
        else {
            a[p2--] = i;
            k -= y;
        }
    }
    for (int i = 0; i < n-1; ++i) cout << a[i] << ' ';
    cout << a[n-1] << '\n';
    return 0;
}