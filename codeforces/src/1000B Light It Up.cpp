//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
a[0]=0，读入 n 个开关位置。
sum[i] = 第 i 段长度。
flg 交替（1,0,1,0...）表示亮/灭：某段是亮段则加上其长度进 pre，灭段则加 0（flg=0 时 flg*sum[i] 为 0）。
a[n+1]=m，补上最后一段。
得到 pre[i] = 前 i 段中亮段总长度。（提醒：这里灭段用 flg=0 表示"不加"，所以 pre 是纯亮段累计。）
从末尾往前，cnt 从 0 开始递增，t[cnt%2] 是"该奇偶层的累计长度"。
suf[i] = 从第 i 段到末尾的亮段总长度。
因为亮灭是交替的，"从第 i 段起"到末尾的亮段总和 = 第 i 段起每隔一段累加。用 t[cnt%2] 朝一个方向累加，正好累计"与末尾同奇偶"的那些段的长度。
suf[1]：什么都不改时，整条线段 [0,m] 的亮段总长（初始答案）。
遍历每个段边界 i：pre[i] - 1 + suf[i+1]。
pre[i] = 前 i 段亮段长；suf[i+1] = i+1 段往后的亮段长；
中间的"−1"代表对第 i 段做一次长度 +1 的翻转（题里通常是"把某个灭段变成亮段且长度 +1"，即在某个空档多点亮 1 单位）后，这一段的贡献由原来的"亮 or 灭"变为最优。
取最大值。
输出总最大亮时长 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+10;

int n, m, a[N], sum[N], pre[N], suf[N], t[N];
int main() {
    fast;
    cin >> n >> m; a[0] = 0;
    int flg = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = a[i] - a[i-1];
        pre[i] = pre[i-1] + flg*sum[i];
        flg = !flg;
    }
    a[n+1] = m; sum[n+1] = a[n+1] - a[n]; pre[n+1] = pre[n] + flg*sum[n];
    int cnt = 0;
    for (int i = n+1; i > 0; i--) {
        t[cnt%2] += sum[i];
        suf[i] = t[cnt%2];
        cnt++;
    }
    int ans = suf[1];
    for (int i = 1; i <= n+1; i++) ans = max(ans, pre[i]-1+suf[i+1]);
    cout << ans << '\n';
    return 0;
}