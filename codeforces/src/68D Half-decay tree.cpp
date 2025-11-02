//
// Created by Psy.C on 2025/11/1.
//
/*
*h: 树的高度
q: 操作次数
x, y: 临时变量，用于输入
str: 操作类型字符串
a: 用map存储树节点的值，键为节点编号，值为节点值
s: 计算结果的累积和
 *
*t: 当前访问的节点编号
k: 到达当前节点时已经累积的最小支配值
d: 当前节点的深度（根节点深度为0）
*叶节点处理：如果 t >= (1 << h)，说明是叶节点或更深的节点，更新 k 值
剪枝条件：如果节点不存在或节点值小于等于累积值，则计算贡献并返回
递归处理：否则继续递归处理左右子树，传递更新后的参数
 *
*add操作 (str[0] == 'a')：

读取节点 x 和增加值 y
对节点 x 及其所有祖先节点（通过 x >>= 1 向上遍历）都增加 y
查询操作 (str[0] != 'a')：

初始化结果 s = 0
从根节点开始DFS计算结果
输出计算结果，保留8位小数
 *
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
using namespace std;

int h, q, x, y;
string str;
map<int, int> a;
double s;

void dfs(int t, int k, int d) {
     if (t >= (1 << h)) k = max(k, a[t]);
     if (!a.count(t) || a[t] <= k) {
          s += k * 1. / (1 << d);
          return;
     }
     dfs(t * 2, max(k, a[t] - a[t * 2]), d + 1);
     dfs(t * 2 + 1, max(k, a[t] - a[t * 2 + 1]), d + 1);
}

int main() {

     cin.tie(nullptr)->sync_with_stdio(false);
     cin >> h >> q;
     while (q--) {
          cin >> str;
          if (str[0] == 'a') {
               for (cin >> x >> y; x; x >>= 1) a[x] += y;
          } else {
               s = 0;
               dfs(1, 0, 0);
               cout << setprecision(8) << fixed << s << '\n';
          }
     }
     return 0;
}