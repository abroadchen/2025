//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
a[i]：第 i 个元素的值；
b[val]：记录值 val 出现多少次（频次计数）；
mx：所有值中出现次数的最大值；
c[val][color]：布尔表，标记"值 val 是否已经用了 color 这个颜色"
读入每个元素并累计其值的出现次数 b[a[i]]++；
动态维护 mx = 出现次数最多的那个值出现了多少次。
关键判断：每个值最多出现 mx 次，而相同值必须用不同颜色，所以总共至少需要 mx 种颜色
若 mx > k：出现最多的值有 mx 个但只有 k 种颜色，不够分配 → 无解，输出 NO；
若 n < k：颜色数多于元素个数，必然会有某种颜色用不到，也无法构成合法方案（通常这类题要求所有 k 种颜色都要用到）→ 无解。
否则进入构造 YES 方案
先保证前 k 个元素分别用颜色 1,2,...,k（每个颜色先用一次），并更新 c[a[i]][i+1]=1 记录"值 a[i] 已用颜色 i+1"。
这一步是为了满足"所有 k 种颜色都用上"的要求。
前提是前 k 个数互不冲突——因为有 mx <= k 的保证，前 k 个里同值的最多 mx 个，能错开用不同颜色（这里直接顺序分配 1..k，靠条件保证可行）
对剩余元素（第 k 个到第 n-1 个），贪心地给每个元素挑一个该值还没用过的颜色：
从小到大找颜色 j，若 c[a[i]][j]==0（该值还没用 j 色），就分配 j 并标记、输出，然后 break。
由于每个值最多 mx <= k 个、且颜色有 k 种，这种贪心总能找到可用颜色（鸽巢原理保证：同值元素数量 ≤ k-1 时，始终有剩余颜色）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5010;

int a[N], b[N], mx;
bool c[N][N];
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i]; b[a[i]]++;
        mx = max(mx, b[a[i]]);
    }
    if (mx > k || n < k) cout << "NO\n";
    else {
        cout << "YES\n";
        cout << "1"; c[a[0]][1] = 1;
        for (int i = 1; i < k; i++) {
            cout << ' ' << i+1;
            c[a[i]][i+1] = 1;
        }
        for (int i = k; i < n; i++)
            for (int j = 1; j <= k; j++) if (c[a[i]][j] == 0) {
                cout << ' ' << j; c[a[i]][j] = 1;
                break;
            }
        cout << '\n';
    }
    return 0;
}