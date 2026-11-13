# CH32V203x6 空白工程

这是一个适用于 CH32V203x6 的空白工程，包含基础初始化代码，可用于验证本机编译环境和 WCH RISC-V 工具链能否正常完成固件的编译与链接，也可作为新项目的起点。

## 适用范围

| MCU 型号 | 使用说明 |
| --- | --- |
| CH32V203F6P6 | 可直接使用本工程编译，默认配置为 32 KB Flash 和 10 KB SRAM |
| CH32V203F8P6 | 也可使用，但默认仍按 x6 的容量进行链接，即 32 KB Flash 和 10 KB SRAM |
| CH32V203F8U6 | 也可使用，但默认仍按 x6 的容量进行链接，即 32 KB Flash 和 10 KB SRAM |
| CH32V203G6U6 | 可直接使用本工程编译，默认配置为 32 KB Flash 和 10 KB SRAM |
| CH32V203G8R6 | 也可使用，但默认仍按 x6 的容量进行链接，即 32 KB Flash 和 10 KB SRAM |
| CH32V203K8T6 | 也可使用，但默认仍按 x6 的容量进行链接，即 32 KB Flash 和 10 KB SRAM |
| CH32V203K8U7 | 也可使用，但默认仍按 x6 的容量进行链接，即 32 KB Flash 和 10 KB SRAM |
| CH32V203C6T6 | 可直接使用本工程编译，默认配置为 32 KB Flash 和 10 KB SRAM |
| CH32V203C8T6 | 也可使用，但默认仍按 x6 的容量进行链接，即 32 KB Flash 和 10 KB SRAM |
| CH32V203C6U6 | 可直接使用本工程编译，默认配置为 32 KB Flash 和 10 KB SRAM |
| CH32V203C8U6 | 也可使用，但默认仍按 x6 的容量进行链接，即 32 KB Flash 和 10 KB SRAM |
| CH32V203RBT6 | 不属于本工程默认适用范围，需另行适配 |

本工程的 [Ld/Link.ld](Ld/Link.ld) 默认配置为 32 KB Flash 和 10 KB SRAM。使用 CH32V203x8 时，若需使用完整的 64 KB Flash 和 20 KB SRAM，应将 `MEMORY` 段中 `FLASH` 的 `LENGTH` 改为 `64K`，将 `RAM` 的 `LENGTH` 改为 `20K`

## 编译准备

- 安装 CMake（3.16 或更高版本）和 Ninja，并确保命令行可以调用 `cmake` 和 `ninja`
- Windows 平台安装 [**MounRiver Studio**](https://www.mounriver.com/)，WCH RISC-V GCC 工具链随其捆绑安装，官方不单独分发 Windows 版工具链；Linux 和 macOS 平台可从 [MounRiver Studio 官方下载页](https://www.mounriver.com/download/) 单独下载对应平台的工具链。
- 确认 `CMakeLists.txt` 中对应操作系统的工具链目录已设置为本机实际安装路径：Windows 使用 `TOOLCHAIN_DIR_WIN`，Linux 使用 `TOOLCHAIN_DIR_LINUX`，macOS 使用 `TOOLCHAIN_DIR_MAC`

Windows 下，工具链通常位于 MounRiver Studio 安装目录中的以下路径：

```text
resources/app/resources/win32/components/WCH/Toolchain/RISC-V Embedded GCC
```

例如，假设 MounRiver Studio 安装在 `e:/RISCV/MRS`，则将 `CMakeLists.txt` 中已有的 `TOOLCHAIN_DIR_WIN` 定义修改为：

```cmake
set(TOOLCHAIN_DIR_WIN   "e:/RISCV/MRS/resources/app/resources/win32/components/WCH/Toolchain/RISC-V Embedded GCC")
```

## 命令行编译

在本目录（`empty`）打开终端，执行：

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

第一条命令配置工程并生成 Ninja 构建文件，第二条命令编译并链接固件。上述命令适用于 Windows、Linux 和 macOS，各平台应分别生成自己的 `build` 目录。

配置完成后，仅修改源代码时，通常只需再次执行 `cmake --build build`

## VS Code 编译

VS Code 编译同样需要先完成上述[编译准备](#编译准备)。

1. 在 VS Code 中安装 Microsoft 提供的 [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) 扩展。
2. 使用 VS Code 打开本目录（`empty`）作为工作文件夹。
3. 点击左下角状态栏中 CMake Tools 的构建按钮（齿轮图标），扩展会在需要时自动配置工程并编译。

## 编译产物

编译成功后，`build` 目录中会生成 `ch32v203x6.elf`、`ch32v203x6.hex`、`ch32v203x6.bin`、`ch32v203x6.map` 和 `ch32v203x6.lst`
