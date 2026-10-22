//
// Created by Psy.C on 2026/10/22.
//
/**
循环 i 从 1 到 x-1（共 x-1 步），双指针向中间收缩。
分支 1：若 s[l] <= y → l++ 且 r--（两端各收缩一步）。
分支 2（else if）：若 y+x-i == s[r] → y++，且 ans += x-i（累加贡献）。
这类似一种对排列的判定/计数算法——右侧指针指向的值与 y+x-i 比较，匹配则计数
重置双指针和 y（r=n, l=1, y=0），但不重置 ans（继续用第一段算出的 ans）。
循环逻辑与第一段完全相同，但在命中 else if (y+x-i == s[r]) 时额外输出一组编号：for (j = i+1; j <= x; j++) cout << i << ' ' << j << '\n';——输出所有形如 (i, j) 的对，其中 j 从 i+1 到 x。
然后 y++, ans += x-i 与第一段一致（但此时 ans 已无实际输出作用，只是在累计，最终未再输出 ans——注意第二段末尾没有再 cout ans）。
最终 return 0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1024;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int s[N];
int main() {
    fast;
    int n = rd(), ans = 0;
    for (int i = 1; i <= n; i++) s[i] = rd();
    int x = s[n] + 1, r = n, l = 1, y = 0;
    for (int i = 1; i < x; i++) {
        if (s[l] <= y) l++, r--;
        else if (y+x-i == s[r]) y++, ans += x-i;
    }
    cout << ans << '\n';
    r = n, l = 1, y = 0;
    for (int i = 1; i < x; i++) {
        if (s[l] <= y) l++, r--;
        else if (y+x-i == s[r]) {
            for (int j = i+1; j <= x; j++) cout << i << ' ' << j << '\n';
            y++;
            ans += x-i;
        }
    }
    return 0;
}