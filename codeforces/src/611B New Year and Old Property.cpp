//
// Created by Psy.C on 2026/3/23.
//
/**
l, r：查询区间的左右边界
ans：满足条件的数字计数
num：当前遍历到的数字
flag：标志位，表示是否已经经过了"转折点"

剪枝条件：如果当前数字已经超过右边界r，直接返回
计数条件：如果数字在区间[l,r]内且flag==1，计数器加1
递归扩展：
如果flag==0（还未经过转折点），可以走左子树（num<<1），并将flag置为1
无论何时都可以走右子树（num<<1|1），保持flag不变

从根节点1开始（二进制为"1"）
左子节点操作num<<1相当于在末尾加"0"
右子节点操作num<<1|1相当于在末尾加"1"
flag标记是否已经添加过"0"
所以这个算法是在寻找区间[l,r]内，二进制表示中至少包含一个"0"位的数字个数

时间复杂度：
O(log r)，因为每个数字最多有log位，搜索树的深度为O(log r)。
空间复杂度：
O(log r)，递归调用栈的深度

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll l, r, ans;
void dfs(ll num, int flag) {
    if (num > r) return;
    if (num >= l && num <= r && flag == 1) ans++;
    if (flag == 0) dfs(num<<1, 1);
    dfs(num<<1|1, flag);
}

int main() {
    fast;
    cin >> l >> r; dfs(1, 0);
    cout << ans << '\n';
    return 0;
}