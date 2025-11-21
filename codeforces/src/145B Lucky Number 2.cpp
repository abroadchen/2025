//
// Created by Psy.C on 2025/11/21.
//
/*
 *a(4的个数), b(7的个数), c("47"子串个数), d("74"子串个数)
 *"47"和"74"的个数最多只能相差1，因为它们交替出现
 *调整a和b，减去已经在"47"模式中使用的4和7的个数
 */
#include <cstdio>
using namespace std;

int main() {
    int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
    if (c > d + 1 || d > c + 1) { puts("-1"); return 0; }
    a -= c, b -= c;
    bool l(0), r(0);//是否需要在开头和结尾添加额外的数字
    if (c == d) {
        if (a > 0) { --a; r = 1; }//使用一个额外的4 标记需要在右侧添加4
        else { l = 1; --b; }
    } else if (d > c) { --a; --b; l = 1; r = 1; }//需要额外的一个4和一个7
    if (a < 0 || b < 0) { puts("-1"); return 0; }//检查调整后的a和b是否为非负数

    if (l) printf("7");//如果需要在左侧添加7，则先打印7
    while (a--) printf("4");//打印剩余的4
    while (c--) printf("47");//打印c个"47"模式
    while (b--) printf("7");//打印剩余的7
    if (r) printf("4");//如果需要在右侧添加4，则最后打印4
    puts("");//换行
    return 0;
}