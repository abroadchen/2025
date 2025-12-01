//
// Created by Psy.C on 2025/11/30.
//
/*
*eps = 1e8：哈希偏移量
mod = 114514：哈希模数
n：幻方阶数
m = n*n：总元素个数
a[20]：输入的数字数组
sum：幻方每行/列/对角线的和
vis[mod]：哈希表，用于快速查找数字是否存在

*自定义哈希函数：(x + eps)² % mod
使用1ll确保中间计算使用long long避免溢出
添加偏移量eps避免小数值导致的哈希冲突
 *
 *p[10][10]：存储构造的幻方矩阵（从索引1开始使用）
 *(x,y)：当前要填充的位置坐标
*t1：主对角线和（除最后一行）
t2：副对角线和（除最后一行）
t3：第一列和（除最后一行）
t4：最后一列和（除最后一行）
如果对角线和不等于边界和，返回
 *
 *填充最后一行并验证
*对每一列计算所需值：tmp = sum - 已填元素和
检查该值是否存在（通过哈希表）
如果不存在，恢复之前的状态并返回
如果存在，使用该值填充最后一行对应位置
*输出幻和
输出完整的幻方矩阵
 *
*填充当前行最后一个元素：
计算该行所需值：tmp = sum - 已填元素和
检查该值是否存在
如果存在，填充并递归到下一行
回溯时恢复状态
 *
*填充倒数第二行第二个位置：
这个位置同时影响第一列和副对角线
计算满足两个约束的值
验证并填充
 *
 * 一般位置处理
*遍历所有输入数字
如果该数字还未被使用（vis[tmp] > 0）
使用该数字填充当前位置
递归处理下一个位置
回溯时恢复状态
 *
*读入幻方阶数n
计算总元素数m = n²
读入所有数字，计算总和，并建立哈希表
计算幻和：sum = 总和/n
从位置(1,1)开始深度优先搜索
 *
*时间复杂度：
最坏情况：O(n²!)
实际由于剪枝会好很多
空间复杂度：
O(n²) 用于存储幻方和辅助数组
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

typedef long long ll;
constexpr int eps = 1e8, mod = 114514;
int n, m, a[20], sum, vis[mod];

int ha(const int x) { return static_cast<int>(1ll * (x + eps) * (x + eps) % mod); }

int p[10][10];
void dfs(const int x, const int y) {
    if (x == n) {
        int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
        for (int i = 1; i < n; ++i) {
            t1 += p[i][i], t2 += p[i][n-i+1], t3 += p[i][1], t4 += p[i][n];
        }
        if (t1 != t4 || t2 != t3) return;
        rep(i,n) {
            int tmp = sum;
            for (int j = 1; j < n; ++j) tmp -= p[j][i];
            const int tmp2 = ha(tmp);
            if (!vis[tmp2]) {
                for (int j = 1; j < i; ++j) vis[ha(p[n][j])]++;
                return;
            }
            vis[tmp2]--, p[n][i] = tmp;
        }
        cout << sum << '\n';
        rep(i,n) {
            rep(j,n) cout << p[i][j] << ' ';
            cout << '\n';
        }
        exit(0);
    }
    if (y == n) {
        int tmp = sum;
        for (int i = 1; i < n; ++i) tmp -= p[x][i];
        const int tmp2 = ha(tmp);
        if (!vis[tmp2]) return;
        vis[tmp2]--, p[x][n] = tmp;
        dfs(x + 1, 1);
        vis[tmp2]++;
        return;
    }
    if (x == n - 1 && y == 2) {
        int tmp = 0;
        for (int i = 1; i < n; ++i) tmp += p[i][1];
        for (int i = 1; i < n - 1; ++i) tmp -= p[i][n - i + 1];
        const int tmp2 = ha(tmp);
        if (!vis[tmp2]) return;
        vis[tmp2]--, p[x][y] = tmp;
        dfs(x, y + 1);
        vis[tmp2]++;
        return;
    }
    rep(i,m) {
        const int tmp = ha(a[i]);
        if (vis[tmp]) {
            vis[tmp]--, p[x][y] = a[i];
            dfs(x, y + 1);
            vis[tmp]++;
        }
    }
}

int main() {
    fast;
    cin >> n; m = n * n;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i]; sum += a[i];
        vis[ha(a[i])]++;
    }
    sum /= n;
    dfs(1, 1);
    return 0;
}