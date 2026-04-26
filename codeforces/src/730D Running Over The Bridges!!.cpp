//
// Created by Psy.C on 2026/4/25.
//
/**
寻找最大的值使得x-mid个物品按2个单位时间处理，mid个物品按1个单位时间处理，总时间不超过y
n：任务数量
r：单次最大处理量
l[N]：每个任务的长度
t[N]：每个任务的时间限制
ans[M]：存储结果数组
初始化mx=0（可用容量）和sum=0（总时间）
对当前任务计算最大可处理量x
如果无法满足时间限制，输出-1并退出
如果当前任务的可处理量小于等于可用容量
前min(l[i], mx)个单位按1个时间单位处理
剩余部分按2个时间单位处理
更新剩余容量
如果可处理量大于可用容量，进入复杂处理流程
先处理mx个单位（1个时间单位/个）
计算剩余需要特殊处理的部分z
如果结果数组已经很大，使用优化方法
否则，按步长r循环处理剩余部分
在每个周期开始时记录当前时间sum到结果数组
更新总时间和剩余容量
输出结果数量
如果结果过多则跳过输出
否则输出所有结果


计算从位置z到l[i]-1之间，按步长r分割有多少个区间
(l[i] - 1 - z + 1 + r - 1)/r 等价于 ceil((l[i] - z) / r)
这是在计算还需要多少个时间段，直接加到结果计数上
计算最后一个完整的r区间开始的位置
(l[i] - 1 - z)/r 是完整的区间数
乘以r再加上z得到最后一个完整区间的起始位置
总时间增加最后一次处理的时间（处理剩余数量，最多为r）
更新剩余容量mx

从位置z开始，以步长r循环直到l[i]
每次处理一个大小为r的区间（最后一个区间可能小于r）
如果结果数组还有空间（未达到阈值），则：
++ans[0] 增加结果计数
ans[ans[0]] = sum 存储当前时间到结果数组
否则只增加计数器（不存储具体值，节约内存）
总时间增加本次处理的时间（处理从j到min(j+r, l[i])的元素）
更新剩余容量mx

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+7, M = 1e7+7, inf = 1e5;

int get(int x, int y) {
    int l = 0, r = x, ans = -1;
    while (l <= r) {
        int mid = (l+r)>>1;
        if ((x-mid)*2+mid <= y) r = (ans=mid) - 1;
        else l = mid + 1;
    }
    return ans;
}

int n, r, l[N], t[N], ans[M];
signed main() {
    fast;
    cin >> n >> r;
    for (int i = 1; i <= n; ++i) cin >> l[i];
    for (int i = 1; i <= n; ++i) cin >> t[i];
    for (int i = 1, mx = 0, sum = 0; i <= n; ++i) {
        int x = get(l[i], t[i]);
        if (x == -1) { cout << "-1\n"; return 0; }
        if (x <= mx) {
            sum += min(l[i], mx);
            sum += max(0ll, (l[i] - mx)*2);
            mx = max(0ll, mx - l[i]);
        } else {
            sum += mx; int y = mx;
            x -= mx; mx = 0;
            int z = l[i] - x; sum += (z-y)*2;
            if (ans[0] > N-7) {//为了节省内存，不再存储具体的时间点，而是只统计结果数量
                ans[0] += (l[i] - 1 - z + 1 + r - 1)/r;
                int _ = (l[i] - 1 - z)/r*r+z;
                sum += min(l[i]-_, r), mx = max(0ll, _+r-l[i]);
            } else {
                for (int j = z; j < l[i]; j += r) {
                    if (ans[0] <= N-7) ans[++ans[0]] = sum;
                    else ans[0]++;
                    sum += min(l[i]-j, r), mx = max(0ll, j+r-l[i]);
                }
            }
        }
    }
    cout << ans[0] << '\n';
    if (ans[0] > inf) return 0;
    for (int i = 1; i <= ans[0]; ++i) cout << ans[i] << ' ';
    return 0;
}