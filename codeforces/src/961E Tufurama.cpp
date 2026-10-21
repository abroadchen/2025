//
// Created by Psy.C on 2026/10/21.
//
/**
low_bit(x) = x & (-x) 取最低位。
update(x)：从 x 开始向下走 x -= low_bit(x)，沿途 mp[x]++ —— 这是把 y 值放入树状数组的"后缀方向"（和常规树状数组的"前缀累加"相反，这里索引向下递减）。
query(x)：从 x 开始向上走 x += low_bit(x)，累加 mp[x] —— 求的是所有已被 update 的且大于等于 x 的元素计数（后缀和）。
可确证：update 沿 x -= low_bit(x) 递增计数，query 沿 x += low_bit(x) 求和，二者方向相反，构成对"≥ x 的元素个数"的维护。
具体验证方向性：

update 写的是 while(x>0){mp[x]++;x-=low_bit(x);}：即往更小的索引累加标记。
query 读的是 while(x<inf){sum+=mp[x];x+=low_bit(x);}：从 x 往更大的索引累加。
两者配起来，query(x) 统计的是所有满足 update 时的起点 ≥ x 的 update 次数（即值 ≥ x 的被加入元素个数）。
可确证：这是一种"后缀式"树状数组，query(x) 返回值域 ≥ x 的已插入元素个数
读入 n，a[1..n]。
对每个下标 i，把 i 挂到桶 v[ min(i-1, a[i]) ] 里。即：key = min(i-1, a[i])。
可确证：每个位置 i 被放入 v[min(i-1, a[i])] 桶中
遍历 i = 1..n：
把 a[i] 通过 update(a[i]) 插入树状数组。
遍历桶 v[i] 中所有位置 x，累加 query(x)。
由于桶 v[i] 里存的是所有 min(i-1, a[位置]) == i 的位置，而这里外层 i 正好对应这些桶。因此对每个位置 x（其被放入桶 v[min(x-1,a[x])]），当外层循环进行到 i = min(x-1, a[x]) 时被处理：

此时已 update 了 a[1..i]。
query(x) = 值域 ≥ x 的已插入元素个数 = 1..i 中满足 a[j] ≥ x 的 j 个数。
可确证：当处理到桶 v[i] 中的位置 x 时，query(x) = 前 i 个元素中满足 a[j] ≥ x 的个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define low_bit(x) (x&(-x))
#define rep(i,n) for(i=1;i<=n;i++)
using namespace std;

constexpr int N = 2e5+5, inf = 1e9;

map<int, int> mp;
int query(int x) {
    int sum = 0;
    while (x < inf) { sum += mp[x]; x += low_bit(x); }
    return sum;
}
void update(int x) { while (x > 0) { mp[x]++; x -= low_bit(x); } }

int n, i, a[N], ans;
vector<int> v[N];
signed main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) v[min(i-1,a[i])].push_back(i);
    rep(i,n) {
        update(a[i]);
        for (int x : v[i]) ans += query(x);
    }
    cout << ans;
    return 0;
}