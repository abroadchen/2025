//
// Created by Psy.C on 2026/2/6.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

bool vis[N];//标记合数
void init() {//建立质数表
    memset(vis, false, sizeof(vis));
    vis[1] = true;//1既不是质数也不是合数
    for (ll i = 2; i <= N-10; ++i) {
        if (!vis[i])//未被标记则为质数
            if (i*i < N-10)//标记所有质数的平方及以上的倍数为合数
                for (ll j = i*i; j <= N-10; j += i)
                    vis[j] = true;
    }
}

int main() {
    fast;
    init();
    int n; cin >> n;
    //a[N]存储数组元素，id[N]存储值到位置的映射
    int a[N], id[N];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        id[a[i]] = i;
    }
    //x[], y[]记录交换操作，p记录操作次数
    int x[N*5], y[N*5], p = 0;
    for (int i = 1; i <= n; ++i) while (id[i] != i) {//目标值i不在正确位置
        int j = i;
        while (vis[id[i]-j+1] != 0) j++;//使得id[i]-j+1不是合数
        x[p] = j; y[p] = id[i];//记录交换位置j和id[i]
        a[id[i]] = a[j]; id[a[j]] = id[i];//更新数组和映射关系
        a[j] = i; id[i] = j;
        p++;
    }
    cout << p << '\n';
    for (int i = 0; i < p; ++i) cout << x[i] << ' ' << y[i] << '\n';
    return 0;
}