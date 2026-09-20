//
// Created by Psy.C on 2026/9/20.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[30];
void get(int s) {
    int t = (s/50)%475;//伪随机种子
    for (int i = 0; i < 25; ++i) {
        t = (t*96 + 42) % 475;//递推伪随机数
        a[i] = t + 26;//映射到 26~500
    }
    sort(a, a + 25);
}

int p;
bool check() {
    int l = 0, r = 24, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (a[mid] == p) return true;
        if (a[mid] > p) { r = mid - 1; continue; }
        l = mid + 1;
    }
    return false;
}

//p:目标分数, x:当前分数, y:分数下限
int x, y, now, ans;
int main() {
    fast;
    cin >> p >> x >> y; now = x;//保存初始分数（用于最后算赢了几场）
    while (x >= y) x -= 50;//把 x 降到刚好小于 y（界限下限以下）
    while (x < y) x += 50;//再升到 ≥ y（得到 x 在 [y, y+50) 内）
    while (true) {
        get(x);//用当前 x 生成榜单
        if (check()) break;//若 p 出现在榜单里，就停
        x += 50;//否则分数 +50
    }
    while (now < x) {
        ans++;//统计赢了 ans 场
        now += 100;//每次赢一场加 100
    }
    cout << ans;
    return 0;
}