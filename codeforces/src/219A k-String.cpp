//
// Created by Psy.C on 2025/12/8.
//
/*
*k：分组参数
b[26]：长度为26的数组，用于统计每个字母的出现次数（对应a-z）
flag：标志变量，用于标记是否可以重新排列
a[1002]：字符数组，存储输入字符串（预留空间防止溢出）
 *
*a[i] - 'a'将字符转换为0-25的索引（'a'->0, 'b'->1, ..., 'z'->25）
对应位置的计数器加1
 *
*遍历计数数组b
如果任何一个字符的出现次数不能被k整除
设置标志flag为1，输出-1，并跳出循环
这是因为只有当每个字符都能平均分配到k组中时，才能形成有效的排列
 *
*外层循环k次（生成k个相同的部分）
中层循环遍历26个字母（a-z）
计算每个字母在每组中应出现的次数：j = b[i] / k
内层循环输出该字母j次
最后输出换行符
 */
#include <iostream>
using namespace std;


int main() {
    int k, b[26], flag = 0; scanf("%d", &k);
    char a[1002]; scanf("%s",a);
    for (int& i : b) i = 0;
    for (int i = 0; a[i] != '\0'; ++i) b[a[i] - 'a']++;
    for (const int i : b) if (i % k != 0) {
        flag = 1;
        printf("-1\n");
        break;
    }
    if (flag == 0) {
        for (int x = 0; x < k; ++x) for (int i = 0, j; i < 26; ++i) {
            j = b[i] / k;
            for (int t = 0; t < j; ++t) printf("%c", 'a' + i);
        }
        printf("\n");
    }
    return 0;
}