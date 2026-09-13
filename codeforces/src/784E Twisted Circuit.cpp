//
// Created by Psy.C on 2026/9/13.
//
/**
freopen("1.txt","w",stdout);//输出路径
    cout<<"int a[5][5][5][5];\n";//定义数组
    for(int iIn1=0;iIn1<2;iIn1++)
    for(int iIn2=0;iIn2<2;iIn2++)
    for(int iIn3=0;iIn3<2;iIn3++)
    for(int iIn4=0;iIn4<2;iIn4++)//每个数都从0到1枚举
    cout<<"a["<<iIn1<<"]["<<iIn2<<"]["<<iIn3<<"]["<<iIn4<<"]="<<(((iIn1^iIn2)&(iIn3|iIn4))^((iIn2&iIn3)|(iIn1^iIn4)))<<";\n";

b	c	d	e	输出(a)
0	0	0	0	0
0	0	0	1	1
0	0	1	0	0
0	0	1	1	1
0	1	0	0	0
0	1	0	1	0
0	1	1	0	0
0	1	1	1	0
1	0	0	0	1
1	0	0	1	1
1	0	1	0	0
1	0	1	1	1
1	1	0	0	1
1	1	0	1	0
1	1	1	0	1
1	1	1	1	1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int main() {
    fast;
    int a[5][5][5][5], b, c, d, e;
    a[0][0][0][0]=0;
    a[0][0][0][1]=1;
    a[0][0][1][0]=0;
    a[0][0][1][1]=1;
    a[0][1][0][0]=0;
    a[0][1][0][1]=0;
    a[0][1][1][0]=0;
    a[0][1][1][1]=0;
    a[1][0][0][0]=1;
    a[1][0][0][1]=1;
    a[1][0][1][0]=0;
    a[1][0][1][1]=1;
    a[1][1][0][0]=1;
    a[1][1][0][1]=0;
    a[1][1][1][0]=1;
    a[1][1][1][1]=1;
    cin >> b >> c >> d >> e;
    cout << a[b][c][d][e];
    return 0;
}