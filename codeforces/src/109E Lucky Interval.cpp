//
// Created by Psy.C on 2025/11/14.
//
/*
*递归函数，用来计算数字x中幸运数字(4或7)的个数
如果x小于等于0，返回0(递归终止条件)
否则检查最后一位是否为4或7，是则计数+1，然后递归处理去掉最后一位的数字
 *
*检查从s1开始和从s2开始的两个长度为len的区间，对应位置的数字是否具有相同的幸运数字个数
如果有任何一对对应位置的数字幸运数字个数不同，返回false
否则返回true
 *
*寻找满足条件的最小数字
基础情况：当l等于r且l小于100时，找到l之后第一个具有相同幸运数字个数的数字
*递归处理高位部分(l/10到r/10)，然后加上l的个位数
如果高位差值大于1，则直接返回结果
 *
*在res和l附近搜索更好的答案
对于s取l和res，在范围[-100, 100]内尝试偏移量i
如果t=l+i满足条件：t大于l、t小于当前最优解ans、且[l, t]区间满足check条件，则更新ans
 *
*s = l: 从原始起点开始搜索，看是否存在更小的有效起点
s = res: 从递归构造的结果开始搜索，寻找附近的更好解
i范围[-100, 100]: 在小范围内搜索，平衡效率和准确性
 *在l和res附近搜索是为了弥补递归贪心构造的不足
 *
 *调用dfs2函数求解从a开始长度为l的区间对应的最小满足条件的数字
 */
#include <iostream>
using namespace std;


int dfs(int x) {
    return x <= 0 ? 0 :
        int(x % 10 == 4 || x % 10 == 7) +
            dfs(x / 10);
}

bool check(int s1, int s2, int len) {
    for (int i = 0; i < len; ++i) {
        if (dfs(s1 + i) != dfs(s2 + i)) return false;
    }
    return true;
}


int dfs2(int l, int r) {
    if (l == r && l < 100) {
        int res = l + 1, x = dfs(l);
        while (dfs(res) != x) ++res;
        return res;
    }
    int res = dfs2(l/10, r/10) * 10 + l%10;
    if (r / 10 > 1 + l / 10) return res;
    int ans = res;
    for (int s : {l, res}) {
        for (int i = -100; i <= 100; ++i) {
            int t = s + i;
            if (t > l && t < ans &&
                check(l, t, r - l + 1)) {
                ans = t;
            }
        }
    }
    return ans;
}



int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int a, l; cin >> a >> l;
    int res = dfs2(a, a + l - 1);
    cout << res << '\n';
    return 0;
}