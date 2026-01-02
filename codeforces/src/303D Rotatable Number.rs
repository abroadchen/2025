use std::io;

const N: usize = 5_000_010;

fn gcd(a: i64, b: i64) -> i64 { if b == 0 { a } else { gcd(b, a % b) } }

fn fast(a: i64, b: i64, p: i64) -> i64 {
    let mut res = 1;//单位元
    let mut base = ((a % p) + p) % p;
    let mut exp = b;
    while exp > 0 {
        if exp & 1 == 1 { res = (res * base) % p; }
        base = (base * base) % p;
        exp >>= 1;
    }
    res
}

fn sieve(pri: &mut Vec<i64>, isp: &mut Vec<bool>) {
    isp[0] = true; isp[1] = true;//表示不是素数
    for i in 2..(N - 10) {
        if !isp[i] { pri.push(i as i64); }
        let mut j = 0;
        while j < pri.len() && pri[j] * i as i64 <= (N - 10) as i64 {
            isp[(pri[j] * i as i64) as usize] = true;// i 的倍数为合数
            if i as i64 % pri[j] == 0 { break; }//遇到最小质因子时跳出
            j += 1;
        }
    }
}
//要分解的数
//pri: 预计算的质数列表
//pr: 存储质因数的向量
//返回值: 找到的质因数个数
fn get(p: i64, pri: &Vec<i64>, pr: &mut Vec<i64>) -> usize {// 分解 p-1 的质因数
    let mut len = 0;
    let mut t = p - 1;
    let mut idx = 0;
    while idx < pri.len() && pri[idx] * pri[idx] <= t {
        if t % pri[idx] == 0 {
            len += 1;
            pr.push(pri[idx]);//找到质因数后加入向量
            while t % pri[idx] == 0 { t /= pri[idx]; }//除尽该质因数
        }
        idx += 1;
    }
    if t > 1 { len += 1; pr.push(t); }// 如果还有大于 √(p-1) 的质因数，加入列表
    len
}

fn ok(d: i64, p: i64, pr: &Vec<i64>) -> bool {// 检查 d 是否是模 p 的原根
    if gcd(p, d) != 1 { return false; }
    for &x in pr.iter() {
        if fast(d, (p - 1) / x, p) == 1 { return false; }
    }
    true
}

fn main() {
    let input = {
        let mut s = String::new();
        io::stdin().read_line(&mut s).unwrap();
        s
    };
    let mut parts = input.trim().split_whitespace();
    let n: i64 = parts.next().unwrap().parse().unwrap();
    let x: i64 = parts.next().unwrap().parse().unwrap();
    let mut pri = Vec::new();
    let mut isp = vec![false; N];
    sieve(&mut pri, &mut isp);
    if n + 1 < N as i64 && isp[(n + 1) as usize] { println!("-1"); return; }
    let mut pr = Vec::new();
    get(n + 1, &pri, &mut pr);
    for i in (2..x).rev() {
        if ok(i, n + 1, &pr) {
            println!("{}", i);
            return;
        }
    }
    println!("-1");
}