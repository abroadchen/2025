//
// Created by Psy.C on 2026/10/11.
//
/**
a 是 RLE 压缩后的段数组：c 是字符，num 是该字符连续出现的次数（剩余数量）
遍历 [0,len)，跳过 num==0 的段（已被消光）。
j 是压缩后数组的新游标：
第一个非零段直接放到 a[0]；
若当前段字符与 a[j] 相同 → 合并数量 a[j].num += a[i].num；
否则放到新的位置 a[++j]。
返回压缩后最后一个有效下标 j（注意返回的是下标，不是长度）
len = update(...) + 1：因为 update 返回的是下标，所以有效段数 = 返回下标 + 1。

每轮操作（假设当前有 len 个段，下标 0..len-1）：

中间段（i=1..len-2）各减 2；
头段 a[0] 减 1，尾段 a[len-1] 减 1；
然后 update 重新合并相邻相同段、清掉 num≤0 的段；
cnt++ 记录轮数。
直到 len 压缩后变成 1（只剩一个段）为止，返回轮数
把每个字符初始化为独立段 num=1，然后调用 get()
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+10;
struct node { char c; int num; } a[N];

int update(int len) {
    int j = 0, flg = 0;
    for (int i = 0; i < len; ++i) {
        if (a[i].num > 0) {
            if (!flg) { flg = 1; a[j] = a[i]; }
            else if (a[i].c == a[j].c) a[j].num += a[i].num;
            else a[++j] = a[i];
        }
    }
    return j;
}

char s[N];
int get() {
    int len = update(strlen(s)) + 1, cnt = 0;
    while (len > 1) {
        for (int i = 1; i < len-1; ++i) a[i].num -= 2;
        a[0].num--; a[len-1].num--;
        len = update(len) + 1;
        cnt++;
    }
    return cnt;
}

int main() {
    fast;
    cin >> s;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) { a[i].c = s[i]; a[i].num = 1; }
    cout << get() << '\n';
    return 0;
}