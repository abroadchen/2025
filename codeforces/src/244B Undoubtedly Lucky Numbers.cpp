//
// Created by Psy.C on 2025/12/16.
//
/*
*n: 输入的上限值
ans: 结果计数器
vis: 用于标记已经计算过的数字，避免重复计数
*a: 当前构建的数字
x, y: 两个固定的数字字符
cnt: 当前数字的位数（深度限制）
 *剪枝条件：如果位数超过10位或者数字超过n，则返回
*如果当前数字符合条件（不超过n，不为0，且未被访问过）
则计数器加1，并标记为已访问
 *递归调用：在当前数字后面分别添加x和y，继续构建
 *
*双重循环遍历所有可能的数字对(0,1),(0,2),...,(8,9)
对每一对数字调用dfs函数
 *
*外层循环: O(1) (固定45对数字)
DFS深度: 最多10层
总体复杂度: 可接受范围
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n, ans;
map<int, bool> vis;
void dfs(const int a, const int x, const int y, const int cnt) {
    if (cnt > 10 || a > n) return;
    if (a <= n && a != 0 && !vis[a]) {
        ans++;
        vis[a] = true;
    }
    dfs(a * 10 + x, x, y, cnt+1);
    dfs(a * 10 + y, x, y, cnt+1);
}

signed main() {
    fast;
    cin >> n;
    for (int i = 0; i <= 9; ++i) for (int j = i + 1; j <= 9; ++j) {
        dfs(0, i, j, 0);
    }
    cout << ans;
    return 0;
}