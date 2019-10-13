class WordCounter:
    def __init__(self, text):
        self.text = text.lower().split()
        self.frequencies = {}

    def freq_of(self, word):
        word = word.lower()
        if word not in self.frequencies:
            self.frequencies[word] = self.text.count(word)
        return self.frequencies[word]

if __name__ == "__main__":
    counter = WordCounter("a very very long text")
    if counter.freq_of("very") != 2:
        raise Exception("\"very\" not properly counted in \"a very very long text\"")
    if counter.frequencies["very"] != 2:
        raise Exception("\"very\" not saved in \"a very very long text\"")
    if counter.freq_of("abu") != 0:
        raise Exception("\"abu\" not properly counted in \"a very very long text\"")
    if counter.freq_of("ry") != 0:
        raise Exception("\"ry\" not properly counted in \"a very very long text\"")
