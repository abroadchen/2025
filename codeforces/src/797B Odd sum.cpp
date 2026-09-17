//
// Created by Psy.C on 2026/9/17.
//
/**
abs(x & 1)：x & 1 取最低位。奇数最低位为 1，偶数最低位为 0。所以 abs(x&1) 为真（1）当且仅当 x 是奇数。用 abs 是因为对负数，x&1 在 C/C++ 里二进制补码表示下奇数是 1 也没问题，abs 更保险处理符号。
实际上 x & 1 对负数也是：
(
−
3
)
&
1
=
(
…
11101
)
&
1
=
1
(−3)&1=(…11101)&1=1，仍能正确判别奇偶。abs 是冗余但无害。
奇数 → 全部 push 进 v（无论正负，稍后处理）。
偶数 → sum += max(0, x)：只累加正偶数，负偶数丢弃（加 0），0 也加 0。
这样 sum 初始 = 所有正偶数之和
rbegin/rend 反向迭代器排序 = 降序排列（从大到小）。v[0] 最大
先 sum += v[0]：强制加上最大的那个奇数。
然后从 i=2 开始，步长 2，每次取 v[i] + v[i-1]（即最大的奇数已经用了 v[0]，剩下的从 v[1] 开始两两配对：v[1]+v[2], v[3]+v[4], …）
break 的合理性：降序排列，越往后 v[i-1]+v[i] 越小。一旦某组和 ≤0，说明没有价值且继续会减少 sum，直接跳出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<int> v;//存放所有读入的奇数
int main() {
    fast;
    int n; cin >> n;
    int sum = 0;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (abs(x&1)) v.push_back(x);
        else sum += max(0, x);
    }
    sort(v.rbegin(), v.rend());
    sum += v[0];
    for (int i = 2; i < v.size(); i += 2) {
        if (v[i]+v[i-1] > 0) sum += v[i]+v[i-1];
        else break;
    }
    cout << sum << '\n';
    return 0;
}