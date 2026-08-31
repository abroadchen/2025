//
// Created by Psy.C on 2026/8/31.
//
/**
last string 上一轮输出的猜测（4 位字符串，如 "0123" ）
tmp string 临时拼接 4 位数字的字符串
T map<string,int> 候选答案集合 （仍可能是正确答案的 4 位数），value 是计数
td map<string,int> 已排除集合 （不可能是正确答案的 4 位数）， td[s]=1 表示 s 已被排除
all_str vector<string> 所有 5040 个可能的 4 位数 （10 选 4 不重复的全排列）
四重循环枚举所有 4 位数（0000~9999 共 10000 种），用 tmp 拼接成字符串
筛选互不重复的 4 位数 ：
- i!=j && j!=k && k!=l && i!=k && i!=l && j!=l ：检查所有位两两互不相同。
- 互不重复 ：加入候选集合 T ，也加入全局列表 all_str 。
- 有重复 ：加入排除集合 td

比较猜测 s 和候选 t ，返回 (X, Y) 即 Bulls 和 Cows
- X ：Bulls 计数。
- Y ：Cows 计数。
- vis ：布尔数组，标记 t 中有哪些数字出现过（用空间换时间）
标记候选 t 中出现过的数字 ：把每个字符的数字值作为下标设为 true 。
- (int)i-'0' ：字符转数字（'5' → 5）
逐位置比较 ：
- 位置相同且数字相同 ：Bulls+1。
- 位置不同但数字存在 （在 t 的 vis 表中查得到）：Cows+1。
返回 (X, Y) 作为结果。

给定一个猜测 g ，计算在当前候选集下， 最坏情况下剩余多少可能答案 。
- TT ：用 (X, Y) 做键，value 是 在当前候选集中，有多少个候选答案与 g 对比后会返回这个 (X, Y) 。
四重循环枚举 所有互不重复的 4 位数 s （候选答案）。
- 如果 s 已被排除（在 td 中），跳过。
- 计算 s 作为真实答案时，猜测 g 会返回什么 (X, Y) ，在 TT 中对应分组计数 +1。
返回最大的分组大小 （即最坏情况下剩余候选数）。Knuth 策略选 H(g) 最小 的猜测，让最坏情况也尽量好。

- ans ：存所有候选猜测。
- cishu ：计数器（ cishu = 次数，看起来是调试用，未在逻辑中使用）。
- srand(time(0)) ：随机数种子（但代码中没用 rand() ，可能被注释掉了）。
- init() ：预生成所有 5040 个候选答案。
固定第一轮猜 "0123" （Knuth 推荐的最优开局之一，能把 5040 个候选分成 14 组，最大组约 840 个）。

- while(1) ：死循环，直到猜对为止。
- 读入系统返回的 (X, Y) 。
- x==4 && y==0 ：猜对了！直接 return 0 退出程序。
把上一轮猜测 last 标记为已排除（不会是答案）。
重新遍历所有 5040 个候选答案 ，根据上一轮返回的 (X, Y) 更新：
- 候选答案 tmp 与 last 对比后返回 (x, y) → 可能是正确答案 ，加入 T 。
- 否则 → 不可能是答案 ，加入 td 排除。
效果 ： T 只保留所有能产生相同 (X, Y) 的候选，大幅缩小范围。
遍历所有未排除的候选，找到 T[tmp] 最大的那个（即 出现次数最多 的候选）。这个 maxs 是当前候选集中 最可能是答案 的数字。
把所有 T[tmp] == minn （出现次数相同，都是最大值）的候选收集到 ans 中。
对所有可能的猜测 g （5040 个）：
- 跳过已排除的 （在 td 中的）。
- 计算 H(g) ：最坏情况下剩余候选数。 选择策略：
- sc==1 ：如果猜测 g 的最坏情况分组大小是 1（猜测能直接锁定唯一答案）， 且 g 也是候选集中的当前最可能答案 （ ans 里有），优先选它！这是 立即锁定 的情况。
- 否则：选 H(g) 最小 的那个（让最坏情况剩余最少）。
这就是 Knuth 策略的精髓 ： 最小化最坏情况 （Minimax），让最不幸的场景也只剩最少的可能性。
- 更新 last 为当前猜测。
- 输出并立即 flush （交互题必须刷新）。
- cishu++ 增加猜测次数（调试用）。
- 回到循环开始，等待系统返回新的 (X, Y) 。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

string last,tmp;
map<string,int>T,td;
vector<string>all_str;
inline void init() {
	for(char i='0';i<='9';i++) {
		for(char j='0';j<='9';j++) {
			for(char k='0';k<='9';k++) {
				for(char l='0';l<='9';l++) {
					tmp=i; tmp+=j; tmp+=k; tmp+=l;
					if(i!=j&&j!=k&&k!=l&&i!=k&&i!=l&&j!=l) {
						T[tmp]++;
						all_str.push_back(tmp);
					} else { td[tmp]=1; }
				}
			}
		}
	}
}
bool vis[15];
inline pair<int,int> cmp(string s,string t){
	int X=0,Y=0;
	memset(vis,0,sizeof(vis));
	for(char i : t) { vis[((int)i-'0')]=1; }
	for(int i=0;i<s.size();i++) {
		if(s[i]==t[i]) { X++; }
		else if(s[i]!=t[i]&&vis[((int)s[i]-'0')]) { Y++; }
	}
	return make_pair(X,Y);
}
inline int H(string g) {
	map<pair<int,int>,int> TT;
	for(char a='0';a<='9';a++) {
		for(char b='0';b<='9';b++) {
			if(b!=a){
				for(char c='0';c<='9';c++) {
					if(c!=a&&c!=b) {
						for(char d='0';d<='9';d++) {
							if(d!=a&&d!=b&&d!=c) {
								string s={a,b,c,d};
								if(td[s]) { continue; }
								TT[cmp(s,g)]++;
							}
						}
					}
				}
			}
		}
	}
	int ma=0;
	for(auto& p:TT) ma=max(ma,p.second);
	return ma;
}
vector<string>ans;
long long cishu=1;
signed main(){
	srand(time(0));
	init();
	last="0123";
	cout<<last<<endl;
	while(1){
		int x,y;
		cin>>x>>y;
		if(x==4&&y==0) { return 0; }
		T[last]=0;
		td[last]=1;
		for(char i='0';i<='9';i++) {
			for(char j='0';j<='9';j++) {
				for(char k='0';k<='9';k++) {
					for(char l='0';l<='9';l++) {
						tmp=i; tmp+=j; tmp+=k; tmp+=l;
						if(i!=j&&j!=k&&k!=l&&i!=k&&i!=l&&j!=l) {
							pair<int,int>qwq=cmp(tmp,last);
							if(qwq==make_pair(x,y)) { T[tmp]++; }
							else { T[tmp]=0; td[tmp]=1; }
						} else { T[tmp]=0; td[tmp]=1; }
					}
				}
			}
		}
		int minn=0;
		string maxs;
		for(char i='0';i<='9';i++) {
			for(char j='0';j<='9';j++) {
				for(char k='0';k<='9';k++) {
					for(char l='0';l<='9';l++) {
						if(i!=j&&j!=k&&k!=l&&i!=k&&i!=l&&j!=l){
							tmp=i; tmp+=j; tmp+=k; tmp+=l;
							if(td[tmp]) { continue; }
							if(T[tmp]>minn) { minn=T[tmp]; maxs=tmp; }
						}
					}
				}
			}
		}
		ans.clear();
		for(char i='0';i<='9';i++) {
			for(char j='0';j<='9';j++) {
				for(char k='0';k<='9';k++) {
					for(char l='0';l<='9';l++) {
						if(i!=j&&j!=k&&k!=l&&i!=k&&i!=l&&j!=l) {
							tmp=i; tmp+=j; tmp+=k; tmp+=l;
							if(td[tmp]) { continue; }
							if(T[tmp]==minn) { ans.push_back(tmp); }
						}
					}
				}
			}
		}
		string next_guess; minn=INT_MAX;
		for(auto& g:all_str){
			if(td[g]) { continue; }
			int sc=H(g);
			if(sc==1&&ranges::find(ans,g)!=ans.end()) {
				next_guess=g; { break; }
			}
			if(sc<minn) { minn=sc; next_guess=g; }
		}
		last=next_guess;
		cout<<last<<endl<<flush;
		cishu++;
	}
	return 0;
}