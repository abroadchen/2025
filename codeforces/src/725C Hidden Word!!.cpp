//
// Created by Psy.C on 2026/4/24.
//
/**
str[30]: 存储输入的27个字符
ans[2][13]: 结果矩阵，2行13列
mark[27]: 标记数组，记录每个字符首次出现的位置
遍历字符串，记录每个字符第一次出现的位置
找到第一个重复的字符
temp: 重复字符第一次出现的位置
dis: 两个相同字符之间的距离
如果两个相同字符相邻（距离为1），则无解

时间复杂度: O(1) - 固定的27个字符
空间复杂度: O(1) - 固定大小的数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char str[30], ans[2][13];
int mark[27];
int main() {
    fast;
    int i,j,dis,temp,step;
    while(cin>>str){
        memset(mark,-1,sizeof(mark));
        int flag=0;
        for(i=0;i<27;++i) {
            if(mark[str[i]-'A']==-1) mark[str[i]-'A']=i;
            else {
                temp=mark[str[i]-'A'];//重复字符第一次出现的位置
                dis=i-mark[str[i]-'A'];//两个相同字符之间的距离
                if(dis==1) flag=1;
                break;
            }
        }
        if(flag) cout<<"Impossible"<<endl;
        else {
            if(dis&1) dis++; //如果距离是奇数，加1变成偶数
            i=dis/2; //半距离
            i=13-i; //起始位置
            ans[0][i++]=str[temp];//在第0行放置重复字符
            step=temp;//设置步进计数器

            //填充第0行右侧
            while(i<13) {
                ans[0][i]=str[++step];//从重复字符位置开始填充
                i++;
            }
            //填充第1行左侧（直到重复字符）
            i=12;
            while(i>=0&&step<26) {
                if(str[++step]!=str[temp]) {//跳过重复字符
                    ans[1][i]=str[step];
                    i--;
                }
            }
            flag=1;
            if(step==26) { step=0; flag=0; }
            while(i>=0) {//如果还有字符未处理，继续填充第1行
                ans[1][i]=str[step];
                i--;
                step++;
            }
            i=0;
            while(step<26&&flag) {//填充第0行的左侧部分
                ans[0][i]=str[++step];
                i++;
            }
            if(step==26) step=0;
            while(step<temp){
                ans[0][i]=str[step];
                step++;
                i++;
            }
            for(i=0;i<2;++i) {
                for(j=0;j<13;++j)
                    printf("%c",ans[i][j]);
                printf("\n");
            }
        }
    }
    return 0;
}