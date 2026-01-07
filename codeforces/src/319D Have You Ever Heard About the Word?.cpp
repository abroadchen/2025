#include<bits/stdc++.h>
using namespace std;
char s[50005];
int nxt[50005];
int main(){
    scanf("%s",s+1);//将字符串读入到s[1]开始的位置（跳过s[0]）
    int n=strlen(s+1);
    for (int i=1;i<n;i++) nxt[i]=i+1;//设置链表的下一个节点指针，形成单向链表
    //nxt[1]=2, nxt[2]=3, ..., nxt[n-1]=n
    int len=1;
    while (len*2<=n){ //枚举长度然后暴力缩短
        int p1=1,p2=1;//两个指针，都指向位置1
        for (int i=1;i<=len;i++) //放好指针
            p2=nxt[p2];//将p2向前移动len个位置 p2沿着链表移动到距离p1为len的位置
        int cnt=0,lst=1;//cnt计数连续匹配字符数，lst记录上一个不匹配的位置
        while (p2){//链表未结束
            if (s[p1]==s[p2]) cnt++; else { cnt=0; lst=nxt[p1]; }//更新lst为p1的下一个位置
            if (cnt==len){ //如果已经有连续len个匹配的就删掉
                nxt[p1]=nxt[p2];//将p1的下一个指针指向p2的下一个，相当于跳过了匹配的字符段
                p1=lst; p2=nxt[p2];//重置指针位置
                cnt=0;// 重置计数器
            }else{
                p1=nxt[p1]; p2=nxt[p2];// 两个指针都向前移动一步
            }
        }
        len++;//将匹配长度增加1
    }
    int p=1;//从位置1开始遍历链表
    while (p){
        printf("%c",s[p]);//输出当前位置的字符
        p=nxt[p];// 移动到链表的下一个节点
    }
    return 0;
}
