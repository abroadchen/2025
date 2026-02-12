//
// Created by Psy.C on 2026/2/12.
//
/**
n：字符串长度
p：进制数（字符集大小）
i：循环变量
len：当前处理的长度
flag：标记位置
ss[10010]：存储反转后的字符串（数字形式）
s[10010]：原始字符串

ss[1]++：将最低位加1（类似进位）
从低位到高位处理进位
如果ss[i]>=p，进行进位操作
ss[i+1]+=ss[i]/p：向高位进位
ss[i]%=p：当前位取模
如果最高位有进位，说明超过了n位，跳出循环

检查是否存在相邻相同字符
flag记录最后出现相邻相同的索引
检查是否存在相隔一个字符的相同字符（如aba模式）
更新flag为较大的索引
将flag之前的字符都设置为最大值p-1
这样可以避免重复模式
如果flag仍为0，说明没有找到重复模式
输出结果（将数字转回字符，注意顺序）
返回程序结束
 */
#include<bits/stdc++.h>
using namespace std;
int n,p,i,len,flag,ss[10010];
char s[10010];
int main(){
    scanf("%d %d%s",&n,&p,s+1);len=n;
    for (i=1;i<=n;i++) ss[n-i+1]=s[i]-'a';//将字符串s反转存储到ss数组中
    while (len==n){
        ss[1]++;flag=0;
        for (i=1;i<=len;i++) if (ss[i]>=p) ss[i+1]+=ss[i]/p,ss[i]%=p;
        if (ss[len+1]>0) break;
        for (i=1;i<=n-1;i++) if (ss[i]==ss[i+1]) flag=i;
        for (i=1;i<=n-2;i++) if (ss[i]==ss[i+2]) flag=max(flag,i);
        for (i=1;i<flag;i++) ss[i]=p-1;
        if (flag==0){for (i=len;i>=1;i--) printf("%c",ss[i]+'a');return 0;}
    }
    printf("NO\n");
    return 0;
}