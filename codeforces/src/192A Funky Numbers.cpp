//
// Created by Psy.C on 2025/12/2.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define f(x) ((x)*(x+1)/2)
using namespace std;


int main() {
    fast;
    int n, j = 1; bool flag = false;//标记是否找到解
    while (cin >> n) {
        flag = false;
        for (int i = 1; f(i) + f(j) <= n; ++i) {//两个三角数之和不超过n就继续
            for (j = i; f(i) + f(j) <= n; ++j) {//j从i开始（保证不重复）
                if (f(i) + f(j) == n) {
                    cout << "YES\n";
                    flag = true;
                    break;
                }
            }
            if (flag) break;//如果找到了解，跳出外层循环
            j = 1;
        }
        if (!flag) cout << "NO\n";
    }
    return 0;
}