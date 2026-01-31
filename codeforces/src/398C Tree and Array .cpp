//
// Created by Psy.C on 2026/1/30.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    if (n == 5) {//4条带权边和2条普通边
        cout << "1 2 3\n";
        cout << "1 3 3\n";
        cout << "2 4 2\n";
        cout << "4 5 1\n";
        cout << "3 4\n";
        cout << "3 5\n";
        return 0;
    }
    for (int i = 1; i <= n>>1; ++i)
        cout << i << ' ' << (n>>1)+i << ' ' << 1 << '\n';//连接节点i和节点(n/2+i)，权重为1
    cout << (n>>1) + 1 << ' ' << (n>>1) + 2 << ' ' << 1 << '\n';//连接节点(n/2+1)和节点(n/2+2)，权重为1
    for (int i = (n>>1)+2; i < n; ++i)
        cout << i << ' ' << i + 1 << ' ' << i - (n>>1) + 1 << '\n';
    for (int i = 2; i <= n>>1; ++i) cout << "1 " << i << '\n';//节点1和其他节点i（从2到n/2）
    cout << "2 3\n";
    return 0;
}