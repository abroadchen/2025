//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
坐标 (行, 列)
(货物id, 行, 列)
第 2 行：向右走（(2,1)→(2,2)→...→(2,n)）。
撞到右边界 (2,n) 后，下到 (3,n)。
第 3 行：向左走（(3,n)→...→(3,2)→(3,1)）。
撞到左边界 (3,1) 后，上到 (2,1)。
a[row][col] 存该格的货物编号，0 表示空。
返回该格是否为空
判断条件：货物 id 的起点 s[id] 和终点 t[id] 行差为 1、列相同（即起点在第2行、终点在第1行，或起点在第3行、终点在第4行，上下相邻同列）。
若成立：
记录操作 (id, 终点行, 终点列)；
把起点格和终点格的 a 都清 0（货物被移除）。
返回 true。
含义：当货物正好在终点正下方/正上方相邻时，直接"推上去/下去"到终点并移出棋盘
遍历第 2、3 行所有格子。
若当前格有货物：
先尝试 check(id)：如果它正好可以"落位"到相邻的终点，就移除它。
否则，看它沿环线的下一格是否为空：若空，把它沿环形路径推一格，更新起点 s[id]，记录操作。
只要有任一货物移动或落位，ok=1，说明本轮有进展。
rot 返回是否有进展 → while(rot()){} 会一直执行直到某轮完全没有可动的货物才停
读入 4×n 棋盘。
对于有货物的格子：
如果在 第 1 或第 4 行 → 记为该货物 id 的终点 t[id]。
如果在 第 2 或第 3 行 → 记为该货物 id 的起点 s[id]
一直执行 rot() 直到某轮没有任何移动/落位发生。
while 条件为真就继续；rot 返回 false 时循环结束，说明到达稳定状态（无法再推进）
tag=1 假设棋盘全空，遍历检查：只要还有任一格非空，tag=0。
若 !tag（有残货）→ 输出 -1，表示无解。
否则（棋盘全空，全部货物都移走了）：
输出操作总数 sz；
依次输出每个操作 (货物id, 行, 列)（表示把该货物放进/移到的格）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (i=j; i<=(k); i++)
#define ti tuple<int,int>
#define t3 tuple<int,int,int>
using namespace std;

constexpr int N = 205;

int n;
ti getn(const ti &pos) {
    int x = get<0>(pos), y = get<1>(pos);
    if (x == 2) {
        if (y == n) return {3,n};
        return {2,y+1};
    }
    if (y == 1) return {2,1};
    return {3,y-1};
}
int a[5][N];
bool isempty(const ti &pos) { return !a[get<0>(pos)][get<1>(pos)]; }


ti s[N], t[N];
vector<t3> ans;
bool check(const int &id) {
    if (abs(get<0>(s[id])-get<0>(t[id])) == 1 && get<1>(s[id]) == get<1>(t[id])) {
        ans.emplace_back(id, get<0>(t[id]), get<1>(t[id]));
        a[get<0>(s[id])][get<1>(s[id])] = a[get<0>(t[id])][get<1>(t[id])] = 0;
        return true;
    }
    return false;
}
bool rot() {
    bool ok = 0; int i, j;
    rep(i,2,3) rep(j,1,n) {
        if (!a[i][j]) continue;//空格跳过
        ti nxt = getn({i,j});//该货物的下一格
        if (check(a[i][j])) ok = 1;//能直接落位就落位
        else if (isempty(nxt)) {//否则，若下一格为空
            int id = a[i][j];
            ans.emplace_back(id, get<0>(nxt), get<1>(nxt));//记录移动
            a[i][j] = 0;//原格清空
            a[get<0>(nxt)][get<1>(nxt)] = id;//移到下一格
            s[id] = nxt;// 更新该货物起点
            ok = 1;
        }
    }
    return ok;//本轮是否有任何进展
}

int m, i, j;
int main() {
    fast;
    cin >> n >> m;
    rep(i,1,4) rep(j,1,n) {
        cin >> a[i][j];
        if (a[i][j]) {
            if (i == 1 || i == 4) t[a[i][j]] = {i,j};
            else s[a[i][j]] = {i,j};
        }
    }
    while (rot()) {}
    bool tag = 1;
    rep(i,1,4) {
        rep(j,1,n) if (a[i][j]) { tag = 0; break; }
        if (!tag) break;
    }
    if (!tag) cout << "-1\n";
    else {
        int sz = ans.size(); cout << sz << '\n';
        for (auto p : ans)
            cout << get<0>(p) << ' ' << get<1>(p) << ' ' << get<2>(p) << '\n';
    }
    return 0;
}