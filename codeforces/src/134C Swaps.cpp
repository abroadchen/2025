//
// Created by Psy.C on 2025/11/19.
//
/*
*首先检查 x 是否为真（非零）
如果 x == 0：由于短路特性，不会执行括号内的代码
如果 x != 0：继续执行括号内的代码
当 x 非零时执行括号内代码
q.push({x,i})：将配对 {x,i} 推入优先队列
, 1：逗号表达式返回值1（总是为真）
 *
 *
 */
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
int n, m;
priority_queue<ii> q;//默认按降序排列
vector<ii> ans;//存储结果配对
queue<ii> t;//临时存储

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        x && (q.push({x,i}), 1);
    }
    while (!q.empty()) {
        ii x = q.top(); q.pop();
        while (x.first) {
            if (q.empty()) return printf("No"), 0;
            ii y = q.top(); q.pop();//取出优先队列中的下一个最大元素赋给y，并从队列中删除
            ans.push_back({x.second, y.second});
            --x.first; --y.first;
            if (y.first) t.push(y);//元素仍大于0，则将其压入临时队列t中
        }
        while (!t.empty()) { q.push(t.front()); t.pop(); }//将临时队列t中的所有元素重新放回优先队列q中
    }
    printf("Yes\n"); printf("%d\n", ans.size());
    for (auto x : ans) printf("%d %d\n", x.first, x.second);
    return 0;
}