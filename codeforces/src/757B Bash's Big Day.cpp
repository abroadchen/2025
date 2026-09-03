//
// Created by Psy.C on 2026/9/3.
//
/**
对每个质数 x，把 x 的所有倍数（x, 2x, 3x, ...）出现的次数加起来，num = 数组中有多少个数是 x 的倍数。取所有质数中的最大值作为答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1e2, inf = 1e5;

//判断 x 是否为质数
bool isok(int x) {
    int mx = sqrt(x);
    for (int i = 2; i <= mx; ++i)
        if (x%i == 0) return false;
    return true;
}

vector<int> v;
int n, a[N], b[N];
int main() {
    fast;
    //把所有 ≤1e5 的质数存进 v
    for (int i = 2; i <= inf; ++i)
        if (isok(i)) v.push_back(i);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[a[i]]++;//b[x] 记录数值 x 出现的次数
    }
    int len = v.size(), ans = 1;
    for (int i = 0; i <= len-1; ++i) {
        int num = 0, x = v[i];
        for (int now = x; now <= inf; now += x)
            num += b[now];
        ans = max(ans, num);
    }
    cout << ans << '\n';
    return 0;
}