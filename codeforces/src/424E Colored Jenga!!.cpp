//
// Created by Psy.C on 2026/2/4.
//
/**
* 哈希表结构：使用链地址法解决冲突
head[N]：哈希桶头指针数组
nxt[N]：链表指针
state[N]：存储状态
dp[N]：存储期望值
init()：初始化哈希表
find()：查找状态对应的期望值
ok()：插入新的状态-期望值对
 *
*将压缩状态x解压到数组st中
每个状态用2位表示（0-3），x的低6位存储3个状态
*
将三个状态a,b,c压缩成一个整数
保证a≤c（标准化顺序）
 *
*对状态数组a进行哈希
先排序（确保相同状态的哈希值相同）
使用67进制多项式哈希
 *
*计算当前状态的哈希值
如果已计算过，直接返回缓存结果
c[1], c[2], c[3]：分别表示选择颜色1,2,3的最小期望
*遍历所有可能的转移
解压状态i和n
!!x[0] + !!x[1] + !!x[2] == 1：只有一个非零状态，跳过
 *如果目标状态满载，增加一个新的槽位
*尝试移动颜色t
更新状态并递归计算期望
*计算概率和期望
使用公式：E = (成功期望 + 1) / (1 - 失败概率)

!!x[i] 的含义
!!x[i] 将 x[i] 转换为布尔值（0或1）
如果 x[i] ≠ 0，则 !!x[i] = 1
如果 x[i] = 0，则 !!x[i] = 0
!!x[0] + !!x[1] + !!x[2] 的含义
计算数组 x 中非零元素的个数
j == 1
检查当前处理的是中间位置（索引1）
或者中间位置本身就是空的（x[1] == 0）

 *
*时间复杂度：O(状态数)，通过记忆化避免重复计算
空间复杂度：O(状态数)，用于哈希表存储
 */
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
#define db double
#define N 4000050
#define inf 1e9
using namespace std;



struct node {
    int head[N], nxt[N], tot;
    ull state[N];
    db dp[N];
    void init() {
        memset(head, -1, sizeof(head));
        tot = 0;
    }
    [[nodiscard]] db find(const ull s) const {//在哈希表中查找状态s对应的期望值
        for (int i = head[s%N]; i != -1; i = nxt[i]) {//遍历哈希值s%N对应的链表
            if (state[i] == s) return dp[i];//找到匹配状态，返回对应期望值
        }
        return -1;
    }
    bool ok(const ull s, const db f) {//插入状态s和期望值f到哈希表
        if (find(s) > -1) return false;//状态已存在
        dp[++tot] = f;//新增节点，存储期望值
        state[tot] = s;//存储状态
        nxt[tot] = head[s%N];//将新节点链接到原有链表头部
        head[s%N] = tot;//更新哈希桶头部指针
        return true;
    }
} mat;

inline void set_st(int st[], const int x) {
    ///提取x的高2位（位4-5），存储到st[0]
    ///提取x的中间2位（位2-3），存储到st[1]
    ///提取x的低2位（位0-1），存储到st[2]
    st[0] = x>>4&3; st[1] = x>>2&3; st[2] = x&3;
}

inline int get_st(int a, const int b, int c) {
    if (a > c) swap(a, c);
    return (((a<<2)+b)<<2)+c;//a占2位，b占2位，c占2位
}


int a[20], b[20];//存储当前状态 用于排序的临时数组
ull get(const int n) {//计算状态数组的哈希值
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    sort(b + 1, b + n);//排序（确保相同状态有相同哈希值）
    ull s = 0;//初始化哈希值
    for (int i = 1; i <= n; ++i) {
        s *= 67;
        s += b[i];
    }
    return s;
}

db dfs(const int n) {
    const ull s = get(n);//计算当前状态哈希值
    db c[4] = {0, inf, inf, inf},//初始化颜色期望数组
    f = mat.find(s); if (f > -1) return f;//已计算，直接返回
    for (int i = 1; i < n; ++i) {//遍历每个槽位
        int x[3], y[3], nn = n; const int ai = a[i], an = a[n];
        set_st(x, ai); set_st(y, an);//解压状态
        if (!!x[0] + !!x[1] + !!x[2] == 1) continue;//只有一个非零状态
        if (y[0] && y[1] && y[2]) {
            nn++;//目标槽位已满（三个位置都有颜色），增加槽位数
            y[0] = y[1] = y[2] = 0;//清空目标槽位的状态
        }
        for (int j = 0; j < 3; ++j) if (x[j]) {//尝试移动x中的每个颜色
            if (!!x[0] + !!x[1] + !!x[2] == 2 && (j == 1 || !x[1])) continue;
            const int t = x[j]; x[j] = 0;//取出颜色t
            a[i] = get_st(x[0], x[1], x[2]);//更新源槽位状态
            if (!!x[0] + !!x[1] + !!x[2] == 1 || !x[1]) a[i] = 0;//只剩一个颜色，清空
            x[j] = t;//恢复x[j]的值
            for (int& k : y) if (!k) {//遍历目标槽位的空位
                k = t;//将颜色t放入空位
                a[nn] = get_st(y[0], y[1], y[2]);//更新目标槽位状态
                k = 0;//恢复k的值（继续寻找下一个空位）
                c[t] = min(c[t], dfs(nn));//更新颜色t的最小期望
            }
        }
        a[i] = ai; a[n] = an;//恢复a[i]和a[n]的原始值
    }
    if (c[1] == inf && c[2] == inf && c[3] == inf) { mat.ok(s, 0); return 0.; }//所有颜色都不可达
    db p = 1./6.;//初始失败概率
    if (c[1] == inf) p += 1./3., c[1] = 0;//颜色i不可达，增加失败概率
    if (c[2] == inf) p += 1./3., c[2] = 0;
    if (c[3] == inf) p += 1./6., c[3] = 0;
    f = (c[1]/3.+c[2]/3.+c[3]/6.+1.)/(1.-p); mat.ok(s, f);//保存结果
    return f;//返回期望值
}


int main() {
    fast;
    int n; cin >> n;//槽位数
    int F[260]{}; F['G'] = 1; F['B'] = 2; F['R'] = 3;//字符到数字的映射
    mat.init();//初始化哈希表
    char str[10];//读取字符串缓冲区
    for (int i = 1; i <= n; ++i) {
        cin >> str;
        a[i] = get_st(F[str[0]], F[str[1]], F[str[2]]);//将RGB字符串转换为状态
    }
    cout << fixed << setprecision(15) << dfs(n) << '\n';
    return 0;
}