//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
"字符→已分配值"的映射表；c 是"值→是否占用"的反向占用表。两者构成双向唯一性约束
x：截止到上一位置，映射串与下界 a 的前缀完全相等，因此当前位置的值必须 ≥ a[now]，否则会小于 a。x=1 表示卡在下界。
y：前缀与上界 b 完全相等，因此当前位置必须 ≤ b[now]。y=1 表示卡在上界。
当既不卡上界也不卡下界时（已进入区间内部），取值自由：l=1, r=k
如果当前字符 s0[now] 之前已分配过值 sum：

若 sum 不在当前步允许的 [l,r] 区间 → 直接返回（剪枝）。
否则更新 x,y：若 sum==l 说明仍贴着下界（保持 x），否则 x 清零（前缀不再与 a 相等，之后不受下界限制）。y 同理。注意用乘法 x*(sum==l) 实现"只有原本卡着才可能继续卡"
给该字符尝试一个未占用的值 i，标记占用后递归；成功（f=1）即返回，否则回溯。枚举顺序从小到大，因此找到的解倾向于让映射尽量小
无解则 NO。
YES 时，i13[1..k] 中某些值（未在 s 中出现过的字符对应的槽位）仍未分配。用贪心把剩余未占用的值按最小可用依次填充给这些槽位，最终打印 i13[i]+96 即把每个值还原成对应字母（值 1→'a'…）。putchar('\n') 保证每行输出换行，避免 case 粘连
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1919810;

int n, f = 0, k, a0[N], b0[N], i13[N], s0[N], c[N];
void dfs(int now, int x, int y) {
    if (now == n+1) { f = 1; return; }
    int l = 1, r = k;
    if (x) l = a0[now];
    if (y) r = b0[now];
    if (i13[s0[now]]) {
        int sum = i13[s0[now]];
        if (sum < l || sum > r) return;
        int da = x*(sum==l), db = y*(sum==r);
        dfs(now+1, da, db);
        return;
    }
    if (f) return;
    for (int i = l; i <= r; i++) {
        if (!c[i]) {
            c[i] = 1;
            i13[s0[now]] = i;
            int da = x*(i==l), db = y*(i==r);
            dfs(now+1, da, db);
            if (f) return;
            c[i] = 0;
            i13[s0[now]] = 0;
        }
        if (f) return;
    }
}

string s, a, b;
void solve() {
    f = 0;
    cin >> k >> s >> a >> b; n = s.size();
    //s 中第 i 个位置的字符值  下界 a 的第 i 字符值  上界 b 的第 i 字符值
    rep(i,n) { s0[i] = s[i-1] - 'a' + 1; a0[i] = a[i-1] - 'a' + 1; b0[i] = b[i-1] - 'a' + 1; }
    rep(i,k) c[i] = 0;//该值是否已被占用（1=占用）
    rep(i,k) i13[i] = 0;//s 中该字符"已被映射到的值"，0=未定
    dfs(1,1,1);
    if (!f) { cout << "NO\n"; return; }
    cout << "YES\n";
    int p = 1;
    rep(i,k) if (!i13[i]) for (int j = p; j <= k; j++) if (!c[j]) {
        c[j] = 1; i13[i] = j; p = j+1; break;
    }
    rep(i,k) printf("%c",i13[i]+96);
    putchar('\n');
}


signed main() {
    int T; cin >> T;
    while (T--) solve();
    return 0;
}