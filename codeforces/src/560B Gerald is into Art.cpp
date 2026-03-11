//
// Created by Psy.C on 2026/3/12.
//
/**
x, y: 大矩形容器的宽和高
a, b: 第一个小矩形的宽和高
aa, bb: 第二个小矩形的宽和高
条件1: 第二个矩形(aa×bb)可以在大矩形(x×y)中竖直放置
布局1: 第一个矩形水平放置在左侧，第二个矩形在右侧：b ≤ x, a + bb ≤ y
布局2: 第一个矩形水平放置在左侧，第二个矩形在右侧：a ≤ x, b + bb ≤ y
布局3: 第一个矩形垂直放置在底部，第二个矩形在上方：b ≤ y, a + aa ≤ x
布局4: 第一个矩形垂直放置在底部，第二个矩形在上方：a ≤ y, b + aa ≤ x

条件2: 第二个矩形(aa×bb)可以在大矩形(x×y)中水平放置（旋转90度）
同样检查四种可能的布局
标准化处理: 确保每个矩形的宽度 ≥ 高度
这样可以减少需要考虑的情况数量

总共考虑了两种基础布局情况：
第二个矩形竖直放置 (aa×bb)
第二个矩形水平放置 (bb×aa)
每种情况又考虑四种子布局：
第一个矩形水平放，第二个在右边
第一个矩形垂直放，第二个在上面

时间复杂度：O(1)，常数时间
空间复杂度：O(1)，常数空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int x, y, a, b, aa, bb;
int check() {
    if (aa <= x && bb <= y) {
        if (b <= x && a + bb <= y) return 1;
        if (a <= x && b + bb <= y) return 1;
        if (b <= y && a + aa <= x) return 1;
        if (a <= y && b + aa <= x) return 1;
    }
    if (aa <= y && bb <= x) {
        if (b <= x && a + bb <= y) return 1;
        if (a <= x && b + bb <= y) return 1;
        if (b <= y && a + bb <= x) return 1;
        if (a <= y && b + bb <= x) return 1;
    }
    return 0;
}

int flag;
int main() {
    fast;
    cin >> x >> y >> a >> b >> aa >> bb;
    if (x < y) swap(x, y);
    if (aa < bb) swap(aa, bb);
    if (a < b) swap(a, b);
    if (check()) flag = 1;
    if (flag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}