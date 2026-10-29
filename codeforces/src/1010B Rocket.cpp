//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
N=32：n 上界（题设 n ≤ 30）。
m：范围右端 [1,m]。
n：撒谎周期长度。
f[N]：记录前 n 次询问中每个位置是否撒谎（0=这次回答真实，1=这次回答被翻转）
读入 m、n。
连续 n 次都猜 1（答案显然 > 1，因为范围 [1,m] 且 m 较大）。
每次读入裁判回答 x：
x==-1：真实含义是"答案 < 1" → 矛盾（1 已是最小），所以这次回答是假的 → f[i]=0（记录为"这轮是真实回答"？不，这里语义需注意，见下）。
x==1：裁判回答"答案 > 1"，而真实答案必然 >1，所以真实 → f[i]=1。
x==0：猜中答案 → 直接结束（return 0）
初始 l=2（因为已排除 1），r=m，cur=0（当前询问轮，对应 f 周期下标）。

循环：

mid=(l+r)>>1 取中点，cout << mid << endl 询问。
cin >> x 读裁判回答（1=答案更大，-1=更小，0=猜中）。
if (!f[cur]) x = -x;：如果当前轮是撒谎轮（f[cur]==0），把收到的回答 x 取反，还原成真实符号。这样后续判断基于真实关系。
if (x == 0) return 0; 猜中 → 结束。
if (x == 1) l = mid+1;（真实情况：答案 > mid，答案在上半区）。
else r = mid-1;（答案 < mid，在下半区）。
++cur, cur %= n;：进入下一个询问轮，周期回绕（n 周期内撒谎模式重复）。
二分在 [1,m] 中定位答案并输出。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 32;

int m, n;
bool f[N];
int main() {
    fast;
    cin >> m >> n;
    for (int i = 0, x; i < n; ++i) {
        cout << 1 << endl;
        cin >> x;
        if (x == -1) f[i] = 0;
        else if (x == 1) f[i] = 1;
        else return 0;
    }
    int l = 2, r = m, cur = 0, x;
    while (l <= r) {
        int mid = (l+r)>>1;
        cout << mid << endl;
        cin >> x;
        if (!f[cur]) x = -x;
        if (x == 0) return 0;
        if (x == 1) l = mid+1; else r = mid - 1;
        ++cur, cur %= n;
    }
    return 0;
}