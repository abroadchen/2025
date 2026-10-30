//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
n: 长度, cnt: 交换次数
a,b: 输入串, c,d: 排序后的副本
记录每次交换发生的位置（下标+1，即1-based）
若 a 已经等于 b：无需操作，输出 0 并结束。
若排序后 c != d：说明两串的字符多重集不同（所含字符及数量不一致），那么无论怎么交换，a 都不可能变成 b，输出 -1 并结束
从头开始遍历位置 i，如果 a[i] 与 b[i] 不相等，就打算把 b[i] 需要的字符挪到位置 i
在 a 的 i 之后找到目标字符（a[j] == b[i]），即要把 a[j] 一路左移到 i
从 j-1 往左一直到 i，进行相邻交换：把 a[k] 与 a[k+1] 交换（即把字符一步步往左移一位）。
记录交换位置 k+1（1-based 下标，即本来程序里"交换第 k 和第 k+1 个元素位置"，记录的是靠前的那个下标 +1——需要结合输出语义看）。
cnt++ 累计交换次数。
break：本次 i 修正完成，进入下一个 i。
核心思想：贪心地从左到右，逐个位置把 b[i] 需要的字符从右侧移到 i 处，每次移动用一次相邻交换，累计次数即最小总交换次数
第一行输出总交换次数 cnt。
第二行按顺序输出每次交换的位置（1-based，通常用空格分隔
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, cnt;
string a, b, c, d;
vector<int> v;
int main() {
    fast;
    cin >> n >> a >> b; c = a, d = b;
    ranges::sort(c); ranges::sort(d);
    if (a == b) return cout << "0\n", 0;
    if (c != d) return cout << "-1\n", 0;
    for (int i = 0; i < n; i++) if (a[i] != b[i]) {
        for (int j = i+1; j < n; j++) if (b[i] == a[j]) {
            for (int k = j-1; k >= i; k--)
                v.emplace_back(k+1), swap(a[k], a[k+1]), cnt++;
            break;
        }
    }
    cout << cnt << '\n';
    for (auto i : v) cout << i << ' ';
    return 0;
}