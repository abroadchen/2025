use std::thread;
use std::time::Duration;

/**
@author: June
@since: 2025/7/26
@desc:
*/


struct Worker {
  // thread: thread::JoinHandle<()>
  thread: Option<std::thread::JoinHandle<()>>,
}

impl Worker {
  fn new() -> Worker {
    let thread = thread::spawn( move|| {
      thread::sleep(Duration::from_millis(100));
    });
    Worker { thread: Some(thread) }
  }
}

struct ThreadPool {
  workers: Vec<Worker>,
}

impl ThreadPool {
  fn new(size: usize) -> ThreadPool {
    assert!(size > 0);
    let mut workers = Vec::with_capacity(size);
    for _ in 0..size {
      workers.push(Worker::new());
    }
    ThreadPool { workers }
  }
}

impl Drop for ThreadPool {
  fn drop(&mut self) {
    for worker in &mut self.workers {
      // worker.thread.join().unwrap();
      if let Some(thread) = worker.thread.take() {
        thread.join().unwrap();
      }
    }
  }
}

fn main() {
  let pool = ThreadPool::new(5);

}