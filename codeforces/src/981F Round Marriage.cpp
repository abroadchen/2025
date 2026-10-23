//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
a[N]：数组 A（n 个数）。
b[N<<2]：数组 B，被扩成 3n 长用于环形处理（见下）。
n：每组元素个数；m：环形"周长"
双指针贪心匹配：

假设要让 a[i] 与数组 B 中某个值配对，要求 |a[i] - b[j]| <= x。
对每个 a[i]（已排序）：
while(a[i]-b[l] > x) l++;：若当前左指针 b[l] 太小差得超过 x，右移 l，直到 a[i]-b[l] <= x。
while(b[r]-a[i] > x) r--;：若右指针 b[r] 太大差得超过 x，左移 r。
l++, r++;：成功匹配一对后，左右指针都后移，继续处理下一个 a。
返回 l <= r：所有 a 都能找到一个可配对且不冲突的 b（贪心可证正确）。
即：判断是否存在一种一一配对（每个 a 配一个不同的 b 元素），使所有配对差值 ≤ x
读入 A 数组。

读入 B 数组，并构造三段展开（模拟环形）：

b[i]：原值。
b[n+i] = b[i] + m：向右平移一个环长 m。
b[2*n+i] = b[i] - m：向左平移一个环长 m。
这样 b 长度为 3n，覆盖了"越过边界"的情况（环形匹配可跨过 0/m 边界）。
对 a 和 b 分别排序。

check 的双指针初值 l=1, r=3*n 配合三段展开，实现无环对齐下的"每个 a 找最接近的未用 b"，等价于解决环形排列的最小化最大距离问题
二分的值域 [0, ceil(m/2)]：因为环形上两点的最大可能"最短角度距离"至多为 m/2。
check(mid):能否让所有匹配的差值 ≤ mid。
若可行，记录 ans=mid 并收缩上界 r=mid-1（尝试更小）；否则增大下界。
最终输出最小的可行 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+10;

int n, a[N], b[N<<2];
bool check(int x) {
    int l = 1, r = 3*n;
    for (int i = 1; i <= n; i++) {
        while (a[i]-b[l] > x) l++;
        while (b[r]-a[i] > x) r--;
        l++, r++;
    }
    return l <= r;
}

int m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i]; b[n+i] = b[i]+m; b[2*n+i] = b[i]-m;
    }
    sort(a+1, a+1+n);
    sort(b+1, b+1+3*n);
    int l = 0, r = (m+1)/2, mid, ans;
    while (l <= r) {
        mid = (l+r)>>1;
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans << '\n';
    return 0;
}