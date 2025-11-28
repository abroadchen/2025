//
// Created by Psy.C on 2025/11/28.
//
/*
*n: 第一组物品数量
m: 第二组物品数量
f[N]: 匹配数组，记录匹配关系
cnt: 匹配成功的对数
ans: 总价值（使用long long）
e[N]: 邻接表，存储图的连接关系
*money: 价值
siz: 大小
num: 编号
定义两个数组 a[N] 和 b[N] 分别存储两组物品
 *
*匈牙利算法的DFS实现，用于二分图最大匹配：
遍历x能连接的所有点
如果该点未被匹配或能通过增广路重新匹配
则建立匹配关系并返回成功
 *
 *num，用于存储大小到索引的映射
 *读入第一组n个物品的信息，并记录原始编号
 *按价值降序排序第一组物品
 *读入第二组m个物品的信息
 *建立大小到排序后索引的映射
 *
*对每个第二组物品，建立可能的匹配关系：
可以匹配大小相等或大1的物品，前提是价值足够
 *初始化匹配数组，-1表示未匹配
 *对每个第一组物品尝试匹配，成功则累加价值和计数
*输出总价值和匹配对数
输出具体的匹配关系（第二组物品编号对应第一组原始编号）
 *
 */
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

typedef long long ll;
constexpr int N = 1e5+9;
int n, m, f[N], cnt;
ll ans{};
vector<int> e[N];
void add(const int u, const int v) { e[u].push_back(v); }

struct node { int money, siz, num; } a[N], b[N];
bool cmp(const node x, const node y) { return x.money > y.money; }

bool dfs(const int x) {
    for (int i = 0; i < e[x].size(); ++i) if (f[e[x][i]] != x) {
        if (f[e[x][i]] == -1 || dfs(f[e[x][i]])) {
            f[e[x][i]] = x;
            return true;
        }
    }
    return false;
}

int main() {
    fast;
    map<int,int> num;
    cin >> n;
    rep(i,n) { cin >> a[i].money >> a[i].siz; a[i].num = i; }
    sort(a + 1, a + n + 1, cmp);
    cin >> m;
    rep(i,m) cin >> b[i].money >> b[i].siz;
    rep(i,n) num[a[i].siz] = i;
    rep(i,m) {
        if (num[b[i].siz + 1] && b[i].money >=
            a[num[b[i].siz + 1]].money) add(num[b[i].siz + 1], i);
        if (num[b[i].siz] && b[i].money >=
            a[num[b[i].siz]].money) add(num[b[i].siz], i);
    }
    for (auto& x : f) x = -1;
    rep(i,n) if (dfs(i)) { ans += a[i].money * 1ll; cnt++; }
    cout << ans << '\n' << cnt << '\n';
    rep(i,m) if (f[i] != -1) cout << i << ' ' <<  a[f[i]].num << '\n';
    return 0;
}