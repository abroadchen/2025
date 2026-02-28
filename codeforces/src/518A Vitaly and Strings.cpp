//
// Created by Psy.C on 2026/2/28.
//
/**
a：下界字符串
b：上界字符串
将a复制给c（这将是我们的候选字符串）
获取字符串长度

从最后一个字符开始向前遍历（从右到左）
对于每个位置i：
当字符小于'z'时，递增位置i的字符
递增后，检查c < b
如果是，我们找到了答案并返回
如果达到'z'，将其环绕到'a'并继续处理左边的下一个位置

时间复杂度： 平均情况O(n)，其中n是字符串长度。 空间复杂度： O(n)用于存储字符串
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string a, b;
int main() {
    fast;
    cin >> a >> b;
    string c = a;
    const int n(a.length());
    for (int i = n-1; i >= 0; --i) {
        while (c[i] < 'z') {
            c[i]++;
            if (c < b) {
                cout << c << '\n';
                return 0;
            }
        }
        if (c[i] == 'z') c[i] = 'a';
    }
    cout << "No such string";
    return 0;
}