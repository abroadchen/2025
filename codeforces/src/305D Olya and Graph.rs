/**
1. i + k
含义: 从位置 i 开始，长度为 k 的区间的右边界
功能: 从位置 i 向右延伸 k 个单位
2. (i + k).min(n - k - 1)
含义: 取上述结果与 n - k - 1 的最小值
功能:
n - k - 1 是有效的右边界限制
确保区间不超过允许的最大范围
3. (i + k).min(n - k - 1) - i
含义: 计算从位置 i 到有效右边界之间的总位置数
功能: 这是理论上可用的位置范围
4. - num
含义: 减去已被特殊区间占用的位置数
功能: num 是特殊区间的数量，每个特殊区间会占用一个位置

res 表示在位置 i 可用的自由选择位置数量
pow(2, res) 计算这些位置的所有可能组合（每个位置可选或不可选）

1. r - k
含义: 从右边界位置 r 减去 k
功能: 计算一个起始位置的下界
2. (r - k).max(1)
含义: 取 r-k 和 1 中的较大值
功能: 确保起始位置不小于 1，起到边界保护作用

既要考虑右边界约束（r-k），又要考虑左边界约束（l）
同时保证不超出数组边界（至少为1）
*/
use std::io;

const MOD: i64 = 1_000_000_007;

fn fast(a: i64, b: i64) -> i64 {
    if b < 0 { return 0; }
    let mut ans = 1i64;//幂的单位元
    let mut base = a % MOD;//确保底数在模范围内
    let mut exp = b;
    while exp > 0 {
        if exp & 1 == 1 { ans = (ans * base) % MOD; }//将当前底数乘入结果
        base = (base * base) % MOD;//平方底数
        exp >>= 1;
    }
    ans
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i64> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0];
    let m = parts[1];
    let k = parts[2];
    let mut flag = true;//条件是否满足
    let mut l = n + 1;//最左边的特殊区间起始位置
    let mut r = 0;//最右边的特殊区间起始位置
    let mut num = 0;//特殊区间的数量
    for _ in 0..m {//遍历 m 个约束条件
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i64> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let u = parts[0];//读取每个约束的起始和结束位置
        let v = parts[1];
        if v != u + 1 && v != u + k + 1 { flag = false; }//是否为合法约束
        else if v == u + k + 1 {//识别特殊约束（长度为 k+1）
            l = l.min(u); r = r.max(u); num += 1;//更新
        }
    }
    if r != 0 && r - l > k { flag = false; }//特殊区间是否冲突
    let ans = if !flag { 0 } else if r != 0 {
        let mut ans = 0i64;
        for i in ((r - k).max(1))..=l {
            let mut res = (i + k).min(n - k - 1) - i - num;
            if i == l { res += 1; }
            ans = (ans + fast(2, res)) % MOD;
        }
        ans
    } else {
        let mut ans = 1i64;
        for i in 1..=n - (k + 1) {
            ans = (ans + fast(2, (n - k - 1).min(i + k) - i)) % MOD;
        }
        ans
    };
    println!("{}", ans);
}