'use strict'

function factorial_zeroes(n) {
  // trailing_zeroes(n) == n! div 10 == min(n! div 2, n! div 5)
  // == min(sum[i = 1..n](i div 2), sum[i = 1..n](i div 5))

  let twos = 0, fives = 0

  for (let i = 1; i <= n; i++) {
    let counter = i
    while (counter % 2 == 0) {
      twos++
      counter /= 2
    }

    counter = i
    while (counter % 5 == 0) {
      fives++
      counter /= 5
    }
  }

  return Math.min(twos, fives)
}

function get_trailing_zeroes(n) {
  let res = 0
  while (n % BigInt(10) == 0) {
   res++
   n /= BigInt(10)
 }
 return res
}

let acc = BigInt(1)
for (let i = BigInt(1); i < BigInt(2000); i++) {
  acc *= BigInt(i)
  if (factorial_zeroes(i) != get_trailing_zeroes(acc)) {
    console.log(i, acc, factorial_zeroes(i), get_trailing_zeroes(acc))
  }
}
