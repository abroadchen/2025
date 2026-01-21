//
// Created by Psy.C on 2026/1/21.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, k, t, cnt = 0; cin >> n >> m >> k;
    while (n--) {
        cin >> t;//晚餐种类
        if (t == 1) {//吃第一种菜只能用碗
            if (m != 0) m--; else cnt++;//洗碗次数
        } else if (t == 2) {//吃第二种菜优先用盘子再用碗
            if (k != 0) k--; else {
                if (m != 0) m--; else cnt++;
            }
        }
    }
    cout << cnt;
    return 0;
}