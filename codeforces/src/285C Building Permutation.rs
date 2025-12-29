use std::io;

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let n: i64 = input.trim().parse().unwrap();
    input.clear();
    stdin.read_line(&mut input).unwrap();
    let mut a: Vec<i64> = input.trim().split(' ').map(|x| x.parse().unwrap()).collect();
    a.sort_by(|a, b| b.cmp(a));//降序排序，b.cmp(a)使得大的数在前
    let mut ans = 0;
    let mut cur = n;//可变副本
    for i in 0..n {
        ans += (cur - a[i as usize]).abs();//对于排序后的数组，第i个元素与(n-i)的差的绝对值之和
        cur -= 1;
    }
    println!("{}", ans);
}