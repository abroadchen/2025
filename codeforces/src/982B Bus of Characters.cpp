//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
node 存每个元素的权值 w 和原始编号 id。
cmp：按权值 w 从小到大排序；权值相同则按原编号 id 升序
读入 n 和每个元素的权值 w，同时记录其原编号 id = i。
对整个数组按上面定义的 cmp 排序
t 是"已分配元素"的指针，初值 1。
读入长度 2n 的操作序列：
遇到 0（入栈）‍：把排序后第 t 个元素的原编号 a[t].id 输出并压入栈，t++ 指向下一个。
遇到 1（出栈）‍：输出当前栈顶元素的原编号并弹出栈。
关键点：操作序列里 0 的数量恰好是 n（因为总长度 2n 且栈最终为空，0 和 1 各半）。所以 t 从 1 走到 n，正好把所有已排序元素都用完

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

struct node { int w, id; } a[N];
bool cmp(const node &x, const node &y) {
    if (x.w == y.w) return x.id < y.id;
    return x.w < y.w;
}

int n;
char ch;
stack<int> s;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> a[i].w; a[i].id = i; }
    sort(a+1, a+1+n, cmp);
    for (int i = 1, t = 1; i <= 2*n; i++) {
        cin >> ch;
        if (ch == '0') {
            cout << a[t].id << ' ';
            s.push(a[t].id);
            t++;
        } else if (ch == '1') {
            cout << s.top() << ' ';
            s.pop();
        }
    }
    return 0;
}