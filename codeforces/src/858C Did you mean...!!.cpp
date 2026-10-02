//
// Created by Psy.C on 2026/10/1.
//
/**
arr 是元音集合 a,e,i,o,u。
all_of：对 arr 中每一个元素调用 lambda，当所有元素都满足 i != a 时返回 true。
所以 in(a) 返回 true ⟺ 所有元音都不等于 a ⟺ a 不是任何一个元音。
⚠️ 关键：函数名叫 in，作者本意显然是"a 在(元音集合)内"即"a 是元音"。但当前实现返回的是 "a 不是元音"（取反了）。也就是说 in() 实际表达的是"非元音"。这不是语法错误，而是逻辑/命名与意图相悖，会影响主循环判断。

修复建议：若想表达"是元音"，应写 !ranges::all_of(...)，或直接用 arr 反过来判断。这里我按代码实际语义（"a 非元音"）继续解释主循环
读入字符串 s。
ans 初始 = in(s[0])：即第一个字符"非元音"时为 1、是元音时为 0。这就是"当前连续的某种字符长度计数"的初值。
先输出首字符（不加前导空格）
结合 in() 实际语义（"非元音"为 true），逻辑变为：

!in(s[i]) ⟺ s[i] 是元音 → ans = 0（元音处中断非元音计数）。
else ⟺ s[i] 非元音 → ans++：
当 ans >= 3（连续 ≥3 个非元音）‍且s[i], s[i-1], s[i-2] 不全是同一个字母（排除 bbb 这类三连相同）→ 在 s[i] 前插一个空格，重置 ans = 1。
这正是经典的"每三个连续辅音（且不得全同）之间加空格"规则——为了保证单词不会出现连续 3 个不同辅音。举例：字符串中若出现 abc（三个不同非元音）就会在 c 前插空格
循环里每次调 strlen(s)，总体 O(n)，n ≤ 3e3，无压力。
ans 在每次插入后重置为 1（当前这个非元音算作新的第 1 个
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e3+7;
char arr[] = {'a', 'e', 'i', 'o', 'u'};
bool in(char a) {
    return ranges::all_of(arr, [a](const char i) {
        return i != a;
    });
}

char s[N];
int main() {
    fast;
    cin >> s;
    int ans = in(s[0]); cout << s[0];
    for (int i = 1; i < strlen(s); ++i) {
        if (!in(s[i])) ans =  0;
        else {
            ++ans;
            if (ans >= 3 && !(s[i] == s[i-1] && s[i-2] == s[i])) {
                cout << ' '; ans = 1;
            }
        }
        cout << s[i];
    }
    return 0;
}