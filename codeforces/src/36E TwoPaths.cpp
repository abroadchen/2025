//
// Created by Psy.C on 2025/9/22.
//

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 51000;
int m, tot, n, e[N], nxt[N], head[N], ru[N], s, fa[N], g[N];
bool vis[N];
int ans[3][N];

void add(int x, int y) {// 向邻接表中添加边
    tot++;// 边的总数加1
    e[tot] = y;// 存储边的终点
    nxt[tot] = head[x];// 链接下一条边
    head[x] = tot;// 更新头指针
}

void dfs(int x) {// DFS遍历连通分量
    fa[x] = s;// 标记节点x属于第s个连通分量
    for (int i = head[x]; i; i = nxt[i]) {// 遍历x的所有邻接点
        int y = e[i];// 获取邻接点
        if (fa[y] == 0) dfs(y);// 如果未访问过，继续DFS
    }
}

void ola(int x, int now) {// 搜索欧拉路径
    for (int i = head[x]; i; i = nxt[i]) {// 遍历所有邻接边
        if (!vis[i / 2]) {// 如果边未被访问（i/2是因为无向图每条边存储两次）
            vis[i / 2] = true;
            ola(e[i], now);// 递归搜索
            ans[now][++ans[now][0]] = i / 2;// 将边加入答案
        }
    }
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &m);// 读取边数m
    if (m <= 1) {
        printf("-1");
        return 0;
    }
    tot = 1;// 初始化边计数器
    for (int i = 1; i <= m; ++i) {// 读取所有边
        int x, y; scanf("%d%d", &x, &y);// 读取边的两个端点
        n = max(n, x); n = max(n, y);// 更新最大节点编号
        add(x, y);// 添加正向边
        add(y, x);// 添加反向边（无向图）
        ru[x]++;// x的度数加1
        ru[y]++;// y的度数加1
    }
    s = 0;// 连通分量计数器
    for (int i = 1; i <= n; ++i) {// 遍历所有节点
        if ((ru[i] > 0) && (fa[i] == 0)) {// 如果节点有边且未访问
            s++;// 连通分量数加1
            dfs(i);// DFS标记整个连通分量
        }
    }
    if (s > 2) {// 如果连通分量超过2个
        printf("-1");
        return 0;
    }
    if (s == 2) {
        int sum = 0;// 奇度数节点计数器
        for (int i = 1; i <= n; ++i) {// 遍历第一个连通分量
            if ((fa[i] == 1) && (ru[i] % 2 == 1)) sum++;// 统计奇度数节点
        }
        if (sum > 2) {// 如果奇度数节点超过2个
            printf("-1");
            return 0;
        }
        for (int i = 1; i <= n; ++i) {// 寻找起始点
            if ((fa[i] == 1) && ((ru[i] % 2 == 1) || sum == 0)) {
                ola(i, 1);// 从该点开始搜索欧拉路径
                break;
            }
        }
        sum = 0;
        for (int i = 1; i <= n; ++i) {// 处理第二个连通分量
            if ((fa[i] == 2) && (ru[i] % 2 == 1)) sum++;
        }
        if (sum > 2) {
            printf("-1");
            return 0;
        }
        for (int i = 1; i <= n; ++i) {
            if ((fa[i] == 2) && ((ru[i] % 2 == 1) || sum == 0)) {
                ola(i, 2);// 搜索第二个连通分量的欧拉路径
                break;
            }
        }
        for (int i = 1; i <= 2; ++i) {
            printf("%d\n", ans[i][0]);// 输出路径长度
            for (int j = ans[i][0]; j > 0; --j)
                printf("%d ", ans[i][j]);// 输出路径
            printf("\n");
        }
    } else {// 如果只有一个连通分量
        int sum = 0;
        for (int i = 1; i <= n; ++i) {// 统计奇度数节点
            if ((fa[i] == 1) && (ru[i] % 2 == 1)) {
                sum++;
                g[sum] = i;// 记录奇度数节点
            }
        }
        if (sum > 4) {// 如果奇度数节点超过4个
            printf("-1");
            return 0;
        }
        if (sum < 4) {
            for (int i = 1; i <= n; ++i) {
                if ((fa[i] == 1) && ((ru[i] % 2 == 1) || sum == 0)) {
                    ola(i, 1);
                    break;
                }
            }
            ans[2][0] = 1;// 构造第二条路径
            ans[2][1] = ans[1][ans[1][0]];
            ans[1][0]--;
            for (int i = 1; i <= 2; ++i) {
                printf("%d\n", ans[i][0]);
                for (int j = ans[i][0]; j > 0; --j)
                    printf("%d ", ans[i][j]);
                printf("\n");
            }
        } else {// 如果恰好4个奇度数节点
            for (int i = 1; i <= sum; ++i) {// 枚举所有可能的配对
                for (int j = i + 1; j <= sum; ++j) {
                    add(g[i], g[j]);// 添加虚拟边
                    add(g[j], g[i]);
                    memset(vis, false, sizeof(vis));// 重置访问标记
                    memset(ans, 0, sizeof(ans));
                    for (int k = 1; k <= 4; ++k) {// 从其他两个奇度数节点开始搜索
                        if ((k != i) && (k != j)) ola(g[k], 1);
                    }
                    if (ans[1][0] == m + 1) {// 如果找到欧拉路径
                        int t = 0;
                        for (int k = 1; k <= m + 1; ++k) {
                            if (ans[1][k] == tot / 2) {
                                t = k;
                                break;
                            }
                        }
                        printf("%d\n", m - t + 1);// 输出第一条路径
                        for (int k = m + 1; k > t; --k)
                            printf("%d ", ans[1][k]);
                        printf("\n");
                        printf("%d\n", t - 1);// 输出第二条路径
                        for (int k = t - 1; k > 0; --k)
                            printf("%d ", ans[1][k]);
                        goto aaa;
                    }
                    tot -= 2;// 回退添加的边
                }
            }
        }
    }

    aaa:;
    return 0;
}