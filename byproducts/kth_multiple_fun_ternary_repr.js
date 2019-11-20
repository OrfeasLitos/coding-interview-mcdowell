'use strict'

// Interesting but ultimately useless representation
// conversion while solving 17.9
// N.B.: Doesn't actually solve the exercise correctly

// convert integer to array of ternary digits
function ternary(k) {
  return k.toString(3)
          .split("")
          .map(c => parseInt(c))
}

// convert usual ternary representation to a modified one:
// in this representation, padding with zeroes is not allowed,
// Zero is not a special symbol anymore and it may be on the
// most significant position meaningfully. Normal increment rules
// apply, with the difference that the successor of 2^k is 0^(k+1).
// examples:
// 1 -> 0
// 3 -> 2
// 4 -> 00
// 9 -> 12
// 10 -> 20
// 12 -> 22
// 13 -> 000
function components(k) {
  const t = ternary(k)
  const res = t.slice(0)
  for (let i = t.length - 1; i >= 0; i--) {
    if (res[i] > 0) {
      res[i]--
    } else {
      let j = i
      while (j >= 0 && res[j] === 0) {
        res[j] = 2
        j--
      }
      res[j]--
      if (j === 0 && res[j] === 0) {
        res.shift()
        i--
      }
    }
  }
  return res
}

// converts the number to the modified ternary representation
// and multiplies an accumulator with 3, 5 or 7 for each
// ternary digit, depending on which digit it is
function k_multiple(k) {
  if (k < 1 || ((k | 0) !== k)) {
    throw new RangeError(`Positive integer expected, got ${k}`)
  }

  if (k === 1) {
    return 1
  }

  let acc = 1
  for (const d of components(k-1)) {
    switch (d) {
      case 0:
        acc *= 3
        break
      case 1:
        acc *= 5
        break
      case 2:
        acc *= 7
        break
    }
  }
  return acc
}
