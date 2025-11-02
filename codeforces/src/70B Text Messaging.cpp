//
// Created by Psy.C on 2025/11/2.
//
/*
*n: 每行最大字符数限制
l: 当前行开始位置的索引（left pointer）
r: 当前行结束位置的索引（right pointer）
cnt(0): 计数器，初始化为0，用于统计行数
s: 存储输入文本的字符串
 *
*读取每行最大字符数n
第一个getline读取cin >> n后剩余的换行符
第二个getline读取实际的文本内容
 *
*设置右指针位置为从左指针开始的第n个字符位置
这是理想情况下当前行的结束位置
 *
*当右指针大于左指针时继续循环
从理想的行尾位置向前寻找合适的断句点
*检查当前字符是否为句子结束符号（句号、问号、感叹号）
如果是，则将下一行的起始位置设为当前结束符号后两个字符的位置（跳过空格）
然后跳出内层循环
如果不是，则将右指针向前移动一位继续检查
 *
*如果右指针等于左指针，说明在整行范围内没有找到合适的句子结束符号
这意味着有一个句子的长度超过了n个字符，无法按要求分行
输出"Impossible"并立即退出程序
 *否则成功找到一行的结束位置，行数计数器加1
 *
 */
#include <iostream>
#include <string>
using namespace std;

int n, l, r, cnt(0);
string s;

void solve() {
    cin >> n;
    getline(cin, s);
    getline(cin, s);
    while (l < s.size()) {
        r = l + n - 1;
        while (r > l) {
            if (s[r] == '.' || s[r] == '?' || s[r] == '!') {
                l = r + 2;
                break;
            } else r--;
        }
        if (r == l) cout << "Impossible", exit(0);
        else cnt++;
    }
    cout << cnt;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}