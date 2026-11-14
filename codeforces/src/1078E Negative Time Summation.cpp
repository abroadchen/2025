//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
① 加前导零（<--- 加前导零 --->）

dd
0l0l0l0l...0l   ← 30 个 "0" 带右移
sut0dtrsut0dtrs...   ← 反复 "取-上-停-0-下-移" 的复制动作
uerererererer...     ← 反复右移
uuuul
复制一份（0l 换成 0d、sdt0utr、uele...ldddl）
0l/0d：在当前位置写数字 0，并游标左移/下移——这一步在第二串数前面补上若干个 0，让两个数位宽对齐。
sut0dtr / sdt0utr：s(取)/u(上)/t(放)/0(写)/d(下)/r(右)——重复"复制一格内容到下一位"的动作，把第一串数整体平移复制到对齐后的位置。
uerer... / derer...：e(擦除)、r(右移)重复多次，清空/复位这一行。
一句话：给较短的数补前导零，使两数从个位到高位逐位对齐。底部 uuuul/ddddl 是游标归位到起点。
② 统计个数（<-- 统计个数 -->）

uurlstdd0uurltleurlstddddut0uudtuurltledddedeul   ← 同一行重复 30 次
这一整串（uurlstdd0uurltle...）能看懂的关键：s(取)、t(放)、0、e(擦) 的组合，配合 r/l/d/u 移动。
作用：把两串数里每一位搬运到"统计区"，统计它有几个数字 / 长度是多少（相当于求出两数的位数，用于确定补零和结果长度）。重复 30 行 = 最多处理 30 位。
③ 进位计算（<-- 进位计算 -->）

这段被拆成四个子步骤：

a. 造墙（<-- 造墙 -->）‍

rddddll0r0r0r0...r0u...r0lld
r0r0r0...r0u：在网格上写下一排 0（一面"墙"），把当前工作区和数字区隔开，为逐位进位准备进位用的"占位 0"。
b. 计算（<-- 计算 -->）‍

lrtudutdut0ddtdtuurtrdutsutluutdlddutueddtdtdtrrruultltlutdtut0u1dddtdtueueuueddl  ← 同一行重复 30 次
能拆出的核心动作：lrt、utdut0ddtd...（下移取数）、uut（上传）、ddut...、1ddd（写 1 进位）、ue（擦除上一位）……
作用：从个位到高位逐位执行"两数相加"：
取当前位两个数字；
加上上一位产生的进位 1；
结果中 ≥ 10 时在该处写 1 作为进位，下一位累加这一位；
当前位存结果的个位。
重复 30 次 = 处理 30 位，模拟了完整的进位传播。
c. 拆墙（<-- 拆墙 -->）‍

dddlererererer...uuuurere
e(擦除)、r(右移)反复：把 a 步骤造的"墙"拆掉，因为进位计算已完成。
uuuur归位。
④ 去前导零（<-- 去前导零 -->）

a. 补零（<-- 补零 -->）‍

lllllllll...l0   ← 大量 l（左移）后再写 0
游标一路左移到最高位，准备清理。
b. 去零（<-- 去零 -->）‍

erstersterst...   ← 重复 3 行
e(擦除)、r(右移)、s(取)、t(放)反复：从最高位开始，把前面多余的"前导零"逐个擦掉，直到遇到第一个非 0 数字为止。
也就是把前面为对齐补上的那些 0 清理掉。
c. 归位（<-- 归位 -->）‍

r
游标回到原位展示最终结果。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

string add(string a, string b) {
    auto trim = [](string &s) {
        int i = 0;
        while (i+1 < (int)s.size() && s[i] == '0') i++;
        s = s.substr(i);
    };
    trim(a); trim(b); ranges::reverse(a); ranges::reverse(b);
    string res;
    int c = 0, n = max(a.size(), b.size());
    for (int i = 0; i < n; i++) {
        int da = i < a.size() ? a[i]-'0' : 0, db = i < b.size() ? b[i]-'0' : 0;
        int s = da + db + c;
        res.push_back(char('0'+s%10));
        c = s/10;
    }
    if (c) res.push_back(char('0'+c));
    ranges::reverse(res);
    return res;
}

int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        string a, b; cin >> a >> b;
        cout << add(a, b) << '\n';
    }
    return 0;
}