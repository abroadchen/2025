//
// Created by Psy.C on 2026/3/24.
//
/**
n: 输入的字母种类数
c: 计数器，用于记录奇数个字符的字母数量
x: 记录唯一奇数个字符的字母位置
a[30]: 存储每个字母的数量（最多30种字母）
如果有奇数个字符的字母，记录其数量c和位置x

有超过1个字母数量为奇数
输出0（不能构成回文串）
将所有字符按顺序输出，形成普通字符串
有1个或0个字母数量为奇数（可构成回文串）
有1个字母数量为奇数
计算所有数量的最大公约数c（回文串的重复周期）
输出最大公约数（可形成的回文串数量）
构造回文串：
前半部分：输出除中心字母外的字符
中间部分：输出中心字母（奇数个的那个）
后半部分：反向输出前半部分
所有字母数量都为偶数
计算最大公约数
输出可形成的回文串数量
构造回文串：前半部分 + 后半部分（镜像）

 */
#include <bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}
int n,c,x,a[30];
int main(){
    scanf("%d",&n);
    int i, j, k;
    for(i = 1; i <= n; i++) scanf("%d",&a[i]);

    for(i = 1; i <= n; i++) {
        if(a[i] & 1) { c++; x = i; }
    }
    if(c > 1){
        printf("0\n");
        for(i = 1; i <= n; i++) {
            while(a[i]) {
                a[i]--;
                printf("%c",'a'-1+i);
            }
        }
    } else {
        if(c == 1) {
            c = a[1];
            for(i = 2; i <= n; i++) c = gcd(c,a[i]);
            printf("%d\n",c);
            for(i = 1; i <= c; i++) {
                for(j = 1; j <= n; j++) {
                    if(j != x){
                        for(k = 1; k <= a[j]/c/2; k++)
                            printf("%c",'a'-1+j);
                    }
                }
                for(j = 1; j <= a[x]/c; j++)
                    printf("%c",'a'-1+x);
                for(j = n; j > 0; j--) {
                    if(j != x) {
                        for(k = 1; k <= a[j]/c/2; k++)
                            printf("%c",'a'-1+j);
                    }
                }
            }
        } else {
            c = a[1];
            for(i = 2; i <= n; i++)
                c = gcd(c,a[i]);
            printf("%d\n",c);
            for(i = 1; i <= c/2; i++) {
                for(j = 1; j <= n; j++) {
                    for(k = 1; k <= a[j]/c; k++)
                        printf("%c",'a'-1+j);
                }
                for(j = n; j > 0; j--) {
                    for(k = 1; k <= a[j]/c; k++)
                        printf("%c",'a'-1+j);
                }
            }
        }
    }
    return 0;
}