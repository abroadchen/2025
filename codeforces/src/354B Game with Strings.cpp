//
// Created by Psy.C on 2026/1/17.
//
/**
* vis[40][1<<20]: 记忆化访问标记，防止重复计算
dp[40][1<<20]: 动态规划数组，存储每个状态的结果
n: 网格大小
a[25][25]: 存储输入的字符网格
 *
*y|y<<1: 当前状态向左扩展
y|y>>1: 当前状态向右扩展
&mask[i]: 与字符位置掩码求交集
 *
*k: 根据字符('a'=0,'b'=1)确定收益
'a': k=1 (第一玩家收益)
'b': k=-1 (第二玩家收益)
if (x&1): 第二玩家回合，取最大值
else: 第一玩家回合，取最小值
 *
*第一玩家（偶数轮）：希望结果最小化（对对手有利）
第二玩家（奇数轮）：希望结果最大化（对自己有利
 *
*上半三角区域 (x+1 < n)
y|y<<1：当前可达位置向左扩展
表示可以从当前位置向左移动一步
&mask[i]：与目标字符位置取交集
下半三角区域 (x+1 >= n)
*y|y>>1：当前可达位置向右扩展
表示可以从当前位置向右移动一步
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define inf 0x3f3f3f3f
using namespace std;

bool vis[40][1<<20];
int dp[40][1<<20], n;
char a[25][25];
int dfs(const int x, const int y) {//从状态(x,y)开始的游戏结果
    if (vis[x][y]) return dp[x][y];
    int& res = dp[x][y];// 引用，直接操作dp数组元素
    vis[x][y] = true;
    if (x == (n<<1)-2) res = 0; else {//如果到达终点，结果为0（平局）
        //如果x是奇数（第二玩家回合）：初始化为-inf（寻找最大值）
        //如果x是偶数（第一玩家回合）：初始化为inf（寻找最小值）
        if (x&1) res = -inf; else res = inf;
        int mask[30] = {}, cnt = 0;
        for (int j = 0; j <= x + 1; ++j) {
            const int u = x + 1 - j, v = j;//遍历当前对角线上的位置 (u,v)
            if (u >= n || v >= n) continue;
            mask[a[u][v] - 'a'] |= 1<<cnt;//为每个字符建立位置掩码
            cnt++;
        }
        //遍历所有可能的字符('a'到'z')
        for (int i = 0; i < 26; ++i) if (mask[i]) {//如果该字符在当前对角线存在
            int t;
            if (x + 1 < n) t = (y|y<<1)&mask[i];//计算可能的下一步状态
            else t = (y|y>>1)&mask[i];
            if (t == 0) continue;//没有可行的下一步，跳过
            int k = 0;
            if (i == 0) k = 1; else if (i == 1) k = -1;
            if (x&1) res = max(res, k + dfs(x + 1, t));
            else res = min(res, k + dfs(x + 1, t));
        }
    }
    if (x == 0) {//起点(0,1)，考虑第一个字符的影响
        if (a[0][0] == 'a') res += 1;
        else if (a[0][0] == 'b') res -= 1;
    }
    return res;
}


int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    memset(vis, false, sizeof(vis));
    if (const int res = dfs(0, 1); res == 0) cout << "DRAW\n";
    else if (res > 0) cout << "FIRST\n";
    else cout << "SECOND\n";
    return 0;
}