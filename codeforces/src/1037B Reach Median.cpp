//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
读入数组长度 n、目标中位数 s，以及 n 个元素。
对数组 升序排序，得到 a[0..n-1]。
mid = n/2 是中位数下标
⚠️ 这里用 mid = n/2，在 n 为偶数时取的是"偏右"的中位数（C++整数除法向下取整)
每次操作可以把某个元素 +1 或 -1，问最少操作多少次能让数组的"中位数为 s"。

因为排序后中位数只取决于中间元素，且要保证中位数恰好为 s，需要做到：

中位数本身 = s；
中位数左边元素 ≤ s，右边元素 ≥ s（保证排序后仍是 s 位处中间）。
情况一：a[mid] < s（中位数偏小）

必须先花 s - a[mid] 步把中位数抬到 s；
因为排过序，中位数右侧元素都 ≥ a[mid] 但仍可能 < s。若右侧某个元素 < s，为了让新中位数仍是 s（不能让右侧出现比 s 小的数），需要把这些 < s 的元素也抬到 s，花费 s - a[i]。
一旦遇到 a[i] >= s 就 break（之后元素更大，无需再改）。
情况二：a[mid] > s（中位数偏大）

对称逻辑：先花 a[mid] - s 把中位数降到 s；
中位数左侧元素都 ≤ a[mid] 但仍可能 > s，把这些 > s 的降到 s，花费 a[i] - s；
遇到 a[i] <= s 就 break。
情况三：a[mid] == s

已经满足条件，输出 0。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

int n, s, a[N];
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    int mid = n/2; ll c = 0;
    if (a[mid] < s) {
        c = s - a[mid];
        for (int i = mid+1; i < n; ++i)
            if (a[i] < s) c += s - a[i]; else break;
        cout << c;
    } else if (a[mid] > s) {
        c = a[mid] - s;
        for (int i = mid-1; i >= 0; --i)
            if (a[i] > s) c += a[i] - s; else break;
        cout << c;
    } else cout << "0\n";
    return 0;
}