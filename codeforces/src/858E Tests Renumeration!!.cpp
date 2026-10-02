//
// Created by Psy.C on 2026/10/2.
//
/**
qr：已占编号 ≤ exn 区域、但属性是 1（错位，应滚去 >exn 区）的元素 → 想移到右侧
qe：已占编号 > exn 区域、但属性是 0（错位，应滚去 ≤exn 区）的元素 → 想移到左侧
rr/re：空槽位。rr 是 >exn 区的空位（right 区），re 是 ≤exn 区的空位
er/ee：名字无法解析成合法编号（get 返回 0）的元素，即完全没法定位、需要临时槽帮忙的"游离元素"。er=属性0，ee=属性1。
简单说：qr,qe 是"错位但占着合法编号位"的；rr,re 是"空槽"；er,ee 是"名字乱、没占编号位"的。
仅当字符串全为数字、无前导 0 时返回其数值，否则返回 0 表示"名字无法解析成合法编号"（比如 lmy999 这类含字母的名字）
读入 n 个条目，a[i].first 是名字字符串，a[i].second 是 0/1 属性。
exn 累加 = 属性为 1 的条目总数。含义：编号 ≤ exn 的位置应放属性 0，编号 > exn 的位置应放属性 1
re（≤exn 空槽）要接收从 qe 里出来的属性=1 元素（正确，因为 ≤exn 区放属性1）。
rr（>exn 空槽）要接收从 qr 里出来的属性=0 元素（正确，因为 >exn 区放属性0）
qe（占 >exn 位但属性1，属"左区元素"）→ 移到 re（≤exn 空槽）。它腾出的原位置（>exn）变成空槽，加入 rr。
qr（占 ≤exn 位但属性0，属"右区元素"）→ 移到 rr（>exn 空槽）。它腾出的原位置（≤exn）变成空槽，加入 re。
一轮下来 re 和 rr 会不断产生新的空槽，所以用 while(con) 反复跑直到没有可配对的。
这样错位元素通过"空槽接力"逐步归位。当没有空槽可用时（rr,re 都空但 qr,qe 都非空），说明所有槽位都被占满且都错位，就借临时槽 lmy999
之后就能继续匹配了。最后 flag 阶段再把临时槽里的那个元素放回：
er（名字乱、属性0）逐个移到 rr（>exn 空槽）。
ee（名字乱、属性1）逐个移到 re（≤exn 空槽）。
用完对应的空槽。
先输出总步数，再按行输出每一步 move A B
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+10;
int n, con, exn, ans, flag;
pair<string, int> a[N];
bool used[N];
queue<int> qr, qe, er, ee, rr, re;
inline void solve() {
    auto get = [&](string s) -> int {
        int len = s.size(), num = 0;
        for (int i = 0; i < len; ++i)
            if (!isdigit(s[i])) return 0;
        if (s[0] == '0') return 0;
        for (int i = 0; i < len; ++i)
            (num*=10) += s[i]^48;//逐位累加
        return num;
    };
    cin >> n; con = 1;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].first >> a[i].second, exn += a[i].second;
    for (int i = 1; i <= n; ++i) {
        int num = get(a[i].first);
        if (num > 0 && num <= n) {//名字可解析且编号在 1..n
            used[num] = 1;
            if (num <= exn && a[i].second == 0) qr.emplace(num);//错位：应0位放了1
            if (num > exn && a[i].second == 1) qe.emplace(num);//错位：应1位放了0
        } else {//名字不可解析（游离元素)
            if (a[i].second == 0) er.emplace(i);
            if (a[i].second == 1) ee.emplace(i);
        }
    }
    ostringstream os;
    for (int i = 1; i <= n; ++i)
        if (!used[i]) i <= exn ? re.emplace(i) : rr.emplace(i);
    if (rr.empty() && re.empty() && !qr.empty() && !qe.empty()) {
        ++ans, flag = 1, os << "move " << qr.front() << " lmy999" << endl;
        re.emplace(qr.front()), qr.pop();
    }
    while (con) {
        con = 0;
        while (!re.empty() && !qe.empty()) {
            con = 1, ++ans, os << "move " << qe.front() << ' ' << re.front() << endl;
            rr.emplace(qe.front()), qe.pop(), re.pop();
        }
        while (!rr.empty() && !qr.empty()) {
            con = 1, ++ans, os << "move " << qr.front() << ' ' << rr.front() << endl;
            re.emplace(qr.front()), qr.pop(), rr.pop();
        }
    }
    while (!er.empty())
        ++ans, os << "move " << a[er.front()].first << ' ' << rr.front() << endl, er.pop(), rr.pop();
    while (!ee.empty())
        ++ans, os << "move " << a[ee.front()].first << ' ' << re.front() << endl, ee.pop(), re.pop();
    if (flag) ++ans, os << "move lmy999 " << rr.front() << endl;
    cout << ans << endl << os.str() << endl;
}

signed main() {
    fast;
    solve();
    return 0;
}