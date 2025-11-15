//
// Created by Psy.C on 2025/11/15.
//
/*
*a[N]：整型数组，用于存储索引
c[N + 1]：字符数组，用于存储字符串（多1个位置用于字符串结束符）
 *
*当前字符串编号（i+1）
第一个位置编号（a[j-1]+1）
第二个位置编号（a[j]+1）
 *
*这实际上是插入排序的变形：
将当前索引i插入到数组a的正确位置
插入规则：按照字符串中对应位置字符是否为'1'来决定位置
 *
 *
 */
#include <iostream>
using namespace std;

const int N = 5000;
static int a[N];
static char c[N + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, i, j, cnt(0); cin >> n;
    for (i = 0; i < n; ++i) {
        cin >> c;//每次读入一个字符串
        for (j = 1; j < cnt; ++j) {
            if (c[a[j - 1]] == '1' && c[a[j]] == '0') {
                cout << i + 1 << " " << a[j - 1] + 1 <<
                    " " << a[j] + 1 << "\n";
                return 0;
            }
        }
        cnt++;
        for (j = cnt - 1; j > 0 && c[a[j - 1]] == '1'; --j)
            a[j] = a[j - 1];//将前面的元素向后移动
        a[j] = i;
    }
    cout << -1 << '\n';
    return 0;
}