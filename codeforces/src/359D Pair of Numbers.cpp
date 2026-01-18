//
// Created by Psy.C on 2026/1/18.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300007
using namespace std;


int main() {
    fast;
    int n, a[N], mx = 0; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> ans;
    for (int i = 1; i <= n;) {//每次跳跃式前进
        int l = i, r = i;//都指向当前位置i
        while (l >= 1 && a[l] % a[i] == 0) l--;//向左扩展
        l++;//指向第一个不能整除的位置，需要调整回来
        while (r <= n && a[r] % a[i] == 0) r++;//向右扩展
        r--;
        if (r - l > mx) {
            ans.clear(); ans.push_back(l);//添加新区间的起始位置
            mx = r - l;
        } else if (r - l == mx) ans.push_back(l);
        i = r + 1;//直接跳到当前区间之后
    }
    cout << ans.size() << ' ' << mx << '\n';
    for (const int an : ans) cout << an << ' ';
    return 0;
}