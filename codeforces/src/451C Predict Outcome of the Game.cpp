//
// Created by Psy.C on 2026/2/10.
//
/**
时间复杂度：O(q)，因为内层循环最多9次（3×3）
空间复杂度：O(1)

!flag条件确实是有意义的，因为当flag=1时，内层循环不会再执行，外层循环也会停止。
原代码的意图：确实是想用!flag来控制双重循环的提前退出，但由于内层循环的break只跳出一层循环，
所以外层循环的条件!flag在内层循环结束后才被检查。
所以!flag在原代码中是有意义的，只是需要确保一旦找到解就正确退出双重循环
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, d1, d2;

int main() {
    fast;
    int q; cin >> q;
    while (q--) {
        cin >> n >> k >> d1 >> d2;
        if (n % 3) cout << "no\n";
        else {
            int flag = 0;
            for (int s1 = -1; s1 <= 1 && !flag; ++s1)
                for (int s2 = -1; s2 <= 1 && !flag; ++s2) {
                    if (s1 == 0 || s2 == 0) continue;
                    const ll f1 = 2 * s1 * d1 + s2 * d2 + k;
                    if (f1 % 3) continue;
                    const ll w1 = f1 / 3, f2 = -1 * s1 * d1 + s2 * d2 + k;
                    if (f2 % 3) continue;
                    const ll w2 = f2 / 3, f3 = -1 * s1 * d1 + 2 * (-1) * s2 * d2 + k;
                    if (f3 % 3) continue;
                    if (const ll w3 = f3 / 3; w1 + w2 + w3 == k &&
                        w1 >= 0 && w1 <= n/3 && w2 >= 0 && w2 <= n/3 &&
                        w3 >= 0 && w3 <= n/3) {
                        flag = 1;
                        break;
                    }
                }
            cout << (flag ? "yes" : "no") << '\n';
        }
    }
    return 0;
}