use std::io::{self, BufRead};
//从位置j到位置i是否满足某种条件
fn ok(j: usize, i: usize, b: &[i32], str_v: &[i64]) -> bool {
    if str_v[j] % str_v[i] != 0 { return false; }
    if b[i] == 0 { return true; }
    else {
        if i - j == (b[i] - b[j]) as usize { return true; }
        if b[i] < (i - j) as i32 { return true; }
    }
    return false;
}

fn main() {
    let stdin = io::stdin();//标准输入句柄
    let mut input = String::new();//存储输入
    stdin.read_line(&mut input).unwrap();//读取一行到input字符串中
    let n: usize = input.trim().parse().unwrap();
    input.clear();//准备读取下一行
    stdin.read_line(&mut input).unwrap();//再次读取一行
    let num: Vec<i64> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();//i64类型的向量
    let mut str_v: Vec<i64> = vec![0; n + 1];//处理后的数值 +1 to accommodate str[n]=1
    let mut b: Vec<i32> = vec![0; n + 1];//2的幂次
    let mut dp: Vec<i32> = vec![0; n + 2];//+2 to accommodate dp[0] and dp[n]
    for i in 0..n {
        let mut t = num[i];//存储当前数字
        b[i] = 0;//初始化计数器
        while t % 2 == 0 {
            b[i] += 1;//记录2的幂次
            t >>= 1;
        }
        str_v[i] = t;//存储去除所有因子2后的结果
    }
    str_v[n] = 1; dp[0] = 0;//设置最后一个元素为1
    for i in 1..=n {//进行动态规划
        dp[i] = i as i32;//最坏情况
        for j in 0..i {
            if ok(j, i, &b, &str_v) {//如果满足条件
                dp[i] = dp[i].min(dp[j] + (i - j) as i32 - 1);
            }//dp[i]表示处理前i个元素所需的最小操作数。对于每个位置i，尝试从之前的所有位置j转移过来，选择最优解。
        }
    }
    println!("{}", dp[n]);
}