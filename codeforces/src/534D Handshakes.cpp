//
// Created by Psy.C on 2026/3/4.
//
/**
cnt[N]: 计数数组，记录每个值的出现次数
get()函数：寻找与x同余模3的最大可用值
l = x % 3: x除以3的余数
r = x - 3: 从x-3开始向下搜索
在[l, r]范围内寻找最大的cnt[r] > 0的值

n: 输入元素个数
x[N]: 输入数组
ans[N]: 结果数组，ans[0]用作计数器
g[N]: 每个值对应的位置列表

循环直到填满n个位置或无法继续：
如果cnt[k] > 0（还有值为k的元素）：
设置flag=1
从g[k]中取出一个位置（使用并减少计数）
将该位置加入结果
k递增
否则：
使用get(k)寻找下一个合适的k值
如果flag=0（已经循环过），则退出
否则设置flag=0

如果成功放置了n个元素（ans[0]==n）：
输出"Possible"
输出所有位置编号，最后一个元素后输出换行符
否则输出"Impossible"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1;

int cnt[N];
int get(const int x) {
    int l = x % 3, r = x - 3;
    while (l < r) {
        if (cnt[r]) return r;
        r -= 3;
    }
    return l;
}

int n, x[N], ans[N];
vector<int> g[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        g[x[i]].push_back(i);
        cnt[x[i]]++;
    }
    int flag = 1, k = 0;
    while (true) {
        if (ans[0] == n) break;
        if (cnt[k]) {
            flag = 1;
            const int t = g[k][--cnt[k]];
            ans[++ans[0]] = t;
            k++;
        } else {
            k = get(k);
            if (flag == 0) break;
            flag = 0;
        }
    }
    if (ans[0] == n) {
        cout << "Possible\n";
        for (int i = 1; i <= ans[0]; ++i)
            cout << ans[i] << " \n"[i==ans[0]];
    } else cout << "Impossible\n";
    return 0;
}