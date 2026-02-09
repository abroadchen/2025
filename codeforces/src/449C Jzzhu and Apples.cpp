//
// Created by Psy.C on 2026/2/9.
//
/**
素数筛选：O(N log log N)
配对过程：外层循环O(π(N))，内层循环累计O(N)，总体O(N)
总体：O(N log log N)

优先处理大倍数：3i及以上倍数优先（因为它们可能已被其他小素数处理）
确保素数参与：i本身必须参与配对
特别处理2倍：2i是特殊的（偶数倍），需要特殊判断是否已访问
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
#define N 100007
using namespace std;

bool pri[N], vis[N];
int n;
queue<int> q;//配对的队列
vector<ii> ans;//配对结果

int main() {
    fast;
    memset(pri,true,sizeof(pri));//所有数为素数
    pri[0] = pri[1] = false;//0和1不是素数
    for (int i = 2; i < N; ++i) {
        if (!pri[i]) continue;
        for (int j = i*2; j < N; j += i) pri[j] = false;//所有倍数标记为非素数
    }
    cin >> n;
    for (int i = n; i >= 2; --i) {
        if (!pri[i]) continue;
        //将3i, 4i, 5i, ... (即3*i的倍数)加入队列（如果未访问）
        for (int j = 3*i; j <= n; j += i)
            if (!vis[j]) q.push(j);
        q.push(i);//素数i本身加入队列
        if (2*i <= n && !vis[2*i]) q.push(2*i);
        while (q.size() >= 2) {
            int x = q.front(); q.pop();
            int y = q.front(); q.pop();
            vis[x] = vis[y] = true;
            ans.emplace_back(x, y);
        }
        while (!q.empty()) q.pop();//清空队列，为下一轮做准备
    }
    cout << ans.size() << '\n';
    for (auto&[fst, snd] : ans) cout << fst << ' ' << snd << '\n';
    cout << '\n';
    return 0;
}