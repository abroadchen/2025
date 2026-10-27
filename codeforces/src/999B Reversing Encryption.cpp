//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
遍历 i 从 2 到 n。
若 i 能整除 n（n % i == 0），就把 s 的 [0, i) 这段前 i 个字符原地翻转（reverse 左闭右开，next(s.begin(), i) 指向 s[i]，所以翻转的是前 i 个字符）。
注意翻转是累积的：后面的翻转作用在已经多次翻转过的字符串上。
最后输出处理后的 s
i 从 2 开始是因为 i=1 时 n%1==0 恒成立，会无条件翻转前 1 个字符（翻转 1 个字符等于没变），跳过可省一次空操作
前缀翻转的累加：按升序遍历 n 的所有因子 i（≥2），每次把当前字符串的前 i 个字符反转，多次反转累积作用在同一字符串上，最后输出结果。复杂度 O(n²)（最多 n 次 × 每次 O(n) 的 reverse）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
string s;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 2; i <= n; i++)
        if (n%i == 0) reverse(s.begin(), next(s.begin(), i)) ;
    cout << s << '\n';
    return 0;
}