# CSBox - CS1.6 External ESP Learning & Research Tool

[中文版 (Chinese Version)](../README.md)

This repository contains an external ESP (Extra Sensory Perception) prototype tool for Counter-Strike 1.6. This project is intended for studying Windows graphics drivers, memory reading techniques, and World-to-Screen (W2S) algorithms. For educational and technical exchange purposes only.

## ⚠️ Legal Disclaimer

1.  **Educational Use Only:** All code, documentation, and related materials in this project are for research and exchange in computer security, memory management, and low-level graphics technology.
2.  **Illegal Use Forbidden:** It is strictly prohibited to use this project for any behavior that undermines game fairness, violates game terms of service, or violates local laws and regulations. Any legal liabilities and consequences arising from the user's violation of this provision shall be borne by the user themselves and have nothing to do with the developer.
3.  **No Warranty:** This tool is in the prototype stage. The developer is not responsible for any system crashes, game bans, or other technical risks.
4.  **Legal Risk Warning:** Creating, distributing, or using game cheats may cross legal lines. Please delete within 24 hours after downloading and do not use for commercial purposes.

## Features

*   **External Overlay**: High-performance transparent window rendering based on Raylib.
*   **W2S Projection Algorithm**: Supports automatic detection of Column-Major and Row-Major matrices.
*   **Smart Sync**: Automatically detects game window resolution changes and positions to ensure boxes do not offset.
*   **Anti-Screenshot Protection**: Integrated `SetWindowDisplayAffinity` technology to make the overlay invisible in screenshots.
*   **Auto-Attach**: Automatically detects and re-attaches to the process after a game restart.

## Technical Architecture

*   **Rendering Engine**: Raylib + Win32 API
*   **Language**: C++20
*   **Build System**: CMake + vcpkg
*   **Memory Technique**: Wrapped ReadProcessMemory (RPM)

## Quick Start

### Development Environment Requirements
*   Visual Studio 2022 (Community or higher)
*   CMake 3.20+
*   vcpkg

### Build Steps
1.  Ensure CS 1.6 is launched (Recommended startup parameters: `-window -noborder`).
2.  Run `build_release32.bat` for Release x86 compilation.
3.  After compilation, find `csbox.exe` in the `bin/Release` directory and run it.

## License

This project adopts the **"For Learning and Exchange Only"** protocol.
Any form of commercial distribution, sale, or use for illegal profit is prohibited.
