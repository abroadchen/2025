mod pin;
mod test;
mod join;
mod recursion;
mod pool;
mod queue;
mod read_file;
mod stack;
mod list;

use std::thread;
use std::thread::JoinHandle;
use std::time::Duration;

trait SimpleFuture {
    type Output;
    fn poll(&mut self, wake: u32) -> Poll<Self::Output>;
}

enum Poll<T> {
    Ready(T),
    Pending,
}
static mut FINISHED: bool = false;
struct MySleeper {
    poll: u64,
    wake: u32,
}
impl MySleeper {
    fn new(wake: u32) -> Self {
        MySleeper {
            poll: 0,
            wake
        }
    }
}
impl SimpleFuture for MySleeper {
    type Output = ();
    fn poll(&mut self, wake: u32) -> Poll<Self::Output> {
        unsafe {
            if FINISHED {
                Poll::Ready(())
            } else {
                self.poll += 1;
                self.wake = wake;
                Poll::Pending
            }
        }
    }
}

struct MyReactor {
    wake: u32,
    handle: Option<JoinHandle<()>>,
}
impl MyReactor {
    fn new() -> Self {
        MyReactor {
            wake: 0,
            handle: None,
        }
    }

    fn add_wake(&mut self, wake: u32) {
        self.wake = wake;
    }

    fn check_status(&mut self) {
        if self.handle.is_none() {
            let _wake = self.wake;
            let handle = thread::spawn(|| {
                thread::sleep(Duration::from_millis(1));
                unsafe {
                    FINISHED = true;
                }
            });
            self.handle = Some(handle);
        }
    }
}

struct MyExecutor {}
impl MyExecutor {
    fn block_on<F: SimpleFuture>(mut myfuture: F, wake: u32) {
        loop {
            match myfuture.poll(wake) {
                Poll::Ready(_) => {
                    println!("poll got");
                    break
                },
                Poll::Pending => {
                    unsafe {
                        while !FINISHED {
                            thread::sleep(Duration::from_millis(1));
                        }
                    }
                }
            }
        }
    }
}


fn main() {
    let mut reactor = MyReactor::new();
    let sleeper = MySleeper::new(5);
    let wake = sleeper.wake;
    reactor.add_wake(wake);
    reactor.check_status();
    MyExecutor::block_on(sleeper, wake);
    println!("Hello, world!");
}
