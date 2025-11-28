//
// Created by Psy.C on 2025/11/28.
//
/*
 *返回布尔值，表示当前玩家是否处于必败状态
 *如果 a 为 0，当前玩家获胜，返回 true（表示上一玩家失败）
*交换参数并继续游戏
如果递归调用返回 true（对手处于必败状态），则当前玩家必胜，返回 false
 *
 *当 a 是奇数时，游戏规则简化为判断 b / a 的奇偶性
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

bool dfs(const ll a, const ll b) {
    if (a == 0) return true;
    if (dfs(b % a, a)) return false;
    if (a % 2 == 1) return (b / a) % 2;
    return (b / a) % (a + 1) % 2;
}

int main() {
    fast;
    int t; cin >> t;
    while (t--) {
        ll a, b; cin >> a >> b;
        if (a > b) { const ll c = a; a = b; b = c; }
        cout << (dfs(a, b) ? "Second" : "First") << '\n';
    }
    return 0;
}