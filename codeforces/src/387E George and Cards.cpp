//
// Created by Psy.C on 2026/1/28.
//
/**
* 时间复杂度
单调栈：O(n)
排序：O(n log n)
树状数组操作：O(n log n)
总体：O(n log n)
空间复杂度
O(n)，用于存储各种数组和树状数组
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000007
#define rep(i,n) for (int i = 1; i <= (n); ++i)
using namespace std;

struct node {
    int a[N];
    void modify(const int x, const int v) {//位置x增加v
        for (int i = x; i < N; i += i & -i) a[i] += v;
    }
    [[nodiscard]] int sum(const int x) const {//前缀和[1, x]
        int ans = 0;
        for (int i = x; i; i -= i & -i) ans += a[i];
        return ans;
    }
    [[nodiscard]] int query(const int l, const int r) const {//区间[l, r]的和
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
} bit;


int main() {
    fast;
    int n, k; cin >> n >> k;
    rep(i,n) bit.modify(i, 1);//初始化为全1（所有位置都可用）
    int p[N], b[N];//排列数组 被禁止的值
    rep(i,n) cin >> p[i];
    bool ban[N];//标记哪些值被禁止
    rep(i,k) cin >> b[i], ban[b[i]] = true;
    int top = 0, l[N], r[N]; pair<int, int> stk[N];
    rep(i,n) {
        if (ban[p[i]]) {//加入单调栈（维护递增序列）
            while (top && stk[top].first > p[i]) top--;
            stk[++top] = {p[i], i};
        } else {//第一个≥p[i]的禁止元素位置
            const int pos = static_cast<int>(lower_bound(stk + 1, stk + top + 1,
                make_pair(p[i], 0)) - stk - 1);
            l[i] = pos ? stk[pos].second : 0;
        }
    }
    top = 0;
    for (int i = n; i >= 1; --i) {
        if (ban[p[i]]) {
            while (top && stk[top].first > p[i]) top--;
            stk[++top] = {p[i], i};
        } else {
            const int pos = static_cast<int>(lower_bound(stk + 1, stk + top + 1,
                make_pair(p[i], 0)) - stk - 1);
            r[i] = pos ? stk[pos].second : n + 1;
        }
    }
    vector<int> v;
    rep(i,n) if (!ban[p[i]]) v.push_back(i);//收集所有非禁止元素的位置
    ranges::sort(v, [&p](const int& x, const int& y) {
        return p[x] < p[y];
    });
    ll ans = 0;
    for (const auto& x : v) {
        ans += bit.query(l[x] + 1, r[x] - 1);//区间[l[x]+1, r[x]-1]内还存在的元素个数
        bit.modify(x, -1);//移除当前位置
    }
    cout << ans << '\n';
    return 0;
}