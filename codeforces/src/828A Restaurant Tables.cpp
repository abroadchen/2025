//
// Created by Psy.C on 2026/9/24.
//
/**
读入 n（顾客组数）、初始单人位数 a[1]、初始双人位数 a[2]，a[0] 初始 0
情况 A：来的是 2 人组 x == 2
若有空闲双人位 → 直接给这 2 人用掉一个（a[2]--）。
否则 → 没有能容纳 2 人的位置了，这 2 人被拒绝，sum += 2
情况 B：来的是 1 人组 x == 1
优先用空闲单人位 a[1] → 若还有，直接用掉（a[1]--）。
若没有单人位了：
其次拆一个双人位：若还有空闲双人位 a[2] → 占用一半（a[2]--），同时剩下的一半变成一个额外单人位（a[0]++）。
再用拆出来的剩余单人位 a[0] → 若还有就用（a[0]--）。
全都没有 → 这 1 人被拒，sum++
输出被拒绝的总人数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[3], n, sum;
int main() {
    fast;
    a[1] = 0, a[2] = 0, a[0] = 0;
    cin >> n >> a[1] >> a[2];
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (x == 2) {
            if (a[2] > 0) a[2]--;
            else sum += 2;
        } else if (x == 1) {
            if (a[1] > 0) a[1]--;
            else {
                if (a[2] > 0) { a[2]--; a[0]++; }
                else if (a[0] > 0) a[0]--;
                else sum++;
            }
        }
    }
    cout << sum;
    return 0;
}