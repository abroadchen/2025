//
// Created by Psy.C on 2026/4/19.
//
/**
t[N][2]: 01字典树，t[p][0/1]表示节点p的0/1子节点
tot: 节点总数
cnt[N]: 每个节点的计数（有多少个数经过该节点）
val[N]: 叶子节点存储的实际值

将数字x插入字典树
从最高位（第31位）到最低位遍历
x>>i&1: 获取x的第i位
如果子节点不存在就创建
cnt[p]++: 经过该节点的数数量+1
在叶子节点存储原值

将数字x从字典树中删除
沿着x的路径，将经过的节点计数-1
注意：这里只是减少计数，没有真正删除节点

查找与x异或结果最大的数
to^1: 与x的第i位相反的位
优先选择相反位（使异或结果更大）
cnt[t[p][to^1]]: 确保该路径上有可用的数
如果相反位路径不可用，就走相同位路径
返回找到的数

插入0，确保集合中始终有数
时间复杂度：O(32) ≈ O(1) per operation
插入/删除/查询: O(log C)，其中C是数值范围
空间复杂度: O(n log C)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 6e6+7;

int t[N][2], tot, cnt[N], val[N];
void insert(int x) {
    int p = 0;
    for (int i = 31; i >= 0; --i) {
        int to = x>>i&1;
        if (!t[p][to]) t[p][to] = ++tot;
        p = t[p][to];
        cnt[p]++;
    }
    val[p] = x;
}
void del(int x) {
    int p = 0;
    for (int i = 31; i >= 0; --i) {
        int to = x>>i&1;
        p = t[p][to];
        cnt[p]--;
    }
}
int get(int x) {
    int p = 0;
    for (int i = 31; i >= 0; --i) {
        int to = x>>i&1;
        if (t[p][to^1] && cnt[t[p][to^1]]) p = t[p][to^1];
        else p = t[p][to];
    }
    return val[p];
}

int q;
int main() {
    fast;
    insert(0);
    cin >> q;
    while (q--) {
        char op; int x; cin >> op >> x;
        if (op == '+') insert(x);
        else if (op == '-') del(x);
        else if (op == '?') cout << (x^get(x)) << '\n';
    }
    return 0;
}