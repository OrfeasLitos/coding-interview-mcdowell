from collections import Counter

def checkPermutation(a, b):
    if len(a) != len(b):
        return False

    for c in a:
        if c in b:
            b.replace(c, '')
        else:
            return False

    return True

def checkPermutationFaster(a, b):
    return sorted(a) == sorted(b)

def checkPermutationFastest(a, b):
    return Counter(a) == Counter(b)

# test
if checkPermutation('ab', 'ac'):
    raise Exception('ab, ac')

if not checkPermutation('ab', 'ba'):
    raise Exception('ab, ba')

if checkPermutation('ab', 'aba'):
    raise Exception('ab, aba')

if checkPermutationFaster('ab', 'ac'):
    raise Exception('ab, ac')

if not checkPermutationFaster('ab', 'ba'):
    raise Exception('ab, ba')

if checkPermutationFaster('ab', 'aba'):
    raise Exception('ab, aba')

if checkPermutationFastest('ab', 'ac'):
    raise Exception('ab, ac')

if not checkPermutationFastest('ab', 'ba'):
    raise Exception('ab, ba')

if checkPermutationFastest('ab', 'aba'):
    raise Exception('ab, aba')
