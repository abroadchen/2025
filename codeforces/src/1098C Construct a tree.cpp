//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
ans 累加深度和，初始 = 根节点深度和 1（根深度 0，贡献 0？其实 ans=1 是深度 0 的节点? 见下）。
l = n-1：叶子节点数还差多少个没分配（除根外）。
循环 i=2..，j 一开始 = cur，之后每轮 j *= cur。这里 j 表示第 i 层最多能放下多少个节点（若每点 cur 叉）。
if (l <= j)：剩余节点能全部放进当前层 → 这层放 l 个，贡献 i*l 后结束。
否则这层放满 j 个，贡献 i*j，剩余 l -= j 继续下一层。
目标是找到使得 check(mid) <= s 成立的最小分叉 mid（越大越紧凑、check 越小）。
ans 记录该最优分叉数（在缩小上界时更新，最终指向最小的可行 mid）。
ss[++cnt] = 1：根深度记为 1（这里把根也当成深度1处理，简化计数）。
循环 i=2..，j=i 层可放数量。
剩余节点能放满当前层就放满（rep(k,j) ss[++cnt]=i），不够则放剩余并 vis[i]=l 结束。
vis[i]：记录"第 i 层实际放了多少个节点"，用于后续（调整 ss[cur] 深度用的计数）。

最后 ss 是 [1, 2,2,..., 3,3,3,...] 这种按深度递增排列的序列
从序列末尾（最大深度、即 ss[cur] 最大）向前挑节点来增加深度：
while 跳过"该层只剩1个节点（vis==1）"或"已是它上层 depth+1"（不能再提）的点。
找到可提升的点后 vis[ss[cur]]--（移出本层），若能一次性提升到紧邻上一层深度则整段提升（p -= 跨度），否则只 +1（p--）。
更新 vis[ss[cur]]++
深度按 ss 升序排好后，每一层内把新节点挂到"上一层还有空位的节点"上：
换层时，把上一层所有节点记到 lst，新层用 cc 收集。
now[x] 记录节点 x 还剩多少子节点可放（初始为 ans，即分叉数）。
每挂一个节点 fa[i]=lst.back()（父 = 上一层某有位置的点），并 now[父]--；父空位用尽则从 lst 弹出
最大可能深度和：1+2+...+n = n(n+1)/2（一条"满叉到深度n"上限）。
最小可能深度和：星形树，根连所有 n-1 个叶子，深度和 = 2*(n-1)（除根外每个都在深度1——按本代码深度1是根，节点在深度2，所以非根节点深度和=2(n-1)）。
只有 2(n-1) < s ≤ n(n+1)/2 才可构造；否则输出 No
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define int long long
using namespace std;

constexpr int N = 4e5+5;

int n;
int check(int cur) {
    int ans = 1, l = n-1;
    for (int i = 2, j = cur; i <= n; i++, j *= cur) {
        if (l <= j) { ans += i*l; break; }
        ans += i*j;
        l -= j;
    }
    return ans;
}

int ss[N], cnt, vis[N];
void run(int cur) {
    int l = n-1; ss[++cnt] = 1;
    for (int i = 2, j = cur; i <= n; i++, j *= cur) {
        if (l <= j) {
            rep(k,l) ss[++cnt] = i;
            vis[i] = l;
            break;
        }
        rep(k,j) ss[++cnt] = i;
        l -= j; vis[i] = j;
    }
}

int s, now[N], fa[N];
vector<int> cc,lst;
signed main() {
    fast;
    cin >> n >> s;
    if (s > (1+n)*n/2) cout << "No\n";
    else if (s <= 2*(n-1)) cout << "No\n";
    else {
        int l = 1, r = n-1, ans = n-1;
        while (l <= r) {
            int mid = (l+r)>>1;
            if (check(mid) <= s) { ans = mid; r = mid-1; }
            else l = mid+1;
        }
        int p = s - check(ans); run(ans);
        int cur = n-1, pre = n;
        rep(i,n) now[i] = ans;
        while (p > 0) {
            while (vis[ss[cur]] == 1 || ss[cur] == ss[pre]+1) {
                if (ss[cur] == ss[pre] + 1) pre = cur;
                cur--;
            }
            vis[ss[cur]]--;
            if (p >= ss[pre]+1-ss[cur]) {
                p -= ss[pre]+1-ss[cur];
                ss[cur] += ss[pre]+1-ss[cur];
            } else { p--; ss[cur]++; }
            vis[ss[cur]]++;
        }
        sort(ss+1,ss+n+1); cc.clear(); cc.push_back(1);
        for (int i = 2; i <= n; i++) {
            if (ss[i] != ss[i-1]) { lst = cc; cc.clear(); }
            cc.push_back(i); now[lst.back()]--; fa[i] = lst.back();
            if (now[lst.back()] == 0) lst.pop_back();
        }
        cout << "Yes\n";
        for (int i = 2; i <= n; i++) cout << fa[i] << ' ';
        cout << '\n';
    }
    return 0;
}