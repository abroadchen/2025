//
// Created by Psy.C on 2026/2/26.
//
/**
h：树的高度
n：目标节点编号
ans：答案计数器

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll h, n, ans;

/**
 *
 * @param q 当前区间的左右边界
 * @param w
 * @param vis 访问方向（0左1右）
 * @param hi 当前深度
 * @param sum 当前层的节点数
 */
void dfs(const ll q, const ll w, const int vis, const int hi, const ll sum) {
    if (hi == h) return;//达到树的最大深度
    const ll mid = (q + w) >> 1;
    if (vis == 0) {//当前是向左访问
        if (n <= mid) {//向左子树走，累加左侧节点数
            ans += (sum*2 - 2)/2 + 1;
            dfs(q, mid, 0, hi+1, sum/2);
        } else {//向右子树走，计数器加1
            ans++;
            dfs(mid+1, w, 1, hi+1, sum/2);
        }
    } else {
        if (n <= mid) {
            ans++;
            dfs(q, mid, 0, hi+1, sum/2);
        } else {
            ans += (sum*2 - 2)/2 + 1;
            dfs(mid+1, w, 1, hi+1, sum/2);
        }
    }
}

ll n1, n2;
int main() {
    fast;
    cin >> h >> n; ans = 0; n1 = 1; n2 = 1;
    for (int i = 0; i < h; ++i) n2 *= 2;//完全二叉树的叶子节点数 2^h
    ///根据n与根节点左右子树的分界点m的关系决定初始走向
    if (const ll m = (n1+n2)/2; n <= m) {
        ans++;
        dfs(n1, m, 0, 1, n2/2);
    } else {
        ans += (n2*2-2)/2 + 1;
        dfs(m+1, n2, 1, 1, n2/2);
    }
    cout << ans << '\n';
    return 0;
}