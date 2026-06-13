# 03 - Resources（资源）目录说明

## 目录概览

`resources/` 目录是 ai-infra-junior-engineer-learning 项目的资源中心，汇集了学习过程中所需的速查表、推荐书单、工具清单等辅助材料。该目录旨在为学习者提供高效、即查即用的参考资料，减少学习过程中的搜索成本，帮助学习者将精力聚焦于核心技能的掌握。

---

## 目录结构

### 一、Cheat Sheets（速查表）— `resources/cheat-sheets/`

速查表是为日常开发和运维工作准备的快速参考文档，涵盖 AI 基础设施工程师最常用的技术栈。每份速查表采用精简的表格和代码示例形式，适合打印或在第二屏打开随时查阅。

| 文件名 | 内容简介 |
|---|---|
| `.gitkeep` | 占位文件，用于在 Git 中保留空目录结构 |
| `python-cheat-sheet.md` | Python 语法速查表，涵盖：数据类型与类型转换、控制流（if/for/while）、函数定义与参数传递、常用标准库（os、sys、json、collections、itertools）及第三方库（numpy、pandas）速览 |
| `linux-cheat-sheet.md` | Linux 命令速查表，涵盖：文件与目录操作（ls/cp/mv/find/grep）、权限管理（chmod/chown）、进程管理（ps/top/kill/systemctl）、网络诊断（curl/wget/ss/netstat/ping） |
| `git-cheat-sheet.md` | Git 命令速查表，涵盖：基本提交流程（add/commit/push）、分支管理（branch/checkout/merge/rebase）、远程仓库操作（remote/fetch/pull）、历史查看（log/diff/blame）与常见工作流 |
| `docker-cheat-sheet.md` | Docker 命令速查表，涵盖：镜像操作（build/pull/push/tag）、容器生命周期（run/start/stop/exec/logs）、网络配置（network create/connect）、Docker Compose 常用指令与文件模板 |
| `kubernetes-cheat-sheet.md` | Kubernetes 命令速查表，涵盖：kubectl 基础命令、Pod 管理与调试、Deployment 滚动更新与回滚、Service 与 Ingress 配置、ConfigMap/Secret 管理、常用故障排查命令 |
| `sql-cheat-sheet.md` | SQL 语法速查表，涵盖：基础 CRUD 操作（SELECT/INSERT/UPDATE/DELETE）、多表 JOIN（INNER/LEFT/RIGHT/FULL）、聚合查询（GROUP BY/HAVING/聚合函数）、索引创建与优化、窗口函数速览 |
| `prometheus-cheat-sheet.md` | Prometheus/PromQL 速查表，涵盖：PromQL 查询语法与常用函数（rate/irate/increase/histogram_quantile）、告警规则编写（alerting rules）、Recording Rules 与 Dashboard 常用表达式 |

### 二、Reading Lists（推荐书单）— `resources/reading-lists/`

推荐书单按学习阶段划分为三个等级，为不同阶段的学习者提供针对性的阅读建议。每个路径均包含在线教程（免费）和经典书籍（需购买或借阅），并标注了建议的阅读顺序和优先级。

| 文件名 | 内容简介 |
|---|---|
| `.gitkeep` | 占位文件，用于在 Git 中保留空目录结构 |
| `beginner-path.md` | **入门路径推荐阅读**（适用于 0～3 个月学习者）：包含 Python 入门教程（如 Python 官方教程、Automate the Boring Stuff）、Linux 基础（鸟哥的 Linux 私房菜）、Git 入门（Pro Git）、计算机网络基础等。标注了"必读"与"选读"标签 |
| `intermediate-path.md` | **中级路径推荐阅读**（适用于 3～6 个月学习者）：包含进阶编程书籍（如 Fluent Python、Effective Python）、Docker 与 Kubernetes 实战指南、ML 系统工程（Designing Machine Learning Systems）、数据库原理等。附实战项目推荐 |
| `advanced-path.md` | **进阶路径推荐阅读**（适用于 2～5 年职业发展）：包含系统设计经典（Designing Data-Intensive Applications / DDIA）、分布式系统原理、MLOps 实践、架构设计模式、技术领导力等。附职业发展规划建议 |

### 三、其他资源文件

| 文件名 | 内容简介 |
|---|---|
| `README.md` | 资源目录总览与使用指南：介绍 resources/ 下的子目录结构、各文件的推荐使用方式、以及如何贡献新的资源文件（Pull Request 流程） |
| `tools.md` | 推荐工具清单：涵盖四大类工具 —— IDE 与编辑器（VS Code、PyCharm、Jupyter）、CLI 工具与终端（Oh My Zsh、tmux、fzf、jq）、协作平台与知识管理（GitHub、Notion、Obsidian）、学习辅助工具（Anki、Excalidraw、draw.io），并附安装指引和使用场景说明 |

---

## 如何高效使用本资源目录

### 1. 按需查阅，而非通读

速查表的目的是"速查"，不是"速学"。当你在编码或运维过程中遇到遗忘的语法或命令时，打开对应的速查表快速定位，而不是尝试一次性背诵所有内容。熟练来自反复使用。

### 2. 结合模块进度使用书单

- **开始 Module 001 之前**：先浏览 `beginner-path.md`，确保预备知识扎实
- **通过中期评估后**：开始阅读 `intermediate-path.md` 中的进阶书籍，与实际项目练习交替进行
- **接近结业或入职后**：将 `advanced-path.md` 作为长期阅读计划，每季度攻克 1～2 本

### 3. 善用工具清单提升效率

`tools.md` 中的每个工具都标注了"必装"(must-have)和"选装"(nice-to-have)标签。建议在学习第一周内完成必装工具的安装与配置，避免后期因工具问题拖慢学习进度。

### 4. 贡献与反馈

如果你发现了优秀的速查表资源、好书推荐或高效工具，欢迎通过 Fork + Pull Request 的方式贡献到对应文件中。请在 PR 中简要说明推荐理由，社区维护者会定期审核合并。

---

> **提示**：本目录会随技术栈演进而持续更新。如果你发现某个速查表内容过时或有误，请在 GitHub Issues 中提交修正请求。
