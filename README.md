# 由SN-Grotesque开启并维护的加密算法项目
###### Encryption algorithm written by 'SN-Grotesque'

### Symmetric Encryption by SN-Grotesque
##### S2048: v1.2.5 (Release)
| 版本号(Version) | 描述(Description)                                                          |
| :---            | :---                                                                       |
| v1.2.5          | 进行了微小改动                                                             |
| v1.2.4          | 还原了snCrypto_ctx内的size，使得部分功能更易使用                           |
| v1.2.3          | 修改了部分代码细节，让代码更具便捷性                                       |
| v1.2.2          | 删除了s2048_ctx内的size，更加贴合分组加密算法的理念                        |
| v1.2.1          | 修改了s2048_RoundKey，s2048_ctx的构造节省系统资源                          |
| v1.1.2          | SBOX修改为IV，后续版本添加真正的sbox与rsbox                                |
| v1.1.1          | 修复了上一个版本s2048_BlockPaddingAdd函数的BUG                             |
|                 | 如果原数据的内存空间足够存放填充数据那么就不申请新的内存空间               |
|                 | 重构了s2048_keyPadding函数内容                                             |
| v1.1.0          | 展开了以往压缩的代码                                                       |
|                 | 修改了填充值                                                               |
|                 | 重新设计了函数，宏定义，变量名                                             |
|                 | 添加了一个新函数s2048_BlockPaddingRemove                                   |
| v1.0.1          | 简单修改了一下代码的格式                                                   |
| v1.0.0          | 将此仓库闭源，并重新设计了使用形式                                         |
|                 | 修改了ENCRYPT与DECRYPT的宏定义，使其更不易被破译                           |
| Beta v0.7.2     | 重新设计了sbox的使用形式                                                   |
| Beta v0.7.1     | 修补了一个对称加密算法都容易存在的问题。                                   |
|                 | 加密轮数修改为9轮                                                          |
| Beta v0.7       | 创建了新的分支用于更新此版本，修复了加密函数多次执行会过度消耗资源的问题。 |
| Beta v0.6       | 优化了代码结构与复杂度                                                     |
| Beta v0.5       | 修复了以往版本中被忽视的一个重大BUG(足以引起安全问题)                      |
| Beta v0.4       | 修复了前期代码的某些算法问题并优化了资源占用问题                           |
|                 | 加密轮数修改为7轮                                                          |
| Beta v0.3       | 修复了v0.2时期产生的某些BUG并优化了算法复杂度                              |
|                 | 并添加了sbox用于混淆密钥                                                   |
| Beta v0.2       | 修复了v0.1时期产生的某些BUG并优化了使用体验                                |
| Beta v0.1       | 建立了初始大纲                                                             |
|                 | 所有数据的长度均为256的倍数                                                |
|                 | 不足时填充为256的倍数                                                      |
|                 | 初始为14轮加密                                                             |

##### MBS512: v1.0.0 (Release)
| 版本号(Version) | 描述(Description)                                                          |
| :---            | :---                                                                       |
| v1.0.0          | 修改为512位分组加密算法                                                    |
|                 | 输入输出均为uint8_t类型数据                                                |
|                 | 加密与解密采用11轮                                                         |
|                 | 添加了IV，与子密钥盒，均可自定义                                           |
| Beta v0.0.1     | 初始大纲：256位分组对称加密算法                                            |
|                 | 明文输入为uint8_t类型，密文输出与密钥为0x1000 ~ 0xffff的uint16_t类型数据   |
|                 | MBS名称就是这么来的，3轮加密与解密                                         |

### Public-key Cryptography by SN-Grotesque
##### S000: v0.0.1 (Beta)
| 版本号(Version) | 描述(Description)                                                          |
| :---            | :---                                                                       |
| v0.0.1          | 公钥常数pkn为随意一个4位数字.                                              |
|                 | 公钥公式 pk = (pkn * (256 ** 24)) ^ (pkn ** 16)                            |
|                 | c = m\*pk mod N mod 256; m = c\*sk mod N mod 256                           |