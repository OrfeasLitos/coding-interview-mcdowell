DECK_SIZE = 52

# naive:
# create a 1-1 mapping M : [52!] -> deck ordering
# choose a uniformly random number rn in [52!]
# return M(rn)
# gives probability 1/(52!) for every ordering

# smarter:
# keep list of non-shuffled cards
# choose one at a time from this list uniformly at random
# gives probability 1(52!) for every ordering
# proof: let ordering O.
# Pr[card 1] = 1/52, Pr[card 1, 2] = 1/52 * 1/51, ...,
# Pr[card 1, ..., i] = 1/(i!), Pr[card 1, ..., 52] = 1/(52!)

import random

def shuffle(size):
    unshuffled = set(range(0, size))
    shuffled = list()

    while unshuffled:
        card = random.sample(unshuffled, 1)[0]
        unshuffled.remove(card)
        shuffled.append(card)

    return shuffled

def test_size_uniqueness(size):
    deck = shuffle(size)
    checked = set()

    while deck:
        top = deck.pop()
        assert(top not in checked)
        checked.add(top)

    assert(len(checked) == size)

if __name__ == "__main__":
    test_size_uniqueness(DECK_SIZE)
