//
// Created by Psy.C on 2025/12/9.
//
/*
 *
*循环生成广义斐波那契数列（受限制的斐波那契数列）：
当累计和sum小于等于s时继续循环
f[i] = sum（当前项等于前k项的和）
sum += f[i]（更新累计和）
如果i+1 > k，则减去最早的一项f[i-k]（维持窗口大小为k）
t自增（记录生成了多少项）
 *
 *将t的值赋给j（j指向最后一项）
*贪心算法分解s：
当s不为0时继续循环
如果s大于等于f[j]：
从s中减去f[j]
将f[j]添加到向量v中
j自减（检查更小的项）
 *
*如果向量v中只有一个元素：
输出2（表示有两个数）
换行后输出0和该元素（构造两个不同的数）
*否则（向量v中有多个元素）：
输出向量大小（数的个数）
遍历向量v，输出每个元素（用空格分隔）
最后换行
 *时间复杂度约为O(log s)，空间复杂度为O(log s)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
using namespace std;


int main() {
    fast;
    int s, k; cin >> s >> k;
    int f[N]; f[0] = 1;
    int sum = 1, t = 0;
    for (int i = 1; sum <= s; ++i) {
        f[i] = sum;
        sum += f[i];
        if (i + 1 > k) sum -= f[i-k];
        t++;
    }
    int j = t;
    vector<int> v;
    while (s) {
        if (s >= f[j]) { s -= f[j]; v.push_back(f[j]); }
        j--;
    }
    if (v.size() == 1) cout << 2 << '\n' <<
        0 << ' ' << *v.begin() << '\n';
    else {
        cout << v.size() << '\n';
        for (const int& it : v) cout << it << ' ';
        cout << '\n';
    }
    return 0;
}