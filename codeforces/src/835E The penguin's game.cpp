//
// Created by Psy.C on 2026/9/25.
//
/**
N：下标集合数组容量（最多 1010 个元素）。
st[N]：临时存放当前要询问的下标集合
询问下标 st[l] 到 st[r] 这一连续段（共 r-l+1 个下标）的异或结果。
交互协议输出：? 个数 下标1 下标2 ...
读入返回的 ret。
返回值 ret 就是该集合的异或值（包含 0 或 2 个"不同数"时为 0，包含 1 个时为其本身）
读入元素个数 n 和两个不同元素的值 x、y（题目输入会给这两个值，但程序实际只用 x^y 判断）
对每个二进制位 i（0..9）：
把所有下标中第 i 位为 1 的下标收集到 st[1..top]。
若 top==0（这一位没有下标为 1 的元素）则 break（后续更高位也不会有）。
输出询问这 top 个下标，得到 ret。
关键判断：x 和 y 是仅有的两个不同数。如果它们在第 i 位上不同，那么集合中"恰好含一个不同数"，异或结果不为 0（等于 x 或 y）。题目提供的 x、y 值让代码用 ret==(x^y)||ret==y 来判断。
一旦发现该位能区分两个数（即返回非 0），记录该位 id = i，并把该位计入 p。
循环结束后，p 是 x 和 y 不同的那些二进制位拼成的值 = x ^ y？（实际上由题设逻辑，p 累积后等于 x^y，id 是其中某一位，用来把下标集合二分成一半）。
选取区分位 id，把所有第 id 位为 1 的下标按顺序收集到 st[1..top]。
二分法：在这个有序集合上定位"包含不同数的那些下标"。
每次询问 st[l..mid] 这段：
若返回非 0（即这段里有答案），则答案在左半 → r = mid。
否则在右半 → l = mid+1。
循环结束时，st[l] 就是其中一个不同数所在的下标（在"位 id 为 1"的那一半里必然包含恰好一个不同数，因为两个不同数在位 id 不同）
st[l] 是 x 和 y 中"在第 id 位为 1"的那个的值（假设该数就是 pos）。
p 是 x 和 y 异或得到的位差集合，即 p = x ^ y。
那么另一个数 = pos ^ p（因为 pos ^ (x^y) 会翻转 x 与 y 不同的那些位，从 pos 得到另一个）。
输出 min(pos, pos^p) 和 max(pos, pos^p) 即为两个不同数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1010;

int st[N];
int check(int l, int r) {
    int ret;
    cout << "? " << r - l + 1 << ' ';
    for (int j = l; j <= r; j++)
        cout << st[j] << ' ';
    cout << endl;
    cin >> ret;
    return ret;
}

int n, x, y, top, p, id, l, r;
int main() {
    fast;
    cin >> n >> x >> y;
    for (int i = 0, ret; i < 10; i++) {
        top = 0;
        for (int j = 1; j <= n; j++)
            if (j >> i & 1) st[++top] = j;
        if (!top) break;
        cout << "? " << top << ' ';
        for (int j = 1; j <= top; j++) cout << st[j] << ' ';
        cout << endl;
        cin >> ret;
        if (ret == (x ^ y) || ret == y) id = i, p += (1 << i);
    }
    top = 0;
    for (int j = 1; j <= n; j++)
        if (j >> id & 1) st[++top] = j;
    l = 1, r = top;
    while (l < r) {
        int mid = (l + r) >> 1, t = check(l, mid);
        if (t == (x ^ y) || t == y) r = mid;
        else l = mid + 1;
    }
    cout << "! " << min(st[l] ^ p, st[l]) << ' ' << max(st[l] ^ p, st[l]) << endl;
    return 0;
}