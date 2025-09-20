//
// Created by Psy.C on 2025/9/21.
//
/*
*const int N = 503;     // 定义最大节点数
vector<int> adj[N];    // 邻接表，存储图的边
int d[N][N][2];        // 距离数组，d[u][v][turn]表示状态下的距离
int p[N][N][2];        // 父节点数组，用于路径重构
 *
*d[1][n][0] = 0;              // 初始状态：玩家1在节点1，玩家2在节点n，轮到玩家1移动
    queue<pair<int, int> > Q[2]; // 两个队列，分别对应两个玩家的回合
    Q[0].push(pair<int, int>(1, n));  // 将初始状态(1,n)加入队列0
 *
 *
 *
 */
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define sz(x) int((x).size())
using namespace std;
const int N = 503;
vector<int> adj[N];
int d[N][N][2], p[N][N][2];

int main() {
      int n, m; scanf("%d%d", &n, &m);
      while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
      }
      memset(d, -1, sizeof(d));
      d[1][n][0] = 0;
      queue<pair<int, int> > Q[2];
      Q[0].push(pair<int, int>(1, n));

      while (!Q[0].empty()) {
            while (!Q[0].empty()) {//// 玩家1的回合
                  int u = Q[0].front().first, v = Q[0].front().second;
                  Q[0].pop();// 取出当前状态(u是玩家1位置，v是玩家2位置)
                  // 玩家1尝试移动到所有相邻节点
                  for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
                        if (d[*it][v][1] == -1) {
                              d[*it][v][1] = d[u][v][0] + 1;
                              p[*it][v][1] = u;
                              Q[1].push(pair<int, int>(*it, v));
                        }
                  }
            }
            while (!Q[1].empty()) {// 玩家2的回合
                  int u = Q[1].front().first, v = Q[1].front().second;
                  Q[1].pop();
                  for (vector<int>::iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
                        if (d[u][*it][0] == -1 && u != *it) {
                              d[u][*it][0] = d[u][v][1];
                              p[u][*it][0] = v;
                              Q[0].push(pair<int, int>(u, *it));
                        }
                  }
            }
      }

      if (d[n][1][0] == -1) { puts("-1"); return 0; }

      vector<int> res[2];
      res[0].push_back(n);// 路径1从n开始
      res[1].push_back(1);// 路径2从1开始

      int u = n, v = 1;
      while (p[u][v][0]) {
            v = p[u][v][0];// 获取玩家2的前一步位置
            res[1].push_back(v);
            u = p[u][v][1];// 获取玩家1的前一步位置
            res[0].push_back(u);
      }
      // 反转路径使其从起点到终点
      reverse(res[0].begin(), res[0].end());
      reverse(res[1].begin(), res[1].end());

      printf("%d\n", d[n][1][0]);

      for (int i = 0; i < sz(res[0]); ++i) {
            if (i) printf(" ");
            printf("%d", res[0][i]);
      }
      printf("\n");

      for (int i = 0; i < sz(res[1]); ++i) {
            if (i) printf(" ");
            printf("%d", res[1][i]);
      }
      printf("\n");

      return 0;
}