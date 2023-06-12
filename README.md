# STMF103 C6T6 驱动

## 工具

### arm-none-eabi-gcc

### openocd

openocd下载脚本

```shell

```

### clangd

clangd依赖compile_commands.json文件来解析代码。

生成compile_commands.json：

```shell
#在win下依赖python的compiledb库
#1. 安装compiledb
pip install compiledb
#2. 使用compiledb运行make命令即可生成compile_commands.json
compiledb make
```

配置clangd，在vscode中设置clangd参数：

```json
{
    "clangd.arguments": [
//        "--all-scopes-completion",
//        "--completion-style=detailed",
        "--query-driver=toolchain/bin/arm-linux-gnueabi*"
    ]
}
```

`–query-driver=toolchain/bin/arm-linux-gnueabi*`:匹配交叉编译器指令，clangd会调用`xxx -v`指令获取**头文件路径**信息，用于头文件解析
