//
// Created by Psy.C on 2025/11/21.
//
/*
 *c4:区间内'4'的个数, c7:区间内'7'的个数
 *li:最长不降子序列长度, ld:最长不增子序列长度
 *flip:翻转标记，表示是否需要翻转'4'和'7'
 *st[N<<2];  // 线段树数组，大小为4*N
 *
*构建：O(n)
查询/更新：O(log n)
 */
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e6+5;
int n;
string s;

struct node {
    int c4, c7, li, ld;
    bool flip;
    node() { c4 = c7 = li = ld = flip = 0; }
} st[N<<2];

void combine(int x, int sl, int sr) {//合并左右子树的信息到父节点
    if (sl == sr) return;//如果是叶子节点，无需合并
    st[x].c4 = st[x<<1].c4 + st[x<<1|1].c4;//左子树'4'个数 + 右子树'4'个数
    st[x].c7 = st[x<<1].c7 + st[x<<1|1].c7;
    st[x].li = max({//形如444...777
        st[x<<1].c4 + st[x<<1|1].c4,//全'4'序列
        st[x<<1].c7 + st[x<<1|1].c7,//全'7'序列
        st[x<<1].c4 + st[x<<1|1].li,//左全'4'+右不降序列
        st[x<<1].c4 + st[x<<1|1].c7,//左全'4'+右全'7'
        st[x<<1].li + st[x<<1|1].c7//左不降序列+右全'7'
    });
    st[x].ld = max({//形如777...444
        st[x<<1].c4 + st[x<<1|1].c4,
        st[x<<1].c7 + st[x<<1|1].c7,
        st[x<<1].c7 + st[x<<1|1].ld,//左全'7'+右不增序列
        st[x<<1].c7 + st[x<<1|1].c4,
        st[x<<1].ld + st[x<<1|1].c4
    });
}

void build(int x, int sl, int sr) {
    if (sl == sr) {//如果是叶子节点
        if (s[sl] == '4') ++st[x].c4;//根据字符设置'4'或'7'的计数
        else ++st[x].c7;
        st[x].li = st[x].ld = 1;
        return;
    }
    int mid = (sl + sr) >> 1;
    build(x<<1, sl, mid);
    build(x<<1|1, mid+1, sr);
    combine(x, sl, sr);//合并左右子树信息
}

void change(int x, int sl, int sr) {//处理翻转标记（懒标记下传）
    if (!st[x].flip) return;//如果没有翻转标记，直接返回
    st[x].flip = 0;//清除当前节点的翻转标记
    if (sl != sr) { st[x<<1].flip ^= 1; st[x<<1|1].flip ^= 1; }//如果不是叶子节点，将翻转标记传递给子节点
    swap(st[x].li, st[x].ld);//不降序列和不增序列互换
    swap(st[x].c4, st[x].c7);//'4'和'7'计数互换
}

void update(int x, int sl, int sr, int l, int r) {
    change(x, sl, sr);//先处理当前节点的翻转标记
    if (sl > r || sr < l) return;//当前区间与目标区间无交集
    if (sl >= l && sr <= r) {
        st[x].flip = 1;//设置翻转标记
        change(x, sl, sr);// 立即处理翻转
        return;
    }
    int mid = (sl + sr) >> 1;
    update(x<<1, sl, mid, l, r);
    update(x<<1|1, mid + 1, sr, l, r);
    combine(x, sl, sr);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int q; cin >> n >> q;
    cin >> s; s = " " + s;//添加空格使其从索引1开始
    build(1, 1, n);
    while (q--) {
        string op; cin >> op;
        if (op[0] == 'c') cout << st[1].li << '\n';//输出根节点的最长不降子序列长度
        else {
            int l, r; cin >> l >> r;
            update(1, 1, n, l, r);//翻转区间[l,r]内的'4'和'7'
        }
    }
    return 0;
}