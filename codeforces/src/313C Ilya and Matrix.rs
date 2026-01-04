use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut a = vec![0i32; n];
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    a.copy_from_slice(&parts);//parts切片的内容复制到向量a中
    a.sort_by(|a, b| b.cmp(a));//b在前，a在后，表示b > a时b排在前面
    let mut sum: i64 = 0;
    let mut i = 1;
    while i <= n {//0到min(i, n)
        for j in 0..i.min(n) { sum += a[j] as i64; }
        i *= 4;//4倍增长
    }
    println!("{}", sum);
}
