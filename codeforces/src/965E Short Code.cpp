//
// Created by Psy.C on 2026/10/22.
//
/**
N = 200005：Trie 节点池上限（n 个字符串总字符数可到 2e5 量级）。
M = 26：小写字母种类数，nxt 数组大小为 26（每个节点最多 26 个子节点）
ch：通过哪条边进入本节点（根节点的 ch 不实际使用）。
dep：深度，根节点 dep=0，每一层 +1。
tot：在本节点结束的单词数（用于统计哪些节点是"单词结尾"）。
nxt[26]：26 个孩子指针，值为节点的下标，-1 表示没有该字母的孩子
init() 只重置根节点（rt=0）：把 dep、tot 清零，所有子指针置 -1，并把全局 cnt 归零。
注意：只初始化了根节点，其余节点是在 insert 创建时逐一手动初始化的
递归式插入：每次取 s[0] 作为当前节点到孩子的"边字母"，id = s[0]-'a'。
若该孩子不存在（-1），就新建节点并初始化（dep、tot、nxt）。
然后 insert(s+1, ...) 把字符串剩余部分递归到子节点继续插入。
当 strlen(s)==0 时表示整串插入完成，把当前节点的 tot++（该单词在此节点结尾）
这是一个自定义小根堆比较器：tr[a].dep < tr[b].dep 返回 true 表示 a 应在 b 后面，于是 dep 越小的节点越先出队。
每个 Trie 节点 rt 都对应一个 q[rt]，里面存的是节点编号，按深度从小到大排列

空节点直接返回；否则先清空本节点队列（防止多次运行残留）
先 dfs(x) 递归处理子树（先内后外）。
然后把该孩子队列里的所有元素全部搬到本节点队列（q[x] 清空、元素进 q[rt]）。
if (x==-1) continue; 是必须的：没有它就会出现上一轮分析里 q[-1] 越界崩溃
条件：本节点不是根（rt≠0）且本节点没有单词在这里结束（tot==0）且队列非空。
含义：如果当前节点本身没有归属的单词，那么可以从队列里取出深度最小的那个代表节点，把它的"计数"转移到本节点：本节点 tot++、被取出的节点 tot--，并从队列弹出该代表。
效果：某个单词的"结尾节点"被上移一层，相当于把该节点的深度上提、以本节点作为新的归属点（用于前缀压缩）
若本节点恰好有 1 个单词在此结束，就把本节点编号入队，表示它可以成为后续（更上层）贪心转移的对象

读入 n；init() 复位；循环读入每个单词并 insert 进 Trie。
dfs(0) 从根节点开始做自底向上的队列合并与贪心转移。
最后把根节点队列里剩下的所有代表节点深度累加，输出 sum——这组数据的答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5, M = 26;

struct node {
    char ch;
    int dep, tot, nxt[M];
} tr[N];

int cnt;
void init(int rt=0) {
    cnt = 0;
    tr[rt].dep = 0; tr[rt].tot = 0;
    for (int &i : tr[rt].nxt) i = -1;
}

void insert(char s[], int rt=0) {
    if (strlen(s) == 0) { tr[rt].tot++; return; }//单词走完，本节点结尾计数+1
    int id = s[0] - 'a';//当前字母下标（0~25）
    if (tr[rt].nxt[id] == -1) {//该孩子还不存在
        tr[rt].nxt[id] = ++cnt;//新建节点，编号 +1
        tr[cnt].dep = tr[rt].dep + 1;
        tr[cnt].tot = 0;
        for (int &i : tr[cnt].nxt) i = -1;//新节点孩子全部置 -1
    }
    insert(s+1, tr[rt].nxt[id]);//递归处理下一个字符
}
struct cmp {
    bool operator () (int a, int b) const {
        return tr[a].dep < tr[b].dep;
    }
};
priority_queue<int, vector<int>, cmp> q[N];

void dfs(int rt) {
    if (rt == -1) return;
    while (!q[rt].empty()) q[rt].pop();
    for (int x : tr[rt].nxt) {
        if (x == -1) continue;
        dfs(x);
        while (!q[x].empty()) { q[rt].push(q[x].top()); q[x].pop(); }
    }
    if (rt != 0 && tr[rt].tot == 0 && !q[rt].empty()) {
        tr[rt].tot++;
        tr[q[rt].top()].tot--;
        q[rt].pop();
    }
    if (tr[rt].tot == 1) q[rt].push(rt);
}

int n;
string s[N];
int main() {
    fast;
    while (cin >> n) {
        init();
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            insert((char*)s[i].c_str());
        }
        dfs(0);
        int sum = 0;
        while (!q[0].empty()) {
            sum += tr[q[0].top()].dep;
            q[0].pop();
        }
        cout << sum << '\n';
    }
    return 0;
}