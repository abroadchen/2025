//
// Created by Psy.C on 2025/11/19.
//

#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e5;
int a[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (!flag) cout << " ";//先输出一个空格作为分隔符
        flag = false;
        if (i == n - 1 && a[i] == 1) cout << 2;//最后一个元素且该元素值为1
        else if (i == 0) cout << 1;
        else cout << a[i - 1];//输出前一个位置的元素值
    }
    cout << '\n';
    return 0;
}