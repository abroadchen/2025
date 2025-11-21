//
// Created by Psy.C on 2025/11/21.
//
/*
 *n:数组长度, a:原数组, pos:符合条件位置, pre:前驱数组
 *
*(pos[k]-*l)：区间长度
// (pos[i-1]-pos[k])：某种系数
// (pos[i]-pos[i-1])：另一种系数
 */
#include <cstdio>
#include <set>
using namespace std;

typedef unsigned long long ull;
const int N = 1e5+5, M = 1005;
int n, a[N], pos[M], pre[M];
set<int> s;//用于维护位置集合
set<int>::iterator l, r;

bool ok(int x) {//判断数字是否只包含4和7
    while (x) {
        if (x % 10 != 4 && x % 10 != 7) return 0;//x的最后一位既不是4也不是7
        x /= 10;//去掉x的最后一位
    }
    return 1;
}

ull C(int n, int m) {
    if (m == 2) return (ull)n * (n - 1) / 2;
    if (m == 3) return (ull)n * (n - 1) * (n - 2) / 6;
    if (m == 4) return (ull)n * (n - 1) * (n - 2) / 6 * (n - 3) / 4;//C(n,4) = n*(n-1)*(n-2)*(n-3)/(4*3*2*1)
}

int main() {
    while (~scanf("%d", &n)) {
        int m = 0;//符合条件的数字个数
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            if (ok(a[i])) pos[++m] = i;//记录符合条件数字的位置
        }
        pos[m+1] = n+1;//设置边界条件 在最后一个符合条件位置之后添加一个虚拟位置
        for (int i = 1; i <= m; ++i) {//计算每个符合条件位置的前驱位置（相同数字的最近位置）
            pre[i] = 0;//表示没有前驱
            for (int j = i - 1; j >= 1; --j) {//从当前位置的前一个位置开始向前搜索
                if (a[pos[i]] == a[pos[j]]) {//如果找到相同数值的位置
                    pre[i] = j;
                    break;
                }
            }
        }
        ull ans = C(n, 4) + 2ull * C(n, 3) + C(n, 2);
        for (int i = 2; i <= m; ++i) {//减去不合法的四元组
            s.clear(); s.insert(0); ull res = 0;
            for (int j = i; j <= m; ++j) {//对于每个起始位置i，计算影响范围
                if (pre[j] < i) {//位置j的前驱不在当前考虑范围内
                    for (int k = pre[j]; k; k = pre[k]) {//处理所有前驱位置
                        l = r = s.lower_bound(pos[k]); l--;//大于等于该值的第一个元素
                        //l向前移动一位，指向小于pos[k]的最大元素
                        if (r == s.end()) {
                            res+=(ull)(pos[k]-*l)*(pos[i-1]-pos[k])*(pos[i]-pos[i-1]);
                            res+=(ull)(pos[k]-*l)*C(pos[i]-pos[i-1]+1,2);
                        } else res+=(ull)(pos[k]-*l)*(*r-pos[k])*(pos[i]-pos[i-1]);
                        s.insert(pos[k]);
                    }
                }
                ans -= res * (pos[j + 1] - pos[j]);//减去当前的贡献
            }
        }
        printf("%llu\n", ans);
    }
    return 0;
}