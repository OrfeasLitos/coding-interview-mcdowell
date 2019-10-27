import secrets
import string

def randomString(length):
    chars = string.ascii_lowercase + string.digits
    return ''.join(secrets.choice(chars) for i in range(length))

class LettersNumbers:
    def __init__(self, string):
        if not string.isalnum():
            raise ValueError("LettersNumbers accepts only alphanumeric strings")
        self.str = string
        self.res = [dict() for _ in range(0, len(string))]

    def longest_rec(self, start, end):
        if len(self.res[start]) > end and self.res[start][end]:
            return self.res[start][end]

        if end == start + 1:
            if self.str[start].isalpha():
                self.res[start][end] = {
                    "start": start, "end": end,
                    "letters": 1, "numbers": 0,
                    "best": None
                }
            else:
                self.res[start][end] = {
                    "start": start, "end": end,
                    "letters": 0, "numbers": 1,
                    "best": None
                }
            return self.res[start][end]

        left = self.longest_rec(start, end - 1)
        res = {
            "start": start, "end": end,
            "letters": left["letters"] + (1 if self.str[end - 1].isalpha() else 0),
            "numbers": left["numbers"] + (0 if self.str[end - 1].isalpha() else 1),
        }
        if res["letters"] == res["numbers"]:
            res["best"] = (start, end)
            return res

        right = self.longest_rec(start + 1, end)

        if right["best"] == None:
            res["best"] = left["best"]
        elif left["best"] == None:
            res["best"] = right["best"]
        else:
            right_length = right["best"][1] - right["best"][0]
            left_length = left["best"][1] - left["best"][0]
            res["best"] = right["best"] if right_length > left_length else left["best"]

        return res

    def longest(self):
        return self.longest_rec(0, len(self.str))

if __name__ == "__main__":
    for _ in range(0,500):
        length = secrets.choice(range(1, 21))
        ln = LettersNumbers(randomString(length))
        res = ln.longest()
        if res["best"]:
            print(ln.str, res["best"][0], res["best"][1],
                ln.str[res["best"][0]:res["best"][1]])
        else:
            print(ln.str, "No balanced substring")
