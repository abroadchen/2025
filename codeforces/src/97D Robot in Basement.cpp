//
// Created by Psy.C on 2025/11/10.
//
/*
*n：网格行数
m：网格列数
k：移动指令数
s[M]：存储移动指令和网格行的字符数组
*a：当前可达位置集合
b：可行走位置集合（非墙位置）
e：目标位置集合
w：墙位置集合
 *
*id = i*m - m + j：将二维坐标(i,j)映射到一维索引
标记各种位置：
'E'：目标位置
'#'：墙位置
非'#'：可行走位置
 *
*(a>>1)&b：
a>>1：所有位置向右移动1位（相当于人物向左移动）
&b：只保留在可行走区域内的位置
(w<<1)&a：
w<<1：墙位置向左移动1位
&a：保留在墙左边且当前可达的位置
两者取或：得到移动后的新可达位置集合
 *
*位运算优化：使用bitset进行并行操作，一次处理多个位置
空间效率：用位集代替传统队列，节省内存
时间效率：位运算比传统BFS更快
 */
#include <bitset>
#include <iostream>
#define rep(j,n) for(int (j)=1;(j)<=(n);++(j))
using namespace std;

const int N = 23000, M = 250000;
int n, m, k;
char s[M];
bitset<N> a, b, e, w;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    rep(i,n) {
        scanf("%s", s + 1);
        rep(j,m) {
            int id = i*m - m + j;
            if (s[j] == 'E') e[id] = 1;
            if (s[j] == '#') w[id] = 1;
            if (s[j] != '#') b[id] = 1;
        }
    }
    a = b;//初始化当前位置为所有可行走位置
    if (a == e) return puts("0"), 0;//如果初始位置就包含目标位置
    scanf("%s", s + 1);//读取移动指令字符串
    rep(i,k) {
        if (s[i] == 'L') a = ((a>>1)&b)|((w<<1)&a);
        if (s[i] == 'R') a = ((a<<1)&b)|((w>>1)&a);
        if (s[i] == 'U') a = ((a>>m)&b)|((w<<m)&a);
        if (s[i] == 'D') a = ((a<<m)&b)|((w>>m)&a);
        if (a == e) { printf("%d\n", i); return 0; }
    }
    puts("-1");
    return 0;
}