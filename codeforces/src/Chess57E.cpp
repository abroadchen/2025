//
// Created by Psy.C on 2025/10/22.
//
/*
*N = 401: 网格大小
M = N * N: 队列大小
mod = 1000000007: 模数
 *
*n: 某个大的数值参数
m: 障碍物数量
k: 限制步数
sx, sy: 起始坐标
h, t: 队列头尾指针
qx[], qy[], qs[]: 队列数组，分别存储x坐标、y坐标和步数
v[][]: 访问标记数组
 *
*初始化BFS队列：
队列头h=0，队列尾t=1
将起始位置(sx,sy)加入队列，步数为0
标记起始位置已访问
 *
*BFS主循环，当队列不为空时继续
取出队首元素的位置(x,y)和步数s
如果达到步数限制k则跳出循环
*尝试8个骑士移动方向
如果新位置未被访问过，则标记为已访问，步数加1，并加入队列
 *
*如果步数限制等于n或者队列中最后一个元素的步数小于k
直接输出当前可达位置数t
 *
*计算宽度w（当前层的节点数）
计算剩余步数r = (n-k) % mod
使用公式计算最终答案：
t: 已经计算出的位置数
(ll)r * w % mod: 每层w个位置，还有r层
14ll * r % mod * (r + 1) % mod: 额外的计算项
 *
 *
 *
 */
#include <cstdio>
using namespace std;

typedef long long ll;
const int N = 401, M = N * N, mod = 1e9+7;
ll n;
int m, k, sx, sy, i, x, y, h, t, qx[M], qy[M], qs[M], s, w;
bool v[N][N];

int dx[8] = {-2,-2,-1,-1,1,1,2,2}, dy[8] = {-1,1,-2,2,-2,2,-1,1};

int main() {
    scanf("%lld%d", &n, &m);
    k = 100; sx = sy = 2 * k;
    if (n < k) k = n;
    for (i = 1; i <= m; ++i) {//读取m个障碍物坐标，并在访问数组中标记这些位置
        scanf("%d%d", &x, &y);
        v[sx + x][sy + y] = 1;
    }
    h = 0; t = 1; qx[1] = sx; qy[1] = sy; qs[1] = 0; v[sx][sy] = 1;
    for (; h != t;) {
        h++;
        x = qx[h];y = qy[h];s = qs[h];
        if (s == k) break;
        for (i = 0; i < 8; ++i) {
            int cx = x + dx[i], cy = y + dy[i];
            if (!v[cx][cy]) {
                v[cx][cy] = 1;
                qs[++t] = s + 1;
                qx[t] = cx; qy[t] = cy;
            }
        }
    }
    if (k == n || qs[t] < k) {
        printf("%d", t);
        return 0;
    }
    w = t - h + 1;
    int r = (n - k) % mod,
    ans = t + (ll)r * w % mod + 14ll * r % mod * (r + 1) % mod;
    printf("%d", ans % mod);
    return 0;
}