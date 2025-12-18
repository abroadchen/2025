//
// Created by Psy.C on 2025/12/18.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5010
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n; cin >> n;
    vector<int> p[N];
    for (int i = 1, x; i <= n<<1; ++i) {
        cin >> x;
        p[x].push_back(i);
    }
    int flag = 0;
    for (int i = 1; i <= 5000; ++i) {
        if (p[i].size() % 2 == 1) {//每个组的元素个数是否为偶数
            flag = 1; break;
        }
    }
    if (flag == 1) { cout << "-1\n"; return 0; }
    for (int i = 1; i <= 5000; ++i) for (int j = 0; j < p[i].size(); j += 2) {
        cout << p[i][j] << ' ' << p[i][j+1] << '\n';//每次取两个连续元素组成一对输出
    }
    return 0;
}