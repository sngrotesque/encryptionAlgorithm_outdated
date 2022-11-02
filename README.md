# 由SN-Grotesque开启并维护的加密算法项目
###### Encryption algorithm written by 'SN-Grotesque'

### Symmetric Encryption by SN-Grotesque
##### S2048: v1.1.1 (Release)

| 版本号(Version) | 描述(Description)                                                          |
| :---            | :---                                                                       |
| v1.1.1          | 修复了上一个版本s2048_BlockPaddingAdd函数的BUG                             |
|                 | 如果原数据的内存空间足够存放填充数据那么就不重新申请新的内存空间           |
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

### MBS256: v0.0.1 (Beta)

| 版本号(Version) | 描述(Description)                                                          |
| :---            | :---                                                                       |
| v0.0.1          | 正在开发中...                                                              |

### Public-key Cryptography by SN-Grotesque
##### S000: v0.0.1 (Beta)

| 版本号(Version) | 描述(Description)                                                          |
| :---            | :---                                                                       |
| v0.0.1          | 正在开发中...                                                              |
