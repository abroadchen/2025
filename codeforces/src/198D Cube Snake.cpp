//
// Created by Psy.C on 2025/12/3.
//
/*
*o: 方向控制参数
x, y, z: 起始坐标位置
dx, dy, dz: 坐标变化增量
n, m: 控制循环次数的参数
id: 起始填充数字
d: 数字变化增量
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 53
using namespace std;

int a[N][N][N], b[N][N][N];

void f(const int o, int x, int y, int z, int dx, int dy, int dz, const int n, const int m, int id, int d) {
    rep(i,n) rep(j,m) {
        a[x][y][z] = id, id += d;//在当前位置(x,y,z)填入数字id，然后id增加d
        if (j < m) x += dx, y += dy, z += dz;//如果不是内层循环的最后一次，按指定方向移动坐标
        else if (o == 1 || o == -1) x += o, dy *= -1, dz *= -1;//如果是内层循环最后一步且o为±1，改变x坐标方向，并反转y和z的增量方向
        else if (o == 2 || o == -2) y += o / 2, dx *= -1, dz *= -1;
        else z += o / 3, dx *= -1, dy *= -1;
    }
}

void add(const int n) {
    const int m = n * n * n; f(1,1,0,1,0,0,1,n,n,0,-1);//基础填充
    if (n & 1) {//如果n是奇数，进行两次额外的填充操作
        f(-2,0,n,1,0,0,1,n+1,n,m+1,1);
        f(1,0,0,0,0,1,0,n+1,n+1,m+n*(n+1)+1,1);
        rep(i,n+1) rep(j,n+1) rep(k,n+1) {//对已填充的数组a进行坐标变换和数值偏移，结果存储在b中
            b[i][j][k] = a[n-i+1][k-1][n-j+1] + n * n;//i→n-i+1, j→k-1, k→n-j+1，数值加上n²
        }
    } else {
        f(3,0,n,1,0,-1,0,n,n+1,m+1,1);
        f(1,0,n,n+1,0,-1,0,n+1,n+1,m+n*(n+1)+1,1);
        rep(i,n+1) rep(j,n+1) rep(k,n+1) {
            b[i][j][k] = a[n-i+1][k-1][j] + n * n;
        }
    }
    memcpy(a, b, sizeof(b));
}


int main() {
    fast;
    int n; cin >> n, a[1][1][1] = 1;
    rep(i,n-1) add(i);
    rep(i,n) {
        rep(j,n) rep(k,n) {
            cout << a[i][j][k] << (k == n ? '\n' : ' ');
        }
        cout << '\n';
    }
    return 0;
}