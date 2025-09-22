//
// Created by Psy.C on 2025/9/22.
//

#include <cstdio>
#include <cstring>
using namespace std;


int main() {

#ifdef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);// 重定向标准输入到input.txt文件
    freopen("output.txt", "w", stdout);
#endif

    int n, m, q;
    char mmap[32][32][16];// 三维字符数组，用于存储地图信息，最大32x32的网格，每个位置存储长度为16的字符串
    scanf("%d %d %d", &n, &m, &q);// 读取网格的行数n、列数m和操作数q

    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j)
            memset(mmap[i][j], 0, sizeof(mmap[i][j]));
    }

    for (int i = 0; i < q; ++i) {
        int Q, x, y;
        char s[16];// 临时字符串变量
        scanf("%d", &Q);// 读取操作类型Q

        if (~Q) {// 如果Q不为-1（即放置操作）
            scanf("%d %d %s", &y, &x, s);
            // 从指定位置开始遍历网格
            for (int j = m * (y - 1) + x - 1; j < n * m; ++j) {
                int ty = j / m, tx = j % m;// 计算当前格子的行列坐标
                if (!mmap[ty][tx][0]) {// 如果当前位置为空（字符串第一个字符为0）
                    strcpy(mmap[ty][tx], s);// 将字符串s复制到当前位置
                    goto qend;// 跳转到qend标签结束本次操作
                }
            }
            qend:;
        } else {// 如果Q为-1（即查询操作）
            scanf("%s", s);
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    if (!strcmp(s, mmap[j][k])) {// 如果找到匹配的字符串
                        printf("%d %d\n", j + 1, k + 1);
                        memset(mmap[j][k], 0, sizeof(mmap[j][k]));
                        goto suc;
                    }
                }
            }
            printf("-1 -1\n");
            suc:;
        }
    }

    return 0;
}