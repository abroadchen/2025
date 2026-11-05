//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
n：元素个数
a[]：数组
vis[]：标记"此位置需要被删除/处理"（标记为 1）
num：负数的个数
mx, pos：负数中的最大值及其位置（用于选中"绝对值最小的那个负数"）
把所有 0 标记为待处理（vis=1）。
统计负数个数 num，并记录绝对值最小的负数（即最大的负数）所在位置 pos
若负数个数为奇数，则在结尾时乘积会是负的。为了让乘积为正（或避免负号），需要删掉一个负数——选"绝对值最小"的负数删掉（这样损失最小）。
把这个"绝对值最小的负数"也标记为待处理。
若负数为偶数，则无需删负数（负负得正）。
对所有被标记待删除的位置，依次用操作 1（1 x y，把 x 和 y 合并/删除其一）串联起来：1 pre i，表示把已标记的元素逐个合并掉。
cnt 统计用了多少次操作 1。
若存在待删点（pre != 0）且还没删完（cnt < n-1），再用操作 2（2 pre）整体删除这个被合并出来的"最后一个复合元素"。
这一步的作用：把 0 们和一个"最弱负数"合并成一个并整体删掉，从而在数轴上"剔除"这些会拖累乘积的元素
遍历未被标记（保留下来的）元素，用操作 1 依次串联它们。这样保留的所有元素会被合并为一个大复合体，其乘积 = 所有保留元素的乘积，达到要求的"非负且尽量大"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); i++)
using namespace std;

constexpr int N = 2e5+5, inf = 2e9;

int n, a[N], vis[N], num, mx(-inf), pos;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> a[i];
        if (a[i] == 0) vis[i] = 1;
        if (a[i] < 0) {
            num++;
            if (a[i] > mx) mx = a[i], pos = i;
        }
    }
    if (num&1) vis[pos] = 1;
    int pre = 0, cnt = 0;
    rep(i,n) if (vis[i]) {
        if (pre) cout << "1 " << pre << ' ' << i << '\n', cnt++;
        pre = i;
    }
    if (pre && cnt < n-1) cout << "2 " << pre << '\n';
    pre = 0;
    rep(i,n) if (!vis[i]) {
        if (pre) cout << "1 " << pre << ' ' << i << '\n';
        pre = i;
    }
    return 0;
}