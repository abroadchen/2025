//
// Created by Psy.C on 2026/1/7.
//
/**
 * mat[N+5]：存储材料卡的数组
 * atk[N+5]：存储攻击卡的数组
 * mx：记录最大收益的变量
 * n是卡牌总数，m是材料卡总数
 * str[N]：读取卡牌类型的临时字符串
 */
#include <algorithm>
#include <iostream>
#include <set>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100
using namespace std;

int mat[N+5], atk[N+5], mx;
int get(const int k) {//使用前k张材料卡和k张攻击卡的收益
    int ans = 0;//初始化收益为0
    for (int i = 1; i <= k; ++i) {
        if (mat[i] >= atk[k-i+1]) ans += mat[i] - atk[k-i+1];//第i张材料卡是否能抵消第(k-i+1)张攻击卡 累加收益
        else return -1;
    }
    mx = max(mx, ans);//更新最大收益
    return ans;//返回当前收益
}


int main() {
    fast;
    int n, m; cin >> n >> m; char str[N];
    int def[N+5], defn = 0, atn = 0;//防御卡数组、防御卡计数器、攻击卡计数器
    for (int i = 1, t; i <= n; ++i) {
        cin >> str >> t;
        if (str[0] == 'D') { defn++; def[defn] = t; } else { atn++; atk[atn] = t; }
    }
    multiset<int> num;//存储材料卡
    for (int i = 1; i <= m; ++i) { cin >> mat[i]; num.insert(mat[i]); }
    sort(atk + 1, atk + 1 + atn);
    sort(mat + 1, mat + 1 + m, [](const int a, const int b) { return a > b; });
    for (int i = 1; i <= min(atn, m); ++i) get(i);//不同数量的卡牌匹配收益
    if (m > atn + defn) {//材料卡数量超过攻击卡和防御卡总数
        set<int>::iterator it;//集合迭代器
        int ok = 1;//是否能成功处理所有防御卡
        for (int i = 1; i <= defn; ++i) {
            it = num.upper_bound(def[i]);//第一个大于防御卡数值的材料卡
            if (it == num.end()) { ok = 0; break; }//没有找到合适的材料卡，标记失败
            num.erase(it);//删除使用的材料卡
        }
        if (ok == 1) {//成功处理了所有防御卡
            m = 0;
            memset(mat, 0, sizeof mat);//重置材料卡数组
            for (it = num.begin(); it != num.end(); ++it) {//将剩余的材料卡从集合复制到数组
                m++;
                mat[m] = *it;
            }
            sort(mat + 1, mat + 1 + m, [](const int a, const int b) { return a > b; });
            if (int ans = get(atn); ans != -1) {//尝试匹配所有攻击卡
                for (int i = atn + 1; i <= m; ++i) ans += mat[i];//将多余的材料卡收益加到总收益
                mx = max(mx, ans);//更新最大收益
            }
        }
    }
    cout << mx << '\n';
    return 0;
}