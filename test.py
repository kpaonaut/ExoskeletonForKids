import termios, fcntl, sys, os
fd = sys.stdin.fileno()
oldterm = termios.tcgetattr(fd)
newattr = termios.tcgetattr(fd)
newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
termios.tcsetattr(fd, termios.TCSANOW, newattr)
oldflags = fcntl.fcntl(fd, fcntl.F_GETFL)
fcntl.fcntl(fd, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)
global signal
def detectKeyboard():
    try:
        while 1:
            try:
                c = sys.stdin.read(1)
                print "the little guy is about to stop!"
                signal = 1 - signal
                return
            except IOError: return
    finally:
        termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
        fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
        return

def main():
    detectKeyboard()
    print "done!"

if __name__ == "__main__": main()