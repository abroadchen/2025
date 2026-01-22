//
// Created by Psy.C on 2026/1/22.
//
///O(1)，只进行常数次计算
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define inf 0x3f3f3f3f
using namespace std;

int a, b, s1, s2, ans = inf;
void get(const int x, const int y) {
    if (x%a==0 && y%b==0) {//目标距离x是否能被a整除 目标距离y是否能被b整除
        s1 = x/a, s2 = y/b;//沿a方向需要的步数 沿b方向需要的步数
        if ((s1+s2)&1^1)//当且仅当s1+s2为偶数
            ans = min(ans, max(s1, s2));//可以同时移动x和y方向
    }
}

int main() {
    fast;
    //棋盘大小 起始位置 移动参数
    int n, m, i, j; cin >> n >> m >> i >> j >> a >> b;
    get(i-1, j-1); get(i-1, m-j);// 向左 向上  向左 向下
    get(n-i, j-1); get(n-i, m-j);//向右 向上 向右 向下
    if (ans == inf) cout << "Poor Inna and pony!\n"; else {
        if (ans && (n<=a||m<=b)) cout << "Poor Inna and pony!\n";//无法在棋盘内移动
        else cout << ans << '\n';
    }
    return 0;
}