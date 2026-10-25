//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
读入长度 n、周期 p、字符串 s。f 标记是否成功制造出"非周期"
遍历所有位置对 (l, r=l+p)（r 必须在 n 范围内）：

情况1：s[l] != s[r] —— 这一对已经不同，说明串已经不是周期 p：

若 s[l] == '.'：让 s[l] 填成 s[r] 的反字符。('1'-s[r])+'0' 的作用：若 s[r]=='1'，则 '1'-'1'=0，+'0'='0'；若 s[r]=='0'，则 '1'-'0'=1，+'0'='1'。即取反。

否则若 s[r]=='.'：让 s[r] 填成 s[l] 的反字符（同样取反）。

设 f=true 并 break。

注意：只有当其中一个是 . 时才需要填。若两者都是确定数字且不同（如 '0' vs '1'），则无需填任何，直接 f=true 即可（这一对不同就足够了）。
情况2：s[l] == '.'（走到这说明 s[l]==s[r] 且 s[l] 是 '.'，即 s[l]==s[r]=='.'）：

把 s[l]='1'、s[r]='0'，制造出不同。

设 f=true 并 break。

注意这里如果 s[l] 是确定数字且 s[r] 也是确定数字且相等（如都 '0'），则情况1和情况2都不触发，继续找下一对。
若 f 为真（成功制造了非周期）：输出最终串，剩余未填的 . 一律填 '0'（其他位置已保证产生一对不同，其余随便填都不影响"非周期"性质）。
否则输出 "No"（找不到任何制造不同的机会
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2007;

int n, p;
char s[N];
int main() {
    fast;
    cin >> n >> p >> s;
    bool f = false;
    for (int l = 0, r; (r=l+p) < n; l++) {
        if (s[l] != s[r]) {
            if (s[l] == '.') s[l] = ('1'-s[r]) + '0';
            else if (s[r] == '.') s[r] = ('1'-s[l]) + '0';
            f = true; break;
        }
        if (s[l] == '.') { s[l] = '1', s[r] = '0'; f = true; break; }
    }
    if (f) {
        for (int i = 0; i < n; i++) {
            if (s[i] == '.') cout << '0'; else cout << s[i];
        }
        cout << '\n';
    } else cout << "No\n";
    return 0;
}