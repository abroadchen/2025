//
// Created by Psy.C on 2026/10/19.
//
/**
hh：当前小时
mm：当前分钟
h：当前饥饿值
d：每分钟增加的饥饿值
c：每个披萨原价
n：每个披萨能抵消的饥饿值
情况一：hh >= 20（已经是 20 点或之后）
已经是 20 点以后直接按八折买。需要的披萨数 = ceil(h/n)（饥饿值 h 除以每个披萨 n，向上取整），每个 × 原价 c，再 × 0.8 折扣。输出这个花费
情况二：hh < 20（还没到 20 点）
方案 1：现在就买，需 ceil(h/n) 个披萨 × 原价 c，不打折。这是"即刻购买"的成本
准备方案 2：算出从现在距 20:00 还有多少分钟。

20 点与当前小时的差 (20-hh) 小时 × 60 转成分钟，再减去当前分钟 -mm，得到还需等待的分钟数。
每分钟饥饿值增加 d，所以届时饥饿值 = 当前 h + 等待分钟数 × d
方案 2：等到 20 点后，用增长后的饥饿值 h 计算需要的披萨数 ceil(h/n)，× 原价 c，× 0.8 折扣。
取两个方案花费的较小值输出（保留 4 位小数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
using namespace std;

db hh, mm, h, d, c, n;
int main() {
    fast;
    cin >> hh >> mm >> h >> d >> c >> n;
    if (hh >= 20) {
        db p = ceil(h/n)*c*0.8;
        printf("%.4lf", p);
    } else {
        db p1 = ceil(h/n)*c;
        h += ((20-hh)*60-mm)*d;
        db p2 = ceil(h/n)*c*0.8;
        printf("%.4lf", min(p1, p2));
    }
    return 0;
}