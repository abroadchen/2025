/**
@author: June
@since: 2025/7/28
@desc: 在析构器中做最终处理

*/

//如果函数中存在无线循环或者运行函数退出前崩溃，则不会运行drop函数
struct A(u8);
impl Drop for A {
    fn drop(&mut self) {
        println!("A exit");
    }
}

#[derive(Debug)]
struct B(u8);
impl Drop for B {
    fn drop(&mut self) {
        println!("B exit");
    }
}

fn main() {
    let a = A(1);
    {
        let b = B(1);
        println!("a: {:?}", a);
        println!("b: {:?}", b);
    }
    panic!("error");
}