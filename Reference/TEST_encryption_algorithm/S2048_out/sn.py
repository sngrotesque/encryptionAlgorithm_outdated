from base64 import b64decode as bde, b64encode as ben
from binascii import a2b_hex as a2b, b2a_hex as b2a
from random import randint as rint, choice
from os import urandom

def true_random_key(num = 256, size = 8):
    data = ["0x%02x"%x for x in urandom(num)]
    for x in range(len(data)):
        print(data[x], end=",")
        if (x + 1) % size != 0:
            print(" ", end="")
        if (x + 1) % size == 0:
            print()

def key(min, max, num, size = 8):
    a = ["0x%02x"%(rint(min, max)) for x in range(num)]
    for x in range(len(a)):
        print(a[x], end=",")
        if (x + 1) % size != 0:
            print(" ", end="")
        if (x + 1) % size == 0:
            print()

def hex_key():
    hextable = "0123456789abcdef"
    data = "".join([choice(hextable) for x in range(512)])
    for x in range(512):
        print(data[x], end="")
        if(x+1) % 64 == 0:
            print()

def str_hex_key():
    data = ["%02x"%rint(1, 255) for x in range(256)]
    for x in range(len(data)):
        if x == 0: print("\"", end="")
        print(f"\\x{data[x]}", end="")
        if(x+1) % 16 == 0:
            print("\"", end="\n\"")

def NULL_KEY(size = 8):
    for x in range(256):
        print("0x00", end=",")
        if (x+1)%size != 0:
            print(" ", end="")
        if (x+1)%size == 0:
            print()

def read_key(file_name, size = 8):
    with open(file_name, "rb") as f:
        data = f.read().split(b"\n")
    
    for x in data:
        if x:
            a = ["0x%02x"%x for x in list(bde(x))]
            for x in range(len(a)):
                print(a[x], end=",")
                if (x+1)%size != 0:
                    print(" ", end="")
                if (x+1)%size == 0:
                    print()

if __name__ == "__main__":
    # key(0x10, 0xF0, 256)
    # read_key("./out/sn.key")
    # NULL_KEY()
    # hex_key()
    # str_hex_key()
    true_random_key()


