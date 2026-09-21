//
// Created by Psy.C on 2026/9/21.
//
/**
s[i][j] = 前 i 个字符中，字符 j 出现的次数（二维前缀和）。
用于 O(1) 求任意区间 [l,r] 内某个字母的出现次数：s[r][j]-s[l-1][j]
遍历所有起点为 i、长度为 x 的窗口 [i, i+x-1]。
该窗口内字符 b 的数量 = s[i+x-1][b]-s[i-1][b]。
要把整个窗口都变成 b，需要把"非 b 的字符"改掉，数量 = x - (b的数量)。
若这个改动数 ≤ a（可用次数），则该长度 x 可行 → return true。
这是滑动窗口/双指针判断：是否存在一个长 x 的子串，改 ≤ a 次后全为 b
对每个 (可改次数 i, 字母 j)，二分搜索满足 check 的最大长度 x。
check 具有单调性：能改出长度 x 的全 b 段，那么更短的也一定能 → 可二分。
结果存进 ans[i][j] = 可用 i 次修改时，j 的最长连续段
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1505, M = 26;

int n, s[N][M];
inline bool check(int a, int b, int x) {
    for (int i = 1; i+x-1 <= n; ++i)
        if (x-(s[i+x-1][b]-s[i-1][b]) <= a)
            return true;
    return false;
}

string str;
int q, ans[N][M], m;
char c;
int main() {
    fast;
    cin >> n >> str >> q; str = ' ' + str;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 26; ++j)
            s[i][j] = s[i-1][j] + (str[i]-'a'==j);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 26; ++j) {
            int l = 1, r = n;
            while (l < r) {
                int mid = (l+r+1)>>1;
                if (check(i, j, mid)) l = mid;
                else r = mid-1;
            }
            ans[i][j] = r;
        }
    while (q--) {
        cin >> m >> c;
        cout << ans[m][c-'a'] << '\n';
    }
    return 0;
}