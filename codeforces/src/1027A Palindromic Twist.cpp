//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
c[0], c[1]：字符 a 可以变换成的两个候选：a-1（前驱）和 a+1（后继）。若越界（a='a' 则 a-1 不存在，a='z' 则 a+1 不存在），设为 0（表示"无此选项"）。
d[0], d[1]：同理，字符 b 的两个可变换候选。
双重遍历：对 a 的每个候选 c[cnt]，检查 b 的每个候选 d[i] 是否相等（都非 0 且相同）。
只要找到一组相等 → return 1（可配平）。
本质：check(a,b) 返回 a、b 经过各自"移一步"后能否变成同一个字母。

注意：这个 check 没有比较 a 自身和 b 自身，只比较它们变换后的选项。也就是说——它判断的是"端点都能往相邻字母各动一格，能否落在同一个字符上"
读入多组测试。
对每一组，检查对称的每一对 (s[i], s[n-1-i])。
只要有一对 check 返回 false → flg=1 → 输出 NO。
全部配平则输出 YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

bool check(char a, char b) {
    char c[2], d[2];
    c[0] = a-1 >= 'a' ? a-1 : 0;
    c[1] = a+1 <= 'z' ? a+1 : 0;
    d[0] = b-1 >= 'a' ? b-1 : 0;
    d[1] = b+1 <= 'z' ? b+1 : 0;
    int cnt = 0;
    while (cnt < 2) {
        for (char i : d) if (c[cnt] && i && c[cnt] == i) return 1;
        cnt++;
    }
    return 0;
}

int main() {
    fast;
    int t; cin >> t;
    while (t--) {
        int n; string s; cin >> n >> s;
        bool flg = 0;
        for (int i = 0; i < n/2; i++) {
            if (check(s[i], s[n-i-1])) {}
            else flg = 1;
        }
        if (flg) cout << "NO\n"; else cout << "YES\n";
    }
    return 0;
}