//
// Created by Psy.C on 2026/9/27.
//
/**
b:前三位数字；c:后三位数字
s1 前三位和、s2 后三位和
记录"每次改动最多能缩小多少差值"的候选
前三位 b[1..3] 求和得 s1；对每位：
mx 记录"该位当前数字的最大可减小量"：前三位数字本身就是 b[i]，把它改成 0 最多减 b[i]（记入 mx）；
mn 记录"该位最大可增加量"：前三位数字改成 9 最多增加 9-b[i]（记入 mn）。
后三位 c[1..3] 求和得 s2，逻辑反过来：
后三位数字 c[i] 改成 0 最多减 c[i] → 记入 mn（因为这时要减小的是 s2，减 s2 用到的量放进 mn，具体见下面判断）；
后三位改成 9 最多加 9-c[i] → 记入 mx。
仔细看：mx 收集的是"能让当前较大和减下来的量"：对前三位（和 s1 较大时）是 b[i]，对后三位（和 s2 较大时）是 9-c[i]。mn 收集的是"能让当前较小和加起来的量"：前三位是 9-b[i]，后三位是 c[i]。这样 mx 与 mn 分别对应"大和往下减"和"小和往上加"两种策略。
两组候选量都降序排好，方便"每次优先用最大的量"来贪心减少改动次数
前三位和 == 后三位和，无需任何改动，输出 0
前三位和比后三位大，需要把 s1 往下减到 ≤ s2。
每次改动选"当前能减最大量"的那一位（mx[i] 降序），s1 -= mx[i]，改动次数 t++。
一旦 s1 <= s2 就停止，输出所需改动次数 t
后三位和更大，需要把 s2 往下减，或等价地把 s1 往上加；这里用 mn[]（记录把较小和 s1 加大 / 把 s2 减小的量）。
每次 s2 -= mn[i]，改动次数 t++，直到 s2 <= s1 停止，输出 t
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool cmp(int x, int y) { return x > y; }
char a[8];//存 6 位数字串
int b[8], s1, s2, mx[8], mn[8], c[8];
int main() {
    fast;
    cin >> a;
    int t1 = 0, t2 = 0;//mx / mn 的游标
    for (int i = 0; i < 3; ++i) {
        b[i+1] = a[i] - '0'; s1 += b[i+1];//前三位数字及其和
        //改动前三位里一位，最多能减多少
        mx[t1++] = b[i+1]; mn[t2++] = 9 - b[i+1];//改动前三位里一位，最多能加多少
    }
    for (int i = 3; i < 6; ++i) {
        c[i+1] = a[i] - '0'; s2 += c[i+1];
        mx[t1++] = 9 - c[i+1]; mn[t2++] = c[i+1];
    }
    sort(mx, mx+6, cmp);
    sort(mn, mn+6, cmp);
    if (s1 == s2) cout << "0\n";
    else if (s1 > s2) {
        int t = 0;
        for (int i = 0; i < 6; ++i) {
            s1 -= mx[i]; t++;
            if (s1 <= s2) break;
        }
        cout << t << '\n';
    } else {
        int t = 0;
        for (int i = 0; i < 6; ++i) {
            s2 -= mn[i]; t++;
            if (s2 <= s1) break;
        }
        cout << t << '\n';
    }
    return 0;
}