//
// Created by Psy.C on 2026/2/10.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) if (a[i-1] > a[i]) {//第一个降序对
        for (int j = i + 1; j <= n; ++j) {//从第一个降序对之后的位置开始检查
            if (a[j-1] > a[j]) {
                cout << "-1\n";//数组不能通过旋转一个非递减排列得到
                return 0;
            }
        }
        if (a[n] > a[1]) {
            cout << "-1\n";//旋转后仍不是非递减排列
            return 0;
        }
        cout << n - i + 1 << '\n';//旋转次数
        return 0;
    }
    cout << "0\n";
    return 0;
}