//
// Created by Psy.C on 2026/3/14.
//
/**
w1,w2,w3: 存储不同配对方案的权重
a,b: 原始数组
bb: 记录重新排列后的位置映射关系
w1[i]: 单个元素配对 a[i]*b[i]，要求位置i没有固定
w2[i]: 两个元素交叉配对 a[i]*b[i-1] + a[i-1]*b[i]
w3[i]: 三个元素的两种配对方案中的最优解
分别对a和b数组的索引按对应值排序
对原数组a和b进行排序
创建排名映射：ra[i]表示原来第i个元素在新序列中的排名
bb[ra[i]] = rb[i]创建两个数组排名之间的映射关系
对每个位置计算初始权重值
读取两个要交换的原始索引，并转换为排名索引
只更新交换位置前后5个单位内的权重值（因为影响范围有限）
f[i]表示前i个位置能获得的最大权值和
每个位置可以选择：
不选当前元素（继承f[i-1]）+ w1[i]
不选最近2个元素（继承f[i-2]）+ w2[i]
不选最近3个元素（继承f[i-3]）+ w3[i]

1e18 用于标记绝对无效的状态（权重计算）
1e16 用于标记相对无效的状态（DP状态转移）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;
constexpr int N = 3e4+5;
constexpr ll inf = 1e18;

ll w1[N], w2[N], w3[N], a[N], b[N];
int bb[N];
void get(int i) {
    w1[i] = w2[i] = w3[i] = -inf;
    if (i >= 1 && bb[i] != i) w1[i] = a[i]*b[i];
    if (i >= 2 && bb[i] != i-1 && bb[i-1] != i)
        w2[i] = a[i]*b[i-1] + a[i-1]*b[i];
    if (i >= 3) {
        if (bb[i] != i-2 && bb[i-1] != i && bb[i-2] != i-1)
            w3[i] = a[i]*b[i-2]+a[i-1]*b[i]+a[i-2]*b[i-1];
        if (bb[i] != i-1 && bb[i-1] != i-2 && bb[i-2] != i)
            w3[i] = max(w3[i], a[i]*b[i-1]+a[i-1]*b[i-2]+a[i-2]*b[i]);
    }
}

int n, q, ai[N], bi[N], ra[N], rb[N];
ll f[N];
int main() {
    fast;
    cin >> n >> q;
    rep(i,n) cin >> a[i], ai[i] = i;
    rep(i,n) cin >> b[i], bi[i] = i;
    sort(ai + 1, ai + n + 1, [](int i, int j) {
        return a[i] < a[j];
    });
    sort(bi + 1, bi + n + 1, [](int i, int j) {
        return b[i] < b[j];
    });
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    rep(i,n) ra[ai[i]] = i, rb[bi[i]] = i;
    rep(i,n) bb[ra[i]] = rb[i];
    rep(i,n) get(i);
    int x, y;
    while (q--) {
        cin >> x >> y; x = ra[x], y = ra[y]; swap(bb[x], bb[y]);
        for (int i = max(1,x-5); i <= min(n,x+5); ++i) get(i);
        for (int i = max(1,y-5); i <= min(n,y+5); ++i) get(i);
        f[0] = 0;
        rep(i,n) {
            f[i] = -1e16;
            if (i >= 1) f[i] = max(f[i], f[i-1] + w1[i]);
            if (i >= 2) f[i] = max(f[i], f[i-2] + w2[i]);
            if (i >= 3) f[i] = max(f[i], f[i-3] + w3[i]);
        }
        cout << f[n] << '\n';
    }
    return 0;
}