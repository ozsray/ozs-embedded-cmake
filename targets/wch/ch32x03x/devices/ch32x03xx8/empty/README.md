# CH32X03xx8 空白工程

这是一个适用于 CH32X033x8 和 CH32X035x8 的空白工程，包含基础初始化代码，可用于验证本机编译环境和 WCH RISC-V 工具链能否正常完成固件的编译与链接，也可作为新项目的起点。

## 适用范围

| MCU 型号 | 使用说明 |
| --- | --- |
| CH32X035R8T6 | 支持，可直接使用本工程编译 |
| CH32X035C8T6 | 支持，可直接使用本工程编译 |
| CH32X035G8U6 | 支持，可直接使用本工程编译 |
| CH32X035G8R6 | 支持，可直接使用本工程编译 |
| CH32X035F8U6 | 支持，可直接使用本工程编译 |
| CH32X035F7P6 | 可能支持；按手册的型号命名规则，Flash 容量应为 48 KB，需核对实际容量，谨慎使用 |
| CH32X035D8U6 | 支持，可直接使用本工程编译 |
| CH32X033F8P6 | 支持，可直接使用本工程编译 |

本工程的 [Ld/Link.ld](Ld/Link.ld) 默认配置为 62 KB Flash 和 20 KB SRAM。使用 CH32X035F7P6 前，应先核对 Flash 实际容量，并据此调整 `MEMORY` 段中 `FLASH` 的 `LENGTH`

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

编译成功后，`build` 目录中会生成 `ch32x03xx8.elf`、`ch32x03xx8.hex`、`ch32x03xx8.bin`、`ch32x03xx8.map` 和 `ch32x03xx8.lst`
