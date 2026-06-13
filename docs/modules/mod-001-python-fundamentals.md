# 模块 001 — Python 基础设施编程基础

> **时长**: 15 小时 | **难度**: 入门 | **前置知识**: 基本的编程概念（变量、循环、函数）

---

## 模块概述

本模块为 AI 基础设施工程师奠定扎实的 Python 编程基础。你将学习如何搭建专业的 Python 开发环境、掌握编写生产级 Python 代码所需的高级特性，以及 DevOps 自动化、异步编程和代码质量保障的最佳实践。本模块是后续所有模块的前置基础。

---

## 主题分解

### 1. Python 环境搭建（2小时）

- **虚拟环境管理**: venv 与 conda 的选型与使用，隔离项目依赖的核心方法
- **pip 包管理**: requirements.txt 与 pyproject.toml 的规范管理、依赖锁定与版本冲突解决
- **IDE 配置**: VS Code / PyCharm 的 Python 开发环境调优、调试器配置、扩展推荐

### 2. 高级 Python 特性（6小时）

- **类型提示与静态检查**: typing 模块的使用（Optional、Union、List、Dict 等泛型）、mypy 静态类型检查的集成与配置
- **日志最佳实践**: logging 模块的层级架构（Logger / Handler / Formatter）、日志级别策略、结构化日志设计、多模块日志管理
- **配置管理**: 环境变量、.env 文件、YAML/JSON 配置文件的管理、pydantic-settings / dynaconf 配置库使用
- **异常处理**: 自定义异常类与异常层级设计、try/except/finally 最佳实践、上下文管理器（with 语句）与资源管理

### 3. Python DevOps（4小时）

- **subprocess 进程管理**: subprocess.run() 的安全使用、标准输入/输出/错误流处理、进程超时与退出码检查
- **文件系统操作**: pathlib 面向对象路径操作、os/shutil 文件与目录管理、glob 模式匹配、文件权限与属性
- **JSON/YAML 解析**: json 模块的序列化与反序列化、PyYAML 的安全加载与导出、Schema 验证基础
- **CLI 命令行工具**: argparse 参数解析器的完整构建、子命令设计、帮助文档与交互提示

### 4. 异步编程（自学）

- **async/await 机制**: 协程基础概念、事件循环（event loop）的运行原理
- **并发模式**: asyncio.gather() 并发执行、异步上下文管理器、aiofiles / httpx 异步 I/O 库

### 5. 测试与代码质量（3小时）

- **pytest 单元测试**: 测试用例的编写与组织、fixture 的创建与复用、参数化测试、Mock 与 Patch 的使用
- **代码格式化**: black 自动格式化、isort 导入排序、代码风格的一致性保障
- **静态分析**: pylint 代码质量检查、flake8 风格检查、类型提示驱动的 Bug 检测
- **pre-commit hooks**: 提交前自动执行的检查链条（格式化、lint、测试），保障仓库代码质量的最后一道防线

---

## 学习目标

完成本模块后，你应当能够：

1. 搭建并维护一个专业、可复现的 Python 开发环境
2. 编写带有类型提示、日志与异常处理的生产级 Python 代码
3. 实现常见的 DevOps 自动化任务（文件处理、命令调用、配置管理）
4. 理解异步编程模型并能够编写基础的异步程序
5. 使用 pytest 编写和维护测试用例
6. 通过格式化工具与 pre-commit hooks 保障代码质量

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/01-environment-setup.md` | 讲义 | Python 环境搭建（venv/conda/pip/IDE） |
| `lecture-notes/02-advanced-python.md` | 讲义 | 高级 Python 特性（类型提示、日志、配置、异常处理） |
| `lecture-notes/03-python-devops.md` | 讲义 | Python DevOps（subprocess、文件操作、JSON/YAML、CLI） |
| `lecture-notes/04-async-programming.md` | 讲义 | 异步编程（async/await、asyncio） |
| `lecture-notes/05-testing-and-quality.md` | 讲义 | 测试与代码质量（pytest、black/isort、lint、pre-commit） |
| `exercises/01-environment-setup.md` | 练习 | 环境搭建实操练习 |
| `exercises/02-advanced-python.md` | 练习 | 高级 Python 特性练习 |
| `exercises/03-python-devops.md` | 练习 | Python DevOps 练习 |
| `exercises/04-async-programming.md` | 练习 | 异步编程练习 |
| `exercises/05-testing-quality.md` | 练习 | 测试与代码质量练习 |
| `exercises/06-mini-project.md` | 练习 | 综合小项目：构建一个 CLI 工具 |
| `exercises/07-capstone-project.md` | 练习 | 综合项目：自动化运维脚本集 |
| `quizzes/module-001-quiz.md` | 测验 | 模块 001 知识检测测验 |
| `resources.md` | 资源 | 推荐阅读、参考链接与延伸学习资料 |

---

## 关联模块

- **前序**: 无（本模块为起点）
- **后续**: [模块 002 — Linux 系统管理基础](./mod-002-linux-essentials.md)、[模块 003 — Git 版本控制与协作](./mod-003-git-version-control.md)
