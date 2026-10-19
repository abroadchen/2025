//
// Created by Psy.C on 2026/10/18.
//
/**
设当前环大小为 sz：

如果元素当前在一个奇数位置 t，那么它是不会被这一轮删掉的，且它在"去掉所有偶数位后"的新环中的位置是 (t+1)/2（因为奇数位 1,3,5,...→ 1,2,3,...）。
如果元素当前在偶数位置 t，那么它这一轮一定会被删掉……但代码不是这样结束，而是：
int res = n - t/2;
t += res;
这里的 n 实际扮演"当前环大小 sz"的角色。推导：

当 t 为偶数时，说明在当前环中该元素位于偶数位。
但这里用的不是"删掉"而是跳转到更大的环（反向扩展）。t/2 是它在"每轮删偶数位后剩下来"的压缩环里的位置；n - t/2 是"压缩后剩余元素个数 - 该位置"？这更像是在做约瑟夫环的反向映射
对"每轮删除偶数位、剩者重新编号"的约瑟夫变体，给定原始编号 t，可通过重复：

while 真:
    if t 是奇数: 答案是 (t+1)/2，停
    else: t = t + (当前环大小 - t/2)   // 反向扩展到更大的环
求出"元素最终被删的轮次 / 或最终唯一幸存者所对应的原始位置"。
其中 res = sz - t/2 表示"把当前压缩环的大小 sz 里的位置 t/2，反向映射回上一层更大的环"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

signed main() {
    fast;
    int t = 1;
    while (t--) {
        int n, q; cin >> n >> q;
        for (int i = 1, t; i <= q; ++i) {
            cin >> t;
            while (true) {
                if (t&1) {
                    cout << (t+1)/2 << '\n';
                    break;
                }
                int res = n - t/2;
                t += res;
            }
        }
    }
    return 0;
}