//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
b：题面中给的一个数。
n：序列长度 / 判断次数。
k：循环辅助计数器（每轮递减）。
s：统计"符合条件的奇数个数总和"
k 的作用：作为"倒数第 i 个位置"的逆序辅助计数。每读入一个数它就减 1，最终到最后一个元素时 k == 0，用这个条件单独判断"最后一个奇数"
i 从 0 到 n-1，a 在循环内读入。
每轮 i++ 同时 k--。
条件 i < n-1：即不是最后一个元素时才看这个判断（最后一个元素交给 k==0 那支）。
当 a 是奇数 且 b 是奇数 时，s++。
因为 b 在整个过程中不变，所以 b%2 != 0 对所有非末位元素都成立（只要 b 是奇数）。
也就是说：只要 b 是奇数，序列中除了最后一个元素外的所有奇数都会让 s 加 1
k == 0：只有循环进行到最后一个元素（第 n 个，即 i = n-1）时才满足。
此时不看 b，只看 a（最后一个元素）是否是奇数，是则 s++
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll b, n, k, s;
int main() {
    fast;
    cin >> b >> n; k = n-1;
    for (int i = 0, a; i < n; i++, k--) {
        cin >> a;
        if (i < n-1) if (a%2 != 0 && b%2 != 0) s++;
        if (k == 0) if (a%2 != 0) s++;
    }
    if (s%2 == 0) cout << "even"; else cout << "odd";
    return 0;
}