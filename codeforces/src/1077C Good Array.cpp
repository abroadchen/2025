//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
每个元素存 id（原始下标）和 x（值）。
排序时按 x 排序，同时保留原始 id，以便输出
读入 n 个元素，累加总和 sum。
按值升序排序
情况一：i != n（当前元素不是最大值）

如果删掉的是 a[i]（非最大值），那么剩下的元素中：

最大值依然是 a[n].x。
除了最大值和 a[i] 之外的所有元素之和 = sum - a[n].x - a[i].x。
判断：这个和是否等于最大值 a[n].x。
条件：sum - a[n].x - a[i].x == a[n].x
即删掉 a[i] 后，最大值 = 其余元素之和。

满足则把 a[i].id 加入答案。

情况二：i == n（当前元素就是最大值）

如果删掉的是最大值 a[n].x，那么剩下的元素中，新的最大值是 a[n-1].x（原第二大值）。

除了新最大值 a[n-1] 和被删的最大值 a[i]=a[n] 之外的所有元素之和 = sum - a[n-1].x - a[n].x（注意这里 a[i] 就是 a[n]）。
判断：这个和是否等于新最大值 a[n-1].x。
条件：sum - a[n-1].x - a[i].x == a[n-1].x

满足则把 a[n].id 加入答案。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

struct node { int id; ll x; } a[N];
int cmp(node x, node y) { return x.x < y.x; }

int n;
ll sum;
vector<int> v;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i].x, a[i].id = i, sum += a[i].x;
    sort(a+1, a+n+1, cmp);
    rep(i,n) {
        if (i != n) { if (sum-a[n].x-a[i].x == a[n].x) v.push_back(a[i].id); }
        else { if (sum-a[n-1].x-a[i].x == a[n-1].x) v.push_back(a[i].id); }
    }
    if (!v.empty()) {
        cout << v.size() << '\n';
        for (int i : v) cout << i << ' ';
    } else cout << "0";
    return 0;
}