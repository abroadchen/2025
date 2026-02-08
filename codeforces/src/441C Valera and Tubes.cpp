//
// Created by Psy.C on 2026/2/8.
//

#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct grid{int x,y;};
void move(grid &cur){
    if(cur.x%2==1){
        if(cur.y==m)++cur.x;//已在最右列，向下移动一行
        else ++cur.y;//向右移动一列
    }else{
        if(cur.y==1)++cur.x;//已在最左列，向下移动一行
        else --cur.y;//向左移动一列
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    grid a=(grid){1,1};//从(1,1)开始
    for(int i=1;i<k;i++){
        printf("2 ");
        printf("%d %d ",a.x,a.y);move(a);//输出当前位置并移动
        printf("%d %d\n",a.x,a.y);move(a);//输出新位置并移动
    }
    printf("%d ",n*m-2*(k-1));//剩余格子数量
    for(int i=1;i<=n*m-2*(k-1);i++)
        printf("%d %d ",a.x,a.y),move(a);
    return 0;
}