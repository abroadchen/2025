//
// Created by Psy.C on 2025/12/17.
//
/*
*st：开始时间(start time)
v：执行时间(value/time needed)
y：优先级(priority，-1表示待确定)
num：任务编号
重载<运算符按优先级排序(用于优先队列)
*n：任务总数
q：优先队列(最大堆)
s：存储已存在的优先级值
 *
*检查给定优先级p是否能使目标任务在时间k完成
清空优先队列
t表示当前时间
遍历所有任务
处理在新任务到达前能完成的现有任务
如果是目标任务，根据完成时间返回结果：
0：正好在时间k完成
-1：在时间k之前完成(需要延后)
1：在时间k之后完成(需要提前)
*如果队列为空：直接将当前任务入队，时间推进到任务开始时间
如果新任务会打断正在执行的任务：调整正在执行任务的剩余时间，将两个任务都入队
*执行队列中所有剩余任务
检查目标任务完成时间
 *
 *输出给定优先级p下所有任务的完成时间
 *
 *O(log(inf) × n²)：二分搜索 × 模拟过程
 *
 *
*f==0：找到精确解，保存并跳出
f==-1：提前完成，需要更大优先级，调整右边界
f==1：延后完成，需要更小优先级，调整左边界
 *
*从找到的答案ans开始，向左右寻找不在已存在优先级集合中的值
L：向左寻找（更小的可用优先级）
R：向右寻找（更大的可用优先级）
检查L是否有效，如果有效输出L，否则输出R
调用out函数输出所有任务的完成时间
 */
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500005
#define inf 1000000000
using namespace std;

struct node {
    int st, v, y, num;
    friend bool operator<(const node a, const node b) {
        return a.y < b.y;
    }
} w[N];//存储所有任务


int n;
priority_queue<node> q;
set<int> s;

int ok(const int p, const ll k) {//待确定优先级的任务优先级为p时，该任务是否能在时间k完成
    node x{};
    while (!q.empty()) q.pop();//清空优先队列
    ll t = 0;//当前时间
    for (int i = 0; i < n; ++i) {
        while (!q.empty() && q.top().v <= w[i].st - t) {//队首任务执行时间 ≤ 可用时间
            t += q.top().v;
            if (q.top().y == p) {
                if (t == k) return 0;
                if (t < k) return -1;
                return 1;
            }
            q.pop();
        }
        if (q.empty()) {
            x = w[i];//当前任务
            if (x.y == -1) x.y = p;//待确定优先级的任务
            q.push(x);
            t = x.st;//更新为任务开始时间
        } else if (w[i].st - t < q.top().v) {//可用时间 < 当前任务剩余时间
            x = q.top(); q.pop();//取出当前任务
            x.v -= static_cast<int>(w[i].st - t);//减少其剩余执行时间
            q.push(x);//重新放入队列
            x = w[i];//处理新到达的任务
            if (x.y == -1) x.y = p;
            q.push(x);
            t = x.st;
        }
    }
    while (!q.empty()) {
        t += q.top().v;//执行队列中所有剩余任务
        if (q.top().y == p) {
            if (t == k) return 0;
            if (t < k) return -1;
            return 1;
        }
        q.pop();
    }
    return 0;//如果都没有找到目标任务，返回0
}

ll st[N];//存储每个任务的完成时间
void out(const int p) {//优先级为p时所有任务的完成时间
    node x{};
    while (!q.empty()) q.pop();
    ll t = 0;
    for (int i = 0; i < n; ++i) {
        while (!q.empty() && q.top().v <= w[i].st - t) {
            t += q.top().v;
            st[q.top().num] = t;//任务编号为q.top().num的任务完成时间记录到st数组
            q.pop();
        }
        if (q.empty()) {
            x = w[i];
            if (x.y == -1) x.y = p;
            q.push(x);
            t = x.st;
        } else if (w[i].st - t < q.top().v) {
            x = q.top(); q.pop();
            x.v -= static_cast<int>(w[i].st - t);
            q.push(x);
            x = w[i];
            if (x.y == -1) x.y = p;
            q.push(x);
            t = x.st;
        }
    }
    while (!q.empty()) {
        t += q.top().v;
        st[q.top().num] = t;
        q.pop();
    }
    for (int i = 0; i < n; ++i) {
        if (i == n - 1) cout << st[i] << '\n';
        else cout << st[i] << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> w[i].st >> w[i].v >> w[i].y;
        if (w[i].y != -1) s.insert(w[i].y);
        w[i].num = i;
    }
    ll k; cin >> k;
    sort(w, w + n, [](const node a, const node b) {
        if (a.st == b.st) return a.y > b.y;
        return a.st < b.st;
    });
    int l = 1, r = inf, ans = 0;
    while (l <= r) {
        const int mid = (l + r) >> 1;
        const int f = ok(mid, k);
        if (f == 0) { ans = mid; break; }
        if (f == -1) r = mid - 1; else l = mid + 1;
    }
    int L = ans;//寻找不在已存在优先级集合中的左侧和右侧值
    while (L >= 1 && s.find(L) != s.end()) L--;
    int R = ans;
    while (R <= inf && s.find(R) != s.end()) R++;
    if (L > 1 && ok(L, k) == 0) { cout << L << '\n'; out(ans); }
    else { cout << R << '\n'; out(R); }
    return 0;
}