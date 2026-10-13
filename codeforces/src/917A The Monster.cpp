//
// Created by Psy.C on 2026/10/13.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

string s;
int cnt, flg, ans;
int main() {
    fast;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; ++i) {//外层循环：i 表示每个可能的"起点"
        cnt = 0, flg = 0;//每换一个起点，清空计数
        for (int j = i; j < n; ++j) {//内层循环：j 表示当前"终点"，枚举所有从 i 开头的子串
            if (s[j] == '(') cnt++;//左括号计数 +1
            if (s[j] == ')') cnt--;
            if (s[j] == '?') {
                if (cnt > 0) cnt--, flg++;//优先当右括号：若当前左括号"够用"，就把 cnt-1 并记录用掉一个 flg
                else cnt++;//否则当左括号：cnt+1
            }
            if (cnt == 0) ans++;//若净剩为 0，说明从 i 到 j 是个"合法括号前缀"，答案 +1
            else if (cnt < 0) {//若净剩为负数，说明右括号多了
                //若还有可挽救的 '?'(flg>0)，把之前当右括号的 '?' 改判为左括号：cnt+2 并消耗一个 flg
                if (flg) { cnt += 2; flg--; }
                else break;//否则无法挽救，以 i 为起点的子串到此为止，跳出内层
            }
        }
    }
    cout << ans;
    return 0;
}