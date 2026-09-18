//
// Created by Psy.C on 2026/9/18.
//
/**
先数一下原串里已经有多少个 "VK" 子串。

扫描 s[0..k-2]，若 s[i]=='V' && s[i+1]=='K'，则找到一个 VK，sum++。
用 a[i] = a[i+1] = 1 标记这两个位置已被占用（即这个 VK 已经计数，不能重复用）。
i++：跳过一个位置，避免相邻 VK 重叠冲突（例如 "VVKK" 里 VK 只在位置 1-2，不能与位置 2-3 共享）。
这一步得到原串 VK 数量，并标记哪些位置已被计入
能否通过翻转一个字符，让本来不是 VK 的地方变成一个新的 VK，从而多 1 个。

翻转一个字符后，新产生的 VK 只能是以下两种情况之一才"新增"：

原位置 i 是 'V'、翻 i+1（K→V 或 V→？）后 i+1 变 'K'... 其实更准确地说，翻转一个字符想让 s[i],s[i+1] 变成 VK，需要：
本来 s[i]='V' 且 s[i+1] 不是 'K'（翻成 'K'），或
本来 s[i] 不是 'V'（翻成 'V'）且 s[i+1]='K'。
代码里的判断 if (s[i]=='V' || s[i+1]=='K') 正是筛出这两种"可通过翻转一个字符变成 VK"的候选位置：

s[i]=='V'：翻转 s[i+1] 为 'K'（前提是 s[i+1] 原本不是 K）。
s[i+1]=='K'：翻转 s[i] 为 'V'。
但要注意：这两个条件其实或关系覆盖了更宽的候选，再叠加 a[i]==0 && a[i+1]==0（这两个位置还没被之前的 VK 占用）才算"新增"。

若找到这样的位置，sum++ 并 break（最多只翻一个字符，所以只能加 1 次）
输出原串 VK 数 + （若能翻转新增）1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 105;
int a[N];//标记数组: a[i] = 1 表示位置 i 已被计入某个 VK
char s[N];
int main() {
    fast;
    while (cin >> s) {
        int sum = 0;
        memset(a, 0, sizeof(a));
        int k = strlen(s);
        for (int i = 0; i < k-1; ++i) {
            if (s[i] == 'V' && s[i+1] == 'K') {
                a[i] = a[i+1] = 1;
                sum++;
                i++;
            }
        }
        for (int i = 0; i < k-1; ++i)
            if (s[i] == 'V' || s[i+1] == 'K') {
                if (a[i] == 0 && a[i+1] == 0) {
                    sum++;
                    break;
                }
            }
        cout << sum << '\n';
    }
    return 0;
}