//
// Created by Psy.C on 2026/2/18.
//
/**
时间复杂度：O(n)
空间复杂度：O(N)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+1, M = 2e5+1;

int n, f[N], v[N];
void init() {
    cin >> n;
    memset(f, -1, sizeof(f));//不存在边
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        f[x] = y;//x→y的边
        v[x]++, v[y]++;//更新x和y的度数
    }
}

int ans[M];

/**
 *
 * @param b 起始节点
 * @param x 在答案数组中的起始位置
 */
void solve(int b, int x) {
    while (b > 0) {
        ans[x] = b;//将当前节点b放在ans[x]位置
        x += 2;//间隔2个位置放置下一个
        b = f[b];//跳到下一个节点
    }
}

int main() {
    fast;
    init(); solve(f[0], 2);// 从f[0]开始，从位置2开始填充
    for (int i = 1; i <= N-1; ++i) {//遍历所有节点
        if (v[i] == 1 && f[i] >= 0) {//度数为1且有出边的节点 i是链的起点
            solve(i, 1);//从该节点开始，从位置1开始填充 每隔一个位置放置一个节点
            break;//只处理一个
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " \n"[i==n];
    return 0;
}