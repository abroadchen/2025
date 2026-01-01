/**
* (n - ls[i] - rs[i] - 1) * (ls[i] + rs[i]) 计算的是：
对于线段i，不相交线段数 × 相交线段数
这代表以线段i为中间线段，一条与它相交、一条与它不相交的线段对数量
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define N 200010
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

struct line {
    ll l, r, id;
    bool operator<(const line& o) const { return id < o.id; }
} ln[N];

ll ls[N];//存储左侧信息
void dfs(const int l, const int r) {//分治处理区间[l,r]
    if (l == r) return;//区间只有一个元素时返回
    const int mid = (l + r) >> 1;
    dfs(l, mid);//递归处理左右两半区间
    dfs(mid + 1, r);
    int p = l;
    for (int i = mid + 1; i <= r; ++i) {//遍历右半区间，用双指针统计左半区间中右端点小于当前右半区间元素右端点的数量
        while (p <= mid && ln[p].r < ln[i].r) p++;
        ls[ln[i].id] += p - l;//将结果累加到ls数组对应id位置
    }
    inplace_merge(ln + l, ln + mid + 1, ln + r + 1, [](const line& a, const line& b) {
        return a.r < b.r;//原地合并两个已排序的区间，按右端点r升序排序
    });
}

ll rs[N];//右侧相关信息，按右端点降序排序
void dfs2(const int l, const int r) {
    if (l == r) return;
    const int mid = (l + r) >> 1;
    dfs2(l, mid);
    dfs2(mid + 1, r);
    int p = l;
    for (int i = mid + 1; i <= r; ++i) {//统计左半区间中右端点大于当前右半区间元素右端点的数量
        while (p <= mid && ln[p].r > ln[i].r) p++;
        rs[ln[i].id] += p - l;
    }
    inplace_merge(ln + l, ln + mid + 1, ln + r + 1, [](const line& a, const line& b) {
        return a.r > b.r;//按右端点降序合并
    });
}

int main() {
    fast;
    int n; cin >> n;
    rep(i,n) {
        cin >> ln[i].l >> ln[i].r;
        if (ln[i].l > ln[i].r) swap(ln[i].l, ln[i].r);
        ln[i].id = i;
    }
    sort(ln + 1, ln + n + 1, [](const line& a, const line& b) {
        return a.l > b.l;//按左端点降序排序，调用dfs计算左侧相关信息
    }); dfs(1, n);
    sort(ln + 1, ln + n + 1, [](const line& a, const line& b) {
        return a.l < b.l;//按左端点升序排序，调用dfs2计算右侧相关信息
    }); dfs2(1, n);
    vector<ll> cnt(N * 2, 0);
    rep(i,n) if (ln[i].r < N * 2) cnt[ln[i].r]++;//统计右端点，计算前缀和，更新rs数组
    rep(i,n+n-1) cnt[i] += cnt[i - 1];
    rep(i,n) if (ln[i].l < N * 2) rs[ln[i].id] += cnt[ln[i].l];
    fill(cnt.begin(), cnt.end(), 0);
    rep(i,n) if (ln[i].l < N * 2) ++cnt[ln[i].l];//统计左端点，计算后缀和，更新rs数组
    for (int i = n + n - 1; i >= 1; --i) cnt[i] += cnt[i + 1];
    rep(i,n) if (ln[i].r < N * 2) rs[ln[i].id] += cnt[ln[i].r];
    sort(ln + 1, ln + n + 1);
    ll ans = 0;
    rep(i,n) {
        ans += ls[i] * rs[i] * 2;
        ans += 1ll * (n - ls[i] - rs[i] - 1) * (ls[i] + rs[i]);
    }
    //所有可能的三线段组合数减去不满足条件的组合数
    ans = 1ll * n * (n - 1) * (n - 2) / 6 - ans / 2;
    cout << ans << '\n';
    return 0;
}