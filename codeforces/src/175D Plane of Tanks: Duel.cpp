//
// Created by Psy.C on 2025/11/29.
//
/*
*hp: 初始血量
dt: 攻击间隔时间
l, r: 攻击伤害范围[l,r]
*p0, p1: 闪避概率
f0, f1: 概率分布数组，f[i]表示血量为i的概率
 *
*模拟一次攻击过程：
遍历所有可能的血量状态
对每个非零概率状态：
计算攻击后的各种可能结果
每种伤害j的概率为(1-p)/(r-l+1)
造成伤害后血量变为max(i-j, 0)
原状态保留的概率为闪避概率p
 *
*如果角色0闪避率接近100%，角色1必败，输出0
如果角色1闪避率接近100%，角色1必胜，输出1
 *
*f0[hp0] = 1: 角色0初始血量为hp0的概率为1
f1[hp1] = 1: 角色1初始血量为hp1的概率为1
t0, t1: 双方下次攻击时间
ans: 角色1获胜概率
 *
*时间驱动：比较下次攻击时间，决定谁先攻击
角色0攻击(t0 <= t1)：
更新攻击时间t0 += dt0
重置角色1死亡概率f1[0] = 0
角色0攻击角色1，调用ok(f1, l0, r0, p0)
累加角色1刚死亡的概率：(1-f0[0]) * f1[0]
角色1攻击(t0 > t1)：
更新攻击时间t1 += dt1
角色1攻击角色0，调用ok(f0, l1, r1, p1)
如果没有存活状态(!ok返回false)，战斗结束
 *
 */
#include <iomanip>
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-12
using namespace std;

constexpr int N = 200;
int hp0, dt0, l0, r0;
int hp1, dt1, l1, r1;
double p0, p1, f0[N+20], f1[N+20];

bool ok(double f[N], const int l, const int r, const double p) {
    bool ret = false;
    for (int i = 1; i <= N; ++i) {
        if (f[i] < eps) continue;
        ret = true;
        for (int j = l; j <= r; ++j)
            f[max(i-j, 0)] += f[i] * (1 - p) / (r - l + 1);
        f[i] *= p;
    }
    return ret;
}

int main() {
    fast;
    cin >> hp0 >> dt0 >> l0 >> r0 >> p0;
    cin >> hp1 >> dt1 >> l1 >> r1 >> p1;
    p0 /= 100, p1 /= 100;
    if (p0 > 0.999) { cout << "0" << '\n'; return 0; }
    if (p1 > 0.999) { cout << "1" << '\n'; return 0; }
    f0[hp0] = 1, f1[hp1] = 1;
    int t0 = 0, t1 = 0; double ans = 0;
    while (true) {
        if (t0 <= t1) {
            t0 += dt0;
            f1[0] = 0;
            ok(f1, l0, r0, p0);
            ans += (1 - f0[0]) * f1[0];
        } else {
            t1 += dt1;
            if (!ok(f0, l1, r1, p1)) break;
        }
    }
    cout << fixed << setprecision(12) << ans << '\n';
    return 0;
}