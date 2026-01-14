//
// Created by Psy.C on 2026/1/14.
//
/**
* n: 表示顾客数量
flag = 1: 标志变量，1表示能找开钱，0表示不能找开钱
 *t: 存储当前顾客支付的钱币面额
 *b[i]表示面额为i的钱币数量
 *
 *b[t]++;: 将对应面额的钱币数量加1（收银台收到这张钱）
 *如果之前已经无法找开钱（flag=0），则跳过后续处理
 *如果顾客给的是25元，不需要找零，直接进入下次循环
*如果顾客给的是50元，需要找25元零钱
if (b[25] != 0): 检查是否有25元零钱可找
{ b[25]--; continue; }: 如果有，减少一张25元，继续下一次循环
*如果顾客给的是100元，需要找75元零钱
第一种找零方式: 一张50元+一张25元
if (b[50] >= 1 && b[25] >= 1): 检查是否有1张50元和1张25元
b[50]--; b[25]--; continue;: 如果有，减少相应数量并继续
第二种找零方式: 三张25元
if (b[25] >= 3): 检查是否有至少3张25元
b[25] -= 3; continue;: 如果有，减少3张25元并继续
*如果上述所有找零方式都失败（即100元时既没有"50+25"也没有"三个25元"）
或者50元时没有25元可找
设置flag为0，表示无法完成交易
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, flag = 1; cin >> n;
    for (int i = 1, t, b[500]={}; i <= n; ++i) {
        cin >> t; b[t]++;
        if (flag == 0) continue;//跳过后续处理
        if (t == 25) continue;//直接进入下次循环
        if (t == 50) { if (b[25] != 0) { b[25]--; continue; } }
        if (t == 100) {
            if (b[50] >= 1 && b[25] >= 1) {
                b[50]--; b[25]--; continue;
            }
            if (b[25] >= 3) { b[25] -= 3; continue; }
        }
        flag = 0;
    }
    if (flag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}