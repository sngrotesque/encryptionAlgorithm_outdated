from Crypto.Cipher import AES

t = b'B'

data = b"B"
key = b"vjaldk2nsc1234567890123456789012"
iv = b"qwertyuiopasdfgh"

def PKCS7_Padding(data :bytes, size = 32):
    padding_len = size - len(data) % size
    data += bytes(padding_len - 1)
    data += padding_len.to_bytes(1, byteorder = "big")
    return data

def fread(fileName):
    with open(fileName, "rb") as f:
        return f.read()

def aes256_encrypt(data :bytes, key :bytes, iv :bytes):
    aes = AES.new(key = key, mode = AES.MODE_CFB, IV = iv)
    return aes.encrypt(data)

def fencrypt(fn_in :str, fn_out :str, size = 32):
    data = fread(fileName = fn_in)
    key = b"qlz;fk13-95-as9f1-35u03jsdjfi1o3"
    iv = b"\x01\x02\x03\x04\x0f\x3b\xff\x32\x0a\xbd\x03\xf4\xc3\x0a\x02\xbc"
    
    with open(fn_out, "wb") as f:
        res = b""
        index = 0
        for x in range(len(data) // size):
            res = aes256_encrypt(data[index:index + size], key, iv)
            f.write(res)
            index += size

for x in range(3000):
    data = aes256_encrypt(data, key, iv)
    print("第%d次加密，值: %02x"%((x+1), list(data)[0]))
    if (data == t): break

