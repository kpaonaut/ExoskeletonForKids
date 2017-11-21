class trial:
    def fooo(self):
        self = 0
        x = 0
        return x, self

def main():
    t = trial()
    a, b = t.fooo()
    print (a)

if __name__ == "__main__": main()