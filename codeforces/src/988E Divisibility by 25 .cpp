//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
能被25整除的数，其末两位必须是：00、25、50、75 之一。
由于只能从右往左删数字，所以关键是：找到两个位置 i, j（i<j），使得 v[i]v[j] 构成 00 / 25 / 50 / 75，然后计算需要删掉多少个数字
反复取 n % 10 得到个位，n /= 10 去掉个位，存入 v。
此时 v 是逆序（个位在前）。
ranges::reverse(v) 翻转，使 v 变成从最高位到最低位的顺序，v[0] 是最高位
i, j 是要作为"新数末两位"的两个位置。i 是末两位的十位位置，j 是个位位置。i≠j
两个都是0 → 末两位是 00。成立（因为 00 可被25整除）。

删除次数计算：

要保留位置 i 和 j 作为末两位（i<j）。
位于 j 右边（比 j 更低位）的数字都要删：m-j-1 个。
i 和 j 之间（不含两端的）数字也要删：j-i-1 个。
总数 = (m-j-1) + (j-i-1) = m-i-2
即 (i,j) 的末两位组合是 25 / 50 / 75 之一
t 初始：先把基础删除次数算出来。
-(i<j)：若 i<j（十位在个位左边）减1
找到第一个0的位置 idx。
如果形成了像 0X 这种以0开头的前导零情况，需要把多余的前导0也删掉（否则删完剩下的数可能有前导零，前面的0也要算在删除步骤里）。
若删完发现还是以0开头（无法去掉），设为 inf（不可行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
using namespace std;
constexpr int inf = 1e9;

ll n;
vector<int> v;
int main() {
    fast;
    cin >> n;
    while (n != 0) { v.push_back(n%10); n /= 10; }
    ranges::reverse(v);
    int m = v.size(), res = 1e3;
    rep(i,v.size()) rep(j,v.size()) {
        if (i == j) continue;
        if (v[i] == 0 && v[j] == 0) res=min(res,m-i+m-j-3);
        else if (v[i] == 2 && v[j] == 5 ||
            v[i] == 5 && v[j] == 0 || v[i] == 7 && v[j] == 5) {
            int t = m-i+m-j-2-(i<j), idx = -1;
            rep(k,v.size()) if (v[k] == 0) { idx = k; break; }
            if (idx != j && idx != -1 && ((i==0&&idx==1)||(i==0&&j==1&&idx==2)||
                (j==0&&idx==1))) {
                for (int k = idx+1; k < v.size(); ++k) if (v[k] != 0) { idx = k; break; }
                if (v[idx] == 0) t = inf; else t += idx - (j==1 ? 2 : 1);}
            res = min(res, t);
        }
    }
    if (res == 1e3) cout << "-1\n"; else cout << res << '\n';
    return 0;
}