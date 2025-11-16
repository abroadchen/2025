//
// Created by Psy.C on 2025/11/16.
//
/*
*%*s: 读取一个字符串但不存储（*表示忽略）
%n: 记录到目前为止读取的字符数量，存储到变量a中
%d: 读取一个整数，存储到变量b中
 *
*a + b & 1: 计算a+b的值，并检查最低位（判断奇偶性）
? 82 : 76: 三元运算符：
如果a+b是奇数（a+b&1为真），选择82
如果a+b是偶数（a+b&1为假），选择76
82是字符'R'的ASCII码，76是字符'L'的ASCII码
fputc(...): 将选定的字符写入文件
fopen("output.txt", "w"): 打开"output.txt"文件用于写入
!: 逻辑非运算，将fputc的返回值取反（用于赋值给z）
 */
#include <cstdio>
using namespace std;

int main() {
    int a, b, z;
    fscanf(fopen("input.txt", "r"),
        "%*s%n%d", &a, &b);
    z = !fputc(a + b & 1 ? 82 : 76, fopen("output.txt", "w"));
    return 0;
}