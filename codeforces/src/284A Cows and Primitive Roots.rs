/**
欧拉函数表示小于等于n且与n互质的正整数的个数
欧拉函数公式：对于n = p₁^a₁ × p₂^a₂ × ... × pₖ^aₖ（质因数分解），
φ(n) = n × (1-1/p₁) × (1-1/p₂) × ... × (1-1/pₖ)
时间复杂度是O(√n)
*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let p: i32 = input.trim().parse().unwrap();
    let mut n = p - 1;//计算欧拉函数的数
    let mut cnt = n;//欧拉函数的初始值
    let mut i = 2;//从最小的质数开始
    while i * i <= n {
        if n % i == 0 {//i是n的一个质因数
            while n % i == 0 { n /= i; }//循环去除n中所有的i因子
            cnt = cnt / i * (i - 1);//欧拉函数公式更新计数：cnt = cnt * (1 - 1/i)
        }
        i += 1;//检查下一个可能的质因数
    }
    //如果经过质因数分解后n仍大于1，说明n有一个大于√(原n)的质因数
    if n != 1 { cnt = cnt / n * (n - 1); }//将这个质因数也应用到欧拉函数公式中
    println!("{}", cnt);
}