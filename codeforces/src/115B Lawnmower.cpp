//
// Created by Psy.C on 2025/11/15.
//
/*
*定义常量N=151，表示最大行宽
声明全局变量n（行数）、m（列数）
声明字符数组line用于存储每一行的输入
*x(0)：当前所在的列位置（初始为0）
y(-1)：当前所在的行位置（初始为-1，表示尚未开始）
res(0)：总步数计数器
 *
 *left和right用于记录当前行中'W'的最左和最右位置
*遍历当前行的每一列（从0到m-1）：
如果当前位置是'W'（白色格子）：
更新left为当前列位置和left的较小值
更新right为当前列位置和right的较大值
这样就找到了当前行中所有'W'的最左位置left和最右位置right
 *
 *如果left仍然是N，说明当前行没有'W'，跳过这一行
*如果是偶数行（从0开始计数）：
从左到右扫描
*如果当前行的最左'W'位置在当前位置的左边：
需要向左移动，增加移动步数
更新当前位置x为left
 *
*如果是奇数行：
从右到左扫描
*如果当前行的最右'W'位置在当前位置的右边：
需要向右移动，增加移动步数
更新当前位置x为right
 *
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 151;
int n, m;
char line[N];

int main() {
    scanf("%d %d", &n, &m);
    int x(0), y(-1), res(0);
    for (int i = 0, left, right; i < n; ++i) {
        scanf("%s", line);
        left = N, right = -1;
        for (int j = 0; j < m; ++j) {
            if (line[j] == 'W') {
                left = min(left, j);
                right = max(right, j);
            }
        }
        if (left == N) continue;
        if (i % 2 == 0) {
            if (left < x) { res += x - left; x = left; }
            res += i - y;//从上一行移动到当前行，增加垂直移动步数
            res += right - x;//从当前位置移动到当前行最右的'W'位置，增加水平移动步数
            x = right;//更新当前位置为当前行最右的'W'位置
            y = i;//更新当前行位置
        } else {
            if (right > x) { res += right - x; x = right; }
            res += i - y;
            res += x - left;//从当前位置移动到当前行最左的'W'位置，增加水平移动步数
            x = left;//更新当前位置为当前行最左的'W'位置
            y = i;//更新当前行位置
        }
    }
    printf("%d\n", max(0, res - 1));
    return 0;
}