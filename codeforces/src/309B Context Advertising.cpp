/**
* stk[N+1]：栈数组，用于DFS过程中的路径记录
top：栈顶指针
ans[N+2]：存储每个节点的答案（距离）
s：最多能放的行数
son[N+2]：邻接表，存储每个节点的子节点
 *sum[i]表示前i个字符串的总长度加上空格的数量
 *
索引从0开始，需要存储从 sum[0] 到 sum[N] 共 N+1 个元素
sum[0] 通常初始化为0，所以需要 N+1 个位置来存储 N 个实际数据*
*代码中创建了一个编号为 n+1 的虚拟根节点
当 n 达到最大值 N 时，虚拟节点编号为 N+1
所以需要 N+2 个位置来存储从 0 到 N+1 的节点数据
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 1000000
using namespace std;

int stk[N+1], top, ans[N+2], s;
vector<int> son[N+2];
void dfs(const int x) {
    stk[top++] = x;
    ans[x] = stk[max(0, top - 1 - s)] - x;
    for (int i = 0, y; i < son[x].size(); ++i) {
        y = son[x][i];
        dfs(y);
    }
    top--;
}


int main() {
    fast;
    int n, m, sum[N+1], fa[N+2]; cin >> n >> s >> m; string a[N+1];
    for (int i = 1; i <= n; ++i) cin >> a[i], sum[i] = sum[i - 1] + a[i].size() + 1;
    fa[n + 1] = n + 1;//最后一个虚拟节点的父节点为自己
    for (int i = n; i; --i) {
        fa[i] = fa[i + 1];
        while (sum[fa[i] - 1] - sum[i - 1] - 1 > m) fa[i]--;//满足容量限制
        if (fa[i] != i) son[fa[i]].push_back(i);//当前节点不是根节点，将其加入父节点的子节点列表
    }
    for (int i = 1; i <= n + 1; ++i) if (fa[i] == i) top = 0, dfs(i);//每次DFS前将栈顶指针重置为0
    const int mx = *max_element(ans + 1, ans + n + 2);
    for (int i = 1; i <= n + 1; ++i) if (ans[i] == mx) {
        while (s--) {
            for (int j = i; j < fa[i]; ++j) cout << a[j] << (j < fa[i] - 1 ? ' ' : '\n');
            i = fa[i];//更新节点为它的父节点
        }
        return 0;
    }
    return 0;
}