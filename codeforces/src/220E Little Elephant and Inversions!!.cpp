//
// Created by Psy.C on 2025/12/8.
//
/*
*n：数组长度
a[N]：存储输入数组
k：阈值参数
node：树状数组结构体，包含：
b[N]：树状数组存储空间
update(x, v)：在位置x更新值v
sum(x)：查询前缀和[1,x]
pre, suf：两个树状数组实例
 *
*离散化函数：
创建map映射，将所有不同值初始化为0
给每个唯一值分配递增的排名
将原数组替换为离散化后的排名
 *
*初始化逆序对计数：
从右往左处理，计算初始的后缀逆序对数
suf.sum(a[i] - 1)：统计已经处理过的比a[i]小的元素个数
suf.update(a[i], 1)：将a[i]加入后缀统计
 *
*inv：当前区间的逆序对总数
pre.sum(n) - pre.sum(a[l])：前缀中比a[l]大的元素个数
pre.update(a[l], 1)：将a[l]加入前缀统计
suf.sum(a[l] - 1)：后缀中比a[l]小的元素个数
*调整右边界：
当逆序对数超过k或r≤l时，移动右指针
从inv中减去a[r]的贡献
从后缀统计中移除a[r]
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

int n, a[N];
ll k;

struct node {
    int b[N];
    void update(int x, const int v) {
        for (; x < N; x += x & -x) b[x] += v;
    }
    int sum(int x) const {
        int ans = 0;
        for (; x > 0; x -= x & -x) ans += b[x];
        return ans;
    }
} pre, suf;

void f() {
    map<int, int> mp;
    for (int i = 1; i <= n; ++i) mp[a[i]] = 0;
    int cnt = 0;
    for (auto& x : mp) x.second = ++cnt;
    for (int i = 1; i <= n; ++i) a[i] = mp[a[i]];
}


int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i]; f();
    ll inv = 0;
    for (int i = n; i >= 2; --i) {
        inv += 1ll * suf.sum(a[i] - 1);//有多少个小于a[i]
        suf.update(a[i], 1);
    }
    ll ans = 0; int r = 2;
    for (int l = 1; l <= n; ++l) {
        inv += 1ll * (pre.sum(n) - pre.sum(a[l]));//大于a[l]的元素个数
        pre.update(a[l], 1);
        inv += 1ll * suf.sum(a[l] - 1);
        while ((inv > k || r <= l) && r <= n) {
            inv -= 1ll * suf.sum(a[r] - 1);
            inv -= 1ll * pre.sum(n) - pre.sum(a[r]);
            suf.update(a[r], -1);
            ++r;
        }
        if (r <= n) ans += 1ll * (n - r + 1);//累加有效区间数
    }
    cout << ans << '\n';
    return 0;
}