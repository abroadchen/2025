//
// Created by Psy.C on 2026/2/2.
//
/**
* 时间复杂度：O(n)，其中n为字符串长度
空间复杂度：O(1)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 30
using namespace std;


int main() {
    fast;
    char s1[N], s2[N]; cin >> s1 >> s2;
    int sum = 0;
    for (int i = 0; i < strlen(s1); i += 2) {//只处理偶数位置
        switch (s1[i]) {
            case '8': {
                if (s2[i] == '[') sum++;//s1胜
                if (s2[i] == '(') sum--;//s2胜 s2得分
                break;
            }
            case '[': {
                if (s2[i] == '8') sum--;//s2胜
                if (s2[i] == '(') sum++;//s1胜
                break;
            }
            case '(': {
                if (s2[i] == '8') sum++;//s1胜
                if (s2[i] == '[') sum--;//s2胜
            }
            default: ;
        }
    }
    if (sum > 0) cout << "TEAM 1 WINS\n";
    else if (sum < 0) cout << "TEAM 2 WINS\n";
    else cout << "TIE\n";
    return 0;
}