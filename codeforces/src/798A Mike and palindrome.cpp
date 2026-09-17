//
// Created by Psy.C on 2026/9/17.
//
/**
遍历 i 从 0 到 len/2 - 1（只检查前半部分）。
s[len-1-i] 是 s[i] 的对称位置。
若 s[i] != s[len-1-i]，说明这一对不匹配，cnt++。
最终 cnt = 整个字符串中不对称的字符对数。
cnt == 0（已是回文）且 len 为奇数 → YES

字符串本身已经是回文。
当长度为奇数时，中间的字符可以随意改动而不会破坏回文性（因为中间字符没有对称伙伴）。
所以即使是完美回文，奇数长度下也完全可以"改动中间那个字符"来满足"恰好改动一次"或"改动一个"的要求 → 输出 YES。
cnt == 1（恰好一对不对称）‍ → YES

只有一对对称字符不匹配，改动其中一个字符即可让整串成回文 → 输出 YES。
其余情况 → NO

包括：cnt == 0 且 len 为偶数（已经是回文，但偶数长度没有可单独改动的"中心"字符，改动任何一个都会破坏回文 → 无法满足恰好改动一个 → NO）。
以及 cnt >= 2（需要改动的对超过 1，做不到）→ NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char s[20];
int main() {
    fast;
    cin >> s;
    int len = strlen(s), cnt = 0;//对称位置不匹配的对数
    for (int i = 0; i < len/2; ++i)
        if (s[i] != s[len-1-i]) cnt++;
    if (!cnt && len%2) cout << "YES\n";
    else if (cnt == 1) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}