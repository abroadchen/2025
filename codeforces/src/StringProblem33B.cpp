//
// Created by Psy.C on 2025/9/21.
//
/*
 *
*时间复杂度：

Floyd算法：O(26³) = O(1)
字符串处理：O(n1 × 26) = O(n1)
总体：O(n1)
 *
 *
 *
 *
 */

#include <cstdio>
#include <cstring>
#define inf 1e9
using namespace std;

const int N = 100003;

int main() {
    char a[N], b[N], ans[N], c1, c2;// 输入字符串a,b，结果字符串ans，临时字符变量
    int c[30][30], n, i, j, cost, k, n1, n2, res, mmin;

    while (~scanf("%s%s%d", a, b, &n)) {
        for (i = 0; i < 26; ++i) {
            for (j = 0; j < 26; ++j) c[i][j] = inf;
            c[i][i] = 0;// 自身转换成本为0
        }
        for (i = 0; i < n; ++i) {
            getchar();// 读取换行符
            scanf("%c", &c1);// 读取源字符
            getchar();// 读取空格
            scanf("%c", &c2);// 读取目标字符
            scanf("%d", &cost);
            // 更新转换成本（取最小值）
            c[c1 - 'a'][c2 - 'a'] = (cost < c[c1 - 'a'][c2 - 'a'] ? cost : c[c1 - 'a'][c2 - 'a']);
        }
        for (k = 0; k < 26; ++k) {// 使用Floyd算法计算任意两个字符间的最小转换成本
            for (i = 0; i < 26; ++i) {
                if (c[i][k] == inf) continue;
                for (j = 0; j < 26; ++j) {
                    if (c[k][j] != inf && c[i][k] + c[k][j] < c[i][j])
                        c[i][j] = c[i][k] + c[k][j];
                }
            }
        }
        n1 = strlen(a), n2 = strlen(b);
        if (n1 != n2) {// 如果长度不同，则无法转换
            printf("-1\n");
            continue;
        }
        // 对字符串的每一位计算最优转换
        for (res = 0, i = 0; i < n1; ++i) {
            for (mmin = inf, j = 0; j < 26; ++j) {// 寻找最优的中间字符
                if (c[a[i] - 'a'][j] == inf || c[b[i] - 'a'][j] == inf) continue;
                cost = c[a[i] - 'a'][j] + c[b[i] - 'a'][j];// 计算通过字符j转换的总成本
                if (cost < mmin) {// 更新最小成本和对应字符
                    mmin = cost;
                    ans[i] = 'a' + j;
                }
            }
            if (mmin == inf) break;
            res += mmin;
        }
        if (i < n1) {// 如果未能处理完所有字符，说明无解
            printf("-1\n");
            continue;
        }
        ans[n1] = '\0';// 添加字符串结束符
        printf("%d\n%s\n", res, ans);// 输出总成本和结果字符串
    }

    return 0;
}