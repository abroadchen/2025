//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
flg：标志，表示当前是否处于"需要消除"状态。
num：操作计数
当第 i 列上下两个字符都是 '0'（即 s[i]==s2[i]=='0'）时，置 flg=true，表示这一列需要"消除"
若 flg 为真（需要消除第 i 列）‍：

a) 尝试借助左邻居消（i>0）‍
若左邻列（i-1）的任意一行是 '0'，则可以一次操作把第 i 列消掉（并把左右用 'x' 标记），num++，flg=false。
b) 尝试借助右邻居消（i < len-1）
若右邻列（i+1）的上行或下行是 '0'，也可以配对消除，num++。
（注意两个 if 都检查 flg，第一个 if 若成功会置 flg=false，第二个 if 就不执行了。）
无论消没消成功，重置 flg（这个列处理完，不管）
输出本轮的最小操作数 num
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; i++)
#define ll long long
using namespace std;

string s, s2;
int main() {
    fast;
    while(cin>>s>>s2) {
        bool flg = false; ll num = 0;
        rep(i,s.length()) {
            if (s[i] == s2[i] && s[i] == '0') flg = true;
            if (flg) {
                if (i > 0) {
                    if (s[i-1] == '0' || s2[i-1] == '0') {
                        s[i] = 'x', s2[i] = 'x'; num++, flg = false;
                    }
                }
                if (i < s.length() - 1) {
                    if (s[i+1] == '0' && flg) {
                        s[i] = 'x', s2[i] = 'x'; s[i+1] = 'x';
                        num++, flg = false;
                    }
                    if (s2[i+1] == '0' && flg) {
                        s[i] = 'x', s2[i] = 'x', s2[i+1] = 'x', num++;
                    }
                }
                flg = false;
            }
        }
        cout << num << '\n';
    }
    return 0;
}