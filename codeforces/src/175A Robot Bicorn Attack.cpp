//
// Created by Psy.C on 2025/11/29.
//
/*
*a, b, c: 存储三个分割部分的数值
res: 当前分割方案的和
ans: 记录最大和，初始化为-1
 *
*将字符串str中从位置l到r的字符转换为整数
逐位处理，每一位乘以10并加上当前位数字
str[i] - '0' 将字符转换为对应数字
 *
*l1: 第一部分长度 = i - 0 + 1 = i + 1
l2: 第二部分长度 = j - (i + 1) + 1 = j - i
l3: 第三部分长度 = (len - 1) - (j + 1) + 1 = len - 1 - j
 *
 *剪枝优化：如果任何一部分长度超过7位，则跳过（因为超过1e6）
 *如果某部分以'0'开头且长度不为1，则是无效数字（如"001"）
 *
 *
*for (int i = 0; i < len; ++i) {
    for (int j = i + 1; j < len - 1; ++j) {
        const int l1 = i + 1, l2 = j - i, l3 = len - 1 - j;
        // l1, l2, l3 在每次循环迭代时都会重新创建和初始化
    }
    // l1, l2, l3 在这里已经销毁
}
 *
*int l1, l2, l3;  // 在外部声明，整个函数作用域内有效
for (int i = 0; i < len; ++i) {
    // l1, l2, l3 已经存在，但值还是上次循环的值！
    for (int j = i + 1; j < len - 1; ++j) {
        // 如果不手动更新，l1, l2, l3 还是旧值
    }
}
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr int inf = 1e6;
char str[35];
ll a, b, c, res, ans = -1;

ll get(const int l, const int r) {
    ll t = 0;
    for (int i = l; i <= r; ++i) t = t * 10 + (str[i] - '0');
    return t;
}

int main() {
    fast;
    cin >> str;
    const int len = static_cast<int>(strlen(str));
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len - 1; ++j) {
            const int l1 = i - 0 + 1, l2 = j - (i + 1) + 1, l3 = len - 1 - (j + 1) + 1;
            if (l1 > 7 || l2 > 7 || l3 > 7) continue;
            if ((str[0] == '0' && l1 != 1) || (str[i+1] == '0' && l2 != 1) ||
                (str[j+1] == '0' && l3 != 1)) continue;
            a = get(0, i); b = get(i+1, j); c = get(j+1, len-1);
            if (a > inf || b > inf || c > inf) continue;
            res = a + b + c;
            if (res > ans) ans = res;
        }
    }
    cout << ans << '\n';
    return 0;
}