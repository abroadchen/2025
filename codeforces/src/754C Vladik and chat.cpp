//
// Created by Psy.C on 2026/9/1.
//
/**
N constexpr int 最大消息/用户数 = 105
chat struct 一条聊天消息，含用户名 u 和文本 t
sc[N][N] bool sc[i][j] = true 表示 消息 i 不能分配给用户 j
o[N] int 最终分配方案： o[i] = 消息 i 分配给的用户编号

辅助函数 f —— 判断子串出现位置是否合法
判断字符串 s 是否作为 完整单词 出现在 p 中
p.find(s) 返回 s 在 p 中首次出现的位置索引；找不到返回 string::npos （特殊常量 -1 ）
条件 a：子串是否存在
- a = true → s 作为子串出现在 p 中
- a = false → 完全没出现，后面不用看了 条件 b：左边界检查
x == 0           → s 在 p 的开头位置，左边没有字符，自动合法
!isalnum(p[x-1]) → s 左边那个字符不是字母/数字（是空格、标点等）
!isalnum(s[0])   → s 的第一个字符本身不是字母/数字（比如以空格开头）
条件 c：右边界检查
!isalnum(p[x+s.size()])   → s 右边那个字符不是字母/数字
!isalnum(s[s.size()-1])   → s 的最后一个字符本身不是字母/数字
三个条件全满足 → s 是 p 中的一个完整单词。

tt —— 回溯搜索合法分配方案
u 用户总数
ts 消息总数
now 当前要处理的消息编号 （从 1 开始）
us[] 用户名数组， us[i] = 第 i 个用户的名字
r[] 消息数组， r[i] = 第 i 条消息
- now > ts ：已经处理完所有消息 1~ts，找到合法方案！
- 输出时， r[i].t 最后一个字符被去掉——因为读入时加了一个 ' ' （后面会看到）
- us[o[i]].c_str() ： o[i] 存的是用户编号（1~u）， us[o[i]] 是对应名字
约束 1 sc[now][i] == false 消息 now 可以 分配给用户 i（sc=true 表示禁止）
约束 2 i != o[now-1] 不能和 上一条消息 分配给同一个用户（ o[now-1] 是上一条的分配）

7 个字符 ，用于辅助判断单词边界：
wc[k] + us[j] + wc[l] 构造一个"被标点/空格包围的用户名"，然后检查这个完整单词是否出现在消息文本中。
- sc 全部清零 → 初始状态： 所有消息都可以分配给所有用户
- o 全部清零 → 还没开始分配
- a = 用户总数
- cin >> us[i] 读入每个用户名（不含空格）
- getline(cin, x) 吃掉换行符和多余空白
输入每行是 username: message text 格式。

填充约束表 sc —— 两条路径
路径 1：原消息用户名是 '?' （匿名）
如果消息 i 是匿名的，那么检查 所有可能的用户名 j ——如果 k + us[j] + l （被标点包围的用户名）
出现在消息文本中 ，说明这个消息 不可能 是用户 j 发的（用户全名不能出现在自己消息里），标记 sc[i][j] = true （禁止）。
|= 是关键 ： sc[i][j] |= ... 表示只要有一种标点组合检测到用户名是完整单词，就标记禁止。多种组合取 OR。
路径 2：原消息用户名已知
消息 i 的用户名是 rd[i].u （已知）。
j 就是发这条消息的人 us[j] == rd[i].u 0（允许） 1（禁止上一条同用户） 1（禁止下一条同用户）
j 不是发这条消息的人 else 1（禁止） 不变 不变
提前检查无解情况
如果某条消息 i 对 所有用户 都禁止（ sc[i][1..a] 全是 true），那么这条消息没人能发 → 无解。
hv == a ：sc[i] 中 true 的个数等于用户总数 → 全部禁止 → 提前输出 Impossible 。
尝试回溯搜索
- 从消息 1 开始 DFS 搜索，分配给 a 个用户
- 找到合法方案 → tt 内部已经输出了，返回 true
- 找不到 → 输出 Impossible

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 105;

struct chat { string u, t; };

bool f(string p, string s) {
    auto x = p.find(s);
    bool a = (x != string::npos), b = (x == 0 || !isalnum(p[x-1]) || !isalnum(s[0])),
    c = !isalnum(p[x+s.size()] || !isalnum(s[s.size()-1]));
    return a && b && c;
}

int o[N];
bool sc[N][N];
bool tt(int u, int ts, int now, string us[], chat r[]) {
    if (now > ts) {
        for (int i = 1; i <= ts; ++i) {
            cout << us[o[i]].c_str();
            for (int j = 0; j < r[i].t.size()-1; ++j)
                cout << r[i].t[j];
            cout << '\n';
        }
        return true;
    }
    for (int i = 1; i <= u; ++i) {
        if (sc[now][i] == false && i != o[now-1]) {
            o[now] = i;
            if (tt(u, ts, now+1, us, r) == true)
                return true;
        }
    }
    return false;
}

char wc[] = {'\0', ' ', ',', '.', '!', '?', ':'};
string x;
void solve() {
    memset(sc, 0, sizeof sc);
    memset(o, 0, sizeof o);
    int a; cin >> a; getline(cin, x);
    string us[N];
    for (int i = 1; i <= a; ++i) cin >> us[i];
    getline(cin, x);
    int b; cin >> b; getline(cin, x);
    chat rd[N];
    for (int i = 1; i <= b; ++i) {
        getline(cin, x); x = x + ' ';
        string z; int j;
        for (j = 0; x[j] != ':'; ++j) z = z + x[j];
        rd[i].u = z; z = "";
        for (int k = j; k < x.size(); ++k) z = z + x[k];
        rd[i].t = z;
    }
    for (int i = 1; i <= b; ++i) {
        if (rd[i].u == "?") {
            for (int j = 1; j <= a; ++j)
                for (char k : wc)
                    for (char l : wc)
                        sc[i][j] |= f(rd[i].t, k+us[j]+l);
        } else {
            for (int j = 1; j <= a; ++j) {
                if (us[j] == rd[i].u) {
                    sc[i][j] = 0;
                    sc[i-1][j] = sc[i+1][j] = 1;
                } else sc[i][j] = 1;
            }
        }
    }
    int hv = 0;
    for (int i = 1; i <= b; ++i) {
        for (int j = 1; j <= a; ++j) hv += sc[i][j];
        if (hv == a) { cout << "Impossible\n"; return; }
        hv = 0;
    }
    if (!tt(a, b, 1, us, rd)) cout << "Impossible\n";
}

int main() {
    fast;
    int a; cin >> a; getline(cin, x);
    while (a--) solve();
    return 0;
}