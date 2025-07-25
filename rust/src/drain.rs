use std::marker::PhantomData;
use std::{mem, ptr};
use crate::my_vec::MyVec;
use crate::rawvaliter::RawValIter;

/**
@author: June
@since: 2025/7/25
@desc:
*/



struct Drain<'a, T: 'a> {
    vec: PhantomData<&'a mut MyVec<T>>,
    iter: RawValIter<T>,
}

impl<'a, T> Iterator for Drain<'a, T> {
    type Item = T;
    fn next(&mut self) -> Option<T> {
        self.iter.next()
    }

    fn size_hint(&self) -> (usize, Option<usize>) {
        self.iter.size_hint()
    }
}

impl<'a, T> DoubleEndedIterator for Drain<'a, T> {
    fn next_back(&mut self) -> Option<T> {
        self.iter.next_back()
    }
}

impl<'a, T> Drop for Drain<'a, T> {
    fn drop(&mut self) {
        for _ in &mut self.iter {}
    }
}

impl<T> MyVec<T> {
    fn drain(&mut self) -> Drain<T> {
        unsafe {
            let iter = RawValIter::new(&self);
            self.len = 0;
            Drain {
                iter: iter,
                vec: PhantomData,
            }
        }
    }
}