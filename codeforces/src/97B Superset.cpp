//
// Created by Psy.C on 2025/11/10.
//
/*
*n：输入点的数量
m：输出点的数量
tot：临时计数器
a[N]：存储输入的点
b[N]：存储生成的点
 *
*定义分治函数，参数为左右边界
如果左右边界相等，递归终止
*对于区间[l,r]内的每个点，生成一个新的点：
x坐标取中点的x坐标
y坐标取当前点的y坐标
 *
 *去除重复点，unique将重复元素移到末尾并返回第一个重复元素的位置
 *输出不重复点的个数和所有点的坐标
 *
 *算法复杂度为O(n log n)，主要由排序决定
 */
#include <algorithm>
#include <iostream>
#define rep(i,n) for(int (i)=1;(i)<=(n);++(i))
using namespace std;

typedef pair<int, int> pii;
const int N = 2e5+5;

int n, m, tot;
pii a[N], b[N];

void dfs(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    for (int i = l; i <= r; ++i)
        b[++tot] = {a[mid].first, a[i].second};
    dfs(l, mid), dfs(mid + 1, r);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    rep(i,n) cin >> a[i].first >> a[i].second;//读取n个点的坐标
    sort(a+1, a+1+n);//对点按x坐标排序（a[1]到a[n]）
    dfs(1, n);//调用分治函数生成新点
    rep(i,n) b[++tot] = a[i];//将原始点也加入结果集合
    sort(b+1, b+1+tot);//对所有点排序
    m = unique(b+1, b+1+tot) - b - 1;
    cout << m << '\n';
    rep(i,m) cout << b[i].first << ' ' << b[i].second << '\n';
    return 0;
}