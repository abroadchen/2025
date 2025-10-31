//
// Created by Psy.C on 2025/10/31.
//
/*
// s: 用于读取输入字符串的大数组
// n: 序列长度
// cnt, tot: 分别计数两个序列中读取的数字个数
// p: 临时变量，用于数字解析
// le: 字符串长度
// i: 循环变量
// a[N], b[N], t[N]: 三个辅助数组
// m: LIS长度计数器
// l, r, mid: 二分查找使用的变量

读取两行输入（第一次gets读取换行符，第二次读取实际数据）

解析第一行的数字序列，存储到数组a中
如果当前字符不是数字字符（即分隔符或字符串结束）
将累积的数字p存入a[cnt]，重置p
继续累积数字

重置变量，解析第二行的数字序列，存储到数组b中

构造置换映射：t[a[i]] = i 表示原位置a[i]现在应该放在位置i
重新排列数组a：根据置换映射调整数组a

// 使用二分查找优化的LIS算法求最长上升子序列
// 初始化：m表示当前LIS长度，b数组用于维护单调序列

从倒数第二个元素开始向前处理
b数组末尾放置一个极大值作为哨兵
分查找确定a[i]应该插入的位置
如果插入位置超出了当前长度，说明找到了更大的LIS
将a[i]放到找到的位置上
输出最长上升子序列的长度

时间复杂度：O(n log n)
空间复杂度：O(n)
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1001111;
char s[N*8];
int n, cnt(0), tot(0), p(0), le, i,
a[N], b[N], t[N], m,
l, r, mid;

int main() {
    scanf("%d", &n);
    gets(s); gets(s);
    le = strlen(s) + 1;
    for (i = 0; i < le; ++i) {
        if (s[i] < '0') a[++cnt] = p, p = 0;
        else p = p * 10 + (s[i] - '0');
    }
    gets(s);
    p = 0, le = strlen(s) + 1;
    for (i = 0; i < le; ++i) {
        if (s[i] < '0') b[++tot] = p, p = 0;
        else p = p * 10 + (s[i] - '0');
    }
    for (i = 1; i <= n; ++i) t[a[i]] = i;
    for (i = 1; i <= n; ++i) a[i] = t[b[i]];
    b[m=1] = a[n];//从最后一个元素开始
    for (i = n - 1; i >= 1; --i) {
        b[m + 1] = 0x3fffffff;
        l = 1, r = m + 1;
        while (l < r) {
            mid = (l + r) >> 1;
            if (a[i] < b[mid]) r = mid;
            else l = mid + 1;
        }
        if (l > m) ++m;
        b[l] = a[i];
    }
    printf("%d\n", m);
    return 0;
}