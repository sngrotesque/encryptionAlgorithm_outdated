### Chinese
```text
SNC是由SN-Grotesque开发的对称分组加密算法，是一种采用了Feistel与SPN两种结构的加密算法。
它的区块长度为32字节，也就是256位。
采用三种密钥长度来支持不同场景的加密与解密，分别是：
    32字节（对应9轮加密）
    64字节（对应11轮加密）
    96字节（对应13轮加密）
目前有ECB，CBC两种加密模式。
------------------------------------------------------------------------------------
SNKB是由SN-Grotesque开发的公钥分组密码算法，是一种参考了SPN结构的非对称加密算法。
它的区块长度为128字节，也就是1024位。
公钥与私钥为128个0~65536之间的数字。
加密过程类似于RSA，但不完全相同，具体的讲解请等待此算法研发完成。
```

### English
```text
SNC is a symmetric packet encryption algorithm developed by SN-Grotesque. It is an encryption algorithm that uses Feistel and SPN structures.
Its block length is 32 bytes, which is 256 bits.
Three key lengths are used to support encryption and decryption in different scenarios, respectively:
    32 bytes (corresponding to 9 rounds of encryption)
    64 bytes (corresponding to 11 rounds of encryption)
    96 bytes (corresponding to 13 rounds of encryption)
At present, there are two encryption modes: ECB and CBC.
------------------------------------------------------------------------------------
SNKB is a public key block cipher algorithm developed by SN-Grotesque, which is an asymmetric encryption algorithm with reference to SPN structure.
Its block length is 128 bytes, which is 1024 bits.
The public key and private key are 128 numbers between 0 and 65536.
The encryption process is similar to RSA, but not completely the same. Please wait until the development of this algorithm is completed.
```