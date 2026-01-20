//
// Created by Psy.C on 2026/1/19.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        if (i + 3 < s.size()) {//至少还有4个字符
            if (s[i] == s[i + 1]) {//当前位置和下一个位置字符相同
                if (s[i + 2] == s[i + 3]) {//后面两个字符也相同
                    s.erase(s.begin() + i + 2);//删除位置i+2的字符
                    i--;//回退一步重新检查（因为删除字符后可能影响后续判断）
                } else if (s[i + 1] == s[i + 2]) {
                    s.erase(s.begin() + i + 1);
                    i--;
                }
            }
        } else if (i + 2 < s.size()) {//是否有3个字符
            if (s[i] == s[i + 1] && s[i + 1] == s[i + 2])//连续3个字符相同
                s.erase(s.begin() +  i);
        }
    }
    cout << s;
    return 0;
}