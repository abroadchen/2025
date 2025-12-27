use std::io;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split_whitespace().collect();
    let mut w: i64 = parts[0].parse().unwrap();
    let mut h: i64 = parts[1].parse().unwrap();
    let mut a: i64 = parts[2].parse().unwrap();
    const PI: f64 = std::f64::consts::PI;
    if h > w { std::mem::swap(&mut h, &mut w); }
    if a == 90 {
        println!("{:.9}", (h as f64) * (h as f64));
        return
    }
    if a == 0 || a == 180 {
        println!("{:.9}", (w as f64) * (h as f64));
        return
    }
    if a > 90 { a = 180 - a }//转换为对应的锐角（利用对称性）
    let a_rad = (a as f64) * PI / 180.;//从度转换为弧度
    let sina = a_rad.sin();
    let cos_a = a_rad.cos();
    let tana = a_rad.tan();
    let z = ((h as f64) * sina - (w as f64) * cos_a - (w as f64)) /
        (sina * sina - cos_a * cos_a - 2. * cos_a - 1.);
    let v = ((w as f64) - z * cos_a - z) / sina;
    let x = z * cos_a;//坐标 x 和 y
    let y = z * sina;
    let t = v * sina;//坐标 t 和 u
    let u = v * cos_a;
    let mut ans = (w as f64) * (h as f64) - x * y - t * u;
    if v <= 0. { ans = (h as f64) * (h as f64) / sina }
    println!("{:.9}", ans);
}