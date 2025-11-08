//
// Created by Psy.C on 2025/9/26.
//
/*
 *（!(nm)&1表示n*m为偶数）
 *
 *输出0，表示不需要特殊处理
 *如果n是偶数（n&1为0表示n是偶数）
 *输出第一行的所有格子(1,1)到(1,m)
 *输出从(2,m)到(n,m)的右侧边缘
 *输出第n行从右到左的格子(n,m-1)到(n,1)
*对于中间行，按蛇形方式输出：
奇数行从左到右
偶数行从右到左
 *
 *如果n是奇数
 *输出第一列的所有格子(1,1)到(n,1)
 *输出第n行从(2,2)到(n,m)的格子
 *输出从(n-1,m)到(1,m)的右侧边缘
*对于中间列，按蛇形方式输出：
奇数列从上到下
偶数列从下到上
 *
 *如果不满足前面的条件（n或m等于1，或者n*m是奇数）
 *如果总格子数为2
 *输出0
 *按顺序输出所有格子坐标
 *输出1，表示需要特殊处理
 *输出特殊操作：从(n,m)或(n,1)到(1,1)的移动
*按蛇形方式输出所有格子：
奇数行从左到右
偶数行从右到左
 *最后输出起点坐标(1,1)
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;

int n, m;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;

    if (n > 1 && m > 1 && !((n*m)&1)) {
        cout << 0 << "\n";
        if (!(n&1)) {
            for (int j=1;j<=m;++j) cout<<1<<" "<<j<<"\n";
            for (int i=2;i<=n;++i) cout<<i<<" "<<m<<"\n";
            for (int j=m-1;j>=1;--j) cout<<n<<" "<<j<<"\n";
            for (int i=n-1;i>1;--i) {
                for (int j=1;j<m;++j)
                    cout<<i<<" "<<(i&1?j:m-j)<<"\n";
            }
        } else {
            for (int i=1;i<=n;++i) cout<<i<<" "<<1<<"\n";
            for (int j=2;j<=m;++j) cout<<n<<" "<<j<<"\n";
            for (int i=n-1;i>=1;--i) cout<<i<<" "<<m<<"\n";
            for (int j=m-1;j>1;--j) {
                for (int i=1;i<n;++i)
                    cout<<(j&1?i:n-i)<<" "<<j<<"\n";
            }
        }
    } else {
        if (n*m==2) {
            cout<<0<<"\n";
            for (int i=1;i<=n;++i)
                for (int j=1;j<=m;++j)
                    cout<<i<<" "<<j<<"\n";
        } else {
            cout<<1<<"\n";
            cout<<n<<" "<<((n&1)?m:1)<<" 1 1\n";
            for (int i=1;i<=n;++i)
                for (int j=1;j<=m;++j)
                    cout<<i<<" "<<(i&1?j:m-j+1)<<"\n";
        }
    }
    cout<<"1 1\n";

    return 0;
}