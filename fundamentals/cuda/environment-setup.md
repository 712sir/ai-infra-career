# CUDA 开发环境搭建记录

> 日期：2026-06-04 ~ 2026-06-05 | 状态：✅ 完成

---

## 环境概览

| 项目 | 配置 |
|------|------|
| GPU | NVIDIA GeForce GTX 1650 (4GB) |
| 驱动版本 | 552.12 (CUDA 12.4 支持) |
| CUDA Toolkit | 12.4.131 |
| nvcc 路径 | `D:\NVIDIA\bin\nvcc.exe` |
| CUDA_PATH | `D:\NVIDIA` |
| C++ 编译器 | MSVC 14.44.35207 (VS2022, `D:\vs`) |
| 编译目标 | `-arch=sm_75` (Turing, compute capability 7.5) |
| 操作系统 | Windows 10 x64 |

---

## 安装方式

**最终方案：手动解压法**

NVIDIA 的 CUDA 网络安装器反复失败（创建空目录骨架但不下载实际文件），最终采用：
1. 从 NVIDIA CDN 直接下载独立包（nvcc.exe / cudart.exe / CUDADevelopment.exe）
2. 用 7-Zip 解压到 `D:\NVIDIA`
3. 手动设置环境变量

```
D:\NVIDIA\
├── bin\
│   ├── nvcc.exe          # 编译器驱动 (13MB)
│   ├── ptxas.exe         # PTX 汇编器 (19MB)
│   ├── nvlink.exe        # 链接器 (19MB)
│   ├── cudafe++.exe      # CUDA C++ 前端 (7MB)
│   ├── fatbinary.exe     # Fat binary 打包
│   ├── bin2c.exe         # 二进制转 C 数组
│   └── cudart64_12.dll   # CUDA 运行时
├── include\              # CUDA 头文件
├── lib\                  # 静态库
└── nvvm\                 # LLVM 设备编译器
```

---

## 遇到的问题与解决方案

### 问题 1：网络安装器创建空目录，不下载文件

**现象**：运行 `cuda_12.4.1_windows_network.exe`，选择 D:\NVIDIA，安装程序显示"完成"，但 D:\NVIDIA 下只有 57 个空目录，没有任何二进制文件。

**原因**：网络安装器需要连接 NVIDIA CDN (`developer.download.nvidia.com`) 下载各组件包。网络不通导致下载失败，但安装器不报错。

**解决**：绕过安装器，直接从 CDN 手动下载包文件并用 7-Zip 解压。
- CDN URL：`http://developer.download.nvidia.com/compute/cuda/12.4.1/network_installers/windows/x86_64/wddm2/`
- 备注：该 CDN 会自动 301 重定向到 `.nvidia.cn` 中国镜像

---

### 问题 2：安装过程中出现蓝屏警告

**现象**：网络安装器勾选了 Display Driver 组件，尝试更新显卡驱动时触发蓝屏。

**原因**：CUDA 安装器自带的显示驱动与现有驱动 552.12 冲突。

**解决**：自定义安装时取消勾选所有 Driver components（Display.Driver、Display.Nview、Display.Optimus、Display.Update）。

---

### 问题 3：独立包安装失败 (exit code 9)

**现象**：直接运行下载的 `nvcc.exe` / `cudart.exe` / `CUDADevelopment.exe` 独立包安装器，均返回 exit code 9。

**原因**：这些独立包有依赖关系（nvcc 依赖 CUDADevelopment），独立运行无法解析依赖。

**解决**：用 7-Zip 直接把 `.exe` 包文件当压缩包解压，绕过安装器的依赖检查。这些文件本质是 LZMA2 压缩的 7z 归档。

```
"C:\Program Files\7-Zip\7z.exe" x nvcc.exe -o"D:\NVIDIA" -y
```

---

### 问题 4：nvcc 找不到 cl.exe

**现象**：
```
nvcc fatal: Cannot find compiler 'cl.exe' in PATH
```

**原因**：nvcc 需要 MSVC C++ 编译器作为 host compiler。VS2022 虽已安装，但 `cl.exe` 不在系统 PATH 中，需要先运行 `vcvars64.bat` 设置环境。

**解决**：编译前先调用 vcvars：
```batch
call "D:\vs\VC\Auxiliary\Build\vcvars64.bat"
```

---

### 问题 5：源码编码导致编译警告和运行时异常

**现象**：
```
warning C4819: The file contains a character that cannot be represented
in the current code page (936)
```
且编译后的程序 GPU 计算结果全为 0。

**原因**：中文 Windows 系统默认代码页为 GBK (936)，`.cu` 文件中包含的 Unicode 字符（如 ✓ ✗、中文注释）与 GBK 不兼容，导致 MSVC 处理异常。

**解决**：
1. 源码使用纯 ASCII 字符（中文注释 → 英文注释）
2. 或保存为 UTF-8 with BOM 格式

---

## 编译标准流程

```batch
:: 1. 设置 MSVC 环境
call "D:\vs\VC\Auxiliary\Build\vcvars64.bat"

:: 2. 确保 nvcc 在 PATH 中
set PATH=D:\NVIDIA\bin;%PATH%

:: 3. 编译（指定目标架构 sm_75 = GTX 1650）
nvcc -arch=sm_75 source.cu -o output.exe
```

## 验证结果

| 测试 | 结果 |
|------|:--:|
| `__nvcc_device_query` | 75 (sm_75) ✅ |
| `test_cuda.cu` (setOne kernel, N=1024) | PASS ✅ |
| vecAdd small (N=256) | PASS ✅ |
| vecAdd large (N=16M, 65536 blocks) | PASS ✅ |
