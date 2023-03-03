### SNC (中文描述)
```text
这是一个对称分组加密算法（SN Crypto）
固定区块长度为256位，也就是32字节。
密钥长度分为三种：
    1. 32字节（256位）
    2. 64字节（512位）
    3. 96字节（768位）

此算法的加密过程是这样的：
    1. 将明文分为对应个数的区块，每个区块为32字节大小，也就是4x8的矩阵
    2. 将每个矩阵进行字节置换，列移位，行混合操作。
    3. 使用加密函数将数据与轮密钥进行异或。
    4. 得到密文。

    其中，轮密钥是通过最开始的密钥生成而来，且具有良好的雪崩效应。
    并且跟其他类似的加密算法（如AES）不同的是，IV不仅会用于加密明文，还会直接作用在轮密钥中。
    因为轮密钥中每一个子密钥都是有IV参与。

此算法的解密过程是加密过程的逆运算：
    但要注意的是，密钥从最后一轮开始使用直到第一轮子密钥。

目前支持ECB模式加密
```

### SNKB (中文描述)
```text
这是一个公钥密码算法（SN kilobyte）

具体描述，请等下次
```

### SNC (English description)
```text
This is a symmetric packet encryption algorithm (SN Crypto)
The fixed block length is 256 bits, which is 32 bytes.
There are three key lengths:
    1. 32 bytes (256 bits)
    2. 64 bytes (512 bits)
    3. 96 bytes (768 bits)

The encryption process of this algorithm is as follows:
    1. Divide the clear text into blocks with corresponding number, and each block is 32 bytes in size, which is a 4x8 matrix
    2. Perform byte replacement, column shift and row mixing operations for each matrix.
    3. Use the encryption function to XOR the data and the round key.
    4. Get the ciphertext.

    The round key is generated from the first key and has good avalanche effect.
    And unlike other similar encryption algorithms (such as AES), IV is not only used to encrypt plaintext, but also directly used in the round key.
    Because each sub-key in the round key has IV participation.

The decryption process of this algorithm is the inverse operation of the encryption process:
    However, it should be noted that the key is used from the last round to the first round.

Currently supports encryption in ECB mode
```

### SNKB (English description)
```text
This is a public key cryptography algorithm (SN kilobyte)
Specific description, please wait next time.
```
