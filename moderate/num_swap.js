function swap_numbers(a, b) {
  function magnitude(num) {
    const order = Math.floor(Math.log(num) / Math.LN10 + 0.00000001)
    return Math.pow(10, order)
  }

  if (a.num === b.num) {
   return
  }

  const magn = magnitude(b.num) * 10

  b.num += a.num * magn
  a.num = b.num % magn
  b.num = Math.floor(b.num / magn)
}

const MAX = 5000;
for (let i = 1; i < MAX; i++) {
  for (let j = 1; j < MAX; j++) {
    const foo = {num: i}
    const bar = {num: j}

    swap_numbers(foo, bar)

    if ((foo.num !== j) && (bar.num !== i)) {
      throw new Error(`Couldn't swap ${i} (${foo.num}) with ${j} (${bar.num})`)
    }
  }
}
