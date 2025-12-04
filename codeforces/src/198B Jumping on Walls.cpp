//
// Created by Psy.C on 2025/12/3.
//
/*
*n: 游戏板长度
k: 跳跃距离
d[N][2]: 访问标记数组，d[pos][row]表示位置pos在行row是否已访问或不可达
 *
*初始化障碍标记：
将字符串中的'X'位置在d数组中标记为1（不可达）
注意字符串索引从0开始，而位置从1开始
 *
 *创建初始状态元组(位置1, 第0行, 时间0)并加入队列
*取出队首元素并解析：
x: 当前位置
y: 当前行（0或1）
t: 当前时间
 *如果位置超过游戏板长度n，说明成功到达终点
*剪枝条件：
如果当前位置小于等于当前时间（会被洪水淹没），跳过
如果当前位置是障碍物，跳过
 *标记当前位置已访问
*生成三种可能的移动并加入队列：
t1: 向后移动一步 (x-1, y, t+1)
t2: 向前移动一步 (x+1, y, t+1)
t3: 跳跃到另一行 (x+k, 1-y, t+1)，其中1-y实现行切换(0↔1)
 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define tu tuple<int,int,int>
using namespace std;

int n, k, d[N][2];
char s[2][N];//存储两行游戏板的状态（'.'表示可通过，'X'表示障碍）
queue<tu> q;

int main() {
    fast;
    cin>>n>>k; cin >> s[0]; cin >> s[1];//输入两行游戏板字符串
    for (int i = 1; i <= n; ++i) {
        if (s[0][i-1] == 'X') d[i][0] = 1;
        if (s[1][i-1] == 'X') d[i][1] = 1;
    }
    tu tp{1,0,0}; q.push(tp);
    while (!q.empty()) {
        tp = q.front();
        const int x = get<0>(tp), y = get<1>(tp),
        t = get<2>(tp); q.pop();
        if (x > n) { cout << "YES\n"; return 0; }
        if (x <= t || d[x][y] == 1) continue;
        d[x][y] = 1;
        tu t1{x-1,y,t+1}, t2{x+1,y,t+1}, t3{x+k, 1-y, t+1};
        q.push(t1); q.push(t2); q.push(t3);
    }
    cout << "NO\n";
    return 0;
}