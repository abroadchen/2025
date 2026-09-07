//
// Created by Psy.C on 2026/9/7.
//
/**
N=1e2：轮数组上限（理论上能存 100 轮历史状态）。
M=1e5+1e2：每轮数组长度上限（n 最大 1e5 左右）。
a[i][j]：第 i 轮（排序后）数组中第 j 个元素；a[0][*] 存初始、未排序前读入的数组

逐元素比较第 x 轮与第 y 轮排序后的数组是否完全一致。
完全一致 → 返回 true；只要有一个元素不同 → false。
作用：用来检测变换是否进入循环（即某一轮的状态在之前出现过）

读入 n、k、x 和初始数组，放入 a[0] 并排序（作为第 0 轮的初始有序状态）
对第 i-1 轮（已排序）的数组：下标为奇数（j 是奇数）的元素异或 x，偶数下标元素保持不变。
注意：该数组在第 i-1 轮结束已经排好序，这里按排序后下标位置做奇偶异或。
排序：sort(a[i]+1, a[i]+1+n); 第 i 轮生成后重新排序。
循环检测
从第 i-1 轮往前找，若第 i 轮与之前某轮 j 状态相同，记录 pre=j, now=i 并跳出外层
若发现了循环：now 是当前轮（重复发生的那一轮），pre 是与之相同的更早一轮。
则循环节长度为 now - pre。
用公式把巨大的 k 压缩到循环节内：
k = (k - pre) % (now - pre) + pre
即：先把 k 偏移掉 pre 之后的循环部分，取余，再补回 pre。
这样即使 k 极大，也能 O(1) 得到与最终一致的那一轮编号
取出第 k 轮（已被压缩后的 k，若没进循环则 k 仍是原值）的数组。
遍历求出最大值 mx 和最小值 mn
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e2, M = 1e5+1e2, inf = 0x3f3f3f3f;

int n, a[N][M];
bool check(int x, int y) {
    for (int i = 1; i <= n; ++i) {
        if (a[x][i] != a[y][i])
            return false;
    }
    return true;
}

int k, x;
int main() {
    fast;
    cin >> n >> k >> x;
    for (int i = 1; i <= n; ++i) cin >> a[0][i];
    sort(a[0]+1, a[0]+1+n);
    int pre = -1, now = -1;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j&1) a[i][j] = a[i-1][j]^x;
            else a[i][j] = a[i-1][j];
        }
        sort(a[i]+1, a[i]+1+n);
        for (int j = i-1; j >= 1; --j) {
            if (check(i, j)) {
                pre = j; now = i;
                break;
            }
        }
        if (pre != -1) break;
    }
    if (pre != -1) k = (k-pre)%(now-pre) + pre;
    int mx = -1, mn = inf;
    for (int i = 1; i <= n; ++i) {
        if (a[k][i] > mx) mx = a[k][i];
        if (a[k][i] < mn) mn = a[k][i];
    }
    cout << mx << ' ' << mn << '\n';
    return 0;
}