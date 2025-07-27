use std::sync::{mpsc, Arc, Mutex};
use std::sync::mpsc::Receiver;
use std::thread;


struct Worker {
    id: usize,
    thread: Option<thread::JoinHandle<()>>,
}

impl Worker {
    // fn new(id: usize) -> Worker {
    //     let thread = thread::spawn(|| {});
    //     Worker { id, thread }
    // }
    // fn new(id: usize, receiver: mpsc::Receiver<Job>) -> Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Message>>>) -> Worker {
        let thread = thread::spawn(move || loop {
            // let job = receiver.lock().unwrap().recv().unwrap();
            let message = receiver.lock().unwrap().recv().unwrap();
            match message {
                Message::NewJob(job) => {
                    println!("Worker {} got a job; executing.", id);
                    job();
                }
                Message::Terminate => {
                    println!("Worker {} was told to terminate.", id);
                    break;
                }
            }
            // job();
        });
        Worker { id, thread: Some(thread) }
    }
}

// struct Job;
type Job = Box<dyn FnOnce() + Send + 'static>;

enum Message {
    NewJob(Job),
    Terminate,
}




pub struct ThreadPool {
    // threads: Vec<thread::JoinHandle<()>>,
    workers: Vec<Worker>,
    // sender: mpsc::Sender<Job>,
    sender: mpsc::Sender<Message>,
}

impl ThreadPool {
    pub fn new(size: usize) -> ThreadPool {
        assert!(size > 0);
        // let mut threads = Vec::with_capacity(size);
        let mut workers = Vec::with_capacity(size);
        let (sender, receiver) = mpsc::channel();

        let receiver = Arc::new(Mutex::new(receiver));


        for id in 0..size {
            // workers.push(Worker::new(id));
            workers.push(Worker::new(id, Arc::clone(&receiver)));
        }

        ThreadPool {
            // threads
            workers,
            sender,
        }
    }

    pub fn execute<F>(&self, f: F)
        where F: FnOnce() -> () + Send + 'static {
        let job = Box::new(f);
        // self.sender.send(job).unwrap();
        self.sender.send(Message::NewJob(job)).unwrap();
    }
}


impl Drop for ThreadPool {
    fn drop(&mut self) {
        for _ in &mut self.workers {
            self.sender.send(Message::Terminate).unwrap();
        }


        for worker in &mut self.workers {
            if let Some(thread) = worker.thread.take() {
                thread.join().unwrap();
            }
            // worker.thread.join().unwrap();
        }
    }
}








// pub fn add(left: u64, right: u64) -> u64 {
//     left + right
// }
//
// #[cfg(test)]
// mod tests {
//     use super::*;
//
//     #[test]
//     fn it_works() {
//         let result = add(2, 2);
//         assert_eq!(result, 4);
//     }
// }
