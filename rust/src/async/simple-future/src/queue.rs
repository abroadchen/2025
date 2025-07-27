use futures::Stream;

/**
@author: June
@since: 2025/7/26
@desc:
*/

struct Queue<T> {
    qdata: Vec<T>,
    capacity: usize,
}

impl<T> Queue<T> {
    fn new(size: usize) -> Self {
        Queue { qdata: Vec::with_capacity(size), capacity: size }
    }

    fn enqueue(&mut self, data: T) -> Result<(), String> {
        if self.qdata.len() == self.capacity {
            return Err("Queue full!".to_string());
        }
        self.qdata.push(data);
        Ok(())
    }

    fn dequeue(&mut self) -> Option<T> {
        let size = self.qdata.len();
        if size > 0 {
            let v = self.qdata.remove(0);
            Some(v)
        } else {
            None
        }
    }

    fn size(&self) -> usize {
        self.qdata.len()
    }
}