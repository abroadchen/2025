//
// Created by Psy.C on 2026/2/18.
//
/**
h, a, d: 血量、攻击、防御的提升价格
Hy, Ay, Dy: 我方初始血量、攻击、防御
Hm, Am, Dm: 敌方血量、攻击、防御
x: 购买血量提升的次数
y: 购买攻击提升的次数
z: 购买防御提升的次数
x*h <= c: 血量提升费用不超过预算
x*h+y*a <= c: 攻击提升费用不超过剩余预算
x*h+y*a+z*d <= c: 防御提升费用不超过剩余预算
x+Hy: 最终血量
max(0, y+Ay-Dm): 最终攻击力（不低于0）
Hm: 敌方血量（不变）
max(0, Am-Dy-z): 敌方对我造成的伤害（不低于0）

二分搜索：O(log inf)
每次check：O(预算³)（三层嵌套循环）
总体：O(log(30010) × 预算³) ≈ O(预算³)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int inf = 3e4+10;

/**
 *
 * @param sa 我方血量
 * @param aa 我方攻击力
 * @param sb 敌方血量
 * @param bb 敌方攻击力
 * @return
 */
inline int ok(const int sa, const int aa, const int sb, const int bb) {
    if (aa == 0) return 0;//我方攻击力为0，无法获胜
    if (bb == 0) return 1;//敌方攻击力为0，我方获胜
    int t = sa/bb;//我方能承受敌方攻击的回合数
    if (t*bb == sa) t--;//刚好整除，减1（因为最后一次攻击后就死了）
    if (sb - t*aa <= 0) return 1;//在t回合内能否击败敌人
    return 0;
}

int h, a, d, Hy, Ay, Dm, Hm, Am, Dy;
inline int check(const int c) {
    for (int x = 0; x*h <= c; ++x)
        for (int y = 0; x*h+y*a <= c; ++y)
            for (int z = 0; x*h+y*a+z*d <= c; ++z)
                if (ok(x+Hy, max(0, y+Ay-Dm), Hm, max(0, Am-Dy-z)))
                    return 1;
    return 0;
}

int main() {
    fast;
    cin >> Hy >> Ay >> Dy >> Hm >> Am >> Dm >> h >> a >> d;
    int l = 0, r = inf;
    while (l <= r) {
        if (const int mid = (l + r)>>1; check(mid)) r = mid - 1;//尝试更少钱
        else l = mid + 1;
    }
    cout << r + 1 << '\n';//最小的可行花费
    return 0;
}