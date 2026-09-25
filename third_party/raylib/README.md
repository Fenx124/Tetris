# Raylib 6.0（预编译）

来自 [raylib 6.0](https://github.com/raysan5/raylib/releases/tag/6.0) 的官方 Windows MSVC 包：

- `raylib-6.0_win32_msvc16.zip`
- `raylib-6.0_win64_msvc16.zip`

`include` 中是这两个包里的 `raylib.h` 和 `raymath.h`。`lib/Win32` 与 `lib/x64` 中的 `raylib.lib` 是对应包里的导入库 `raylibdll.lib`（已改名为 `raylib.lib`，便于和源码树 DLL 工程的输出文件名一致），`raylib.dll` 是同目录下的动态库。Debug 与 Release 共用这一套。

许可见同目录的 `LICENSE`（zlib）。
