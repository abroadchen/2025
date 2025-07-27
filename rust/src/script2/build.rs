/**
@author: June
@since: 2025/7/26
@desc:
*/

extern crate cc;
fn main() {
    cc::Build::new().file("src/hello.c").compile("hello.a");
}