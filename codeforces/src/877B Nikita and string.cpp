//
// Created by Psy.C on 2026/10/6.
//
/**
逐个读入字符，当读到的字符 ASCII 码 >= 'a'（即小写字母 a-z）时继续循环；一旦读到非小写字母（如换行、EOF、空格等）就停止。
所以处理的是一个小写字母串
情况 A：c == 'a'：
len++：len 计数 'a' 出现的次数。
若 k > 0，则 k--：这里 k 表示"当前连续的非 a 字符段"里累积的某种数量，读到 a 时会减少它。
情况 B：c != 'a'（其他小写字母）：
++k：k 增加。
mx = max(k, mx)：mx 记录 k 达到过的最大值

len = 字符串中 a 的个数。
k = 当前在处理"，每读到一个非 a 字符 k 累加；mx 是非 a 字符连续段的峰值
最长结果 = 所有 a 的数目 + 最大的一段连续非 a 长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char c;
int len, mx, k;
int main() {
    fast;
    while ((c=getchar()) >= 'a') {
        if (c == 'a') {
            len++;
            if (k > 0) k--;
        }
        else mx = max(++k, mx);
    }
    cout << len + mx << '\n';
    return 0;
}