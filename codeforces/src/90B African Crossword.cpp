//
// Created by Psy.C on 2025/11/9.
//
/*
*r[N][M]：记录每行中每个字母出现的次数
c[N][M]：记录每列中每个字母出现的次数
t[N][N]：存储输入的二维字符矩阵
 *
*声明字符变量x和字符串s
双重循环遍历矩阵的每个位置(i,j)
读取字符x
在对应行的字母计数器中增加该字母的计数
在对应列的字母计数器中增加该字母的计数
将字符存储到二维数组t中
 *
*双重循环再次遍历矩阵的每个位置(i,j)
获取当前位置的字符x
检查条件：该字符在所在行中只出现一次(r[i][x-'a']==1)且在所在列中也只出现一次(c[j][x-'a']==1)
如果满足条件，则将该字符添加到结果字符串s中
 *
 */
#include <iostream>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 101, M = 26;
int r[N][M], c[N][M];
char t[N][N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    char x;
    string s;
    rep(i,n) rep(j,m) {
        cin >> x;
        r[i][x - 'a']++;
        c[j][x - 'a']++;
        t[i][j] = x;
    }
    rep(i,n) rep(j,m) {
        x = t[i][j];
        if (r[i][x - 'a'] == 1 && c[j][x - 'a'] == 1)
            s.push_back(x);
    }
    cout << s;
    return 0;
}