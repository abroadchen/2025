//
// Created by Psy.C on 2026/1/23.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAX 5007

using namespace std;

int n,m;
int dp[MAX][MAX];//每个位置向上连续'1'的高度
char mp[MAX][MAX];//输入的二进制矩阵

int main ()
{
    while ( ~scanf ( "%d%d" , &n , &m ))
    {
        for ( int i = 1 ; i<= n ; i++ )
            scanf ( "%s" , mp[i]+1 );
        for ( int i= 1 ; i <= n ; i++ )
            for ( int j = 1 ; j <= m ; j++ )
                if ( mp[i][j] == '1' )
                    dp[j][i] = dp[j-1][i]+1;//当前位置高度 = 上一行同一列的高度 + 1
                else dp[j][i] = 0;
        int ans = 0;
        for ( int i = 1 ; i <= m ; i++ )//遍历每一列
        {
            sort ( dp[i]+1 , dp[i]+n+1 );//对第i列的所有高度值进行升序排序
            for ( int j = n ; j > 0 ; j-- )//从最大的高度开始向下降序遍历
                ans = max ( ans , dp[i][j]*(n-j+1) ); //当前考虑的高度*以当前高度为最小高度时能形成的宽度
        }
        printf ( "%d\n" , ans );
    }
}