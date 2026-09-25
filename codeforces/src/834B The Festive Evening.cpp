//
// Created by Psy.C on 2026/9/25.
//
/**
N：串长上限。
M：字符种类上限（ASCII 大写字母，'A' 可到 25，留裕量到 110）。
a[N]：差分数组。
b[M]：记录每个字符的出现次数计数
读入串长 n、阈值 k、字符串 s
对每个位置 i，查字符 s[i] 目前出现次数 b[s[i]-'A']：
若为 0，说明这是该字符第一次出现 → 在差分 a[i]++（在这个位置开始一个"段"）。
然后该字符计数 +1（b[...]++）。
效果：a 中记录了每个字符首次出现的位置 +1 标记
逐个位置递减该字符计数（b[...]--）：
若减完之后计数为 0，说明这是该字符的最后一次出现 → 在差分 a[i+1]--（在这个位置之后结束一个"段"）。
效果：a 中记录每个字符末次出现的后一个位置 −1 标记，标志该字符的"活跃段"结束
从前往后做前缀和 sum += a[i]，即差分还原。
sum 在位置 i 的含义：当前同时"已首次出现但尚未末次出现"的字符数量（即活跃中的字符段数）。
mx 记录这个值的历史最大值——扫描过程中最多同时有多少个字符"处于开放段"
若最大同时活跃字符数 mx 大于 k → YES，否则 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+10, M = 110;
int a[N], b[M], n, k;
string s;
int main() {
    fast;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    cin >> n >> k >> s;
    for (int i = 0; i < n; ++i) {
        if (b[s[i]-'A'] == 0) a[i]++;
        b[s[i]-'A']++;
    }
    for (int i = 0; i < n; ++i) {
        b[s[i]-'A']--;
        if (b[s[i]-'A'] == 0) a[i+1]--;
    }
    int sum = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        mx = max(mx, sum);
    }
    if (mx > k) cout << "YES\n"; else cout << "NO\n";
    return 0;
}