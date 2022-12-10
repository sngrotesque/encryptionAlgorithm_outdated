from base64 import b64encode as b64en, b64decode as b64de
from binascii import a2b_hex as a2b
from random import choice

def random_bytes(length):
    temp = [x for x in range(256)]
    arr = [hex(choice(temp)).replace("0x", "") for x in range(length)]
    for x in range(length):
        if (len(arr[x])) == 1:
            arr[x] = "0" + arr[x]
    return a2b("".join(arr))

def xor(x, y, m):
    # C (0x1f + (x ^ y) ^ (50 - y ^ y)) - 0xc4
    return ((x ^ y) - (m ^ y)) + 1000

# move 取值范围: 0 - 888
def encrypt(data, key, move):
    data = list(data)
    dataLen = len(data)
    keyindex = 0
    for x in range(dataLen):
        if keyindex == 256:
            keyindex = 0
        data[x] = str(xor(data[x], key[keyindex], move))
        if len(data[x]) == 3:
            data[x] = "0" + data[x]
        keyindex += 1
    data = [hex(210 - x).replace("0x", "") for x in list(a2b("".join(data)))]
    data = b64en(a2b("".join(data))) # b64encode
    return data

def add_key():
    tmp = [x for x in range(1100, 9901)]
    key = [hex(choice(tmp)).replace("0x", "") for x in range(256)]
    for x in range(256):
        if len(key[x]) == 3:
            key[x] = "0" + key[x]
    print(key)
    key = list("".join(key))
    key = "".join([chr(ord(x) + 18) for x in key])
    key = b64en(key.encode()).decode()
    return key

def key_de(key):
    key = [chr(x - 18) for x in list(b64de(key))]
    index = 0
    for x in range(len(key) // 4):
        key[x] = key[index : index + 4]
        key[x] = int("".join(key[x]), 16)
        index += 4
    del(key[256:])
    return key

if __name__ == "__main__":
    key = key_de("Q0lHdkRCeHZEQkhCQ0JIRUNES0RDQkdEREhEeEJIc3ZDdXVFQ0l4dUNJeEtCdHR0Q0N3SEREc0hDQ3REQ0V1RkJHdHhCd0VCQ0ZJeERCQkRCc0NJQ3N0SUJ0SXNDeEdLQkpJQ0NHdkJCS0ZKQ0d3REN4RkZCSHdzQ0Jzd0J2SXNCdEJ2Qkh0RUNzREtERkRKQ0J2c0JGeEJEQkhDREJFeERHeEhDR0tJQ0VKeERHSkpDc0d0Q3hJSkNLeElCRnZGREZCSkRGR0tCSUlIQ3VCR0NFSUVEQ3N3REZDSURDc0REQ0h2Q3hKc0N4d0VDdHhzQ3ZER0JzSnhCdENFQ0hEREN2R0tDc3VKQnNFRURFSkhDQkh3Q0dGQkN2dUhDc0JEQkZ0dkNGQkdDS0NKQ0dLQ0N0dkdDR0N0Q0hIS0NJSEREQnhEREREd0NLSkVDQkt1Qkh1QkNDdEtDSHVDQ3d0Q0N2REVDRkJ1Qnh2SkNDRUZDdnd1Q0ZzeEJJd0ZCSXVEREJIRURCdUNDdUtDQnh3dkJ0c0RCS0V0Q0tDdUNJSEhDREtIREdDQkNHRUVCRnd0Qkp0dkRHdnNERHZCQkdFeENHc0tCSkl3QnZCRkN0RXRCeHV3Q3ZCQ0N1SHhCR0ZEREJIREJGd3ZDSUV3REhzRkJ0Q3ZERUt1Q0t4SkJGdHZDeHZ3QklFQkJLQ0lDdElDQ0tHdkNER3hCRktCQ3REd0J4QnNEQ3dKQ0pKdEN0RXZCc0N3QnZzSEJ0R3RER0hDQnd0dkJISHNDRklCRERESUN3REtEQndDQ3h2RUJIREVDS0JJREZzR0NJR3VDRUh2REZFSkJKSHVCdHZKQkhGd0N2SktESEhFQ3dHdUJHREVCdEh1QnRDQkJ1REpDeEt4REZ2S0RGS0pCdkpFQ0tDdEJ3RXZERXd1Q0tzS0NLdnNCd0dGRERGdURDSkhDeENLRENCdURESkpDdUVIQ3hHQ0JJS0pDSXRHQ0pFSUNCSUhDR3REQnNJR0N0QkJER0tLREV1c0RFRHVCR3N4Q0l4dERGR0JCd3dIQkp1Q0NGdklDRHR0Q0tERERFSUhDd3N4Q3R2Q0NIR0REREVFQ0lGRUNERHRDSXVzQnV0RkJLRHVDR0JIQ3R2c0J0SkVDRXhHQndDSkRGeElCS0V3QkpIRUNDQndDRklGRERFd0RHSUpDS0R1REdHc0N1SkNCSndLQkZ0RUNFSXdERnREQ0d2eEJ3S0hERUVCQkhKS0N3QktDR0hCQkZHeERIRHdCS3hDQ0tIQ0REd3VCSERGQkZIRUJLSXRCdXdHQ0VGQkN1dkNCdURJQ0lESENESEVCSnRGQnRKd0J0Q0lDRnRKQ3NIQg==")
    # data = random_bytes(1024)
    # with open("../../te.jpg", "rb") as f:
    #     data = f.read()
    data = b"fuck you"
    res = encrypt(data, key, 758)
    print(res)

