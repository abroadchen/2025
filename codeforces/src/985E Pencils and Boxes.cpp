//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
a：输入的数（排序后）。
c[i]：第 i 个位置能否作为某一段的结尾（可达标记，1 表示能从起点划分到此，dp 语义）。
st[i]：能否作为下一段的起点
c[0]=1：虚拟起点（位置 0，表示之前已划分完）。

st[1]=1：位置 1 可以作为起点。

外层遍历每个可能作为起点 s：

if (st[s] == 1)：仅当 s 真的可达为起点时才尝试从这里划分。
内层 while（双指针 e）：
条件 a[e]-a[s] <= d：当前扩展到的位置 e 与起点 s 的差不超过 d，即这一段最大最小差合法（因已排序，a[e]-a[s] 就是段内差）。
if (e - s + 1 >= k)：若这一段长度达到 k，则可作为一段划分；标记 c[e]=1（位置 e 可作结尾），并 st[e+1]=1（下一个位置可作为新起点）。
e++ 继续向后扩展。
最终 c[n]==1 表示能从位置 n 作为一段的结尾完整划分到底 → YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5e5+5;

int n, k, d, a[N], c[N], st[N];
int main() {
    fast;
    cin >> n >> k >> d;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1, a+n+1);
    c[0] = 1; st[1] = 1;
    int e = 1;
    for (int s = 1; s <= n; s++) {
        if (st[s] == 1) {
            while (a[e] - a[s] <= d && e <= n) {
                if (e - s + 1 >= k) { c[e] = 1; st[e+1] = 1; }
                e++;
            }
        }
    }
    if (c[n] == 1) cout << "YES\n"; else cout << "NO\n";
    return 0;
}