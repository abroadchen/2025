//
// Created by Psy.C on 2026/1/23.
//

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1000010,M = 10;
char s[N];
int len,tmp[M] = {1869,1968,1689,6198,1698,1986,1896},cnt[M];
void solve()
{
    //移除数字6、1、8、9各一个，为后面插入特定四位数预留空间
    cnt[6]--,cnt[1]--,cnt[8]--,cnt[9]--;
    int r = 0,pos = 0;//当前余数 结果字符串位置指针
    for(int i=1;i<10;i++)
        while(cnt[i])//只要还有这个数字可用
        {
            r = (r*10+i)%7;//更新当前余数
            s[++pos] = i+'0';//将数字i添加到结果字符串
            cnt[i]--;//对应计数减1
        }
    r=r*10000%7;//将当前余数扩展4位(乘以10000)，为后续插入4位数做准备
    int t = tmp[(7-r)%7],p = 1000;//根据当前余数选择合适的四位数，p用于逐位提取数字
    while(p)//提取并添加四位数的每一位
    {
        char c = t/p+'0';//获取当前最高位数字
        s[++pos] = c;//添加到结果字符串
        t%=p;//去掉最高位
        p/=10;//缩小p，处理下一位
    }
    while(cnt[0])//添加所有剩余的0
    {
        s[++pos] = '0';//将0添加到结果末尾
        cnt[0]--;//计数减1
    }
    printf("%s\n",s+1);
}
int main()
{
    scanf("%s",s+1);
    len = strlen(s+1);
    for(int i=1;i<=len;i++)//遍历输入字符串的每一位
        cnt[s[i]-'0']++;//统计每个数字的出现次数
    solve();
    return 0;
}