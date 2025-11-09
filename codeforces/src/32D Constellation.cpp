//
// Created by Psy.C on 2025/9/21.
//

#include <cstdio>
using namespace std;
const int N = 500;
int n, m, l;// 网格行数、列数、要找的第几个十字
char a[N][N];

int main() {
    scanf("%d%d%d\n", &n, &m, &l);

    for (int i = 0; i < n; ++i) gets(a[i]);// 逐行读取网格字符

    for (int k = 1; k < n; ++k)// 枚举可能的十字臂长k（从1开始）
        for (int i = k; i < n - k; ++i)// 枚举网格中的每个可能的十字中心点(i,j)
            for (int j = k; j < m - k; ++j)
                if (a[i][j] == '*' && a[i + k][j] == '*' &&// 中心点和下方点
                    a[i][j + k] == '*' && a[i - k][j] == '*' &&// 右方点和上方点
                    a[i][j - k] == '*') {// 左方点
                    l--;// 找到一个十字，目标序号减1
                    if (!l) {
                        printf("%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n",
                            i + 1, j + 1,// 中心点
                            i - k + 1, j + 1,// 上方点
                            i + k + 1, j + 1,// 下方点
                            i + 1, j - k + 1,// 左方点
                            i + 1, j + k + 1);// 右方点
                        return 0;
                    }
                }
    printf("-1\n");
    return 0;
}