//
// Created by Psy.C on 2026/3/14.
//
/**
n: 矩阵大小
n2 = n/2: 一半大小
lx[], ly[]: KM算法的顶标数组
lk[]: 匹配数组
w[][]: 当前工作矩阵
w1[][], w2[][]: 两组权重矩阵
s1[]: 松弛数组
p[]: 路径数组
b[]: 访问标记数组
ans: 最终答案

nn: 当前处理的行号
d1, d2: 两个方向的选择计数
如果处理完所有行，更新答案
ch: 选择分支（0或1）
d1 == n2 && ch == 1: 第一类选择已达上限，跳过
d2 == n2 && ch == 0: 第二类选择已达上限，跳过
保存当前KM算法状态
根据ch选择使用w1或w2作为当前权重矩阵
初始化松弛数组和访问标记
KM算法核心：寻找增广路径
t = -lx[cx] - ly[i] - w[cx][i]: 计算边的松弛值
更新最小松弛值和路径
更新顶标：左边加tmp，右边减tmp
更新松弛数组
回溯路径，更新匹配
递归处理下一行
ch^1: 异或操作，0变1，1变0
恢复之前保存的状态

时间复杂度约为O(2^n * n^3)
 */
#include <bits/stdc++.h>
#define mv(a,b) memcpy(a,b,(n<<2)+4)
using namespace std;
constexpr int N = 21, inf = 0x7f7f7f7f;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, lx[N], ly[N], ans, n2, lk[N], w[N][N], w1[N][N], w2[N][N], s1[N], p[N];
bool b[N];
void dfs(int nn, int d1, int d2) {
    if (nn > n) {
        if (ly[0] > ans) ans = ly[0];
        return;
    }
    int _lx[N], _ly[N], _lk[N], cx, cy, i, ny = 0;
    for (int ch = 0; ch < 2; ++ch) {
        if (d1 == n2 && ch == 1) continue;
        if (d2 == n2 && ch == 0) continue;
        mv(_lx, lx), mv(_ly, ly), mv(_lk, lk);
        if (ch) mv(w[nn], w1[nn]);
        else mv(w[nn], w2[nn]);
        memset(s1, 0x7f, (n<<2)+4); memset(b, 0, n+1);
        cy = 0; lk[0] = nn;
        while (lk[cy]) {//当cy还有匹配时继续
            b[cy] = 1;//标记cy为已访问
            cx = lk[cy];//获取cy的匹配点cx
            //从cx出发寻找新的匹配
            int tmp = inf;
            for (i = 1; i <= n; ++i)
                if (!b[i]) {
                    int t = -lx[cx] - ly[i] - w[cx][i];//计算cx→i边的松弛值
                    if (t < s1[i])
                        s1[i] = t, p[i] = cy;//记录路径: cy → i
                    if (s1[i] < tmp)
                        tmp = s1[i], ny = i;//找到最小松弛值
                }
            for (i = 0; i <= n; ++i) {
                if (b[i]) lx[lk[i]] += tmp, ly[i] -= tmp;
                else s1[i] -= tmp;
            }
            cy = ny;//移动到下一个y点
        }
        while (cy) lk[cy] = lk[p[cy]], cy = p[cy];
        dfs(nn + 1, d1 + ch, d2 + (ch^1));
        mv(lx,_lx), mv(ly,_ly), mv(lk, _lk);
    }
}


int main() {
    n2 = (n=rd())>>1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) w1[i][j] = rd();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) w2[i][j] = rd();
    dfs(1, 0, 0);
    printf("%d\n", ans);
    return 0;
}