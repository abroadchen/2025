//
// Created by Psy.C on 2025/12/1.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100001
using namespace std;

char a[N], b[N];
int cnt = 0;

int main() {
    fast;
    cin >> a >> b;
    const int la = static_cast<int>(strlen(a)),
    lb = static_cast<int>(strlen(b));
    if (la != lb) { cout << "NO" << '\n'; return 0; }
    for (int i = 0; i < la; ++i) if (a[i] != b[i]) cnt++;
    if (cnt != 2) { cout << "NO";  return 0; }//不同的位置数不是恰好2个
    sort(a, a + la); sort(b, b + lb);//是否包含相同的字符集合
    if (strstr(a, b) != nullptr) cout << "YES";
    else cout << "NO";
    return 0;
}