//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
输出问句 ? xl yl xr yr，询问是否存在一条从 (xl,yl) 到 (xr,yr) 的合法路径。
读入评测端的回答 Y（有路）或 N（无路）。
注意 endl 会刷新输出缓冲区，交互题必须及时刷新
dis 计算两点间曼哈顿距离（横向+纵向步数）。这在题目中保证是一个合法的可达下界——如果两点曼哈顿距离太大，必然无路
起点在 (1,1)，终点在 (n,n)。要走的总步数是 2n-2（恒定的，因为是曼哈顿最短路径长度）。
dis(x,y,n,n) 是当前点到终点的曼哈顿距离。循环条件是 dis >= n，即只要还剩至少 n 步，就先走前半程。
贪心策略：优先尝试向右（R）——
若 y+1 ≤ n 且从 (x, y+1) 能到达 (n,n)（query 返回 Yes），就向右走。
否则必须向下走（D）。
每走一步记录到 ord[++cnt]（从头开始放）。
为什么前半程走 n 步？ 因为终点 (n,n) 与起点 (1,1) 的曼哈顿距离是 2n-2，把路径"对半分"——前半程走到底部或右部的中间某处，后半程补完
起点改为 (n,n)，向 (1,1) 反推。
cnt 重置为 2*n-1（从末尾倒着放）。
循环条件 dis(x,y,1,1) >= n：同样走约 n 步。
反向贪心：优先尝试向上（即 D，因为反向来看向上 = 之前的向下）——
若 x-1 > 0 且从 (1,1) 能到达 (x-1,y)（query 返回 Yes），则 x--，记录（反向的）D。
否则 y--，记录 R。
这样后半程从终点倒着填进 ord 的末尾
输出 !  加完整路径（2n-2 个 R/D），结束交互
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+10;

char s[30];
bool query(int xl, int yl, int xr, int yr) {
    cout << "? " << xl << ' ' << yl << ' ' << xr << ' ' << yr << endl;
    cin >> s;
    if (s[0] == 'Y') return true;
    return false;
}
int dis(int xl, int yl, int xr, int yr) {
    return abs(xr-xl) + abs(yr-yl);
}

int n;
char ord[N];
int main() {
    fast;
    cin >> n;
    int x = 1, y = 1, cnt = 0;
    while (dis(x,y,n,n) >= n) {
        if (y+1 <= n && query(x,y+1,n,n)) { y++; ord[++cnt] = 'R'; }
        else { x++; ord[++cnt] = 'D'; }
    }
    cnt = 2*n-1; x = n, y = n;
    while (dis(x,y,1,1) >= n) {
        if (x-1 > 0 && query(1,1,x-1,y)) { x--; ord[--cnt] = 'D'; }
        else { y--; ord[--cnt] = 'R'; }
    }
    cout << "! ";
    for (int i = 1; i <= 2*n-2; i++) cout << ord[i];
    return 0;
}