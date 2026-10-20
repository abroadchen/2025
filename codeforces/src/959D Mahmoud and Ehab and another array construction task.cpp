//
// Created by Psy.C on 2026/10/20.
//
/**
num：一个 set<int>，初始化时装入 2..N-1 的所有数，作用是"候选数值池"。
mn[x]：x 的最小质因子（smallest prime factor）‍，预处理用
第一轮：把所有 i=2..N-1 插入 num。
if (mn[i]) continue;：若 mn[i] 非 0，说明 i 已被更小的质数标过（非质数），跳过。
内层：若 mn[i]==0（说明 i 是质数），则对所有 i 的倍数 j，若 mn[j] 还没被赋值，就赋为 i。
这实际是线性筛/埃氏筛的最小质因子版：mn[x] 记录 x 的最小质因子
fac 是全局 set<int>，记录当前已选序列所有数中出现过的所有质因子（注意它在 main 里没被清空，会持续累积）。
check(x) 分两步：
检测阶段：把 x 的每个不同质因子 p 拿出来，若 fac 里已存在 p（即与之前选过的数冲突），返回 false（不能选）。
登记阶段：若都通过，再把 x 的所有质因子插入 fac，表示"这个数被选中了"，返回 true。
注意：while (x%p==0) x/=p 是为了去除重复质因子，保证每个质因子只检测/登记一次

init()：预先生成 mn[] 和 num 池。

cin >> n：读要构造的序列长度。

bool f = 0：标记"是否已经进入严格递增/大于原输入的阶段"。

外层循环（对每个输入 x）：

cin >> x：读第 i 个输入值。
auto it = f ? num.begin() : num.lower_bound(x);
若 f==0（还没触发"大于"），从 num 中找第一个 ≥ x 的位置（lower_bound(x)）。
若 f==1（已触发），每次都从 num.begin() 最小数开始。
内层 while：遍历候选数 t（从 it 开始）：
if (check(t))：若 t 与已选数互质（质因子无冲突），则选中：
if (t > x) f = 1;：如果选出的数大于当前输入 x，说明此位置被迫用更大的数，从此进入"自由选择最小可用数"模式（f=1）。
ans[cnt++] = t;：把 t 写入答案。
break;：跳出内层，处理下一个输入。
it = num.erase(it);：若 t 冲突不能用，则把 t 从 num 中永久删除，并 erase 返回下一个迭代器继续尝试（注意 num.erase(it) 返回删除后的下一个元素迭代器）。
输出：逐行打印 n 个 ans[i]。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e6;

set<int> num;
int mn[N];
void init() {
    for (int i = 2; i < N; ++i) {
        num.insert(i);
        if (mn[i]) continue;
        for (int j = i; j < N; j += i)
            if (!mn[j]) mn[j] = i;
    }
}

set<int> fac;
bool check(int x) {
    int t = x;
    while (x != 1) {
        int p = mn[x];
        if (fac.contains(p)) return false;
        while (x%p == 0) x/=p;
    }
    while (t != 1) {
        int p = mn[t];
        fac.insert(p);
        while (t%p == 0) t/=p;
    }
    return true;
}

int ans[N], cnt;
int main() {
    fast;
    init();
    int n; cin >> n;
    bool f = 0;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        auto it = f ? num.begin() : num.lower_bound(x);
        while (it != num.end()) {
            int t = *it;
            if (check(t)) {
                if (t > x) f = 1;
                ans[cnt++] = t;
                break;
            }
            it = num.erase(it);
        }
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    return 0;
}