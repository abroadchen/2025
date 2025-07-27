/**
@author: June
@since: 2025/7/28
@desc: 滥用Deref trait来模拟结构体间的继承，从而重用方法
*/

use std::ops::Deref;

struct Foo;
impl Foo {
    fn m(&self) {
        println!("Use foo's method!");
    }
}

struct Bar {
    f: Foo,
}

// 不推荐的方式：滥用deref来模拟继承
impl Deref for Bar {
    type Target = Foo;
    fn deref(&self) -> &Foo {
        &self.f
    }
}


// 推荐的方式：显式的实现m方法
impl Bar {
    fn m(&self) {
        self.f.m();
    }
}