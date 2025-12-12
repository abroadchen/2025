//
// Created by Psy.C on 2025/12/12.
//
/*
*用于判断队伍x的排名情况：
返回0：队伍x肯定能获得一等奖
返回1：队伍x肯定不能获得任何奖项
返回2：队伍x可能获得一等奖
 *
 *m(总队伍数)、k(已知获奖队伍数)、t(临时变量)
*从输入读取参赛队伍数量n
设置c1为已知获奖队伍数k
设置c2为剩余可获奖队伍数(m-k)
 *t1(剩余已知获奖队伍数)、t2(剩余未知获奖队伍数)、t3(未知队伍数)
 *
*循环读取t个提交记录的队伍编号x
如果x为0，表示未知队伍，t3加1
如果x在已知获奖队伍中，t1减1
如果x在未知队伍中，t2减1
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

int n;
struct node { int mn, mx; } z[N];//每个队伍可能的得分范围
int f(const int x) {
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (i != x) {
            if (flag && z[x].mn >= z[i].mx) continue;
            flag = false; break;
        }
    }
    if (flag) return 0;
    flag = true;
    for (int i = 0; i < n; ++i) {
        if (i != x) {
            if (flag && z[x].mx >= z[i].mn) continue;
            flag = false; break;
        }
    }
    if (flag) return 2;
    return 1;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int m, k, t, c1, c2; cin>>m>>k;
    bool vis[N] = {};//标记哪些队伍已知获奖
    string str;//队伍名称
    int fac[N];//已知获奖队伍的编号
    for (int i = 0; i < k; ++i) {
        cin>>fac[i];
        vis[fac[i]] = true;
    }
    cin>>n; c1 = k, c2 = m - k;
    for (int i = 0; i < n; ++i) {
        int t1 = c1, t2 = c2, t3 = 0;
        cin >> str >> t;//题目数
        for (int j = 0, x; j < t; ++j) {
            cin>>x;
            if (x == 0) t3++;
            else if (vis[x]) t1--;
            else t2--;
        }
        int t4 = c1 - t1;//当前队伍至少超过的队伍数
        const int t5 = t2;
        if (t3) {//存在未知队伍的提交记录
            t4 += min(t1, t3);
            z[i].mn = c1 - t1; z[i].mx = t4;
            if (t5 < t3) z[i].mn += t3 - t5;//剩余未知队伍数少于未知提交数
        } else z[i].mx = z[i].mn = t4;//不存在未知队伍提交
    }
    for (int i = 0; i < n; ++i) cout << f(i) << '\n';
    return 0;
}