'use strict'

function isUnique(arr) {
  for (const i in arr) {
    if (arr.indexOf(arr[i]) != i) {
      return false
    }
  }

  return true
}

function isUniqueWOtricks(arr) {
  for (const i in arr) {
    for (let j = 0; j < i; j++) {
      if (arr[j] == arr[i]) {
        return false
      }
    }
  }

  return true
}

function fastIsUnique(arr) {
  const set = new Set()

  for (const el of arr) {
    if (set.has(el)) {
      return false
    }
    set.add(el)
  }

  return true
}

// test

if (isUnique([4,4]))
  throw new Error('44')

if (isUnique([1,1,7]))
  throw new Error('117')

if (!isUnique([1,3,2]))
  throw new Error('132')

if (fastIsUnique([4,4]))
  throw new Error('44')

if (fastIsUnique([1,1,7]))
  throw new Error('117')

if (!fastIsUnique([1,3,2]))
  throw new Error('132')

if (isUniqueWOtricks([4,4]))
  throw new Error('44')

if (isUniqueWOtricks([1,1,7]))
  throw new Error('117')

if (!isUniqueWOtricks([1,3,2]))
  throw new Error('132')
