# 模块 002 — Linux 系统管理基础

> **时长**: 15 小时 | **难度**: 入门 | **前置知识**: 基本的计算机操作概念

---

## 模块概述

Linux 是 AI 基础设施和服务器的实际标准操作系统。本模块从零开始，系统性地教授 Linux 操作系统的核心知识，包括命令行操作、文件系统管理、Shell 脚本自动化以及基础的网络配置与安全加固。学完本模块后，你将能够在 Linux 服务器上独立完成日常运维任务。

---

## 主题分解

### 1. Linux 基础（4小时）

- **文件系统层级**: FHS 标准目录结构（/etc、/var、/usr、/opt 等），各目录的用途与最佳实践划分
- **用户、组与权限**: useradd / usermod / groupadd 管理用户与组，chmod / chown / setuid / setgid / sticky bit 权限模型，umask 默认权限掩码
- **进程管理**: ps / top / htop 进程查看，kill / pkill 信号控制（SIGTERM / SIGKILL / SIGHUP），前台/后台任务与 jobs 管理，nice / renice 进程优先级
- **系统资源**: df / du 磁盘空间分析，free / vmstat 内存使用、lscpu / nproc CPU 信息、系统负载 uptime 与 load average 解读

### 2. Shell 脚本编程（5小时）

- **Bash 基础**: shebang（#!/bin/bash）与脚本执行方式，引号规则（单引号 / 双引号 / 反引号）与转义
- **变量、条件、循环与函数**: 变量的定义、作用域与替换，if/elif/else 与 test 条件表达式，for / while / until 循环控制，函数的定义、参数传递与返回值
- **脚本调试**: set -e / -u / -x / -o pipefail 调试选项，shellcheck 静态检查，trap 信号捕获与错误处理，日志输出与脚本健壮性实践

### 3. 系统管理（4小时）

- **包管理器**: apt（Debian/Ubuntu）与 yum / dnf（RHEL/CentOS）的使用，仓库配置与 GPG 密钥管理，包的安装、更新、卸载与依赖解决
- **systemd 服务管理**: Unit 文件的编写（Service / Timer / Socket 类型），systemctl 服务的启动、停止、启用与状态查看，journalctl 日志查询
- **日志管理**: rsyslog 系统日志架构，/var/log 下关键日志文件的解读（syslog、auth.log、kern.log），logrotate 日志轮转配置
- **cron 定时任务**: crontab 语法与时间表达式，用户级与系统级 cron 的配置，定时任务的调试与常见陷阱

### 4. 网络基础（2小时）

- **网络配置**: ifconfig / ip 命令查看与配置网络接口，网络路由表与默认网关，DNS 解析配置 /etc/resolv.conf
- **防火墙**: iptables 链与规则（INPUT / OUTPUT / FORWARD），ufw（Uncomplicated Firewall）简化防火墙管理，常用规则的编写与应用
- **SSH 密钥管理**: ssh-keygen 生成密钥对，authorized_keys 配置免密登录，sshd_config 的安全加固（禁用密码登录、修改默认端口、限制用户）
- **网络排障**: ping / traceroute 连通性测试，netstat / ss 端口与连接分析，tcpdump 抓包基础，常见网络问题的诊断方法

---

## 学习目标

完成本模块后，你应当能够：

1. 熟练操作 Linux 命令行界面，高效完成文件、进程与用户管理
2. 编写结构清晰、健壮可维护的 Bash Shell 自动化脚本
3. 管理 Linux 系统服务、日志与定时任务
4. 排查常见的系统与网络问题
5. 通过 SSH 安全地访问和加固 Linux 服务器

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `EXERCISE_TO_LECTURE_MAPPING.md` | 文档 | 练习与讲义的对应映射关系 |
| `lecture-notes/01-linux-basics.md` | 讲义 | Linux 基础（文件系统、用户、权限、进程管理） |
| `lecture-notes/02-shell-scripting-part1.md` | 讲义 | Shell 脚本编程（上）：基础语法与变量 |
| `lecture-notes/03-shell-scripting-part2.md` | 讲义 | Shell 脚本编程（下）：条件、循环、函数 |
| `lecture-notes/04-system-administration.md` | 讲义 | 系统管理（包管理、systemd、日志管理） |
| `lecture-notes/05-cron-jobs.md` | 讲义 | cron 定时任务管理 |
| `lecture-notes/06-networking-basics.md` | 讲义 | 网络基础（网络配置、防火墙） |
| `lecture-notes/07-ssh-security.md` | 讲义 | SSH 密钥管理与安全加固 |
| `lecture-notes/08-network-troubleshooting.md` | 讲义 | 网络排障方法与实践 |
| `exercises/01-linux-basics.md` | 练习 | Linux 基础操作练习 |
| `exercises/02-shell-basics.md` | 练习 | Shell 脚本基础练习 |
| `exercises/03-shell-advanced.md` | 练习 | Shell 脚本进阶练习 |
| `exercises/04-system-admin.md` | 练习 | 系统管理练习 |
| `exercises/05-networking-basics.md` | 练习 | 网络基础练习 |
| `exercises/06-user-group-permissions.md` | 练习 | 用户与权限管理练习 |
| `exercises/07-process-management.md` | 练习 | 进程管理练习 |
| `exercises/08-mini-project.md` | 练习 | 综合小项目：Linux 服务器初始化脚本 |
| `quizzes/module-002-quiz.md` | 测验 | 模块 002 知识检测测验 |
| `resources/recommended-reading.md` | 资源 | 推荐阅读与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 001 — Python 基础设施编程基础](./mod-001-python-fundamentals.md)（可选前置）
- **后续**: [模块 005 — Docker 容器化技术](./mod-005-docker-containers.md)、[模块 006 — Kubernetes 容器编排入门](./mod-006-kubernetes-intro.md)
