//
// Created by Psy.C on 2026/3/13.
//
/**
b数组存储可选数字，m为b数组长度
vis标记已使用数字，ans存储答案
get函数找到小于k的最大未使用数字并标记
n: 序列长度
a: 原序列（-1表示待填）
f: LIS辅助数组
pos: 位置数组
g: g[i]表示以i结尾的最长上升子序列长度
p: p[i]表示以i结尾的最长上升子序列的前驱

对每个位置i处理：
如果a[i]=-1（待填），用最大的可用数字填充LIS数组
否则，使用LIS算法更新相关信息
g[i]记录以i结尾的LIS长度
p[i]记录前驱位置

从最长上升子序列的末尾向前回溯
处理-1位置的填值，确保LIS长度最大化
标记已使用的数字

i = g[n]：获取整个序列的最长上升子序列长度
j = n：从序列末尾开始回溯
x = a[n]：当前处理的元素值（此时a[n]被设为inf）
从最长子序列的最后一个位置开始向前回溯
i--：每次循环处理一个LIS中的元素
当a[j]不是-1（即不是待填位置）时：
a[p[j]] == -1：如果前驱位置是-1（待填）
调用get(p[j], a[j], x)：为p[j]位置选择一个小于a[j]的合适值
x更新为这个新选择的值
a[p[j]] != -1：如果前驱位置不是-1
x = a[p[j]]：x更新为前驱位置的实际值
j = p[j]：移动到前驱位置继续回溯
当a[j] == -1（待填位置）时：
寻找前面的非-1位置：a[s] != -1
该位置属于当前LIS长度：g[s] == i
该值小于当前x：a[s] < x
如果找到：x = a[j=s]更新值和位置，设置flag=1
如果上面找到了合适的非-1位置，继续循环
否则寻找前面的-1位置进行填值：
get(s, x, x)：为位置s选择一个小于x的合适值
j = s：移动到该位置继续回溯


填充剩余的-1位置
如果ans[i]已经有值，直接使用
否则，使用最小的未使用数字


 */
#include <bits/stdc++.h>
using namespace std;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

constexpr int N = 1e5+5, inf = 0x7f7f7f7f;

int b[N], m, vis[N], ans[N];
void get(int i, int k, int& x) {
    int t = lower_bound(b + 1, b + 1 + m, k) - b - 1;
    vis[t] = 1;
    x = ans[i] = b[t];
}

int n, a[N], f[N], pos[N], g[N], p[N];
int main() {
    rd(n);
    for (int i = 1; i <= n; ++i) rd(a[i]), f[i] = inf;
    n++; a[n] = inf; f[n] = inf; rd(m);
    for (int i = 1; i <= m; ++i) rd(b[i]);
    sort(b + 1, b + 1 + m);
    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1) {
            for (int j = n, k = m; k > 0; k--) {
                while (f[j] >= b[k]) j--;
                f[j+1] = b[k];
                pos[j+1] = i;
            }
        } else {
            int j = lower_bound(f + 1, f + 1 + n, a[i]) - f - 1;
            g[i] = j + 1; p[i] = pos[j]; f[j+1] = a[i]; pos[j+1] = i;
        }
    }
    {
        int i = g[n], j = n, x = a[n];
        while (i--) {
            if (a[j] != -1) {
                if (a[p[j]] == -1) get(p[j], a[j], x);
                else x = a[p[j]];
                j = p[j];
            } else {
                bool flag = 0;
                for (int s = j-1; s > 0; s--) {
                    if (a[s] != -1 && g[s] == i && a[s] < x) {
                        x = a[j=s]; flag = 1;
                        break;
                    }
                }
                if (flag) continue;
                for (int s = j-1; s > 0; s--) {
                    if (a[s] == -1) {
                        get(s, x, x); j = s;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1, j = 1; i < n; ++i) {
        if (a[i] == -1) {
            if (ans[i] != 0) { a[i] = ans[i]; continue; }
            while (vis[j]) j++;
            vis[j] = 1;
            a[i] = b[j];
        }
    }
    for (int i = 1; i < n; ++i) printf("%d ", a[i]);
    puts("");
    return 0;
}