'use strict'

function count_digits_of(n, wanted) {
  if (n === 0 && wanted === 0) {
    return 1
  }

  let count = 0;
  while (n) {
    count += n % 10 == wanted
    n = Math.floor(n/10)
  }
  return count
}

function count_digits_range_naive(n, wanted) {
  let count = 0
  for (let i = 0; i <= n; i++) {
    count += count_digits_of(i, wanted)
  }
  return count
}

function split_number(n, rank) {
  let smaller = []
  for (let i = 0; i < rank; i++) {
    smaller.unshift(n % 10)
    n = Math.floor(n/10)
  }

  const digit = n % 10
  n = Math.floor(n/10)

  let larger = []
  while (n > 0) {
    larger.unshift(n % 10)
    n = Math.floor(n/10)
  }

  smaller = (smaller.length === 0) ? null : Number(smaller.join(''))
  larger = (larger.length === 0) ? null : Number(larger.join(''))
  return [smaller, digit, larger]
}

function count_digits_range_fast(n, wanted) {
  if (n === 0 && wanted === 0) {
    return 1
  }

  let count = 0

  for (let i = 0; 10**i <= n; i++) {
    let [smaller, digit, larger] = split_number(n, i)

    count += larger * 10**i
    if (digit === wanted) {
      count += smaller + 1
    }
    else if (wanted < digit) {
      count += 10**i
    }
  }

  return count
}

for (let i = 0; i < 400; i++) {
  // TODO: find how to count 0's
  for (let j = 1; j <= 9; j++) {
    const naive = count_digits_range_naive(i, j)
    const fast = count_digits_range_fast(i, j)
    if (naive !== fast) {
      throw new Error(`fails at ${i}, ${j}: naive == ${naive}, fast == ${fast}`)
    }
  }
}
