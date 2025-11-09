//
// Created by Psy.C on 2025/9/28.
//
/*
*pii: 整数对的别名
N = 5e5+5: 最大数组大小
n: 字符串长度
vis[N]: 访问标记数组
s: 输入字符串
da结构体：
val: 该位置的数值
le: 左邻居索引
ri: 右邻居索引
a[N]: 存储所有位置信息的数组
 *
*创建一个小顶堆优先队列：

存储类型：pair<int, pii>，即 {价值差, {位置1, 位置2}}
greater<pair<int, pii>>：使队列按价值差从小到大排序
*第二个参数：vector<pair<int, pii>>

这是指定的底层容器类型
表示优先队列内部使用 vector 来存储元素
必须是随机访问容器，因为优先队列需要随机访问来维护堆性质
 *
*设置左右邻居关系：
位置i的左邻居是i-1（i≥2时）
位置i的右邻居是i+1（i≤n-1时）
如果相邻位置字符不同，将它们的价值差和位置对加入优先队列
 *
*创建结果向量val存储配对结果
当优先队列非空时继续：
取出价值差最小的配对
如果其中一个位置已被配对过，跳过
*标记两个位置为已访问
将配对结果加入结果向量
 *
*更新邻居关系：

将x的左邻居的右邻居指向y的右邻居
将y的右邻居的左邻居指向x的左邻居
这样就从链表中移除了x和y两个节点
 *
*如果x的左邻居和y的右邻居都存在且字符不同
计算它们的价值差并加入优先队列
 *
*输出配对数量
输出所有配对的位置
 *
*贪心策略：总是选择价值差最小的可配对相邻不同字符
数据结构：使用优先队列维护所有可能的配对
动态更新：当两个位置被配对后，更新邻居关系并可能产生新的配对
避免冲突：使用访问数组确保每个位置只被配对一次
时间复杂度
时间复杂度：O(n log n)，主要由优先队列操作决定
空间复杂度：O(n)
 *
 *
 *
 *
 */
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#define rep(i, a, b) for(long long i=(a);i<=(b);++i)
using namespace std;

typedef pair<int,int> pii;
const int N = 5e5+5;


int n, vis[N];
string s;

struct da {
    int val, le, ri;
} a[N];

void solve() {
    cin >> n >> s;
    s = ' ' + s;//在字符串前添加空格，使索引从1开始
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> q;
    rep(i, 1, n) {
        cin >> a[i].val;
        if (i >= 2) {
            a[i].le = i - 1;
            if (s[i - 1] != s[i]) q.push({abs(a[i].val - a[i - 1].val), {i - 1, i}});
        }
        if (i <= n - 1) a[i].ri = i + 1;
    }
    vector<pii> val;
    while (!q.empty()) {
        auto v = q.top(); q.pop();
        int x = v.second.first, y = v.second.second;
        if (vis[x] || vis[y]) continue;
        vis[x] = vis[y] = 1;
        val.push_back({x, y});
        if (a[x].le != 0) a[a[x].le].ri = a[y].ri;
        if (a[y].ri != 0) a[a[y].ri].le = a[x].le;
        if (a[x].le != 0 && a[y].ri != 0 && s[a[x].le] != s[a[y].ri])
            q.push({abs(a[a[x].le].val - a[a[y].ri].val), {a[x].le, a[y].ri}});
    }
    cout << val.size() << "\n";
    for (auto x : val) cout << x.first << " " << x.second << "\n";
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}