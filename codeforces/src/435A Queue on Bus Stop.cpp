//
// Created by Psy.C on 2026/2/6.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int a[105];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int ans = 0;
    for (int i = 1, use = 0; i <= n; ++i) {
        ans++;//完成一次操作或处理一个组
        use = a[i];//开始使用当前物品
        int j = i + 1;//从当前位置的下一个开始
        while (use + a[j] <= m && j <= n) {//加入下一个物品后是否超出限制m
            use += a[j];//将物品j加入当前组合
            j++;//移动到下一个物品
        }
        if (j > n) break;//所有物品都已处理完毕
        i = j - 1;//跳过了刚刚处理过的物品组
    }
    cout << ans << '\n';
    return 0;
}