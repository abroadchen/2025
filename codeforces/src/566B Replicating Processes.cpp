//
// Created by Psy.C on 2026/3/12.
//
/**
a, b, c: 存储任务的三个参数（可能是依赖关系）
h: 计数数组，存储每个元素的"使用次数"

尝试执行任务i:
h[b[i]]++: b[i]的计数加1
h[c[i]]++: c[i]的计数加1
h[a[i]]--: a[i]的计数减1
约束检查: b[i]和c[i]的计数都不能超过9
成功: 返回true
失败: 撤销操作，返回false

读入任务数量n
h[i] = 4: 初始化每个元素计数为4
n<<=2: n乘以4（总任务数）
读入所有任务的三个参数
将所有任务ID加入队列q

主循环: 直到所有任务都被处理
第一轮: 从q队列中取出任务，尝试执行
成功执行：加入结果向量ans
失败：放入临时队列p
第二轮: 将p中的任务重新放回q，进行下一轮尝试

最坏情况：O(∞)，如果不存在解
实际情况：取决于约束的松紧程度
每轮处理O(n)个任务

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e4+5;

int a[N<<2], b[N<<2], c[N<<2], h[N];
bool check(const int i) {
    h[b[i]]++; h[c[i]]++; h[a[i]]--;
    if (h[b[i]] <= 9 && h[c[i]] <= 9) return true;
    h[b[i]]--; h[c[i]]--; h[a[i]]++;
    return false;
}

int n, i;
queue<int> p, q;
vector<int> ans;
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; ++i) h[i] = 4; n<<=2;
    for (i = 1; i <= n; ++i) cin >> a[i] >> b[i] >> c[i];
    for (i = 1; i <= n; ++i) q.push(i);
    while (ans.size() != n) {
        while (!q.empty()) {
            i = q.front(); q.pop();
            if (check(i)) ans.push_back(i);
            else p.push(i);
        }
        while (!p.empty()) {
            q.push(p.front()); p.pop();
        }
    }
    cout << "YES\n";
    for (i = 0; i < ans.size() - 1; ++i) cout << ans[i] << ' ';
    cout << ans.back() << '\n';
    return 0;
}