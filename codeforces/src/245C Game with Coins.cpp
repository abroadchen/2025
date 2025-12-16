//
// Created by Psy.C on 2025/12/16.
//
/*
 *只有奇数个节点才能构成有效的完全二叉树
 *
 *a存储每个节点的值，ans存储操作次数
*当前节点是奇数节点（右子节点）且值大于0时：
x = (i-1)/2 计算父节点索引
当前节点值减1
父节点值减1（如果大于0）
父节点的左子节点值减1（如果大于0）
操作次数加1
*当前节点是偶数节点（左子节点）且值大于0时：
x = i/2 计算父节点索引
当前节点值减1
父节点值减1（如果大于0）
父节点的右子节点值减1（如果大于0）
操作次数加1
 *最后处理根节点：根节点剩下的值就是还需要的操作次数
 *
*外层循环：O(n)
内层while循环：取决于节点值大小
总体复杂度：可接受范围
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    if (n <= 2 || n % 2 == 0) { cout << -1 << '\n'; return 0; }
    int a[N], ans = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i >= 2; --i) {
        while (a[i] && i&1) {
            const int x = (i - 1) / 2;
            a[i]--;
            a[x] -= a[x] ? 1 : 0;
            a[x<<1] -= a[x<<1] ? 1 : 0;
            ans++;
        }
        while (a[i] && i % 2 == 0) {
            const int x = i / 2;
            a[i]--;
            a[x] -= a[x] ? 1 : 0;
            a[x<<1|1] -= a[x<<1|1] ? 1 : 0;
            ans++;
        }
    }
    ans += a[1];
    cout << ans << '\n';
    return 0;
}