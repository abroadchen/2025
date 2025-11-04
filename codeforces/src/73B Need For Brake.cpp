//
// Created by Psy.C on 2025/11/3.
//
/*
*n：学生总数
a[N]：存储原始成绩的数组
m：奖励点数个数
b[N]：存储奖励点数的数组（会乘以2）
idx：目标学生的索引（初始为-1）
sum：临时求和变量
cnt：计数器变量
ret：字符串比较返回值
c[N]：存储其他学生修改后成绩的数组
 *
*name[N][M]：二维数组存储学生姓名
str[M]：数组存储目标学生姓名
 *
 *循环读取每个学生的姓名和成绩，分别存入name[i]和a[i]
 *读取奖励点数值，并将每个值乘以2（可能是为了处理平局情况）
 *将剩余位置的奖励值初始化为0（对于没有获得奖励的学生）
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1e5+10, M = 30;
int n, a[N], m, b[N], idx(-1),
sum, cnt, ret, c[N];
char name[N][M], str[M];

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) scanf("%s %d",name[i], a + i);
    scanf("%d",&m);
    for (int i = 0; i < m; ++i) scanf("%d", b + i), b[i] *= 2;
    for (int i = m; i < n; ++i) b[i] = 0;
    sort(b, b + n);
    scanf("%s",str); m = 0;
    for (int i = 0; i < n; ++i) {
        ret = strcmp(name[i], str);//比较当前学生姓名与目标学生姓名
        if (ret == 0) idx = i;//如果是目标学生，记录其索引
        else {
            c[m] = a[i];//将其成绩复制到数组c中
            if (ret < 0) c[m] = c[m] * 2 + 1;//如果姓名字典序更小，则成绩乘以2再加1，否则只乘以2
            else c[m] = c[m] * 2;
            ++m;//增加其他学生计数器
        }
    }
    sort(c, c + m);
    sum = a[idx] * 2 + b[m]; cnt = 0;//计算目标学生的最好可能成绩（成绩*2 + 最好奖励），初始化计数器
    for (int i = 0, j = m - 1; i < m && j >= 0; ++i, --j) {//有多少学生能超过目标学生
        for (; j >= 0 && c[i] + b[j] > sum; --j);//跳过那些成绩加奖励超过目标学生最好成绩的学生
        if (j >= 0) cnt++;//如果还有有效学生，增加计数器
    }
    printf("%d", n - cnt);//输出目标学生的最差排名（总学生数减去能超过他们的人数）
    sum = a[idx] * 2 + b[0];//计算目标学生的最差可能成绩（成绩*2 + 最差奖励）
    for (int i = 0; i < m; ++i) b[i] = b[i + 1]; cnt = 0;//移动奖励数组，去掉第一个元素（最差奖励）
    for (int i = m - 1, j = 0; i >= 0 && j < m; --i, ++j) {//使用最差奖励时仍能超过目标学生的数量
        for (; j < m && c[i] + b[j] <= sum; ++j);//跳过那些成绩加奖励小于等于目标学生最差成绩的学生
        if (j < m) cnt++;//如果还有能超过目标学生的有效学生，增加计数器
    }
    printf(" %d\n", cnt + 1);//输出目标学生的最好排名（能超过他们的人数+1）
    return 0;
}