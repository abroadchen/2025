//
// Created by Psy.C on 2026/3/6.
//
/**
n: 区间数量
b: 临时数组，用于离散化
t: 离散化后的坐标数组
num: 每个坐标段的长度
p: 位置映射数组

读入n个区间[a[i].x, a[i].y]
将所有端点存入数组b用于离散化
对所有端点排序
去重并处理间隙
t[++cnt] = b[i]; num[cnt] = 1: 添加单个点，长度为1
t[++cnt] = b[i] + 1; num[cnt] = b[i+1] - b[i] - 1: 添加间隙段
初始化p数组为恒等映射
对每个区间[a[i].x, a[i].y]，找到其离散化后的索引x和y
交换p[x]和p[y]
从后往前遍历
query(p[i]): 查询p[i]之前已经处理的元素个数
ans += 1ll*num[p[i]]*query(p[i]): 累加贡献
update(p[i], num[p[i]]): 更新树状数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+1;
struct node { int x, y; } a[N];

int low_bit(const int x) { return x & -x; }
int cnt, sum[N<<2];
void update(int k, const int val) {
    while (k <= cnt) {
        sum[k] += val;
        k += low_bit(k);
    }
}
int query(int k) {
    int ans = 0;
    while (k) {
        ans += sum[k];
        k -= low_bit(k);
    }
    return ans;
}

int n, b[N<<1], t[N<<2], num[N<<2], p[N<<2];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y;
        b[i*2-1] = a[i].x; b[i*2] = a[i].y;
    }
    sort(b+1, b+2*n+1);
    for (int i = 1; i <= 2*n; ++i) if (b[i] != b[i+1]) {
        t[++cnt] = b[i]; num[cnt] = 1;
        if (b[i] + 1 < b[i+1]) {
            t[++cnt] = b[i] + 1;
            num[cnt] = b[i+1] - b[i] - 1;
        }
    }
    for (int i = 1; i <= cnt; ++i) p[i] = i;
    for (int i = 1; i <= n; ++i) {
        int x = lower_bound(t + 1, t + cnt + 1, a[i].x) - t,
        y = lower_bound(t + 1, t + cnt + 1, a[i].y) - t;
        swap(p[x], p[y]);
    }
    ll ans = 0;
    for (int i = cnt; i >= 1; --i) {
        ans += 1ll*num[p[i]]*query(p[i]);
        update(p[i], num[p[i]]);
    }
    cout << ans << '\n';
    return 0;
}