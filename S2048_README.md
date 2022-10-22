### Symmetric Encryption by SN-Grotesque

> 当前版本: v1.0.0 (Release)

<table>
    <tr>
        <th>Version</th>  <th>description</th>
    </tr>
    <tr>
        <th rowspan="2">v1.0.0</th> <th>将此仓库闭源，并重新设计了使用形式</th>
    </tr>
    <tr>
                                    <th>修改了ENCRYPT与DECRYPT的宏定义，使其更不易被破译</th>
    </tr>
    <tr>
        <th>Beta v0.7.2</th>
        <th>重新设计了sbox的使用形式</th>
    </tr>
    <tr>
        <th rowspan="2">Beta v0.7.1</th> <th>修补了一个对称加密算法都容易存在的问题。</th>
    </tr>
    <tr>
                                        <th>加密轮数修改为9轮</th>
    </tr>
    <tr>
        <th>Beta v0.7</th> <th>创建了新的分支用于更新此版本，修复了加密函数多次执行会过度消耗资源的问题。</th>
    </tr>
    <tr>
        <th>Beta v0.6</th> <th>优化了代码结构与复杂度</th>
    </tr>
    <tr>
        <th>Beta v0.5</th> <th>修复了以往版本中被忽视的一个重大BUG(足以引起安全问题)</th>
    </tr>
    <tr>
        <th rowspan="2">Beta v0.4</th> <th>修复了前期代码的某些算法问题并优化了资源占用问题</th>
    </tr>
    <tr>
                                        <th>加密轮数修改为7轮</th>
    </tr>
    <tr>
        <th rowspan="2">Beta v0.3</th> <th>修复了v0.2时期产生的某些BUG并优化了算法复杂度</th>
    </tr>
    <tr>
                                        <th>并添加了sbox用于混淆密钥</th>
    </tr>
    <tr>
        <th>Beta v0.2</th> <th>修复了v0.1时期产生的某些BUG并优化了使用体验</th>
    </tr>
    <tr>
        <th rowspan="4">Beta v0.1</th> <th>建立了初始大纲</th>
    </tr>
    <tr>                                <th>1. 所有数据的长度均为256的倍数</th></tr>
    <tr>                                <th>2. 不足时填充为256的倍数</th></tr>
    <tr>                                <th>3. 初始为14轮加密</th></tr>
</table>
