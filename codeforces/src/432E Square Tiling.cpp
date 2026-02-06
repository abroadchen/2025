//
// Created by Psy.C on 2026/2/6.
//
/**

检查在位置 (x, y+i-1)（新的上边界）是否可以放置一个小于当前字母的字母
j 从 'A' 开始，到当前字母 ans[x][y] 之前结束
如果能找到一个小于当前字母且满足相邻条件的字母，说明可以扩展，返回停止
目的：确保如果能用更小字母填上边界，就不必用当前较大字母扩展

检查右侧边界列 (y+i-1) 上是否有任何字符已经被填充
遍历行索引从 x 到 x+i-1
如果边界上已经有字符，说明不能继续扩展，返回停止
目的：确保新扩展的边界没有被其他字符占用

检查底部边界行 (x+i-1) 上是否有任何字符已经被填充
遍历列索引从 y 到 y+i-1
如果边界上已经有字符，说明不能继续扩展，返回停止
目的：确保新扩展的底部边界没有被其他字符占用

检查位置 (x-1, y+i-1) 是否与当前字母相同
这是右上角相邻位置
如果相同，说明扩展会导致相邻相同字符，返回停止
目的：避免相邻位置出现相同字符

检查位置 (x+i-1, y-1) 是否与当前字母相同
这是左下角相邻位置
如果相同，说明扩展会导致相邻相同字符，返回停止
目的：避免相邻位置出现相同字符

检查新扩展区域右边一列 (y+i) 中是否有与当前字母相同的字符
遍历行索引从 x 到 x+i-1
如果发现相同字符，说明扩展会导致相邻相同字符，返回停止
目的：确保扩展后不会与右侧已有字符相邻相同

检查新扩展区域下方一行 (x+i) 中是否有与当前字母相同的字符
遍历列索引从 y 到 y+i-1
如果发现相同字符，说明扩展会导致相邻相同字符，返回停止
目的：确保扩展后不会与下方已有字符相邻相同


 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

char ans[N][N];
//在位置(x,y)放置字符c是否合法
bool ok(const int x, const int y, const char c) {
    static constexpr int dx[] = {1, -1, 0, 0},
    dy[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; ++i)
        if (ans[x+dx[i]][y+dy[i]] == c) return false;
    return true;//四个相邻位置都没有字符c
}

int m, n;
void get(const int x, const int y) {
    int i, j;
    //找到第一个可以在位置(x,y)放置且不与邻居冲突的字母
    //将该字母放置在位置(x,y)
    for (i = 'A'; i <= 'Z'; ++i) if (ok(x, y, static_cast<char>(i))) {
        ans[x][y] = static_cast<char>(i); break;
    }
    for (i = 2; x + i - 1 <= m && y + i - 1 <= n; ++i) {
        for (j='A'; j<ans[x][y]; ++j) if (ok(x, y+i-1, static_cast<char>(j))) return;
        for (j=x; j<=x+i-1; ++j) if (ans[j][y+i-1]) return;
        for (j=y; j<=y+i-1; ++j) if (ans[x+i-1][j]) return;
        if (ans[x-1][y+i-1] == ans[x][y]) return;
        if (ans[x+i-1][y-1] == ans[x][y]) return;
        for (j=x; j<=x+i-1; ++j) if (ans[j][y+i] == ans[x][y]) return;
        for (j=y; j<=y+i-1; ++j) if (ans[x+i][j] == ans[x][y]) return;
        //当前字母填充到新扩展的边界上 形成一个矩形区域的边界
        for (j=x; j<=x+i-1; ++j) ans[j][y+i-1] = ans[x][y];
        for (j=y; j<=y+i-1; ++j) ans[x+i-1][j] = ans[x][y];
    }
}


int main() {
    fast;
    cin >> m >> n;
    int i;
    for (i = 1; i <= m; ++i) for (int j = 1; j <= n; ++j)
        if (!ans[i][j]) get(i, j);//对未填充的位置调用
    for (i = 1; i <= m; ++i) cout << ans[i] + 1 << '\n';//跳过索引0位置
    return 0;
}