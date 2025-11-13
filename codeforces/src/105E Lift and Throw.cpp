//
// Created by Psy.C on 2025/11/13.
//
/*
 *布尔数组f，用于记忆化搜索，避免重复计算
 *
*定义模板类_Lambda_t，用于支持递归lambda表达式
lexp：存储lambda表达式
构造函数：接受并存储lambda表达式
重载()运算符：支持递归调用
 *定义lexp函数模板，用于创建可递归调用的lambda表达式
 *
*a,b,c：三个初始值
ma,mb,mc：三个移动范围参数
ta,tb,tc：三个传送范围参数
 *
*$：递归调用自身
a,b,c：当前三个值
sa,sb,sc：三个状态标志
 *
*边界条件：如果有任何值为负，返回0
如果有重复值或状态已访问过，返回0
标记当前状态已访问
*计算最小值减1作为下界（至少为0）
初始化返回值为三个值中的最大值（不超过N的值）
*如果a不超过N且状态允许移动：
在[a-ma, a+ma]范围内尝试移动a
更新最大值
*如果状态允许传送：
如果a与b相差1，将b传送到N+1位置
如果a与c相差1，将c传送到N+1位置
*如果未传送但可以接收传送：
在[a-ta, a+ta]范围内接收从b或c传送来的值

sa ^ 1  // 翻转移动权限位
sa ^ 2  // 翻转接收权限位
sa ^ 4  // 翻转传送权限位

 */
#include <iostream>
#include <algorithm>
using namespace std;

constexpr int N = 42, M = 8;
bool f[N+5][N+5][N+5][M][M][M];

template<typename T> class _Lambda_t {
    T lexp;
public:
    template<typename U>
    _Lambda_t(U&& lexp): lexp(static_cast<U&&>(lexp)) {}
    template<typename... U>
    decltype(auto) operator()(U&&... args) {
        return lexp(ref(*this), static_cast<U&&>(args)...);
    }
};
template<typename T>
decltype(auto) lexp(T&& l_exp) {
    return _Lambda_t<typename decay<T>::type>(static_cast<T&&>(l_exp));
}
template<typename T, typename K>
bool ckmax(T& a, const K& b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<typename T, typename K>
bool ckmin(T& a, const K& b) {
    if (b < a) { a = b; return true; }
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int a, b, c, ma, mb, mc, ta, tb, tc;
    cin >> a >> ma >> ta >> b >> mb >> tb >> c >> mc >> tc;

    auto dfs = lexp([&](auto $, int a, int b, int c, int sa, int sb, int sc) -> int {
        if (a < 0 || b < 0 || c < 0) return 0;
        if (a == b || a == c || b == c || f[a][b][c][sa][sb][sc]) return 0;
        f[a][b][c][sa][sb][sc] = true;
        int mn = max(min({a, b, c}) - 1, 0),
        ret = max({a > N ? 0 : a, b > N ? 0 : b, c > N ? 0 : c});

        if (a <= N) {
            if (sa == 1 || sa == 7) {
                for (int i = max(mn, a - ma); i <= a + ma; ++i)
                    ckmax(ret, $(i, b, c, sa ^ 1, sb, sc));
            }
            if (sa & 4) {
                if (abs(a - b) == 1) ckmax(ret, $(a, N + 1, c, sa ^ 4, sb, sc));
                if (abs(a - c) == 1) ckmax(ret, $(a, b, N + 1, sa ^ 4, sb, sc));
            }
            if (!(sa & 4) && (sa & 2)) {
                for (int i = max(mn, a - ta); i <= a + ta; ++i) {
                    if (b == N + 1) ckmax(ret, $(a, i, c, sa ^ 2, sb, sc));
                    if (c == N + 1) ckmax(ret, $(a, b, i, sa ^ 2, sb, sc));
                }
            }
        }
        if (b <= N) {
            if (sb == 1 || sb == 7) {
                for (int i = max(mn, b - mb); i <= b + mb; ++i)
                    ckmax(ret, $(a, i, c, sa, sb ^ 1, sc));
            }
            if (sb & 4) {
                if (abs(b - a) == 1) ckmax(ret, $(N + 2, b, c, sa, sb ^ 4, sc));
                if (abs(b - c) == 1) ckmax(ret, $(a, b, N + 2, sa, sb ^ 4, sc));
            }
            if (!(sb & 4) && (sb & 2)) {
                for (int i = max(mn, b - tb); i <= b + tb; ++i) {
                    if (a == N + 2) ckmax(ret, $(i, b, c, sa, sb ^ 2, sc));
                    if (c == N + 2) ckmax(ret, $(a, b, i, sa, sb ^ 2, sc));
                }
            }
        }
        if (c <= N) {
            if (sc == 1 || sc == 7) {
                for (int i = max(mn, c - mc); i <= c + mc; ++i)
                    ckmax(ret, $(a, b, i, sa, sb, sc ^ 1));
            }
            if (sc & 4) {
                if (abs(c - a) == 1) ckmax(ret, $(N + 3, b, c, sa, sb, sc ^ 4));
                if (abs(c - b) == 1) ckmax(ret, $(a, N + 3, c, sa, sb, sc ^ 4));
            }
            if (!(sc & 4) && (sc & 2)) {
                for (int i = max(mn, c - tc); i <= c + tc; ++i) {
                    if (a == N + 3) ckmax(ret, $(i, b, c, sa, sb, sc ^ 2));
                    if (b == N + 3) ckmax(ret, $(a, i, c, sa, sb, sc ^ 2));
                }
            }
        }
        return ret;
    });
    cout << dfs(a, b, c, 7, 7, 7) << '\n';
    return 0;
}