//
// Created by Psy.C on 2026/9/15.
//
/**
求和。
若总和已能被 3 整除，直接输出原串（答案最长，最优）
res1：尝试删 1 个数字（其数位 mod 3 = 1），剩下去掉该位的串。
res2：尝试删 2 个数字（都是 mod 3 = 2），剩下去掉这两位的串。
注意是从末尾往前找（i = n-1 开始），删掉最靠后/权重最低的位，这样能让结果尽可能大（保留高位）
和上面完全镜像：sum mod 3 = 2 时，删 1 个 mod2 的数，或删 2 个 mod1 的数
get 去掉两者的前导零。
若两个方案都不可行（删不出合法结果）→ 输出 -1。
否则优先选位数更长的那个结果（意味着删的位数更少，更优）。
若位数相同，选字典序更小的（值更小？注意：这里是 min(res1,res2)，等长时取较小的串。
细节：因为已经去前导零，res1/res2 为 "0" 时 empty() 为 false，所以能正常参与比较
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

//去掉字符串开头所有的 0；若全是 0 则结果设为 "0"（长度最短的合法结果，代表数字 0）
void get(string& x) {
    if (x.empty()) return;
    int i = 0;
    while (i < x.size() && x[i] == '0') i++;
    x = x.substr(i);
    if (x.empty()) x = "0";
}

string s;
int main() {
    fast;
    cin >> s;
    int n = s.size(), sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (s[i] - '0');
    }
    if (!(sum % 3)) {
        cout << s << "\n";
        return 0;
    }
    string res1, res2;
    if (sum % 3 == 1) {
        for (int i = n - 1; i >= 0; i--) {
            if ((s[i] - '0') % 3 == 1) {
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        res1 += s[j];
                    }
                }
                break;
            }
        }
        int idx1 = -1, idx2 = -1;
        for (int i = n - 1; i >= 0; i--) {
            if ((s[i] - '0') % 3 == 2) {
                if (idx1 == -1) {
                    idx1 = i;
                } else {
                    idx2 = i;
                    break;
                }
            }
        }
        if (idx2 != -1) {
            for (int j = 0; j < n; j++) {
                if (j != idx1 && j != idx2) {
                    res2 += s[j];
                }
            }
        }
    } else {
        for (int i = n - 1; i >= 0; i--) {
            if ((s[i] - '0') % 3 == 2) {
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        res1 += s[j];
                    }
                }
                break;
            }
        }
        int idx1 = -1, idx2 = -1;
        for (int i = n - 1; i >= 0; i--) {
            if ((s[i] - '0') % 3 == 1) {
                if (idx1 == -1) {
                    idx1 = i;
                } else {
                    idx2 = i;
                    break;
                }
            }
        }
        if (idx2 != -1) {
            for (int j = 0; j < n; j++) {
                if (j != idx1 && j != idx2) {
                    res2 += s[j];
                }
            }
        }
    }
    get(res1); get(res2);
    if (res1.empty() && res2.empty()) {
        printf("-1\n");
    } else if (res1.empty()) {
        cout << res2 << "\n";
    } else if (res2.empty()) {
        cout << res1 << "\n";
    } else {
        if (res1.size() > res2.size()) {
            cout << res1 << "\n";
        } else if (res2.size() > res1.size()) {
            cout << res2 << "\n";
        } else {
            cout << min(res1, res2) << "\n";
        }
    }
    return 0;
}