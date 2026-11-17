//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
N = 97，即 ASCII 中小写字母 'a' 的编码
T：测试用例数；n：目标字符串长度；k：要使用的小写字母种类数
cnt：当前要放的字符 ASCII 码，从 97（'a'）开始。
f：本组合法字符的最大 ASCII 码 = 97 + k - 1，即末尾字母（例如 k=3 时 f=99='c'）
循环 n 次，第 i 次：
把当前 cnt 转成字符 char(cnt) 追加到 s 末尾；
cnt++ 指向下一字母；
若 cnt > f（越出了 [a, a+k-1] 范围），就把 cnt 重置回 97（'a'）→ 实现循环
输出构造好的字符串。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 97;

int T, n, k;
int main() {
    fast;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        string s;
        int cnt = N, f = N + k - 1;
        for (int i = 1; i <= n; ++i) {
            s = s + char(cnt);
            cnt++;
            if (cnt > f) cnt = N;
        }
        cout << s << '\n';
    }
    return 0;
}