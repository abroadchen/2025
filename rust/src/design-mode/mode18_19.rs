/**
@author: June
@since: 2025/7/28
@desc:
*/

//1、共享类型，同时实现精准控制:
// (1)personInfo类型共享studentInfo类型，同时又只提供name和id方法
// (2)PersonInfo实现Debug trait可以打印，PersonInfo则没有提供，变成了move语义
#[derive(Debug)]
struct StudentInfo {
    name: &'static str,
    id: &'static str,
    number: &'static str,
}
impl StudentInfo {
    fn new(name: &'static str, id: &'static str, number: &'static str) -> Self {
        StudentInfo {
            name,
            id,
            number: number,
        }
    }

    fn name(&self) -> &'static str {
        self.name
    }

    fn id(&self) -> &'static str {
        self.id
    }

    fn number(&self) -> &'static str {
        self.number
    }
}

struct PersonInfo(StudentInfo);

impl PersonInfo {
    fn new(s: StudentInfo) -> Self {
        PersonInfo(s)
    }

    fn name(&self) -> &'static str {
        self.0.name()
    }

    fn id(&self) -> &'static str {
        self.0.id()
    }
}

struct Miles(f64);
struct Kms(f64);
fn main() {
    let s = StudentInfo {
        name: "Alice",
        id: "123456",
        number: "001",
    };
    let p = PersonInfo::new(s);
    println!("name: {:?}", p.name());
    println!("id: {:?}", p.id());

    let _m = Miles(10f64);
    let _kms = Kms(10f64);
}




//将MyMutexGuard作为Foo获取到锁资源的守护对象
use std::cell::RefCell;
use std::ops::Deref;

struct Foo;
impl Foo {
    fn do_something(&self) {
        println!("Do something");
    }
}

struct MyMutex<T> {
    flag: RefCell<bool>,
    data: T,
}

impl<T> MyMutex<T> {
    fn new(t: T) -> MyMutex<T> {
        MyMutex {
            flag: RefCell::new(false),
            data: t,
        }
    }

    fn lock(&self) -> Result<MyMutexGuard<T>, &'static str> {
        while *self.flag.borrow() {}
        *self.flag.borrow_mut() = true;
        MyMutexGuard::new(self)
    }

    fn try_lock(&self) -> Result<MyMutexGuard<T>, &'static str> {
        if *self.flag.borrow() == false {
            self.lock()
        } else {
            Err("Can't get lock")
        }
    }
}

impl<T> Drop for MyMutex<T> {
    fn drop(&mut self) {
        println!("unlock");
    }
}

struct MyMutexGuard<'a, T: 'a> {
    lock: &'a MyMutex<T>,
}

impl<'a, T> MyMutexGuard<'a, T> {
    fn new(lock: &'a MyMutex<T>) -> Result<MyMutexGuard<'a, T>, &'static str> {
        Ok(MyMutexGuard { lock })
    }
}

impl<'a, T> Deref for MyMutexGuard<'a, T> {
    type Target = T;

    fn deref(&self) -> &T {
        &self.lock.data
    }
}

impl<'a, T> Drop for MyMutexGuard<'a, T> {
    fn drop(&mut self) {
        *self.lock.flag.borrow_mut() = false;
    }
}

fn main() {
    let m = MyMutex::new(Foo);
    {
        println!("++++++++++");
        let m1 = m.lock();
        if let Err(e) = m.try_lock() {
            println!("Can't get lock, err: {:?}", e);
        }
        println!("++++++++++");
        m1.unwrap().do_something();
    }
    println!("++++++++++");
    let m2 = m.lock();
    m2.unwrap().do_something();
    println!("++++++++++");
}




