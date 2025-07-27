include!(concat!(env!("OUT_DIR"), "/scripts.rs"));
fn main() {
    println!("{}", some_func());
    println!("Hello, world!");
}
