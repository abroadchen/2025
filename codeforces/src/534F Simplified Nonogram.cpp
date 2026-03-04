//
// Created by Psy.C on 2026/3/4.
//
/**
m: 阶段数
a[10]: 限制数组
b[25]: 目标数组
p[6][25]: 结果输出矩阵
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define per(i,a,b) for(int i = a; i >= b; --i)
using namespace std;

int n;
int get(const int x) {//相邻两位中前一位为1、后一位为0的模式数量
    int c = 0;
    rep(k,0,n-1)
        if ((x>>k&1) == 1 &&
            (x>>(k+1)&1) == 0) c++;
    return c;
}

int ans[25], cnt[5];
bool dp[21][161051][33];///[阶段][状态][掩码] -> 是否可达
void dfs(const int i, const int s1, const int si) {
    if (i == 0) return;//到达第0层，递归返回
    ans[i] = si;//第i层的状态为si
    int t = s1, tot = 0;
    rep(q,0,4) cnt[q] = 0;//清空计数数组
    while (t) {//将十进制s1转换为11进制
        cnt[tot] = t%11;//取余数作为当前位的值
        t/=11;//处理下一位
        tot++;//位数计数器
    }
    rep(k,0,(1<<n)-1) {//尝试所有可能的前驱状态
        int j = 0, flg = 0;//j:前驱状态的11进制表示，flg:错误标志
        per(q,n-1,0) {//从高位到低位计算前驱状态
            //计算第q位的新值 还原DP转移时的变化
            const int x = cnt[q] - ((si>>q&1) == 1 && (k>>q&1) == 0);//当前位为1，前驱位为0 当前位减1
            if (x < 0) { flg = 1; break; }//状态非法
            j = j*11+x;//将x加入到11进制数j中
        }
        if (flg) continue;//状态非法，尝试下一个k
        if (dp[i-1][j][k]) {//找到合法的前驱状态，继续递归
            dfs(i-1, j, k);//递归到前一层
            break;//找到路径后跳出循环
        }
    }
}

int m, a[10], b[25];
bool p[6][25];
int main() {
    fast;
    cin >> n >> m;
    rep(i,0,n-1) cin >> a[i];
    rep(i,1,m) cin >> b[i];
    dp[0][0][0] = 1;//第0阶段，状态0，掩码0可达
    int t1 = 0;//初始化目标状态值
    per(i,n-1,0) t1 = t1*11+a[i];//将数组a转换为11进制数t1
    //遍历每个阶段和状态
    rep(i,0,m-1) rep(j,0,t1) {
        int tot = 0, t = j;
        rep(q,0,4) cnt[q] = 0;
        while (t) {
            cnt[tot] = t%11;//将状态j转换为11进制存储在cnt中
            if (cnt[tot] > a[tot]) { tot = -1; break; }//是否超过限制
            t/=11;
            tot++;
        }
        if (!~tot) continue;//tot为-1
        rep(k,0,(1<<n)-1) {//k:前一阶段的掩码状态
            if (!dp[i][j][k]) continue;//当前状态不可达
            //尝试所有可能的转移状态
            rep(l,0,(1<<n)-1) {//l:当前阶段的掩码状态
                if (get(l) != b[i+1]) continue;//是否等于目标值
                int nj = 0, flg = 0;//转移后的状态
                per(q,n-1,0) {
                    const int x = cnt[q] + ((l>>q&1) == 1 && (k>>q&1) == 0);
                    if (x > a[q]) { flg = 1; break; }//是否超限
                    nj = nj*11+x;//新的11进制状态
                }
                if (flg) continue;
                dp[i+1][nj][l] |= dp[i][j][k];//状态转移
            }
        }
    }
    rep(i,0,(1<<n)-1) if (dp[m][t1][i]) {//找到可达的最终状态并恢复路径
        dfs(m, t1, i);
        break;//找到一个解就跳出
    }
    rep(i,1,m) rep(j,0,n-1) p[j+1][i] = ans[i]>>j&1;//答案转换为布尔矩阵 ans[i]的第j位提取出来
    rep(i,1,n) {
        rep(j,1,m) cout << (p[i][j] ? '*' : '.');//输出矩阵
        cout << '\n';
    }
    return 0;
}