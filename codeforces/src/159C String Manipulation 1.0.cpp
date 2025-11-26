//
// Created by Psy.C on 2025/11/26.
//
/*
 *遍历整个字符串 t，对于每一个字符，计算它相对于 'a' 的偏移作为索引，
 *在对应的子向量中存储它的实际位置索引
 *
 *输入要删除第几个出现的某个字符及其字符本身
 *计算字符 c 对应于字母表的位置（0~25）
 *将这个字符第 r 次出现在字符串 t 中的那个位置标记为不保留（即删除）
 *同时从记录该字符的所有位置列表中移除这一项，防止影响后续相同字符的删除判断
 *
 *再次遍历字符串 t，如果某位置未被标记为删除，则输出该位置上的字符
 *
 *v[x] 表示第 x 个一维向量
*v[x].begin() + r - 1
从起始位置向前移动 r-1 个位置
最终指向要删除的元素位置
 *
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 26;

int main() {
    fast;
    int k; cin>>k;
    string s, t; cin>>s;
    for (int i = 0; i < k; ++i) t += s;
    vector<vector<int>> v(N);//每个字母在字符串中的位置索引
    vector<bool> f(t.size(), true);//标记字符是否保留
    for (int i = 0; i < t.size(); ++i) v[t[i] - 'a'].push_back(i);
    int n; cin>>n;
    while (n--) {
        int r; char c; cin>>r>>c;
        const int x = c - 'a';
        f[v[x][r - 1]] = false;
        v[x].erase(v[x].begin() + r - 1);
    }
    for (int i = 0; i < t.size(); ++i) if (f[i]) {
        cout << t[i];
    }
    cout << '\n';
    return 0;
}