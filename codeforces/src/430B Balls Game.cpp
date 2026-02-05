//
// Created by Psy.C on 2026/2/5.
//
/**
* n: 数组长度
c[N]: 输入的数字序列
x: 要插入的新数字
 *
 *在pos位置插入x后能消除的数字数量
*p: 当前处理的序列
t: 临时序列
 *
*检查位置i及其左右邻居是否相同
如果相同，标记这三个位置为待删除
设置flag为true表示发生了消除
 *
*将未被标记的元素加入临时数组t
将t复制回p
如果本轮没有发生消除，跳出循环
 *
*返回消除的元素数量：
原长度n减去最终剩余长度
 */
#include <iostream>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

int n, c[N], x;
int get(const int pos) {
    vector<int> p, t;
    for (int i = 0; i < n + 2; ++i) {
        if (i >= 1 && i <= n) p.push_back(c[i]);//添加原始序列的元素
        if (pos == i) p.push_back(x);//在指定位置插入x
    }
    bool vis[N];// 标记要消除的位置
    while (true) {
        bool flag = false;//标记本轮是否有消除操作
        memset(vis, false, sizeof vis);
        t.clear();
        if (p.empty()) break;
        for (int i = 1; i < p.size()-1; ++i) {
            if (p[i] == p[i-1] && p[i] == p[i+1]) {
                vis[i-1] = vis[i] = vis[i+1] = true;
                flag = true;
            }
        }
        for (int i = 0; i < p.size(); ++i) if (!vis[i])
            t.push_back(p[i]);
        p.clear();
        for (int i : t) p.push_back(i);
        if (flag == false) break;
    }
    return n - static_cast<int>(p.size());
}


int main() {
    fast;
    int k; cin >> n >> k >> x;
    for (int i = 1; i < n + 1; ++i) cin >> c[i];
    int ret = 0;
    for (int i = 0; i < n + 2; ++i) ret = max(ret, get(i));
    cout << ret << '\n';
    return 0;
}