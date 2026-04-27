//
// Created by Psy.C on 2026/4/26.
//
/**
pre[N]: 前缀哈希数组
pw10[N]: 10的幂次
getnum(l,r): 获取子串s[l...r]对应的数值（模意义下）
s[N]: 输入表达式字符串
mch[N]: 括号匹配数组
bel[N]: 每个字符所属节点
cnt: 节点计数器
op[N]: 节点操作符(0:+, 1:*, -1:数字)
val[N]: 节点值
son[N]: 节点子节点列表
vl[N]: 子表达式范围列表

递归构建表达式语法分析树
处理括号、加法(*)、乘法(+)的优先级
按照运算符优先级分割表达式
用于处理可能出现的除零情况
x存储实际值，y存储"零因子"计数
在语法树上进行树形DP
计算每个节点的值和子树信息
构建稀疏表用于O(1)区间最值查询
维护深度和嵌套层级信息

预处理: O(n log n)
单次查询: O(log n)
总体: O((n + q) log n)


pre[i]: 字符串s[1...i]的前缀哈希值
pw10[i]: 10的i次方模mod的结果
获取字符串s[l...r]对应的数值(模mod)
pre[r]: 前r位的前缀哈希
pre[l-1]*pw10[r-l+1]: 前l-1位的贡献乘以相应的权值
1ll: 防止整数溢出的long long类型转换
+mod)%mod: 防止负数结果
存储输入的表达式字符串
mch[i]: 位置i处括号的匹配位置
bel[i]: 字符s[i]属于哪个节点
cnt: 节点编号计数器
op[i]: 节点i的操作符(-1:数字, 0:+, 1:*)
val[i]: 节点i的值
son[i]: 节点i的子节点列表
vl[i]: 节点i的子表达式在原字符串中的范围

递归构建表达式语法分析树
参数: 字符串区间[l, r]
如果是完整的括号表达式"(...)"，则递归处理内部
同时标记括号两端属于同一个节点
opt: 找到的第一个操作符，初始化为-1(数字)
id: 创建新节点的ID
找到最低优先级的操作符作为根节点
!~opt 等价于 opt != -1，确保只在第一次找到*时更新
遇到括号跳过整个括号块，否则逐字符前进
设置节点id的操作符
如果是数字节点(!~opt即opt == -1)
将区间[l,r]内的每个字符都标记为属于节点id
计算数值: val[id] = val[id]*10 + (s[i]-'0')
根据找到的操作符类型分割表达式
遇到同优先级操作符时创建子节点
build(pre+1, i-1): 递归构建左侧子表达式
vl[id].emplace_back(pre+1, i-1): 记录子表达式范围
bel[i] = id: 操作符属于当前节点
构建最后一个右侧子表达式
返回当前节点ID

x: 实际数值
y: 零因子计数
构造函数: 如果_x非0则x=_x,y=0；否则x=y=1(表示0)
如果y非0返回0，否则返回x
重载+运算符，处理整数相加
重载*运算符，如果o非0则正常相乘，否则增加零因子计数
重载/运算符，使用费马小定理求逆元

计算每个节点的值和前缀和/积
ss[x][i]: 节点x的前i个子节点的前缀和/积
根据操作符类型执行不同的合并操作

预处理稀疏表，支持O(1)区间最值查询

读入表达式字符串和查询次数
计算前缀哈希数组
计算10的幂次数组
找到括号匹配位置
计算前缀括号嵌套深度
nt[i]: 从位置i开始的连续数字段的结束位置
pr[i]: 从位置i结束的连续数字段的开始位置
构建语法分析树并计算
初始化稀疏表并预处理
查询处理：检查边界条件
括号不匹配、嵌套错误、边界是操作符等都返回-1

 */
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
constexpr int N = 5e5+7, M = 22, mod = 1e9+7;

int pre[N], pw10[N];
int getnum(int l, int r) {
    return (pre[r] - 1ll*pre[l-1]*pw10[r-l+1]%mod+mod)%mod;
}
char s[N];
int mch[N], bel[N], cnt, op[N],val[N];
vector<int> son[N];
vector<ii> vl[N];
int build(int l, int r) {
    if (s[l] == '(' && mch[l] == r)
        return bel[l] = bel[r] = build(l+1, r-1);
    int opt = -1, id = ++cnt;
    for (int i = l; i <= r;) {
        if (s[i] == '+') opt = 0;
        else if (s[i] == '*' && !~opt) opt = 1;
        if (s[i] == '(') i = mch[i] + 1; else i++;
    }
    op[id] = opt;
    if (!~opt) {
        for (int i = l; i <= r; ++i) {
            bel[i] = id;
            val[id] = (10ll*val[id]+s[i]-'0')%mod;
        }
        return id;
    }
    int pre = l-1;
    for (int i = l; i <= r;) {
        if ((s[i] == '+' && !opt) || (s[i] == '*' && opt)) {
            son[id].push_back(build(pre+1, i-1));
            vl[id].emplace_back(pre+1, i-1);
            pre = i; bel[i] = id;
        }
        if (s[i] == '(') i = mch[i] + 1; else i++;
    }
    son[id].push_back(build(pre+1, r));
    vl[id].emplace_back(pre+1, r);
    return id;
}

int ksm(int x, int e) {
    int ret = 1;
    for (; e; e>>=1, x=1ll*x*x%mod)
        if (e&1) ret=1ll*ret*x%mod;
    return ret;
}

struct n0 {
    int x, y;
    n0(int _x=0) { _x ? x = _x, y = 0 : x = y = 1; }
    int val() const { return y ? 0 : x; }
    n0 operator+(const int& o) const {
        int sum = (val() + o) % mod;
        return sum ? n0(sum) : n0(0);
    }
    n0 operator*(const int& o) const {
        n0 res = *this;
        o ? res.x=1ll*res.x*o%mod : res.y++;
        return res;
    }
    n0 operator/(const n0& o) const {
        n0 res; res.x = 1ll*x*ksm(o.x, mod-2)%mod;
        res.y = y - o.y;
        return res;
    }
};

vector<n0> ss[N];
int dep[N];
void calc(int x) {
    if (~op[x]) val[x] = op[x];
    ss[x].resize(son[x].size());
    for (int i = 0; i < son[x].size(); ++i) {
        int y = son[x][i];
        dep[y] = dep[x] + 1; calc(y);
        if (!i) ss[x][i] = val[y];
        if (op[x] == 0) {
            val[x] = (val[x] + val[y]) % mod;
            if (i) ss[x][i] = ss[x][i-1] + val[y];
        } else {
            val[x] = 1ll*val[x]*val[y]%mod;
            if (i) ss[x][i] = ss[x][i-1]*val[y];
        }
    }
}

int st_sum[N][M], n;
ii st_dep[N][M];
void build_st() {
    for (int i = 1; i <= M-2; ++i)
        for (int j = 1; j+(1<<i)-1 <= n; ++j) {
            st_sum[j][i] = min(st_sum[j][i-1], st_sum[j+(1<<(i-1))][i-1]);
            st_dep[j][i] = min(st_dep[j][i-1], st_dep[j+(1<<(i-1))][i-1]);
        }
}
int query_sum(int l, int r) {
    int k = 31 - __builtin_clz(r-l+1);
    return min(st_sum[l][k], st_sum[r-(1<<k)+1][k]);
}
ii query_dep(int l, int r) {
    int k = 31 - __builtin_clz(r-l+1);
    return min(st_dep[l][k], st_dep[r-(1<<k)+1][k]);
}

int q, sum[N], nt[N], pr[N], rt;
stack<int> st;
int main() {
    scanf("%s%d", s + 1, &q); n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        if (isdigit(s[i]))
            pre[i] = (10ll*pre[i-1]+s[i]-'0')%mod;
        else pre[i] = pre[i-1];
    }
    for (int i = (pw10[0]=1); i <= n; ++i)
        pw10[i] = 10ll*pw10[i-1]%mod;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '(') st.push(i), sum[i] = sum[i-1] + 1;
        else if (s[i] == ')') {
            mch[i] = st.top(); mch[st.top()] = i; st.pop();
            sum[i] = sum[i-1] - 1;
        } else sum[i] = sum[i-1];
    }
    int pp = n + 1;
    for (int i = n; i; --i) {
        if (!isdigit(s[i])) pp = i;
        else nt[i] = pp-1;
    }
    pp = 0;
    for (int i = 1; i <= n; ++i) {
        if (!isdigit(s[i])) pp = i;
        else pr[i] = pp+1;
    }
    rt = build(1, n); calc(rt);
    for (int i = 1; i <= n; ++i)
        st_sum[i][0] = sum[i], st_dep[i][0] = {dep[bel[i]], i};
    build_st();
    while (q--) {
        int l, r; cin >> l >> r;
        if (sum[l-1] != sum[r]) { cout << "-1\n"; continue; }//括号不匹配
        if (query_sum(l, r) < sum[l-1]) { cout << "-1\n"; continue; }//括号嵌套错误
        if (s[l] == '+' || s[l] == '*') { cout << "-1\n"; continue; }//边界是操作符
        if (s[r] == '+' || s[r] == '*') { cout << "-1\n"; continue; }
        ii p = query_dep(l, r); int x = bel[p.second];
        if (!~op[x]) {
            if (isdigit(s[l]) && isdigit(s[r])) cout << getnum(l, r) << '\n';
            else cout << val[x] << '\n';
            continue;
        }
        int L = upper_bound(vl[x].begin(), vl[x].end(), make_pair(l, n+1)) - vl[x].begin() - 1,
        R = upper_bound(vl[x].begin(), vl[x].end(), make_pair(r, n+1)) - vl[x].begin() - 1;
        if (L < 0) L = 0;
        int u = son[x][L], v = son[x][R];
        if (op[x] == 1) {
            int res = 1;
            if (L != R) { n0 z = ss[x][R-1]/ss[x][L]; res = z.val(); }
            if (~op[u]) res = 1ll*res*val[u]%mod;
            else {
                if (isdigit(s[l])) res = 1ll*res*getnum(l, nt[l])%mod;
                else res = 1ll*res*val[u]%mod;
            }
            if (~op[v]) res = 1ll*res*val[v]%mod;
            else {
                if (isdigit(s[r])) res = 1ll*res*getnum(pr[r], r)%mod;
                else res = 1ll*res*val[v]%mod;
            }
            cout << res << '\n';
        } else {
            int res = 0;
            if (L != R) res = (ss[x][R-1].val()-ss[x][L].val() + mod)%mod;
            if (~op[u]) {
                if (op[u] == 0) res = (res + val[u])%mod;
                else {
                    int t = upper_bound(vl[u].begin(), vl[u].end(),
                        make_pair(l, n+1)) - vl[u].begin() - 1;
                    if (t < 0) t = 0;
                    int su = son[u][t], mul = 1;
                    if (t + 1 != ss[u].size()) mul = (ss[u].back()/ss[u][t]).val();
                    if (~op[su]) mul = 1ll*mul*val[su]%mod;
                    else {
                        if (isdigit(s[l])) mul = 1ll*mul*getnum(l, nt[l])%mod;
                        else mul = 1ll*mul*val[su]%mod;
                    }
                    res = (res + mul)%mod;
                }
            } else {
                if (isdigit(s[l])) res = (res + getnum(l, nt[l]))%mod;
                else res = (res + val[u])%mod;
            }
            if (~op[v]) {
                if (op[v] == 0) res = (res + val[v])%mod;
                else {
                    int t = upper_bound(vl[v].begin(), vl[v].end(),
                        make_pair(r, n+1)) - vl[v].begin() - 1;
                    int sv = son[v][t], mul = 1;
                    if (t) mul = (ss[v][t-1]).val();
                    if (~op[sv]) mul = 1ll*mul*val[sv]%mod;
                    else {
                        if (isdigit(s[r])) mul = 1ll*mul*getnum(pr[r], r)%mod;
                        else mul = 1ll*mul*val[sv]%mod;
                    }
                    res = (res + mul)%mod;
                }
            } else {
                if (isdigit(s[r])) res = (res + getnum(pr[r], r))%mod;
                else res = (res + val[v])%mod;
            }
            cout << res << '\n';
        }
    }
    return 0;
}