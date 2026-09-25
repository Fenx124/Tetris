# Tetris

基于 Raylib 的俄罗斯方块。程序创建标题为 `Tetris` 的窗口，大小 600×800，目标帧率 60。棋盘 10 列 × 20 行，每格 30 像素。

## 功能

- 七种方块：I、O、T、L、J、S、Z。每种有 4 个旋转状态，开局随机生成当前方块和下一个方块，右侧预览下一个方块。
- 幽灵方块：显示当前方块的落点，可在设置里开关。
- 四种难度，在难度选择界面用鼠标点选：Easy、Normal、Hard、God。下落间隔（按 60 FPS 计的帧数）分别为 30、25、20、10。
- 自动提升难度（可关）：间隔为 1 分钟、3 分钟或 5 分钟（`Difficult_UP_Time` 为 60、180、300，再乘以 60 帧）。计时只在当前难度不是 Hard 时进行。升级只把 Easy 变为 Normal、Normal 变为 Hard，不会升到 God。
- 消行计分：同一次消除 1、2、3、4 行，基础分分别为 100、300、500、800，再按难度相乘：Easy ×1、Normal ×2、Hard ×3、God ×5。当前分数不低于最高分时更新最高分。
- 最高分以二进制写入 `Save/SaveScore.txt`。游戏结束时保存；主界面最高分旁边的 **R** 按钮把最高分清零并保存。启动时若打不开该文件，程序会退出。
- 设置以二进制写入 `Save/SaveSet.txt`，启动时读取，从设置界面返回时保存。可选项：是否自动提升难度、提升间隔、背景音乐（Sound）、音效（Voice）、幽灵方块（Ghost）。**Reset** 恢复默认：自动提升开启、间隔 1 分钟、音乐、音效和幽灵方块均为开启。
- 背景图为 `Resources/1.png`。背景音乐 `Resources/tetris.mp3` 仅在游戏中或暂停、且 Sound 开启时播放。消行播放 `Resources/tetris_s.mp3`，顶行出现已锁定方块而失败时播放 `Resources/tetris_f.mp3`（音效受 Voice 开关控制）。
- 方块无法继续下落时锁定到棋盘，下一个方块成为当前方块，并再随机生成新的下一个方块。旋转时若水平方向越出棋盘，会尝试平移后再旋转：I 形移动 2 格，其余方块移动 1 格。
- 界面状态：主菜单、难度选择、设置、游戏中、暂停、结束。

## 操作

键位与鼠标点击来自 `input.cpp`。菜单用鼠标左键。

主界面：

| 操作 | 作用 |
| --- | --- |
| Start | 进入难度选择 |
| Setting | 进入设置 |
| Exit | 关闭窗口并退出 |
| 最高分旁的 R | 最高分清零并写入存档 |

难度选择：Easy、Normal、Hard、God，点选后进入游戏。

设置：

| 操作 | 作用 |
| --- | --- |
| 自动提升难度开关 | 打开或关闭自动升级 |
| 1 min / 3 min / 5 min | 仅在自动提升开启时可选，设置升级间隔 |
| Sound | 背景音乐开关 |
| Voice | 消行与失败音效开关 |
| Ghost | 幽灵方块开关 |
| Reset | 恢复上面列出的默认设置 |
| Return | 保存设置并回到主界面 |

游戏中的键盘：

| 按键 | 作用 |
| --- | --- |
| 方向键下 | 当前方块向下移动一格 |
| 方向键左 / 右 | 向左 / 向右移动 |
| 方向键上 | 旋转 |
| P | 游戏进行中暂停 |
| C | 暂停时继续 |
| R | 游戏结束时重新初始化并回到主界面 |

## 编译与运行

用 Visual Studio 打开 `Tetris.sln`。解决方案标明 Visual Studio Version 17（`VisualStudioVersion` 为 17.14.36623.8）。工程 `Tetris.vcxproj` 的 `VCProjectVersion` 为 17.0，平台工具集为 `v145`（Visual Studio 2026 的 MSVC 工具集），Windows 目标平台版本为 10.0。配置为 Debug 与 Release，平台为 Win32 与 x64；解决方案里的 x86 对应工程的 Win32。字符集为 Unicode，子系统为控制台。

四个配置的包含目录、库目录和链接依赖相同，都链接 `raylib.lib`、`winmm.lib`、`gdi32.lib`，并定义 `USE_LIBTYPE_SHARED`（按 DLL 使用 Raylib）。克隆后可以直接编译这四个配置，不必改工程文件。

默认使用仓库里的 `third_party/raylib`（Raylib 6.0，取自官方包 `raylib-6.0_win32_msvc16` 与 `raylib-6.0_win64_msvc16`）：

- 头文件：`third_party/raylib/include`（`raylib.h`、`raymath.h`）
- Win32：`third_party/raylib/lib/Win32` 下的 `raylib.lib` 与 `raylib.dll`
- x64：`third_party/raylib/lib/x64` 下的 `raylib.lib` 与 `raylib.dll`

这里的 `raylib.lib` 是官方包中的导入库 `raylibdll.lib`（不是同包里体积更大的静态库）。Debug 和 Release 共用对应平台的这一套文件。生成后，若库目录中有 `raylib.dll`，工程会把它复制到 exe 同一目录。

若要改用本机的 Raylib 源码树，设置环境变量 `RAYLIB_PATH`，或在 MSBuild 里传入 `/p:RAYLIB_PATH=...`。已设置时它优先于上面的默认目录。例如：

```text
RAYLIB_PATH=D:\code tools\raylib-master
```

当该目录中存在 `src\raylib.h` 时，头文件用 `$(RAYLIB_PATH)\src`，库用 Raylib 自带 VS2022 工程编出的 DLL 目录：

`$(RAYLIB_PATH)\projects\VS2022\build\raylib\bin\<Win32 或 x64>\<Debug.DLL 或 Release.DLL>`

其中需要有 `raylib.lib` 和旁边的 `raylib.dll`。当前配置的目录里没有 `raylib.lib` 时，改用同一平台的 `Debug.DLL`。不设置 `RAYLIB_PATH` 则不需要额外准备。

资源与存档使用相对路径，工作目录下需要有 `Resources` 和 `Save`：

- `Resources/1.png`、`Resources/tetris.mp3`、`Resources/tetris_s.mp3`、`Resources/tetris_f.mp3`
- `Save\SaveScore.txt`、`Save\SaveSet.txt`

`Tetris_Game` 目录里已经放好 `Tetris.exe`、`raylib.dll`、`Resources` 和 `Save`。

## 源文件与目录

- `Tetris.sln`、`Tetris.vcxproj`、`Tetris.vcxproj.filters`：Visual Studio 解决方案与工程（筛选器分为源文件、头文件、资源文件）。
- `Tetris.h`：棋盘尺寸、方块、游戏状态、难度与设置结构，以及函数声明。
- `main.cpp`：创建窗口、加载贴图与音频、主循环。
- `Init.cpp`：清空棋盘，生成方块，初始化分数、下落间隔、难度和设置，并读取存档。
- `creat.cpp`：七种方块的形状、随机生成，以及按旋转状态取出 4×4 形状。
- `input.cpp`：鼠标菜单与键盘操作。
- `move.cpp`：左右与向下移动、旋转、自动下落、贴墙平移。
- `judg.cpp`：边界判断、锁定、消行、计分、游戏结束、幽灵方块落点。
- `Cheak.cpp`：游戏进行时的更新、按难度设置下落间隔、自动提升难度。
- `game.cpp`：按状态绘制画面，并按设置暂停或继续背景音乐。
- `draw.cpp`：棋盘、方块、下一个方块、分数、难度、操作提示、菜单和设置界面。
- `File.cpp`：读写最高分和设置。
- `Resources/`：背景图与音频。
- `Save/`：最高分与设置的二进制存档。
- `Tetris_Game/`：可执行文件、`raylib.dll`、`Resources` 和 `Save` 放在一起的目录。
- `third_party/raylib/`：随仓库提供的 Raylib 6.0 头文件，以及 Win32 / x64 的导入库和 DLL。
- `raylib.dll`（仓库根目录）：原先附带的 Win32 动态库，版本字符串为 5.6-dev。用 Visual Studio 生成时，复制到 exe 旁边的是当前链接所用的那份 `raylib.dll`（默认来自 `third_party/raylib`）。

## 许可证

本项目以 [MIT 许可证](LICENSE) 发布。Copyright (c) 2026 Fenx124。

`third_party/raylib` 是 Raylib 6.0 的预编译文件，许可见 [third_party/raylib/LICENSE](third_party/raylib/LICENSE)（zlib）。
