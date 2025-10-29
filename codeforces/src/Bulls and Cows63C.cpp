//
// Created by Psy.C on 2025/10/29.
//
/*
*N = 5：数组大小相关常量
M = 20：最大节点数
K = 10000：循环上界
L = 11：vis数组大小
*n：输入数据的数量
cnt1：计数器1（正确位置的数字个数）
cnt2：计数器2（存在的数字个数）
cnt：满足条件的解的个数
res：结果存储
vis[L]：标记数组，用于检查数字是否重复
t：临时变量
ans[N-1]：存储当前尝试的数字组合
 *
*定义结构体Node，包含：
num[N-1]：存储数字数组
a：正确位置的数字个数
b：存在但位置错误的数字个数
声明结构体数组node[M]
 *
 *定义函数ok，判断数字x是否满足条件（各位数字不重复）
 *
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 5, M = 20, K = 10000, L = 11;
int n, cnt1, cnt2, cnt, res, vis[L], t, ans[N-1];
char arr[N];//字符数组，用于读取输入的字符串

struct Node {
    int num[N-1], a, b;
} node[M];

bool ok(int x) {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < N - 1; ++i) {//循环处理x的每一位数字
        t = x % 10;//取x的个位数字
        if (vis[t]) return false;
        ans[i] = t;//将数字存储到ans数组中
        vis[t] = 1;
        x /= 10;//去掉x的个位数字
    }
    return true;
}

int main() {
    while (scanf("%d", &n) != EOF) {//成功读取一个整数时继续
        for (int i = 0; i < n; ++i) {
            scanf("%s %d %d", arr, &node[i].a, &node[i].b);//读取字符串和两个整数
            for (int j = 0; j < N - 1; ++j)
                node[i].num[j] = arr[j] - '0';//将字符转换为数字存储到node[i].num中
        }
        cnt = 0;
        for (int i = 1; i < K; ++i) {//循环尝试所有可能的数字组合（1到9999）
            if (ok(i)) {//如果数字i满足各位不重复的条件
                int j;//检查该数字是否满足所有输入条件
                for (j = 0; j < n; ++j) {
                    cnt1 = cnt2 = 0;
                    for (int k = 0; k < N - 1; ++k) {//对每一位数字进行检查
                        if (ans[k] == node[j].num[k]) cnt1++;//统计位置正确的数字个
                        if (vis[node[j].num[k]]) cnt2++;//统计存在的数字个数
                    }
                    if (cnt1 != node[j].a || cnt2 - cnt1 != node[j].b) break;
                }
                if (j == n) { res = i; cnt++; }//如果满足所有条件，则记录结果并增加计数器
            }
        }
        if (cnt == 1) {//如果只有一个解
            for (int i = 0; i < N - 1; ++i) {//循环输出结果（逆序）
                printf("%d", res % 10);
                res /= 10;
            }
            printf("\n");
        } else if (cnt > 1) printf("Need more data\n");//有多个解
        else printf("Incorrect data\n");//无解
    }
    return 0;
}