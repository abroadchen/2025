//
// Created by Psy.C on 2025/12/5.
//
/*
 *n: 物品总数, d: 深度限制, s: 特性总预算
 *
*第一类物品（不合法物品）：深度<限制 或 特性>预算
如果价值x>0：累计到ca和all，计数cnt
如果价值x≤0：计数tag
第二类物品（合法物品）：存储到数组v中
如果价值x>0：标记flag=1，累计sum，更新最小特性值mn
如果价值x≤0：计数tag2
 *
 *按特性值(feature)对合法物品进行升序排序
*如果有正价值物品(flag=1)且满足特定条件，则可以选择所有物品
输出总数量n和最小特性值mn
*ok: 最小特性值物品的索引
t: 备用预算
p: 原始预算
如果没有正价值物品，all设为0
否则预留最小特性值物品的空间
*贪心选择物品（排除最小特性值物品）：
按特性值从小到大选择
跳过必须选择的最小特性值物品
直到预算不足或选完所有物品
 *
*tot: 不考虑必须选择物品时能选择的总数
如果tot更大，则更新结果
输出选择的物品数量和使用的特性值总和
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 100010, inf = 1e9+1;
struct node { int c, f; } v[N];

int main() {
    fast;
    int n, d, s, x, y, z, i;
    while (cin >> n >> d >> s) {
        int h = n, cnt = 0, tag = 0, idx = 0, mn = inf, tag2 = 0, flag = 0;
        ll ca = 0, all = 1, sum = 0;
        while (h--) {
            cin >> x >> y >> z;
            if (z < d || y > s) {
                if (x > 0) {
                    ca += x;
                    cnt++;
                    all += x;
                } else tag++;
            } else {
                v[idx].c = x; v[idx].f = y;
                idx++;
                if (x > 0) {
                    flag = 1;
                    sum += x - 1;
                    all += x;
                    if (y < mn) mn = y;
                } else tag2++;
            }
        }
        sort(v, v + idx, [](const node &a, const node &b) {
            return a.f < b.f;
        });
        if (flag && sum + ca - cnt >= tag + tag2) cout << n << ' ' << mn << '\n';
        else {
            int ok = -1, t = s, tot = 0;
            const int p = s;
            if (flag == 0) all = 0;
            else {
                for (i = 0; i < idx; ++i) if (v[i].f == mn) { ok = i; break; }
                s -= mn;
            }
            i = 0;
            while (i < idx && s >= v[i].f) {
                if (i == ok) { i++; continue; }
                s -= v[i].f;
                i++;
                all++;
                if (all >= n) { all = n; break; }
            }
            while (i < idx && t >= v[i].f) { t -= v[i].f; tot++; }
            if (tot > all) { all = tot; s = t; }
            cout << all << ' ' << p - s << '\n';
        }
    }
    return 0;
}