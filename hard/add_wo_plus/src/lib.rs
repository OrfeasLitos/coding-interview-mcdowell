use std::fmt;
use std::error;

#[derive(Debug, Clone, PartialEq)]
pub struct NegativeError;

impl fmt::Display for NegativeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "no negative numbers here")
    }
}

impl error::Error for NegativeError {
    fn source(&self) -> Option<&(dyn error::Error + 'static)> {
        None
    }
}

#[derive(Debug, PartialEq, Clone)]
pub enum MyNum {
    Zero,
    Positive(Box<MyNum>)
}

impl fmt::Display for MyNum {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.to_int())
    }
}

impl MyNum {
    fn succ(self) -> MyNum {
        MyNum::Positive(Box::new(self))
    }

    fn pred(self) -> Result<MyNum, NegativeError> {
        match self {
            MyNum::Zero => Err(NegativeError),
            MyNum::Positive(prev) => Ok(*prev)
        }
    }

    fn to_int(&self) -> usize {
        match self {
            MyNum::Zero => 0,
            MyNum::Positive(prev) => 1 + prev.to_int()
        }
    }

    fn from(n: usize) -> MyNum {
        match n {
            0 => MyNum::Zero,
            _ => MyNum::Positive(Box::new(MyNum::from(n-1)))
        }
    }
}

pub fn add_wo_plus(left: MyNum, right: MyNum) -> MyNum {
    match right {
        MyNum::Zero => left.clone(),
        _ => add_wo_plus(left.succ(), right.pred().unwrap())
    }
}

#[cfg(test)]
mod tests {
    use crate::MyNum;
    use crate::add_wo_plus;

    // TODO: move unit tests close to definition
    #[test]
    fn zero() {
        assert_eq!(MyNum::Zero.to_int(), 0);
        assert_eq!(MyNum::Zero, MyNum::from(0));
    }

    #[test]
    fn one() {
        let one = MyNum::Positive(Box::new(MyNum::Zero));
        assert_eq!(one.to_int(), 1);
        assert_eq!(one, MyNum::from(1));
    }

    #[test]
    fn thousand() {
        let thousand = MyNum::from(1000);
        assert_eq!(thousand.to_int(), 1000);
    }
    // TODO: avoid stack overflows for huge numbers

    #[test]
    fn inc() {
        let one = MyNum::Positive(Box::new(MyNum::Zero));
        assert_eq!(one, MyNum::Zero.succ());
    }

    #[test]
    fn dec() {
        let one = MyNum::Positive(Box::new(MyNum::Zero));
        assert_eq!(one.pred().unwrap(), MyNum::Zero);
    }

    #[test]
    fn one_plus_two() {
        let one = MyNum::Positive(Box::new(MyNum::Zero));
        let two = MyNum::from(2);
        let three = MyNum::from(3);
        assert_eq!(add_wo_plus(one, two), three);
    }

    #[test]
    fn zero_plus_one() {
        let one = MyNum::Positive(Box::new(MyNum::Zero));
        let another_one = one.clone();
        assert_eq!(add_wo_plus(one, MyNum::Zero), another_one);
    }

    #[test]
    fn two_thousand() {
        let thousand = MyNum::from(1000);
        let thousand_one = thousand.clone().succ();
        let sum = add_wo_plus(thousand, thousand_one);

        let two_thousand_one = MyNum::from(2001);
        assert_eq!(sum, two_thousand_one);
    }
}
