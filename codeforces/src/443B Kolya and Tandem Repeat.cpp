//
// Created by Psy.C on 2026/2/8.
//
/**
2*j-i: 表示两个子串拼接后的总长度
2*j-i <= len+k: 约束条件，考虑扩展k个字符

验证从位置i开始的子串是否与从位置j开始的子串完全相同
l < j-i: 验证长度为j-i的子串
l+j < len: 确保不越界
 */
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 200 + 10;
char str[maxn];

int main() {
    int k;
    while (scanf("%s%d", str, &k) != EOF) {
        int len = strlen(str);
        if (len <= k) printf("%d\n", (len+k)&1 ? len+k-1: len+k);
        else {
            int ans = 0;
            for (int i = 0; i < len; i++) {//枚举子串起始位置i
                for (int j = i+1; 2*j-i <= len+k; j++) {//枚举第二个子串的起始位置j
                    bool ok = true;
                    for (int l = 0; l < j-i && l+j < len; l++) {
                        if (str[i+l] != str[j+l]) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) continue;
                    ans = max(ans, 2*(j-i));// 两个相同子串的总长度
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}