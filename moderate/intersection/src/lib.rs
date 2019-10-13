use std::error;
use std::fmt;

#[derive(Debug)]
pub struct Point {
    x: f64,
    y: f64
}

impl PartialEq for Point {
    fn eq(&self, other: &Point) -> bool {
        const EPSILON: f64 = 0.00001;

        self.x - other.x < EPSILON
        && self.y - other.y < EPSILON
    }
}

#[derive(Debug, PartialEq)]
pub struct Line {
    start: Point,
    end: Point
}

impl Line {
    pub fn slope(&self) -> f64 {
        (self.start.y - self.end.y) / (self.start.x - self.end.x)
    }

    pub fn parallel_to(&self, other: &Line) -> bool {
        self.slope() == other.slope()
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct ParallelError;

impl fmt::Display for ParallelError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "parallel lines")
    }
}

impl error::Error for ParallelError {
    fn source(&self) -> Option<&(dyn error::Error + 'static)> {
        None
    }
}

pub fn intersection(a: &Line, b: &Line) -> Result<Point, ParallelError> {
    if a.parallel_to(b) {
        Err(ParallelError)
    } else {
        // solution to system of two lines
        let x =
            (a.slope()*a.end.x - b.slope()*b.end.x - a.end.y + b.end.y)
            / (a.slope() - b.slope());
        let y = a.slope()*x - a.slope()*a.end.x + a.end.y;

        Ok(Point { x, y })
    }
}

#[cfg(test)]
mod tests {
    use crate::Point;
    use crate::Line;
    use crate::intersection;
    use crate::ParallelError;

    #[test]
    fn slope_one() {
        let line = Line {
            start: Point { x: 0.0, y: 0.0 },
            end: Point { x: 1.0, y: 1.0 }
        };
        assert_eq!(line.slope(), 1.0)
    }

    #[test]
    fn slope_half() {
        let line = Line {
            start: Point { x: 0.0, y: 0.0 },
            end: Point { x: 1.0, y: 1.0/2.0 }
        };
        assert_eq!(line.slope(), 1.0/2.0)
    }

    #[test]
    fn slope_infinity() {
        let line = Line {
            start: Point { x: 0.0, y: 0.0 },
            end: Point { x: 0.0, y: 1.0/2.0 }
        };
        assert_eq!(line.slope().abs(), std::f64::INFINITY)
    }

    #[test]
    fn parallel() {
        let a = Line {
            start: Point { x: -1.0, y: 1.0 },
            end: Point { x: 1.0, y: -1.0 }
        };
        let b = Line {
            start: Point { x: -2.0, y: 1.0 },
            end: Point { x: 0.0, y: -1.0 }
        };
        assert_eq!(intersection(&a, &b).unwrap_err(), ParallelError);
    }

    #[test]
    fn parallel_vertical() {
        let a = Line {
            start: Point { x: -1.0, y: 1.0 },
            end: Point { x: -1.0, y: -1.0 }
        };
        let b = Line {
            start: Point { x: -2.0, y: 1.0 },
            end: Point { x: -2.0, y: -1.0 }
        };
        assert_eq!(intersection(&a, &b).unwrap_err(), ParallelError);
    }

    #[test]
    fn origin() {
        let a = Line {
            start: Point { x: -1.0, y: 1.0 },
            end: Point { x: 1.0, y: -1.0 }
        };
        let b = Line {
            start: Point { x: 1.0, y: 1.0 },
            end: Point { x: -1.0, y: -1.0 }
        };
        assert_eq!(intersection(&a, &b).unwrap(), Point { x: 0.0, y: 0.0 });
    }

    #[test]
    fn unit() {
        let a = Line {
            start: Point { x: -2.0, y: 0.0 },
            end: Point { x: 4.0, y: 2.0 }
        };
        let b = Line {
            start: Point { x: 2.0, y: -1.0 },
            end: Point { x: -1.0, y: 5.0 }
        };
        assert_eq!(intersection(&a, &b).unwrap(), Point { x: 1.0, y: 1.0 });
    }
}
