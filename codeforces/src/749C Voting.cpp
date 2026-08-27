//
// Created by Psy.C on 2026/8/27.
//
/**
- queue<char> q ： 字符队列 ，用于模拟消除过程。字符从队首取出，未被消除的从队尾重新入队。
- string s ：存储输入的字符串。
- n ：字符串长度。
- cd ：当前队列中 剩余的 D 的总数 （动态统计）。
- cr ：当前队列中 剩余的 R 的总数 （动态统计）。
- pd ：当前匹配过程中 等待被 R 消除的 D 的数量 （配对中等待的 D ）。
- pr ：当前匹配过程中 等待被 D 消除的 R 的数量 （配对中等待的 R ）
读入字符串长度 n 和字符串 s
遍历字符串的每个字符：
- 若是 D ， cd++ （D的总数加1）；否则 cr++ （R的总数加1）。
- q.push(s[i]) ：将每个字符依次入队，构建初始队列
cd 是 D的总数 ， cr 是 R的总数 。如果 cd == cr ，最终会全部消除；如果不相等，多出来的那种字母就是最终答案
同时存在未消除的D和未消除的R时 ，继续尝试配对消除。
- cd ：剩余的D数量。
- cr ：剩余的R数量。
- 当其中一个为0时，说明无法继续消除，循环终止
从队列中取出队首字符，存到 cur ，并将其从队列中移除。
- q.front() ：获取队首字符（不删除）。
- q.pop() ：删除队首字符
当前字符是 D
- 条件 pr > 0 ：存在 等待与D配对的R （即之前遇到的、未被消除的R）。
  - cd-- ：消除一个D（当前的D被消除）。
  - pr-- ：消除一个等待中的R（配对成功，减少一个等待的R）。
  - 注意：这里 没有将当前D重新入队 ，因为它已经被消除了。
- 否则（ pr == 0 ） ：没有等待的R可以消除当前D。
  - pd++ ：当前D成为 新的等待被R消除的D ，等待后续出现的R。
  - q.push(cur) ： 将D重新放回队尾 ，等待后续有机会被消除（R出现时）。
当前字符是 R （ cur != 'D' ，即 cur == 'R' ）
- 条件 pd > 0 ：存在 等待与R配对的D （之前遇到的、未被消除的D）。
  - cr-- ：消除一个R（当前的R被消除）。
  - pd-- ：消除一个等待中的D（配对成功）。
- 否则（ pd == 0 ） ：没有等待的D可以消除当前R。
  - pr++ ：当前R成为 新的等待被D消除的R 。
  - q.push(cur) ： 将R重新放回队尾
- 循环结束后，要么 cd == 0 ，要么 cr == 0 （或者两者都为0）。
- if (cd) ：若 cd > 0 （还有剩余的D），输出 'D' 。
- 否则 （ cr > 0 ），输出 'R'
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    queue<char> q;
    string s;
    int n, cd = 0, cr = 0, pd = 0, pr = 0;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'D') cd++; else cr++;
        q.push(s[i]);
    }
    while (cd && cr) {
        char cur = q.front(); q.pop();
        if (cur == 'D') {
            if (pr > 0) cd--, pr--;
            else { pd++; q.push(cur); }
        } else {
            if (pd > 0) cr--, pd--;
            else { pr++; q.push(cur); }
        }
    }
    if (cd) cout << 'D'; else cout << 'R';
    return 0;
}