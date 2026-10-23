//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
n：字符串长度。
s+1：让字符串从下标 1 开始存储（方便前后加哨兵）。
读入 n 和字符串 s
在字符串最前面和最后面各补一个 '0' 作为哨兵（边界虚拟字符）。
这样在遍历判断时，i=1 和 i=n 处的判断也能统一处理，不必单独处理边界情况。
逐个字符 s[i] 检查，一旦发现下面任一种"非法情况"就标记 flg=false 并跳出：

条件 A（三个连续 0）
即出现"连续三个及以上的 0"（000）——非法
条件 B（两个连续 1）
即出现"连续两个及以上的 1"（11）——非法
全程没发现非法情况 → Yes；否则 → No
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e3+5;

int n;
char s[N];
int main() {
    fast;
    scanf("%d%s", &n, s+1);
    bool flg = true;
    s[0] = '0'; s[n+1] = '0';
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == '0' && s[i] == '0' && s[i+1] == '0' ||
            s[i] == '1' && s[i+1] == '1') {
            flg = false; break;
        }
    }
    if (flg) cout << "Yes\n"; else cout << "No\n";
    return 0;
}