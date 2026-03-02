# CSBox - CS1.6 外部 ESP 学习研究工具

[English Version (英文版)](doc/README_EN.md)

本仓库包含一个用于 Counter-Strike 1.6 的外部 ESP（Extra Sensory Perception）原型工具。本项目旨在研究 Windows 图形驱动、内存读取技术以及 World-to-Screen (W2S) 算法，仅供学习与技术交流使用。

## ⚠️ 免责声明 (Legal Disclaimer)

1.  **仅供学习：** 本项目的所有代码、文档及相关资料仅用于计算机安全、内存管理及底层图形技术的研究与交流。
2.  **严禁非法使用：** 严禁将本项目用于任何破坏游戏公平性、违反游戏服务条款或违反当地法律法规的行为。用户因违反此条规定而产生的任何法律责任及后果，由用户自行承担，与开发者无关。
3.  **不保证稳定性：** 本工具属于原型阶段，不对任何系统崩溃、游戏封号或其他技术风险负责。
4.  **法律风险提示：** 制作、传播或使用游戏外挂可能触及法律红线。请在下载后 24 小时内删除，请勿用于商业用途。

## 功能特点

*   **外部绘制 (External Overlay)**：基于 Raylib 的高性能透明窗口渲染。
*   **W2S 投影算法**：支持 Column-Major 和 Row-Major 矩阵自动判定。
*   **智能同步**：自动检测游戏窗口分辨率变化及位置，确保方框不偏移。
*   **防截图保护**：集成 `SetWindowDisplayAffinity` 技术，使 Overlay 在截图中不可见。
*   **自动附加**：游戏重启后可自动重新检测并附加进程。

## 技术架构

*   **渲染引擎**：Raylib + Win32 API
*   **语言**：C++20
*   **构建系统**：CMake + vcpkg
*   **内存技术**：ReadProcessMemory (RPM) 封装

## 快速开始

### 开发环境要求
*   Visual Studio 2022 (Community 或更高版本)
*   CMake 3.20+
*   vcpkg

### 编译步骤
1.  确保 CS 1.6 已启动（建议使用 `-window -noborder` 启动参数）。
2.  运行 `build_release32.bat` 进行 Release x86 编译。
3.  编译完成后，在 `bin/Release` 目录下找到 `csbox.exe` 并运行。

## 许可证 (License)

本项目采用 **“仅供学习交流使用”** 协议。
禁止任何形式的商业分发、售卖或用于非法牟利。
