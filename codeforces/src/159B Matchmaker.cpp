//
// Created by Psy.C on 2025/11/26.
//
/*
 *笔的统计表 [尺寸][颜色] 笔帽的统计表 [尺寸][颜色]
 *每种尺寸笔的数量 每种尺寸笔帽的数量
 *
*l1[siz]: 尺寸为siz的笔总数
markers[siz][col]: 尺寸为siz、颜色为col的笔数量
*l2[siz]: 尺寸为siz的笔帽数量
caps[siz][col]: 尺寸为siz、颜色为col的笔帽数量
 *
 *第一类匹配：基于尺寸的匹配 (tot)
*l1[i]: 该尺寸笔的数量
l2[i]: 该尺寸笔帽的数量
min(l1[i], l2[i]): 该尺寸下能匹配的最大对数
 *
 *第二类匹配：基于尺寸和颜色的精确匹配 (res)
*markers[i][j]: 尺寸i、颜色j的笔数量
caps[i][j]: 尺寸i、颜色j的笔帽数量
min(markers[i][j], caps[i][j]): 该尺寸颜色下能精确匹配的对数
 *
 *
*输入处理：O(n + m)
匹配计算：O(N²)
总体：O(n + m + N²)
 *
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
constexpr int N = 1e3;

int main() {
    fast;
    int n, m; cin >> n >> m;
    vvi markers(N + 1, vi(N + 1, 0)), caps(N + 1, vi(N + 1, 0));
    rep(i,N+1) rep(j,N+1) markers[i][j] = caps[i][j] = 0;
    vi l1(N + 1, 0), l2(N + 1, 0);
    rep(i,N+1) l1[i] = l2[i] = 0;
    rep(i,n) {
        int col, siz; cin >> col >> siz;
        ++l1[siz]; ++markers[siz][col];
    }
    rep(i,m) {
        int col, siz; cin >> col >> siz;
        ++l2[siz]; ++caps[siz][col];
    }
    int tot = 0, res = 0;
    for (int i = 1; i <= N; ++i) tot += min(l1[i], l2[i]);
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
        res += min(markers[i][j], caps[i][j]);
    }
    cout << tot << " " << res << '\n';
    return 0;
}