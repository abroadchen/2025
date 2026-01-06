//
// Created by Psy.C on 2026/1/6.
//
/**
* sz: 当前后缀自动机中节点的数量
len[N<<1]: 每个节点表示的最长字符串长度
lst: 指向当前处理字符串的最后一个后缀的节点
ch[N<<1][40]: 后缀自动机的转移边（40个字符空间，对应26个小写字母+其他字符） 从节点i通过字符c能到达的节点
link[N<<1]: 后缀链接数组 指向节点i的后缀链接
cnt[12][N<<1]: 计数数组，cnt[i][j]表示第i个字符串在节点j中出现的次数
 *
*solve函数：为字符串s构建后缀自动机，并标记为id组
遍历字符串s的每个字符，c = s[i] - 'a'将字符转换为0-25的数字
cur = ++sz创建新节点
*设置新节点的长度为前一个节点长度+1
从上一个节点开始，沿着后缀链接向上，直到找到有字符c转移边的节点
在路径上的所有节点添加字符c的转移边
*如果找到的节点q不是刚创建的节点cur
如果长度恰好满足条件，直接设置cur的后缀链接为q
*否则创建一个新的分割节点x
复制q的转移边到x
设置x的后缀链接和长度
*更新路径上所有指向q的转移边，改为指向x
设置q和cur的后缀链接都指向x
*更新lst为当前节点
增加id组在cur节点的计数
 *
 *将所有节点按长度降序排序（拓扑排序）
*从叶子节点向根节点传递计数信息
每个节点的计数累加到其后缀链接指向的节点
 *
 *读取第一个字符串并构建后缀自动机（标记为0组）
*定义左右边界数组
设置第一个字符串的出现次数范围
读取查询数量n
*对于每个查询：
添加一个特殊字符"{"到自动机中（分隔符）
读取字符串并构建后缀自动机（标记为i组）
读取该字符串的出现次数范围
*执行build函数处理计数
遍历所有节点，检查每个节点是否满足所有字符串的出现次数要求
如果满足条件，累加该节点代表的字符串数量（len[i] - len[link[i]]）
 *
 */
#include <iostream>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 500016
#define mod 1000000007
using namespace std;

int sz, len[N<<1], lst, ch[N<<1][40], link[N<<1], cnt[12][N<<1];
void solve(const char *s, const int id) {//要处理的字符串 字符串的标识符
    for (int i = 0; s[i]; ++i) {
        const int c = s[i] - 'a', cur = ++sz;
        len[cur] = len[lst] + 1;
        int p = lst;
        while (!ch[p][c]) { ch[p][c] = cur; p = link[p]; }
        if (ch[p][c] != cur) {
            const int q = ch[p][c];//获取通过字符c到达的节点
            if (len[p] + 1 == len[q]) link[cur] = q; else {
                const int x = ++sz;
                memcpy(ch[x], ch[q], sizeof(ch[q]));//复制q的转移数组到x
                link[x] = link[q];//设置x的后缀链接为q的后缀链接
                len[x] = len[p] + 1;
                while (ch[p][c] == q) {//更新路径上所有指向q的转移边，改为指向x
                    ch[p][c] = x;
                    p = link[p];
                }
                link[q] = link[cur] = x;//设置q和cur的后缀链接都指向x
            }
        }
        lst = cur;//更新lst为当前节点cur
        ++cnt[id][cur];//增加id组在cur节点的计数
    }
}

void build() {
    vector<int> v;//存储所有节点编号
    for (int i = 1; i <= sz; ++i) v.push_back(i);
    sort(v.begin(), v.end(), [&](const int a, const int b) {
        return len[a] > len[b];
    });
    for (const auto u : v) for (const auto x : cnt) {//从叶子节点向根节点传递计数信息
        x[link[u]] += x[u];//将每个节点u的计数累加到其后缀链接指向的节点
    }
}


int main() {
    fast;
    char str[N]; cin >> str; solve(str, 0);//为第一个字符串构建后缀自动机，标识为0
    int l[N], r[N]; l[0] = 1, r[0] = 50000;//设置第一个字符串的出现次数范围为[1, 50000]
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        string t = "{";
        solve(t.c_str(), n + 1);//将分隔符添加到自动机
        cin >> str; solve(str, i);//读取字符串并构建后缀自动机，标识为i
        cin >> l[i] >> r[i];//读取该字符串的出现次数范围[l[i], r[i]]
    }
    build();//统计所有子串在各个字符串中的出现次数
    int ans = 0;
    for (int i = 1; i <= sz; ++i) {
        int ok = 1;//假设当前节点满足条件
        for (int j = 0; j <= n; ++j) if (cnt[j][i] < l[j] || cnt[j][i] > r[j]) {
            ok = 0, j = n + 1;//节点i在每个字符串中的出现次数是否在范围内
        }
        ans += ok * (len[i] - len[link[i]]);
    }
    cout << ans << '\n';
    return 0;
}