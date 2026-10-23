//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
vis[q]：位置 q 是否已被分配。
mp[q]：位置 q 所属段的起点编号（最终输出 mp[x]）。
sy[x]：起点为某值时，该段已分配到的最右位置（可继续延伸的位置）。
核心思想：对每个 x，把它归入前面最长的、还有空位的连续区间，保证区间长度不超过 k
输入 n（个数）、k（每段最大长度上限）。对每个 x：

第一步：找到 x 应归属的段起点 j
从 j = x 开始向前（j 递减），条件是 x - j + 1 <= k（确保该段起点 j 到 x 的长度不超 k），找第一个 vis[j] 为真的已占用位置然后 break，再 j++。
结果 j 是该段的起点：即在满足长度≤k 的前提下，尽量把 x 并入前面未被占满的连续区间（复用前面的段尾空位）。
循环结束后 j++ 让 j 落在"第一个空闲的起点"上，即 x 归入以 j 起始的段
第二步：把 j..x 全标记占用，确定 mp[q]
q 从 j 到 x 全部标记 vis=1。
对每个 q，判断前一段（起点 j-1）是否已经延伸到 x：sy[j-1] + j-1 >= x（j-1 这段的最右端已越过 x）——若成立，说明 x 落在前一段的内部（被前一段覆盖），则归入 mp[j-1]；否则归入新段起点 j
第三步：更新 sy[x]
若前一段已覆盖 x：sy[x] 记录这段还剩下多少延伸空间（sy[j-1]+j-1-x，即前段最右端减去 x）。
否则新建一段（起点 j，容量 k）：sy[x] = j+k-1-x，即从 j 起 k 个位置中后面还剩多少
输出 x 归属段的起点编号。若 x 已在前面被覆盖（vis[x] 为真），本轮跳过不重算，直接输出之前定的 mp[x]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n, k;
map<int, bool> vis;
map<int, int> sy, mp;
signed main() {
    fast;
    cin >> n >> k;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (!vis[x]) {
            int j;
            for (j = x; j >= 0 && x - j + 1 <= k; j--)
                if (vis[j]) break;
            j++;
            for (int q = j; q <= x; q++) {
                vis[q] = 1;
                if (sy[j-1]+j-1 >= x) mp[q] = mp[j-1]; else mp[q] = j;
            }
            if (sy[j-1]+j-1 >= x) sy[x] = sy[j-1]+j-1-x; else sy[x] = j+k-1-x;
        }
        cout << mp[x] << ' ';
    }
    return 0;
}