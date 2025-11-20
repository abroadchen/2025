//
// Created by Psy.C on 2025/11/20.
//
/*
*循环处理共 4*n 句话。
对每一句：
将其读入字符数组 c 中；
从字符串末尾开始向前遍历每个字符；
统计遇到的元音数量 (t)；
当统计到第 k 个元音时，提取该位置及之后的所有字符组成子串并赋给 s[i]；
若未找到足够的元音，则设置默认标识符（根据索引 %4 转换为数字字符 '0'~'3'）
 *
*每四行为一组进行比较，检查不同押韵模式：
x: 类似 aabb 结构 —— 第一第二句相同，第三第四句也相同；
y: 类似 abab 结构 —— 第一二句分别对应三四句；
z: 类似 abba 结构 —— 第一四句相同，第二三句相同；
 *
*如果所有模式都成立，则输出 "aaaa"（代表完全一致）；
否则依次判断哪一种押韵模式成立并输出对应名称；
如果都不成立，则输出 "NO" 表示没有匹配任何已知押韵格式
 */
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e4+5;
char c[N];
string s[N];
int n, k;
bool x(1), y(1), z(1);//诗歌押韵模式是否符合某种规则


bool v(char g) {
    return g == 'a' || g == 'e' || g == 'i' || g == 'o' || g == 'u';
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= 4 * n; ++i) {
        cin >> c; int t = 0;
        for (int j = strlen(c) - 1; j >= 0; --j) {
            if (v(c[j])) t++;
            if (t == k) { s[i] = string(c+j); break; }
        }
        if (s[i].size() == 0) s[i] = char('0'+i%4);
    }
    for (int i = 1; i <= 4*n; i += 4) {
        x &= s[i] == s[i + 1] && s[i + 2] == s[i + 3];
        y &= s[i] == s[i + 2] && s[i + 1] == s[i + 3];
        z &= s[i] == s[i + 3] && s[i + 2] == s[i + 1];
    }
    if (x && y && z) cout << "aaaa";
    else if (x) cout << "aabb";
    else if (y) cout << "abab";
    else if (z) cout << "abba";
    else cout << "NO";
    return 0;
}