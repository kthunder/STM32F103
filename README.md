# Contex-M3 驱动

## 工具

### 编译链

#### arm-none-eabi-gcc

### 下载器驱动

#### openocd

openocd下载脚本

```powershell
openocd.exe ^
-s "C:\\ENV\\EmbeddedToolChain\\xpack-openocd-0.11.0-5\\scripts" ^
-f "./st_nucleo_f103rb.cfg" ^
-c "tcl_port disabled" ^
-c "gdb_port disabled" ^
-c "tcl_port disabled" ^
-c "program %1" ^
-c reset ^
-c shutdown
```

### 代码解析

#### ~~clangd~~  C/C++

 使用vscode自带插件C/C++解析代码,使用compile_commands.json文件辅助解析

win环境下生成compile_commands.json的工具：

```shell
#在win下依赖python的compiledb库
#1. 安装compiledb
pip install compiledb
#2. 使用compiledb运行make命令即可生成compile_commands.json
compiledb make
```

~~clangd依赖compile_commands.json文件来解析代码。~~

~~配置clangd，在vscode中设置clangd参数：~~

```json
{
    "clangd.arguments": [
//        "--all-scopes-completion",
//        "--completion-style=detailed",
        "--query-driver=toolchain/bin/arm-linux-gnueabi*"
    ]
}
```

~~`–query-driver=toolchain/bin/arm-linux-gnueabi*`:匹配交叉编译器指令，clangd会调用 `xxx -v`指令获取**头文件路径**信息，用于头文件解析~~

### Debug工具

#### ContexM-Debug

配置文件 launch.json

```json
{
	// 使用 IntelliSense 了解相关属性。 
	// 悬停以查看现有属性的描述。
	// 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
	"version": "0.2.0",
	"configurations": [
		{
			"name": "Cortex Debug",
			"cwd": "${workspaceFolder}",
			"executable": "./build/main.elf",
			"request": "launch",
			"type": "cortex-debug",
			"svdFile": "./env/STM32F103xx.svd",
			"runToEntryPoint": "main",
			"servertype": "openocd",
			"configFiles": [
				"interface/stlink.cfg",
				"target/stm32f1x.cfg"
			]
		}
	]
}
```
