//
// Created by Psy.C on 2026/3/20.
//
///时间复杂度：O(N)，其中N是枚举上限 空间复杂度：O(解的数量)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2100000;
struct node {
    ll a, b;//整数对(a,b)
    bool operator<(const node &o) const {//按字典序排序
        return a < o.a || a == o.a && b < o.b;
    }
};

///∑(i=1 to a) ∑(j=i+1 to a) |i-j| + a*b
ll ok(ll a, ll b) {
    return a*a*b - (a+b)*(a-1)*a/2 + (2*a-1)*a*(a-1)/6;
}
///根据给定的a，计算对应的b值
ll sum;
ll get(ll a) {
    return (6*sum-a+a*a*a)/(3*a*a+3*a);
}

set<node> ans;
ll a, b;
int main() {
    fast;
    cin >> sum; ans.clear();
    for (a = 1; a <= N; ++a) {
        b = get(a);
        if (ok(min(a, b), max(a, b)) != sum) continue;
        ans.insert({a, b});
        if (a != b) ans.insert({b, a});//也插入(b,a)
    }
    cout << ans.size() << '\n';//解的个数
    for (auto it = ans.begin(); it != ans.end(); ++it)//按顺序输出所有解
        cout << it->a << ' ' << it->b << '\n';
    return 0;
}