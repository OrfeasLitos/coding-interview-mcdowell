'use strict'

// O(res.length)
function increment(res) {
  for (let i = res.length - 1; i >= 0; i--) {
    if (res[i] < 2) {
      res[i]++
      for (let j = i + 1; j < res.length; j++) {
        res[j] = res[i]
      }
      return
    }
  }

  for (const i in res) {
    res[i] = 0
  }
  res.push(0)
}

// Calculates the k-th in modified ternary, as
// exemplified by the following pairs:
// 1 - 0
// 2 - 1
// 3 - 2
// 4 - 00
// 5 - 01
// 6 - 02
// 7 - 11
// 12 - 002
// 13 - 011
// O(k) - TOFIX: find a smarter way to calculate this
function components(k) {
  const res = [0]
  for (let i = 2; i <= k; i++) {
    increment(res)
  }
  return res
}

function product(digits) {
  let res = 1
  for (const digit of digits) {
    switch (digit) {
      case 0:
        res *= 3
        break
      case 1:
        res *= 5
        break
      case 2:
        res *= 7
        break
      default:
        throw new RangeError(`0-2 digit expected, got ${digit}`)
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

  // TOFIX: order statistic tree would be better than list
  const values = [1]
  // TOFIX: 2*k arbitrarily chosen
  for (let i = 1; i <= 2*k; i++) {
    values.push(product(components(i)))
  }
  // O(values.length * log(values.length))
  values.sort((a, b) => a > b)

  return values[k-1]
}

function test(k, expected) {
  const res = k_multiple(k)
  if (res !== expected) {
    throw new Error(`fails at ${k}: expected ${expected}, got ${res}`)
  }
}

test(1, 1)
test(2, 3)
test(3, 5)
test(4, 7)
test(5, 9)
test(6, 15)
test(7, 21)
test(8, 25)
