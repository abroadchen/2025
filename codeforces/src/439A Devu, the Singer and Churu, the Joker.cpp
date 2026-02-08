//
// Created by Psy.C on 2026/2/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, d; cin >> n >> d;//歌数，活动时间
    //休息所需时间
    if ((n-1)*10 >= d) { cout << "-1"; return 0; }
    int dt = 0;//唱歌总用时
    //t每首歌用时
    for (int i = 1, t; i <= n; ++i) { cin >> t; dt += t; }
    const int r = (n - 1) * 10 + dt > d ? -1 : (d - dt) / 5;
    cout << r;
    return 0;
}