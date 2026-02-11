//
// Created by Psy.C on 2026/2/11.
//
/**
移动操作：O(√n)，最多移动√n个块
查询操作：O(√n)，最多√n个块需要处理
空间复杂度：O(n)，分块存储
 */
#include <iostream>
#include <deque>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
#define M 800
using namespace std;

struct node {
    int cnt[N]{};//每个值在当前块中的出现次数
    deque<int> q;//存储当前块的实际元素
} g[200];//分块数组，每块大小约M=800

int l, r;
void rs() {
    //a, b：左右端点所在块号
    //aa, bb：在块内的偏移量
    const int a = l/M, b = r/M, aa = l%M, bb = r%M;
    int val = *(g[b].q.begin()+bb);//获取目标位置的值
    g[b].q.erase(g[b].q.begin()+bb);//从原块删除
    g[a].q.insert(g[a].q.begin()+aa, val);//插入到目标块
    g[b].cnt[val]--; g[a].cnt[val]++;//更新计数
    ///将中间块的最后一个元素移到下一区块首
    for (int i = a; i < b; ++i) {
        val = g[i].q.back();
        g[i].q.pop_back(); g[i+1].q.push_front(val);
        g[i].cnt[val]--; g[i+1].cnt[val]++;
    }
}

int k;
int get() {
    const int a = l/M, b = r/M, aa = l%M, bb = r%M; int res = 0;
    if (a == b) {//同一区间：直接遍历
        for (auto it = g[a].q.begin()+aa;
            it <= g[a].q.begin()+bb; ++it) {
            if (*it == k) res++;
        }
    } else {//跨区间：处理三部分
        //左端不完整块
        for (auto it = g[a].q.begin()+aa;
            it != g[a].q.end(); ++it) {
            if (*it == k) res++;
        }
        //中间完整块
        for (int i = a + 1; i < b; ++i) res += g[i].cnt[k];
        //右端不完整块
        for (auto it = g[b].q.begin(); it <= g[b].q.begin()+bb; ++it) {
            if (*it == k) res++;
        }
    }
    return res;
}


int n, a[N];
void init() {
    for (int i = 0; i < n; ++i) {
        g[i/M].q.push_back(a[i]);//将元素分配到对应块
        g[i/M].cnt[a[i]]++;//更新计数
    }
}

int q, t, ans = 0;

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i]; init();
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> t >> l >> r;
        l = (l+ans-1)%n; r = (r+ans-1)%n;
        if (l > r) swap(l, r);
        if (t == 1) rs();
        else {
            cin >> k; k = (k+ans-1)%n+1;
            ans = get();
            cout << ans << '\n';
        }
    }
    return 0;
}