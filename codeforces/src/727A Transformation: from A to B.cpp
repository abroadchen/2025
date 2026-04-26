//
// Created by Psy.C on 2026/4/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b;///目标值和起始值
vector<int> v;///变换过程中经过的数值
int main() {
    fast;
    cin >> a >> b;
    while (b != a) {
        //b的最后一位是1
        if (b%10 == 1) { v.push_back(b); b/=10; }//去掉最后一位数字
        else if (b%2 == 0) { v.push_back(b); b/=2; }
        else { cout << "NO\n"; return 0; }//b末位不是1且不是偶数
        if (b < a) { cout << "NO\n"; return 0; }
    }
    v.push_back(b);//将最终的b值（也就是a）加入数组
    cout << "YES\n";
    cout << v.size() << '\n';
    for (int i = v.size()-1; i >= 0; --i) cout << v[i] << ' ';//倒序输出变换路径
    return 0;
}