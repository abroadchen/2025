//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
n：字符串长度；s：字符串本身
解方程 1+2+...+f = f(f+1)/2 ≤ n ⇒ f ≤ (-1+√(8n+1))/2。
向下取整即为最大层数 f。
这里因为答案必为整数，直接用 (int) 截断即可（浮点足够精确，8n+1 是安全范围）
对每一层 i（1..f）：
m = i(i+1)/2 是第 i 个三角数，即取到第 i 层时累计消耗的字符数。
输出 s[m-1]（因为字符串下标从 0 起）。
例如 i=1 → 取 s[0]；i=2 → 取 s[2]（c 为 s[0]、s[1]、s[2] 中第 3 个）…… 依此类推，逐层都取该层最后一个字符。
效果：把字符串按 1, 2, 3, ... 分段，每层的最后一位拼成答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int n;
string s;
int main() {
    fast;
    cin >> n >> s;
    int f = (sqrt(8*n+1)-1)/2;
    rep(i,f) {
        int m = i*(i+1)/2;
        cout << s[m-1];
    }
    return 0;
}