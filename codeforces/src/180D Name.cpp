//
// Created by Psy.C on 2025/12/1.
//
/*
*p：源字符串（提供字符资源）
q：目标字符串（字典序下界）
n：源字符串长度
m：目标字符串长度
cnt[M]：每个字母的可用数量计数器
ans[N]：构造的答案字符串（ans[0]存储长度）
 *
*字典序比较函数：
比较当前构造的字符串ans与目标字符串q的字典序关系
返回值含义：
-1：ans < q（字典序小于目标）
0：ans = q（完全相等）
1：ans > q（字典序大于目标）
比较过程：
逐位比较字符
如果发现不等，立即返回比较结果
如果前缀相等，比较长度
 *
*i：当前要填充的位置（相对于目标字符串q的位置）
k：当前构造字符串与目标字符串的比较结果
如果k > 0（已大于目标），返回成功
如果i >= m（已超过目标长度）：
如果相等，只有当源字符串更长时才成功（可以添加更多字符）
 *
*从q[i]开始尝试字符（保证不低于目标字符串）
如果该字符还有剩余，就使用它
递归处理下一个位置
如果成功，返回true
否则回溯：恢复状态并尝试下一个字符
 *
*ans[0] 被用作长度计数器，记录当前数组中有效元素的个数
ans[1] 到 ans[ans[0]] 存储实际的数据元素
*增加数组长度：ans[0]++
在新位置存储元素：将字符 c 转换为数字后存储到新位置
实现动态数组添加元素的效果
 *
*减少数组长度计数器 --ans[0]
逻辑上"删除"最后一个元素（实际数据还在，但不再被视为有效）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) (static_cast<int>((x).size()))
#define N 5005
#define M 26
using namespace std;

string p, q;
int n, m, cnt[M], ans[N];

int isb() {
    for (int i = 1; i <= ans[0] && i - 1 < m; ++i) {//ans[i] 对应 q[i-1]
        if (ans[i] < q[i - 1] - 'a') return -1;
        if (ans[i] > q[i - 1] - 'a') return 1;
        // 如果相等，继续比较下一位
    }
    //如果执行到这里，说明所有对应位置都相等（前缀相等）
    if (ans[0] == m) return 0;//长度也相等，完全相等
    if (ans[0] > m) return 1;//ans更长
    return -1;//ans更短
}

bool dfs(const int i) {
    const int k = isb();
    if (k > 0) return true;
    if (i >= m) {
        if (k == 0) return n > m;
    }
    for (char c = q[i]; c <= 'z'; ++c) {
        if (cnt[c - 'a'] == 0) continue;
        --cnt[c - 'a'];
        ans[++ans[0]] = c - 'a';
        if (dfs(i + 1)) return true;
        --ans[0];
        ++cnt[c - 'a'];
    }
    return false;
}

int main() {
    fast;
    cin >> p >> q; n = sz(p), m = sz(q);
    for (auto& i : cnt) i = 0;
    for (int i = 0; i < n; ++i) ++cnt[p[i] - 'a'];//统计源字符串中每个字符的数量
    ans[0] = 0;//初始化答案字符串长度
    if (!dfs(0)) cout << "-1\n";
    else {//输出已构造的部分（满足字典序要求的前缀）
        for (int i = 1; i <= ans[0]; ++i) cout << static_cast<char>(ans[i] + 'a');
        for (int i = 0; i < M; ++i)//输出剩余的字符（按字典序排列，作为后缀）
            for (int j = 0; j < cnt[i]; ++j)
                cout << static_cast<char>(i + 'a');
        cout << '\n';
    }
    return 0;
}