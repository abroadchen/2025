//
// Created by Psy.C on 2026/10/20.
//
/**
x：给定的目标数。
d：一个间隔量。
now：当前要填写的数值，初始为 1。
b[]：结果数组。
cnt：结果数组的长度。
a：当前处理到的二进制位（从第 0 位开始，每轮 +1；也表示"前 a 个数作为一段"的概念）
逐轮（处理 x 的第 a 位，a 从 0 开始，每轮右移一位、a 自增）：

if (x&1)：当 x 的当前位（第 a 位）为 1 时：
先往数组里连续加入 a 个 now（即 b 中追加 a 个当前值 now）。
if (a != 0) now += d;：若 a 不为 0，把 now 增加 d（拉开间隔）。
再往数组里加入 1 个 now。
now += d;：最后再让 now 增加 d，进入下一段。
x >>= 1; 处理下一位。
++a; 位数 +1。
理解：

这里的 a 既是被处理到的位下标，又表示在某位出现 1 时要先填写的个数。
每段用"间隔 d"让数值形成"高一位都不进位"的间隔，使得不同段之间能独立进行位或（bitwise OR）的组合。
这种构造利用了：不同段用相隔很大的数（差 d，保证最高位不同），使各段可独立选或不选，从而子集 OR 的组合数可乘成 2^k 的形式，进而构造出任意 x。
具体地，若 x 的二进制中有 k 个"组"，第 a 位的那个"1"代表 2^a 份贡献。作者用 a 个重复的 now（贡献 a+1 个选择）来累乘出 2 的幂次关系，从而精确表达 x 的每一位
先输出构造出的数组长度 cnt，再输出整个数组 b，空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

ll x, d, now(1), b[N], cnt;
int main() {
    fast;
    cin >> x >> d;
    int a = 0;
    while (x) {
        if (x&1) {
            for (int i = 1; i <= a; ++i) b[++cnt] = now;
            if (a != 0) now += d;
            b[++cnt] = now;
            now += d;
        }
        x >>= 1;
        ++a;
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i) cout << b[i] << ' ';
    cout << '\n';
    return 0;
}