//
// Created by Psy.C on 2025/11/17.
//
/*
*定义后缀自动机节点结构：
len：当前状态对应的字符串长度
link：后缀链接（指向最长真后缀对应的状态）
cnt：以该状态为结尾的子串出现次数
nxt[26]：转移边数组，对应26个小写字母
sz(1)：当前节点数，初始为1
lst(0)：最后一个添加的节点索引，初始为0
 *
*添加字符c到后缀自动机：
创建新节点cur
新节点长度为前一节点长度+1
初始出现次数为1
初始化所有转移边为-1（表示不存在）
*从lst节点开始，沿着后缀链接向上走
如果当前节点没有字符c的转移边，就建立转移边指向cur
直到遇到已有转移边或到达根节点
*如果一直走到根节点都没有字符c的转移边
则新节点的后缀链接指向根节点0
*如果存在转移边q，且满足len[p]+1 == len[q]
则直接建立后缀链接：cur→q
*否则需要分裂节点：
创建新节点x
x的长度为len[p]+1
复制q的所有转移边给x
x的后缀链接指向q的后缀链接
x的计数初始化为0
*沿着后缀链接将所有指向q的转移边改为指向x
建立q和cur的后缀链接都指向x
更新lst为当前节点cur
 *
 *
*基数排序准备：统计每种长度的节点个数
计算前缀和，用于基数排序
 *按照长度对节点进行排序，得到ord数组
*按照拓扑序更新每个节点的出现次数
通过后缀链接将子节点的计数累加到父节点
 *
*对每个节点i，k是出现次数，num是该节点新增的不同子串数目
每个子串的贡献是k*(k+1)/2（k个相同子串的所有子数组个数）
总贡献为num * k*(k+1)/2
 *
 *时间复杂度为O(n)
 */
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 2e5+10;

struct node {
    int len, link;
    ll cnt;
    int nxt[26];
} st[N];
int sz(1), lst(0);

void build(char c) {
    int cur = sz++;
    st[cur].len = st[lst].len + 1;
    st[cur].cnt = 1;
    for (int& i : st[cur].nxt) i = -1;
    int p = lst;
    while (p != -1 && st[p].nxt[c] == -1) {
        st[p].nxt[c] = cur;
        p = st[p].link;
    }
    if (p == -1) st[cur].link = 0;
    else {
        int q = st[p].nxt[c];
        if (st[p].len + 1 == st[q].len) st[cur].link = q;
        else {
            int x = sz++;
            st[x].len = st[p].len + 1;
            for (int i = 0; i < 26; ++i) st[x].nxt[i] = st[q].nxt[i];
            st[x].link = st[q].link;
            st[x].cnt = 0;
            while (p != -1 && st[p].nxt[c] == q) {
                st[p].nxt[c] = x;
                p = st[p].link;
            }
            st[q].link = st[cur].link = x;
        }
    }
    lst = cur;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin >> s;
    int n = s.size();
    st[0].len = 0;
    st[0].link = -1;
    for (int& i : st[0].nxt) i = -1;
    for (char c : s) build(c - 'a');//依次将字符串中的每个字符加入后缀自动机
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < sz; ++i) if (st[i].len <= n) {
        cnt[st[i].len]++;
    }
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    vector<int> ord(sz);
    for (int i = 0; i < sz; ++i) {
        int len = st[i].len;
        if (len <= n) ord[--cnt[len]] = i;
    }
    for (int i = sz - 1; i >= 0; --i) {
        int x = ord[i];
        if (st[x].link != -1) st[st[x].link].cnt += st[x].cnt;
    }
    ll ans(0);
    for (int i = 1; i < sz; ++i) {
        ll k = st[i].cnt, num = st[i].len - st[st[i].link].len;
        ans += num * (k * (k + 1)) / 2;
    }
    cout << ans << '\n';
    return 0;
}