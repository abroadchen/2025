//
// Created by Psy.C on 2026/2/1.
//
/**
* a1：第一条直角边的长度，从1开始枚举
a2：第二条直角边的长度，通过勾股定理计算
 *
*按比例缩放构造相似三角形
b1/b = a1/a，b2/b = a2/a
即：b1 = a1*b/a，b2 = a2*b/a
 *
*B(-b2, b1)
      *
      |\
      | \
      |  \  b
      |   \
      |    \
      *-----* A(a1, a2)
     O(0,0)
 *
*绕原点逆时针旋转90°的变换：
(x, y) → (-y, x)
 *
*如果 a2 == a1 * b / a，即 a2 * a == a1 * b：
这时会出现向量线性相关的情况
 *
 *
*时间复杂度：O(a)，枚举a1的所有可能值
空间复杂度：O(1)，只使用常数额外空间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b; cin >> a >> b;
    for (int a1 = 1, a2 = 1, b1, b2; a1 < a; ++a1) {
        a2 = static_cast<int>(sqrt(a*a - a1*a1));
        if (a*a == a1*a1 + a2*a2) {//验证(a1, a2, a)是否构成直角三角形
            b1 = a1*b/a, b2 = a2*b/a;
            //验证(b1, b2, b)是否构成直角三角形
            //确保两个三角形不重叠
            if (b*b == b1*b1 + b2*b2 && a2 != b1) {
                cout << "YES\n";
                cout << "0 0\n";
                cout << a1 << ' ' << a2 << '\n';
                cout << -b2 << ' ' << b1 << '\n';
                return 0;
            }
        }
    }
    cout << "NO\n";
    return 0;
}