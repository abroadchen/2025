//
// Created by Psy.C on 2025/10/10.
//
/*
 *s 存储输入的6个字符串，t 用于构建当前可能的解，ans 保存最优解
 *
*l1 + l3 - 1 == l2 和 l4 + l6 - 1 == l5 检查水平和垂直边长是否匹配
后续条件检查相邻字符串在连接点上的字符是否一致（确保边角连接正确）
 *
*将向量s调整为7个元素（索引0不使用）
读入6个字符串（存储在索引1-6）
对这6个字符串进行排序，为后续全排列做准备
*遍历所有可能的字符串排列组合
计算每个字符串的长度
调用check函数验证当前排列是否能构成合法图案
 *
*创建一个l5行l2列的矩阵，初始化为'.'
第一行填充第一个字符串
第l4行填充第二个字符串
最后一行从l1-1列开始填充第三个字符串
左边一列填充第四个字符串
右边一列从l4-1行开始填充第六个字符串
 *
*如果是第一个合法解，则保存为答案
否则比较字典序，保存较小的解
 *
 */
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> s, t, ans;

bool check(int l1, int l2, int l3, int l4, int l5, int l6) {
    return l1 + l3 - 1 == l2 && l4 + l6 - 1 == l5 &&
            s[1][0] == s[4][0] && s[4][l4 - 1] == s[2][0] &&
                s[5][l5 - 1] == s[3][0] &&
                s[5][0] == s[1][l1 - 1] &&
                    s[2][l1 - 1] == s[5][l4 - 1] &&
                    s[6][0] == s[2][l2 - 1] && s[6][l6 - 1] == s[3][l3 - 1];
}

int main() {

    int i, j; bool flag(false);
    s.resize(7);
    for (i = 1; i <= 6; ++i) cin >> s[i];
    sort(s.begin() + 1, s.begin() + 7);

    do {
        int l1 = (int)s[1].size(), l2 = (int)s[2].size(), l3 = (int)s[3].size(), l4 = (int)s[4].size(), l5 = (int)s[5].size(), l6 = (int)s[6].size();
        if (check(l1, l2, l3, l4, l5, l6)) {
            t = vector<string>(l5, string(l2, '.'));
            for (i = 0; i < l5; ++i) {
                if (!i) for (j = 0; j < l1; ++j) t[i][j] = s[1][j];
                if (i == l4 - 1) for (j = 0; j < l2; ++j) t[i][j] = s[2][j];
                if (i == l5 - 1) for (j = l1 - 1; j < l2; ++j) t[i][j] = s[3][j - l1 + 1];
                t[i][l1 - 1] = s[5][i];
                if (i < l4) t[i][0] = s[4][i];
                if (i >= l4) t[i][l2 - 1] = s[6][i - l4 + 1];
            }
            if (!flag) ans = t, flag = true;
            else if (ans > t) ans = t;
        }
    } while (next_permutation(s.begin() + 1, s.begin() + 7));

    if (!flag) printf("Impossible\n");
    else {
        for (i = 0; i < (int)ans.size(); ++i) {
            for (j = 0; j < (int)ans[i].size(); ++j)
                printf("%c", ans[i][j]);
            putchar(10);
        }
    }

    return 0;
}