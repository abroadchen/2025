//
// Created by Psy.C on 2026/4/20.
//
/**
ch[N][26]：字典树节点的子节点数组，每个节点最多26个子节点（对应26个小写字母）
val[N]：每个节点的权值
cnt：节点总数
rt：根节点编号
创建新节点函数：增加节点计数，初始化权值为0，将所有子节点设为-1（表示无子节点），返回新节点编号
初始化字典树：重置计数器和根节点，清空根节点的子节点

将字符串s插入字典树，末尾节点权值增加v
遍历字符串每个字符，计算字符相对于'a'的位置d
如果该字符对应的子节点不存在，创建新节点
到达字符串末尾后，在该节点上增加权值v
计算从根节点到字符串s路径上所有节点的权值和
沿着字符串路径遍历，累加路径上每个节点的权值
如果遇到不存在的节点就停止

计算字符串s的失配函数
j = -1表示无法匹配的情况
如果字符匹配则同时递增i和j，否则回退j
在str中查找模式串s出现的次数
使用KMP算法进行高效的字符串匹配
当匹配成功时，计数器ret增加，并继续寻找下一个匹配

lib[50]：存储较长的字符串模板
str[N]：临时字符串存储
cnt：库中字符串的数量
ctx[50]：对应字符串的权值
对于操作1和2（添加或删除字符串）
长度≤1000的字符串插入字典树
长度>1000的字符串存储到lib数组中
对于操作3（查询）
遍历字符串str的每个后缀，查询字典树中匹配的权值和
对lib数组中的每个模板串，用KMP算法计算其在str中的出现次数
最终结果为所有匹配的权值之和
输出结果并刷新输出缓冲区
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 3e5+7;

struct Trie {
    int ch[N][26], val[N], cnt, rt;
    int new_node() {
        cnt++; val[cnt] = 0;
        memset(ch[cnt], -1, sizeof(ch[cnt]));
        return cnt;
    }
    void init() {
        cnt = rt = 0; val[rt] = 0;
        memset(ch[rt], -1, sizeof(ch[rt]));
    }
    void insert(const char *s, int v) {
        int x = rt;
        for (int i = 0; s[i]; ++i) {
            int d = s[i] - 'a';
            if (ch[x][d] == -1) ch[x][d] = new_node();
            x = ch[x][d];
        }
        val[x] += v;
    }
    int search(const char *s) {
        int sum = 0, x = rt;
        for (int i = 0; s[i]; ++i) {
            int d = s[i] - 'a';
            if (ch[x][d] == -1) break;
            x = ch[x][d];
            sum += val[x];
        }
        return sum;
    }
} tr;

struct KMP {
    int nxt[N];
    void get(const string &s, int len) {
        memset(nxt, 0, sizeof(nxt));
        int i = 0, j = -1; nxt[0] = -1;
        while (i < len) {
            if (j == -1 || s[i] == s[j]) nxt[++i] = ++j;
            else j = nxt[j];
        }
    }
    int search(const string& s, const char *str) {
        int ret = 0, j = 0, lens = s.size(), lenstr = strlen(str);
        get(s, lens);
        for (int i = 0; i < lenstr; ++i) {
            while (j > 0 && s[j] != str[i]) j = nxt[j];
            if (s[j] == str[i]) j++;
            if (j == lens) ret++, j = nxt[j];
        }
        return ret;
    }
} kmp;

string lib[50];
char str[N];
int cnt, ctx[50];
int main() {
    int T = 1, t, m, len, val;
    while (T--) {
        cin >> m; tr.init(); cnt = 0; memset(ctx, 0, sizeof(ctx));
        for (int i = 1; i <= m; ++i) {
            scanf("%d%s", &t, str); len = strlen(str);
            if (t == 1 || t == 2) {
                val = t == 1 ? 1 : -1;
                if (len <= 1000) tr.insert(str, val);
                else {
                    lib[cnt] = string(str);
                    ctx[cnt++] = val;
                }
            } else {
                ll ans = 0;
                for (int j = 0; j < len; ++j)
                    ans += tr.search(str + j);
                for (int j = 0; j < cnt; ++j) {
                    if (lib[j].length() > len) continue;
                    ans += kmp.search(lib[j], str)*ctx[j];
                }
                printf("%lld\n", ans);
                fflush(stdout);
            }
        }
    }
    return 0;
}