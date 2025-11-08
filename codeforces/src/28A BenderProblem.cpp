//
// Created by Psy.C on 2025/9/20.
//
/*
*n: 点的数量
m: 棒子的数量
x[N], y[N]: 存储点的坐标
rod[N]: 存储棒子的长度
ans[N]: 存储结果（每个点对应的棒子编号）
vis[N]: 标记棒子是否已被使用
flag: 标记是否找到有效解
 *
*初始化函数，重置所有状态
将ans数组初始化为-1（表示未分配）
将vis数组初始化为false（表示所有棒子都未使用）
设置flag为true（表示假设能找到解）
 *
 *(j + n - 1) % n 用于处理环形数组的索引，当j=0时指向前一个元素（即索引n-1）
 *(j + 1) % n 用于处理环形数组的索引，当j=n-1时指向后一个元素（即索引0）
 *
 *
 *
*从第i个点开始，每隔一个点分配棒子（j += 2）
计算该点需要的棒子长度
在未使用的棒子中寻找匹配的长度
如果找到匹配，标记该棒子已使用并记录分配结果
如果找不到匹配，标记失败并跳出循环
如果当前策略成功，跳出外层循环
 *
 *
 */

#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 10010;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') { f = -1; ch = getchar(); }
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int n, m;
int x[N], y[N], rod[N], ans[N];
bool vis[N], flag;

void init() {
    memset(ans, -1, sizeof(ans));
    memset(vis, false, sizeof(vis));
    flag = true;
}

int calc(int i, int j) {
    int _x = abs(x[j] - x[(j + n - 1) % n]);
    int _y = abs(y[j] - y[(j + n - 1) % n]);
    int x_ = abs(x[j] - x[(j + 1) % n]);
    int y_ = abs(y[j] - y[(j + 1) % n]);
    return _x + _y + x_ + y_;
}


int main() {

    n = read(); m = read();
    for (int i = 0; i < n; ++i) { x[i] = read(); y[i] = read(); }
    for (int i = 0; i < m; ++i) rod[i] = read();

    for (int i = 0; i < 2; ++i) {
        init();
        for (int j = i; j < n; j += 2) {
            int dis = calc(i, j);
            for (int k = 0; k < m; ++k) {
                if (!vis[k] && rod[k] == dis) {
                    vis[k] = true;
                    ans[j] = k + 1;
                    break;
                }
            }
            if (ans[j] == -1) { flag = false; break; }
        }
        if (flag) break;
    }

    if (flag) {
        printf("YES\n%d", ans[0]);
        for (int i = 1; i < n; ++i) printf(" %d", ans[i]);
        puts("");
    } else printf("NO\n");
    return 0;
}