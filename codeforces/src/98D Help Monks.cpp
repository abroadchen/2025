//
// Created by Psy.C on 2025/11/11.
//
/*
*N = 25: 最大盘子数量
n: 盘子总数
d[N]: 存储每个盘子的尺寸
len[N]: 存储不同尺寸的盘子
m: 不同尺寸盘子的数量
c[N]: 每种尺寸盘子的个数
f[N]: 标记某种尺寸是否有重复盘子
ans: 存储移动步骤的结果向量
 *
*dep: 当前处理的盘子尺寸层数（递归深度）
x: 起始柱子
y: 目标柱子
z: 辅助柱子
ok: 是否允许相邻相同盘子一起移动
 *递归终止条件：如果深度为0，直接返回
 *
*当ok为真时：
如果是最后一层（dep==1）：分别移动该尺寸的盘子
否则执行标准汉诺塔三步法，但考虑多个相同尺寸盘子
当ok为假时：
采用另一种移动策略处理相同尺寸的盘子
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define rep(i,n) for(int (i)=1;(i)<=(n);++(i))
using namespace std;

const int N = 25;
int n, d[N], len[N], m, c[N], f[N];
vector<pair<int,int> > ans;

void dfs(int dep, int x, int y, int z, bool ok) {
    if (!dep) return;
    if (ok) if (dep == 1) {
        rep(i,c[dep]-1) ans.push_back({x,z});//将前 c[dep]-1 个相同尺寸的盘子暂时移动到辅助柱子
        ans.push_back({x,y});//将该尺寸的最后一个盘子从柱子 x 移动到目标柱子 y
        rep(i,c[dep]-1) ans.push_back({z,y});//将之前放在辅助柱子 z 上的 c[dep]-1 个盘子移动到目标柱子 y
    } else {
        dfs(dep-1,x,y,z,0);//将上面 dep-1 层的所有盘子从柱子 x 移动到柱子 y
        rep(i,c[dep]) ans.push_back({x,z});//将当前层的所有 c[dep] 个盘子从柱子 x 移动到柱子 z
        dfs(dep-1,y,x,z,0);//将之前移动到柱子 y 的 dep-1 层盘子移动到柱子 x
        rep(i,c[dep]) ans.push_back({z,y});//将第 dep 层的所有盘子从柱子 z 移动到目标柱子 y
        dfs(dep-1,x,y,z,f[dep-1]);//将剩下的 dep-1 层盘子从柱子 x 移动到柱子 y
    } else {
        dfs(dep-1,x,z,y,0);
        rep(i,c[dep]) ans.push_back({x,y});//批量移动相同尺寸的盘子
        dfs(dep-1,z,y,x,0);
    }
}



int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    rep(i,n) cin >> d[i];
    reverse(d + 1, d + n + 1);
    rep(i,n) len[i] = d[i];
    m = unique(len + 1, len + n + 1) - len - 1;
    rep(i,n) rep(j,m) if (len[j] == d[i]) c[j]++;//统计每种尺寸盘子的数量
    rep(i,n) if (d[i] == d[i - 1]) {//标记哪些尺寸有重复盘子
        rep(j,m) if (len[j] == d[i]) f[j] = 1;
    }
    dfs(m, 1, 3, 2, f[m]);//从第m层开始，1号柱子到3号柱子，2号作为辅助柱子
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    return 0;
}