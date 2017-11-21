class trial:
    def fooo(self):
        self = 0
        x = 0
        return x, self

def main():
    t = trial()
    import numpy as np
    a = np.array([1, 2])
    b = np.array([2, 3])
    print (a - b)

if __name__ == "__main__": main()