/**
new函数用于创建指定值的Data实例
default函数创建全零的Data实例

dp[i][0]表示不严格小于当前前缀的状态
dp[i][1]表示严格小于当前前缀的状态


*/
use std::io;

const MOD: i64 = 1000000007;
#[derive(Clone, Copy)]
struct Data { sqr: i64, sum: i64, cnt: i64 }
impl Data {
    fn new(sqr: i64, sum: i64, cnt: i64) -> Self { Data { sqr, sum, cnt } }
    fn default() -> Self { Data { sqr: 0, sum: 0, cnt: 0 } }
}
fn u4(p: Data) -> Data {
    Data::new(
        (p.sqr * 100 + p.sum * 80 + p.cnt * 16) % MOD,
        (p.sum * 10 + p.cnt * 4) % MOD,
        p.cnt
    )
}
fn u7(p: Data) -> Data {
    Data::new(
        (p.sqr * 100 + p.sum * 140 + p.cnt * 49) % MOD,
        (p.sum * 10 + p.cnt * 7) % MOD,
        p.cnt
    )
}
fn add(x: &mut Data, y: Data) {//将两个Data结构体相加的函数
    x.sqr += y.sqr;
    if x.sqr >= MOD { x.sqr -= MOD; }
    x.sum += y.sum;
    if x.sum >= MOD { x.sum -= MOD; }
    x.cnt += y.cnt;
    if x.cnt >= MOD { x.cnt -= MOD; }
}

fn get(x: Data, k: usize, pw: &[i64], sv: &[i64], fr: &[i64]) -> i64 {
    let res = (
        sv[k] * fr[k] % MOD * x.cnt % MOD +
        sv[k] * pw[k + 1] % MOD * x.sum % MOD +
        sv[k] * 7 % MOD * pw[k] % MOD * x.cnt % MOD +
        fr[k] * pw[k + 1] % MOD * x.sum % MOD +
        fr[k] * 4 % MOD * pw[k] % MOD * x.cnt % MOD +
        pw[(k<<1) + 2] * x.sqr % MOD +
        110 * pw[k<<1] % MOD * x.sum % MOD +
        28 * pw[k<<1] % MOD * x.cnt % MOD
    ) % MOD;
    res
}
fn calc(s: &Vec<u8>, pw: &[i64], sv: &[i64], fr: &[i64]) -> i64 {
    let n = s.len() - 1;
    let mut dp = vec![vec![Data::default(); 2]; n + 1];
    dp[0][1] = Data::new(0, 0, 1);
    for i in 1..=n {
        dp[i][0] = Data::default();
        dp[i][1] = Data::default();
        let pre0 = dp[i - 1][0];
        let pre1 = dp[i - 1][1];
        if s[i] == b'4' {
            add(&mut dp[i][0], u4(pre0));
            add(&mut dp[i][0], u7(pre0));
            add(&mut dp[i][1], u4(pre1));
        } else {
            add(&mut dp[i][0], u4(pre0));
            add(&mut dp[i][0], u4(pre1));
            add(&mut dp[i][0], u7(pre0));
            add(&mut dp[i][1], u7(pre1));
        }
    }
    let mut ans = 0i64;
    for i in 0..n {
        if s[i + 1] == b'4' {
            ans = (ans + get(dp[i][0], n - i - 1, &pw, &sv, &fr)) % MOD;
        } else {
            ans = (ans + get(dp[i][0], n - i - 1, &pw, &sv, &fr)) % MOD;
            ans = (ans + get(dp[i][1], n - i - 1, &pw, &sv, &fr)) % MOD;
        }
    }
    ans
}
fn main() {
    let mut pw = vec![0i64; 200005];
    let mut sv = vec![0i64; 100005];
    let mut fr = vec![0i64; 100005];
    pw[0] = 1;
    for i in 1..=200002 { pw[i] = pw[i - 1] * 10 % MOD; }//10^i % MOD
    for i in 1..=100000 { sv[i] = (sv[i-1]*10 + 7) % MOD; }//i个数字7组成的数
    for i in 1..=100000 { fr[i] = (fr[i-1]*10 + 4) % MOD; }
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let sl = input.trim().chars().collect::<Vec<char>>();//将字符串转换为字符向量
    let mut slb = vec![0u8; sl.len() + 1];//转换为字节向量并调整为1索引
    for i in 0..sl.len() { slb[i+1] = sl[i] as u8; }
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let sr = input.trim().chars().collect::<Vec<char>>();
    let mut srb = vec![0u8; sr.len()+1];
    for i in 0..sr.len() { srb[i+1] = sr[i] as u8; }
    let l = calc(&slb, &pw, &sv, &fr);
    let r = calc(&srb, &pw, &sv, &fr);
    println!("{}", (r - l + MOD) % MOD);
}