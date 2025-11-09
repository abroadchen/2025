//
// Created by Psy.C on 2025/9/19.
//
/*
*定义网格大小n(行)、m(列)
定义三种方块的数量：a(1×2横放)、b(2×1竖放)、c(2×2方块)
定义状态数组st[105][105]用于标记方块类型
定义字符数组st1[105][105]用于存储最终输出
flag用于标记是否可能完成填充
 *
*cc函数：放置2×2方块，标记为3
bb函数：放置2×1竖放方块，标记为2
aa函数：放置1×2横放方块，标记为1
 *
*aaa函数：为横放的1×2方块填充相同字符
寻找一个与周围不同字符的字母
将该字符填入两个位置
 *
 *bbb函数：为竖放的2×1方块填充相同字符
 *ccc函数：为2×2方块填充相同字符
 *
*判断不可能情况：
网格总面积为奇数（无法用2格方块填满）
方块总覆盖面积不足
 *
*预先放置尽可能多的2×2方块
在每个2×2的区域内放置一个2×2方块
 *
*处理边界情况：
如果列数为奇数，在最右列放置竖放方块
如果行数为奇数，在最下行放置横放方块
 *
*检查方块数量是否足够
如果2×2方块超用，将其转换为其他方块
 *
 *时间复杂度：O(n×m)
 */
#include <cstdio>
using namespace std;

int n, m, a, b, c, st[105][105], flag = 1;
char st1[105][105];

void cc(int i, int j) {
    st[i][j] = st[i + 1][j] = st[i][j + 1] = st[i + 1][j + 1] = 3;
}

void bb(int i, int j) {
    st[i][j] = st[i + 1][j] = 2;
}

void aa(int i, int j) {
    st[i][j] = st[i][j + 1] = 1;
}

void aaa(int x, int y) {
    char s;
    for (char i = 'a'; ; ++i) {
        if (i != st1[x - 1][y] && i != st1[x + 1][y] && i != st1[x][y - 1] &&
            i != st1[x][y + 2] && i != st1[x - 1][y + 1] && i != st1[x + 1][y + 1]) {
            s = i;
            break;
        }
    }
    st1[x][y] = st1[x][y + 1] = s;
    st[x][y] = st[x][y + 1] = 0;
}

void bbb(int x, int y) {
    char s;
    for (char i = 'a'; ; ++i) {
        if (i != st1[x - 1][y] && i != st1[x + 2][y] && i != st1[x][y - 1] &&
            i != st1[x][y + 1] && i != st1[x + 1][y + 1] && i != st1[x + 1][y - 1]) {
            s = i;
            break;
        }
    }
    st1[x][y] = st1[x + 1][y] = s;
    st[x][y] = st[x + 1][y] = 0;
}

void ccc(int x, int y) {
    char s;
    for (char i = 'a'; ; ++i) {
        if (i != st1[x - 1][y] && i != st1[x - 1][y + 1] && i != st1[x][y - 1] &&
            i != st1[x][y + 2] && i != st1[x + 1][y - 1] && i != st1[x + 1][y + 2] &&
            i != st1[x + 2][y] && i != st1[x + 2][y + 1]) {
            s = i;
            break;
        }
    }
    st1[x][y] = st1[x][y + 1] = st1[x + 1][y] = st1[x + 1][y + 1] = s;
    st[x][y] = st[x][y + 1] = st[x + 1][y] = st[x + 1][y + 1] = 0;
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);

    if ((m * n) % 2 == 1 || m * n > 2 * a + 2 * b + 4 * c) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    c -= (m / 2) * (n / 2);
    for (int i = 1; i <= n; i+=2) {
        for (int j = 1; j <= m; j+=2) {
            cc(i, j);
        }
    }
    if (m % 2 == 1) {
        for (int i = 1; i <= n; i+=2) {
            bb(i, m);
            b--;
        }
    }
    if (n % 2 == 1) {
        for (int i = 1; i <= m; i+=2) {
            aa(n, i);
            a--;
        }
    }
    if (a < 0 || b < 0) {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    if (c < 0) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (st[i][j] == 3) {
                    if (a >= 2) {
                        aa(i, j);
                        aa(i + 1, j);
                        a -= 2;
                        c++;
                    } else if (b >= 2) {
                        bb(i, j);
                        bb(i, j + 1);
                        b -= 2;
                        c++;
                    } else {
                        flag = 0;
                        break;
                    }
                }
                if (c == 0) break;
            }
            if (flag == 0) break;
            if (c == 0) break;
        }
    }

    if (flag == 0) {
        printf("IMPOSSIBLE\n");
        return 0;
    } else {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (st[i][j] == 0) continue;
                else if (st[i][j] == 1) aaa(i, j);
                else if (st[i][j] == 2) bbb(i, j);
                else if (st[i][j] == 3) ccc(i, j);
            }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                printf("%c", st1[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}