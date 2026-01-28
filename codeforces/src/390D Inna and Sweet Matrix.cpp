//
// Created by Psy.C on 2026/1/28.
//
/**
* n, m: 网格尺寸 (n×m)
k: 需要处理的路径数量
l, i: 循环变量
ans: 累计得分
cnt: 已处理的路径计数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

//从 (1,1) 到 (x,y) 的路径
void out(const int x, const int y) {
    //先沿第一行向右走到 (1,y)
    for (int i = 1; i <= y; ++i) cout << "(1," << i << ") ";
    //再沿第y列向下走到 (x,y)
    for (int i = 2; i <= x; ++i) cout << "(" << i << ',' << y << ") ";
    cout << '\n';
}


int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    int l, i, ans = 0, cnt = 0;
    for (l = 2; ; ++l) {//遍历所有可能到达的点 (i, l-i)
        for (i = 1; i <= n && i < l; ++i) {
            if (l - i > m) continue;
            ans += l - 1;//每个点 (i, l-i) 贡献 l-1 分
            cnt++;
            if (cnt >= k) break;//一旦找到 k 条路径就停止
        }
        if (cnt >= k) break;
    }
    cout << ans << '\n';
    for (; i >= 1; --i) {
        if (l - i > m) break;
        out(i, l - i);
    }
    l--;
    for (; l >= 2; --l) {
        for (i = 1; i < l && i <= n; ++i) {
            if (l - i > m) continue;
            out(i, l - i);
        }
    }
    return 0;
}