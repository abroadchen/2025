//
// Created by Psy.C on 2025/9/20.
//
/*
*v: 节点的价值
c: 节点的颜色
l: 左边界
r: 右边界
 *
*条件判断：如果左边界为0或者状态(l, r+c)已存在
计算当前节点的dp值：前驱节点的dp值加上当前节点价值
记录路径：nxt[i]指向最优前驱节点
 *
*如果右边界为0且当前dp值更大，更新head为当前节点
这表示找到了更优的结束节点
 *
*如果当前dp值优于之前存储的状态(l+c, r)，则更新该状态为当前节点
这是在维护状态转移表，用于后续节点的决策
 *
*从head节点开始，沿着nxt指针回溯，重构最优路径
将路径节点存储在ans数组中
 *倒序输出路径节点（因为重构时是反向存储的）
 *
 *
 *
 *程序维护了一个状态表ghs，用于快速查找满足条件的前驱节点。
 *dp[i]表示以节点i结尾的最优值，nxt数组用于记录路径
 *
 *
 *
 *
 *
 */
#include <cstdio>
#include <map>
using namespace std;

const int N = 2e5+10;
int n, head;
map<int,int> ghs[N];
int dp[N], nxt[N], ans[N];

int main() {

    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) {
        int v, c, l, r;
        scanf("%d%d%d%d",&v,&c,&l,&r);

        if (!l || ghs[l].count(r + c)) {
            dp[i] = dp[ghs[l][r+c]] + v;
            nxt[i] = ghs[l][r+c];
            if (!r && dp[i] > dp[head]) head = i;
            if (dp[i] > dp[ghs[l+c][r]]) ghs[l+c][r] = i;
        }
    }

    int idx = 0;
    for (int i = head; i; i = nxt[i]) ans[idx++] = i;
    printf("%d\n",idx);
    for (int i = idx - 1; i >= 0; --i) printf("%d ",ans[i]);
    return 0;
}