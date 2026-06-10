@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" > nul 2>&1
echo === MSVC Environment Ready ===
cl.exe 2>&1 | findstr "Microsoft"
echo.

set NVCC_FLAGS=-O2 -arch=sm_75 -Xcompiler "/utf-8"

echo === 1/4: Compiling vec_add ===
nvcc %NVCC_FLAGS% "d:\study\ai-infra-career\fundamentals\cuda\kernels\01-vec-add\vec_add.cu" -o "d:\study\ai-infra-career\fundamentals\cuda\kernels\01-vec-add\vec_add.exe"
if %ERRORLEVEL% EQU 0 (
    echo PASS
    "d:\study\ai-infra-career\fundamentals\cuda\kernels\01-vec-add\vec_add.exe"
) else (
    echo FAIL
)

echo.
echo === 2/4: Compiling Softmax v1-v4 ===
nvcc %NVCC_FLAGS% "d:\study\ai-infra-career\fundamentals\cuda\kernels\03-softmax\softmax_v1_to_v4.cu" -o "d:\study\ai-infra-career\fundamentals\cuda\kernels\03-softmax\softmax_v1_to_v4.exe"
if %ERRORLEVEL% EQU 0 (
    echo PASS
    "d:\study\ai-infra-career\fundamentals\cuda\kernels\03-softmax\softmax_v1_to_v4.exe"
) else (
    echo FAIL
)

echo.
echo === 3/4: Compiling MatMul naive ===
nvcc %NVCC_FLAGS% "d:\study\ai-infra-career\fundamentals\cuda\kernels\04-matmul\matmul_naive.cu" -o "d:\study\ai-infra-career\fundamentals\cuda\kernels\04-matmul\matmul_naive.exe"
if %ERRORLEVEL% EQU 0 (
    echo PASS
    "d:\study\ai-infra-career\fundamentals\cuda\kernels\04-matmul\matmul_naive.exe"
) else (
    echo FAIL
)

echo.
echo === 4/4: Compiling MatMul tiled ===
nvcc %NVCC_FLAGS% "d:\study\ai-infra-career\fundamentals\cuda\kernels\04-matmul\matmul_tiled.cu" -o "d:\study\ai-infra-career\fundamentals\cuda\kernels\04-matmul\matmul_tiled.exe"
if %ERRORLEVEL% EQU 0 (
    echo PASS
    "d:\study\ai-infra-career\fundamentals\cuda\kernels\04-matmul\matmul_tiled.exe"
) else (
    echo FAIL
)

echo.
echo === All Done ===
pause
