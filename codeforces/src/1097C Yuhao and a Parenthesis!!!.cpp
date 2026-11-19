//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
b：整个串扫描完的净盈余（正=左多，负=右多）。
mn：扫描过程中的最低点，判断这个串"前段是否还能撑住"很关键
1) b==0 && mn>=0：净盈余为 0 且过程中从未降到负 → 它自己就是完整合法括号序列。两个这样的"完整体"前后拼接仍然是合法序列（拼接处不掉下去），所以它们两两配 cnt/2。
2) b>0 && mn>=0：左括号偏多，而且过程中最低点没低于 0——说明这个串前面部分不会塌，可以安全放在左边，后面可以接一个"缺这个多出的左括号"的串。归入 l（light：缺右），键为盈余 b。
3) b<0 && mn>=b：右括号偏多。mn>=b 意思是它总盈余就是最低点附近，即"它前面不会有多余的左括号撑不住"…… 其实这里的几何含义是：这个串整体右偏，mn（最低）不低于它的最终值 b，这样的串适合放在右边去"补齐"别人的左盈余。归入 r，键为 −b（即需要补的左括号个数）
已平衡完整体先两两自配：cnt/2。
然后让"左盈余 x"的 l 串 和"缺 x 个左括号"的 r 串配对，取两边较小者为最多能配出的对数：min(l[x], r[x])
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
string s;
unordered_map<int,int> l, r;
int main() {
    fast;
    cin >> n;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int b = 0, mn = 0;
        for (char c : s) {
            if (c == '(') b++; else b--;
            mn = min(mn, b);
        }
        if (b == 0 && mn >= 0) cnt++;
        else if (b > 0 && mn >= 0) l[b]++;
        else if (b < 0 && mn >= b) r[-b]++;
    }
    int ans = cnt/2;
    for (auto [fst, snd] : l) {
        int x = fst, y = snd;
        ans += min(y, r[x]);
    }
    cout << ans << '\n';
    return 0;
}