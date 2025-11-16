//
// Created by Psy.C on 2025/11/16.
//
/*
 *
*循环条件：~fscanf(p,"%d",&n)
fscanf返回读取成功的项目数（1表示成功，EOF表示失败）
~EOF = -1（非零，条件为真），~1 = -2（非零，条件为真）
实际上这是不安全的写法，应该用fscanf(...) == 1
循环体：t++&&fprintf(q,"%d ",~n&1)
t++：计数器递增
&&：逻辑与，只有t非零时才执行fprintf
~n&1：对n按位取反后与1进行按位与运算
 *
 *
 *
 */
#include <cstdio>
using namespace std;

int main() {
    FILE *p, *q;
    int t = 0, n;
    p = fopen("input.txt", "r");
    for (q = fopen("output.txt", "w");
        ~fscanf(p, "%d", &n); t++ && fprintf(q, "%d ", ~n & 1));
    fclose(p);
    fclose(q);
    return 0;
}