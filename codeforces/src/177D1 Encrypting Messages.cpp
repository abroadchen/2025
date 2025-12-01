//
// Created by Psy.C on 2025/11/30.
//
/*
*n: 第一个序列的长度
m: 第二个序列的长度
c: 模数
a[N]: 第一个序列数组
b[N]: 第二个序列数组
 *
 *读取第一序列的元素，并将它们存储在sum[i][2]中
 *读取第二序列的元素 初始化sum[1][1]为第二个序列的第一个元素
 *输出第一个结果：(b[1] + a[1]) % c
 *如果m=1，则所有结果都是a[i]+b[1]
 *
*xb: 滑动窗口的起始位置
j: 用于追踪滑动窗口中被移除元素的索引
 *从i=2开始处理，gs表示当前窗口大小
 *如果当前窗口大小不超过允许的最大窗口大小(n-m+1)
 *如果达到最大窗口大小，记录起始位置
 *如果窗口大小不超过m
 *如果窗口大小等于m，记录起始位置
 *累加当前元素到前缀和
 *增加窗口大小
 *否则保持前缀和不变
 *如果窗口超过允许大小
 *移除窗口左边元素，添加新元素
 *移动窗口起点
 *
 *sum[i][1] 存储第二个序列相关的计算结果，sum[i][2] 存储第一个序列的原始值
*- b[j]: 移除窗口左边界的元素
+ b[j + (n - m + 1)]: 添加窗口右边界的元素
j++: 更新下次需要移除的元素位置
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define ll long long
using namespace std;

int n, m, c, a[N], b[N];
ll sum[N][5];//存储前缀和

int main() {
    fast;
    cin >> n >> m >> c;
    for (int i = 1; i <= n; ++i) { cin >> a[i];  sum[i][2] += a[i]; }
    for (int i = 1; i <= m; ++i) cin >> b[i];
    sum[1][1] += b[1];
    cout << (sum[1][1] + sum[1][2]) % c << " ";
    if (m == 1) {
        for (int i = 2; i <= n; ++i) cout << (a[i] + b[1]) % c << " ";
        return 0;
    }
    int xb = 1, j = 1;
    for (int i = 2, gs = 2; i <= m; ++i) {
        if (gs <= n - m + 1) {
            if (gs == n - m + 1) xb = i - 1;
            if (gs <= m) {
                if (gs == m) xb = i - 1;
                sum[i][1] += sum[i - 1][1] + b[i];
                gs++;
            } else sum[i][1] = sum[i - 1][1];
        } else {
            sum[i][1] += sum[i - 1][1] - b[j] + b[j + (n - m + 1)];
            j++;//移动窗口起点
        }
        cout << (sum[i][1] + sum[i][2]) % c << " ";
    }
    for (int i = m + 1; i <= n; ++i) {//处理剩余的元素
        if (i < n - xb + 1) sum[i][1] += sum[i - 1][1];//如果还在窗口范围内，保持前缀和
        else {//否则移除窗口左边元素
            sum[i][1] += sum[i - 1][1] - b[j];
            j++;
        }
        cout << (sum[i][1] + sum[i][2]) % c << " ";
    }
    return 0;
}