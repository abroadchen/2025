//
// Created by Psy.C on 2026/4/25.
//
/**
tot: 当前字符串长度, a1: 整数部分总和, a2: 小数部分总和
s: 输入字符串, p: 输出格式化字符串
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1007;

char a[N];///临时存储单个金额字符串
int tot, a1, a2;
void get() {
    if (a[tot-2] == '.') {//检查是否为小数格式（倒数第三位是小数点）
        a2 += (a[tot-1]-'0')*10+a[tot]-'0';//提取小数点后的两位作为小数部分
        tot -= 3;//减去小数点和两位小数的长度
    }
    if (a2 >= 100) a2 -= 100, a1++;//如果小数部分超过100，进位到整数部分
    int sum = 0;
    for (int i = 1; i <= tot; ++i)//计算整数部分的值
        if (a[i] != '.')
            sum = sum*10 + a[i] - '0';//字符转数字并累加
    a1 += sum;//加到整数总和中
}

char s[N], p[N];
int main() {
    fast;
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i) {
        if ((s[i] < '0' || s[i] > '9') && s[i] != '.') continue;//跳过非数字和非小数点字符
        //前一个字符是分隔符，说明当前字符是一个新数字的开始
        if ((s[i-1] < '0' || s[i-1] > '9') && s[i-1] != '.') {//检查是否为新数字的开始
            get();//处理之前收集的数字
            memset(a, 0, sizeof(a));//清空临时数组
            tot = 0;//重置计数器
        }
        a[++tot] = s[i];//添加当前字符到临时数组
        if (i == len) get();//如果是最后一个字符，处理剩余数据
    }
    int np = 0;
    if (a1 == 0) np = 1, p[1] = '0';//如果整数部分为0，输出"0"
    else {
        int t = 0;
        while (a1 > 0) {//将整数部分转换为字符串格式
            p[++np] = a1%10 + '0'; t++;//取个位数字并转换为字符
            if (t == 3) { p[++np] = '.'; t = 0; }//每三位添加千分位分隔符
            a1 /= 10;//去掉已处理的个位
        }
    }
    if (p[np] != '.') cout << p[np];//输出最高位（如果不是小数点）
    for (int i = np-1; i >= 1; --i) cout << p[i];//倒序输出其余位
    if (a2) printf(".%02d", a2);//输出小数部分（保留两位，不足补0）
    return 0;
}