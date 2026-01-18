//
// Created by Psy.C on 2026/1/17.
//
/**
 * mi[i]: bas^i, ha[i]: 前i个字符的哈希值
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ull unsigned long long
#define N 100010
#define bas 211
using namespace std;

ull mi[N], ha[N];
char s[N];

int n;
//从l1和l2开始长度为le的两个子串是否相等
bool ok(const int l1, const int l2, const int le) {//字符串哈希比较函数
    const int r1 = l1 + le - 1, r2 = l2 + le - 1;
    if (r1 > n || r2 > n) return false;
    const ull s1 = ha[r1] - ha[l1-1] * mi[r1 - l1 + 1],
    s2 = ha[r2] - ha[l2-1] * mi[r2 - l2 + 1];
    return s1 == s2;
}//滚动哈希算法，用于O(1)比较两个子串是否相等


bool gray[N][30];//位置i开始的长度为len[j]的串是否满足特殊条件
int len[31], num[N][26], a[N];//len: 特殊长度序列, num: 字符前缀计数, a: 字符转数字
void judge(const int l, const int k) {//位置l开始的长度为len[k]的串是否满足条件
    if (k == 1) { gray[l][k] = true; return; }//长度为1的串总是满足条件
    if (const int mid = l + len[k-1],r = l + len[k] - 1;
        num[r][a[mid]] - num[l-1][a[mid]] == 1 &&//中间字符在整个区间只出现一次
        ok(l, mid + 1, len[k-1]) && gray[l][k-1] &&
        gray[mid+1][k-1]) gray[l][k] = true;//左半部分等于右半部分且都满足条件
}

int mx;
int lcp(const int l1, const int l2) {//从位置l1和l2开始的最长公共前缀
    int le = 0;
    for (int i = mx; i >= 0; --i) if (ok(l1 + le, l2 + le, 1<<i)) {
        le += 1<<i;//如果前2^i个字符相等，则长度增加2^i
    }
    return le;//使用倍增法计算最长公共前缀，时间复杂度O(log n)
}

ll val[N][26];//位置i的字符改为字符'a'+j的价值
void f(const int l, const int k) {//计算修改价值
    const int r = l + len[k] - 1, mid = l + len[k-1];
    if (k == 1) {
        for (int i = 0; i < 26; ++i) if (a[l] != i) val[l][i]++;//每个非当前字符，增加价值1
        return;
    }
    //左右两半相等且都满足条件
    if (ok(l, mid + 1, len[k-1]) && gray[l][k-1] && gray[mid+1][k-1]) {
        //字符不同且该字符在区间内未出现
        for (int i = 0; i < 26; ++i) if (a[mid] != i && num[r][i] - num[l-1][i] == 0) {
            val[mid][i] += 1ll * len[k] * len[k];//中间位置给该字符增加价值len[k]^2
        }
    }
    const int l1 = l, l2 = mid + 1, t = lcp(l1, l2);//左半部分起点、右半部分起点和公共前缀长度
    if (t >= len[k-1]) return;
    if (l1 + t + 1 + lcp(l1 + t + 1, l2 + t + 1) < mid) return;
    //右半部分满足条件且中间字符在后半部分未出现
    if (gray[l2][k-1] && num[r][a[mid]] - num[mid][a[mid]] == 0)
        val[l1 + t][a[l2 + t]] += 1ll * len[k] * len[k];//在对应位置增加价值
    //左半部分满足条件且中间字符在前半部分未出现
    if (gray[l1][k-1] && num[mid-1][a[mid]] - num[l-1][a[mid]] == 0)
        val[l2 + t][a[l1 + t]] += 1ll * len[k] * len[k];
}

int main() {
    fast; scanf("%s", s + 1);
    n = static_cast<int>(strlen(s + 1)); mi[0] = 1;

    for (int i = 1; i <= n; ++i) {
        a[i] = s[i] - 'a';//字符转为0-25的数字
        num[i][a[i]]++;//当前位置字符计数
        for (int j = 0; j < 26; ++j) num[i][j] += num[i-1][j];
        mi[i] = mi[i-1] * bas;//bas^i
        ha[i] = ha[i-1] * bas + s[i];//滚动哈希值
    }
    for (int i = 1; i <= 30; ++i) {//特殊长度序列
        len[i] = len[i-1] * 2 + 1;
        if (len[i] > n) { mx = i - 1; break; }//超出字符串长度，停止
    }
    ll ans = 0, cost[N]={};//ans: 总价值, cost: 差分数组
    for (int i = 1; i <= mx; ++i) for (int j = 1; j <= n; ++j) {
        if (j + len[i] - 1 > n) break;
        judge(j, i);
        if (gray[j][i]) {
            ans += 1ll * len[i] * len[i];//累加基础价值
            cost[j] += 1ll * len[i] * len[i];//差分数组标记开始
            cost[j + len[i]] -= 1ll * len[i] * len[i];//差分数组标记结束
        }
    }
    for (int i = 1; i <= n; ++i) cost[i] += cost[i-1];//差分数组前缀和恢复
    for (int i = 1; i <= mx; ++i) for (int j = 1; j <= n; ++j) {//所有可能的起始位置和长度等级
        if (j + len[i] - 1 > n) break;
        f(j, i);//额外价值
    }
    ll sum = 0;
    for (int j = 1; j <= n; ++j) for (int k = 0; k < 26; ++k) {
        sum = max(sum, -cost[j] + val[j][k]);//最大的净收益
    }
    cout << sum + ans << '\n';
    return 0;
}