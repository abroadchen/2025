//
// Created by Psy.C on 2026/10/17.
//
/**
ceil(k/d)*d：大于等于 k 的最小 d 的整数倍，即一个完整周期总时长。周期 = ceil(k/d)*d。
一个周期内：
前 k 时间全功率（速率 1），积累进度 k；
剩余 (ceil(k/d)*d - k) 时间半功率（速率 0.5），积累进度 (周期-k)/2；
x = (ceil(k/d)*d-k)/2 + k 就是一个完整周期积累的总进度（前 k 全速 + 后半速部分 ÷2）。
所以 x = 单个周期能获得的进度总量
cnt = t / x 向下取整 = 完整周期个数（能完整跑多少个整周期）
res = 跑完 cnt 个完整周期后，剩余还需要积累的进度
若剩余进度 res ≤ k：说明剩下的部分只需要在全功率段内完成，时间就是 res（全速 1:1），加上已跑完的 cnt 个完整周期时间 (ceil(k/d)*d)*cnt
若 res > k：前 k 进度在全功率段完成（时间 k），剩下 res-k 进入半功率段，半功率下所需实际时间是 (res-k)*2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define ll long long
using namespace std;

db k, d, t;
int main() {
    fast;
    cin >> k >> d >> t;
    db x = (ceil(k/d)*d-k)/2+k;
    ll cnt = t/x;
    db res = t-x*cnt, ans;
    if (res <= k) ans = res + (ceil(k/d)*d)*cnt;
    else ans = (ceil(k/d)*d)*cnt+k+(res-k)*2;
    cout << fixed << setprecision(9) << ans;
    return 0;
}