//
// Created by Psy.C on 2026/9/18.
//
/**
nxt[i]：a[i] 这个值下一次出现在序列中的下标；若没有则为一默认大值（这里是 w[] 初始 0x3f 会影响，实际靠后续处理）。
w[v]：值 v 最近一次（从右往左扫时）出现的位置，用于构造 nxt。
s：当前在缓存中的元素的集合，按 nxt[i]（即下一次出现位置）排序，这样 s 的末尾就是"下一次出现最晚"的元素 → 最优淘汰它
从右往左扫：w[v] 存"值 v 在当前位置 i 右侧最近一次出现的位置"。
nxt[i] = w[a[i]]：记录当前元素的下一次出现位置。
之后更新 w[a[i]] = i，继续向左。
初始 w[] = 0x3f（一个很大的数），表示该值之后不再出现 → nxt[i] 也会是很大的值（对不再次出现的元素）
(a) 元素 a[i]（下标 i）已在缓存中 s.contains(i)：

说明这次访问命中缓存，不计数（ans 不变）。
但该元素"下一次出现位置"已经变成 nxt[i]，需要更新它在 set 中的排序位置：s.erase(i) 再 s.insert(nxt[i])。
注意：这里 s 存的是下标，而现在插入了 nxt[i]（它不是原下标 i），这在逻辑上有点混乱——因为这可能是想维护"下一个需要被淘汰的关键点"。我们下面细讲。
(b) 元素不在缓存 且缓存未满 s.size() < k：

未命中，++ans，把 nxt[i]（下一次出现位置）插入缓存集合 s。
(c) 不在缓存 且缓存已满：

淘汰 --s.end()：即集合中最大的元素（按存的内容）。删除它腾出一个槽，再插入 nxt[i]，++ans
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 4e5+10;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int w[N], a[N], nxt[N];
set<int> s;
int main() {
    int n, k; rd(n); rd(k);
    memset(w, 0x3f, sizeof w);
    for (int i = 1; i <= n; ++i) rd(a[i]);
    for (int i = n; i >= 1; --i) {
        nxt[i] = w[a[i]];
        w[a[i]] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (s.contains(i)) {
            s.erase(i); s.insert(nxt[i]);
            continue;
        }
        if (s.size() < k) {
            ++ans;
            s.insert(nxt[i]);
        } else {
            s.erase(--s.end());
            s.insert(nxt[i]);
            ++ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}