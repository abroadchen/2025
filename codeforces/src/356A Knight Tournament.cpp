//
// Created by Psy.C on 2026/1/17.
//
// f[N]: 存储每个位置的最终值
// nxt[N]: 存储下一个未处理位置的索引（跳跃指针）
// vis[N]: 标记是否已访问过该位置
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 300007
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int f[N], nxt[N], vis[N];
    for (int i = 1; i <= n; ++i) {
        f[i] = i;//每个位置的值等于其索引
        nxt[i] = i + 1;//下一位置是i+1（形成链表）
        vis[i] = 0;//所有位置都未访问
    }
    while (m--) {
        int l, r, x; cin >> l >> r >> x;//区间[l,r]和目标值x
        for (int i = l; i < x;) {
            if (vis[i] == 0 && i != x) { vis[i] = 1; f[i] = x; }//设置值为x
            //保存当前位置 移动到下一位置 将原位置的next指向x（跳过中间元素）
            const int t = i; i = nxt[i]; nxt[t] = x;
        }
        for (int i = x; i <= r;) {
            if (vis[i] == 0 && i != x) { vis[i] = 1; f[i] = x; }
            const int t = i; i = nxt[i]; nxt[t] = nxt[r];//将原位置的next指向r之后的位置
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (i != 1) cout << ' ';//不是第一个元素，输出空格
        //值未改变，输出0 否则输出新值
        if (f[i] == i) cout << '0'; else cout << f[i];
    }
    cout << '\n';
    return 0;
}