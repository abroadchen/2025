use std::io;

const N: usize = 2000007;
fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut a = vec![0; N];
    for i in 1..=n { a[i] = i as i32; }
    let mut l = 1;
    let mut r = n as i32;
    for i in 2..=n {
        let mut p = ((n/i)*i - 1 + l as usize) as i32;//计算位置p
        a[(r + 1) as usize] = a[(p + 1) as usize];
        while p - i as i32 >= 0 {
            a[(p + 1) as usize] = a[(p - i as i32 + 1) as usize];
            p -= i as i32;
        }
        l += 1;//每次外层循环后，区间[l,r]向右扩展一个位置
        r += 1;
    }
    for i in l..=r { print!("{} ", a[i as usize]); }
    println!();
}