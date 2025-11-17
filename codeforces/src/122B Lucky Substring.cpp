//
// Created by Psy.C on 2025/11/17.
//
/*
*s：用于读取输入字符
q：用于统计字符'4'的个数
w：用于统计字符'7'的个数
*s=getchar()：从标准输入读取一个字符并赋值给s
~(s=getchar())：对读取的字符按位取反
当getchar()返回EOF(-1)时，~(-1) = 0，循环结束
当getchar()返回其他字符时，结果非0，继续循环
 *
 *'4'（ASCII码52）
 *'7'（ASCII码55）
 */
#include <cstdio>
using namespace std;

char s, q, w;

int main() {
    for (; ~(s=getchar());) s - 52 ? s - 55 ? 0 : w++ : q++;
    puts(q + w ? q >= w ? "4" : "7" : "-1");
    return 0;
}