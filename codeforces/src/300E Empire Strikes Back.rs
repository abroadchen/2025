use std::io;

//检查 x! 中是否包含足够的质因数
fn ok(x: i64, cnt: &[i64], pri: &[usize], tot: usize) -> bool {
    for i in 1..=tot {
        let mut cur = x;
        let mut sum = 0i64;
        while cur > 0 {
            cur /= pri[i] as i64;//计算 x 除以质数的幂次
            sum += cur;
        }
        if sum < cnt[pri[i]] { return false; }//个数不够
    }
    true
}

const N: usize = 10_000_005;
fn main() {
    let mut f = vec![0; N];//f[i] 存储 i 的最小质因子
    let mut pri = vec![0; N];//质数数组
    let mut tot = 0;//质数计数器
    for i in 2..10_000_001 {// 2 到 10^7 遍历
        if f[i] == 0 {// i 是质数
            tot += 1;
            pri[tot] = i;//将 i 加入质数数组
            f[i] = i;//i 的最小质因子是自己
        }
        let mut j = 1;//当前质数 prime[j] 乘以 i 生成合数
        while j <= tot && i * pri[j] <= 10_000_000 {
            f[i * pri[j]] = i;//合数的最小质因子
            if i % pri[j] == 0 { break; }
            j += 1;
        }
    }
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let k: usize = input.trim().parse().unwrap();
    let mut cnt = vec![0; N];//cnt[x] 表示数字 x 出现的次数
    let mut s = 0i64;//所有数字的和
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i64> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    for i in 0..k {
        let x = parts[i];
        s += x;//累加所有数字
        cnt[x as usize] += 1;//统计每个数字出现次数
    }
    //计算阶乘中质因数的个数
    for i in (2..10_000_001).rev() { cnt[i] += cnt[i + 1]; }//大于等于 i 的数字个数
    //统计阶乘中每个质数的幂次
    for i in (2..10_000_001).rev() {
        cnt[(i as i64 / f[i] as i64) as usize] += cnt[i];//将数字 i 的贡献传递给 i/f[i]
        if i != f[i] { cnt[f[i]] += cnt[i]; }//如果 i 不是质数，将贡献也加到其最小质因子上
    }
    let mut l = 1i64;
    let mut r = s;
    while l <= r {
        let mid = (l + r) >> 1;
        if ok(mid, &cnt, &pri, tot) { r = mid - 1; } else { l = mid + 1; }
    }
    println!("{}", l);
}