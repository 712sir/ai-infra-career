# 模块 005 — Docker 容器化技术

> **时长**: 15 小时 | **难度**: 入门 | **前置知识**: Linux 命令行操作（模块 002 推荐）

---

## 模块概述

容器化是现代软件部署的事实标准。本模块从 Docker 的核心架构讲起，深入 Dockerfile 的最佳实践、Docker Compose 的多容器编排，以及生产环境中的容器运维知识。你将学会如何将 Python 应用和 ML 模型服务打包成轻量级、可移植、可复现的容器镜像。

---

## 主题分解

### 1. Docker 基础（4小时）

- **容器 vs 虚拟机**: 虚拟化层级的对比（Hypervisor vs Container Runtime），容器的进程级隔离与资源效率优势，容器技术的适用场景与局限性
- **Docker 架构**: Docker Engine 的组件（dockerd / containerd / runc），客户端-服务端通信模型，Docker 的镜像分层存储机制（Union File System / Overlay2）
- **镜像与容器**: docker pull / docker images 镜像管理，docker run / docker ps / docker stop / docker rm 容器生命周期管理，docker exec 进入运行中的容器，docker logs 查看容器日志
- **Docker Hub 与 Registry**: 镜像仓库的概念与分层结构，docker push / docker pull 推送与拉取镜像，镜像标签（tag）的版本管理策略（latest / semver / sha256），私有 Registry 的搭建与使用

### 2. Dockerfile 最佳实践（5小时）

- **分层缓存**: Docker 的 layer 缓存机制原理，指令排序的优化策略——将不常变动的指令放在前面（依赖安装）以最大化缓存利用率，COPY 与 ADD 的差异与选择
- **多阶段构建**: multi-stage build 的语法与用途，将构建环境与运行环境分离以减小镜像体积，builder 阶段与 production 阶段的文件选择性复制（COPY --from=builder）
- **安全考虑**: 以非 root 用户运行容器（USER 指令），最小化基础镜像的选择（alpine vs slim vs distroless），.dockerignore 防止敏感文件泄露，镜像漏洞扫描工具（trivy / docker scout）的使用
- **镜像优化**: 减少镜像层数（合并 RUN 指令），清理包管理器缓存（apt-get clean / rm -rf /var/lib/apt/lists/*），合理设置 ENTRYPOINT 与 CMD 的配合使用（exec form vs shell form），HEALTHCHECK 健康检查指令

### 3. Docker Compose（3小时）

- **服务定义**: docker-compose.yml 文件结构解析，services / networks / volumes 三大顶层元素，服务的构建（build）与直接使用镜像（image）的两种方式
- **网络**: Compose 的默认网络与自定义网络，服务间的 DNS 名称解析（服务名即主机名），网络驱动（bridge / host / overlay）的选择
- **卷与持久化**: named volumes 与 bind mounts 的区别与使用，数据库与状态服务的持久化策略，卷的备份与恢复
- **环境配置**: environment 与 env_file 的环境变量注入，.env 文件与变量替换，多环境配置（development / staging / production）的管理策略，profiles 按需启动服务

### 4. 容器运维（3小时）

- **容器网络模式**: bridge（默认桥接网络）、host（主机网络）、none（无网络）、overlay（跨主机网络）四种模式的特性与使用场景，容器端口映射（-p / --publish）与暴露（--expose）
- **卷管理**: docker volume create / ls / inspect / rm 命令，卷驱动（local / nfs / cloud-storage），容器间数据共享策略
- **资源限制**: CPU 限制（--cpus / --cpu-shares）与内存限制（--memory / --memory-swap），OOM（Out of Memory）的预防与处理，资源监控（docker stats）
- **日志与调试**: Docker 的日志驱动（json-file / syslog / fluentd），docker logs 的查看与过滤，docker inspect 获取容器与镜像的详细元数据，常见容器故障的诊断流程

---

## 学习目标

完成本模块后，你应当能够：

1. 理解容器与虚拟机的差异，以及 Docker 的核心架构
2. 将 Python/ML 应用容器化为可复用的 Docker 镜像
3. 编写高效、安全、体积优化的生产级 Dockerfile
4. 使用 Docker Compose 编排多容器应用（如 API + 数据库 + 缓存）
5. 配置容器的网络、存储卷与资源限制
6. 调试容器化应用中的常见问题

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/01-docker-basics.md` | 讲义 | Docker 基础（容器 vs VM、架构、镜像与容器操作） |
| `lecture-notes/02-dockerfile-best-practices.md` | 讲义 | Dockerfile 最佳实践（缓存、多阶段构建、安全、优化） |
| `lecture-notes/03-dockerfile-advanced.md` | 讲义 | Dockerfile 进阶（ENTRYPOINT vs CMD、HEALTHCHECK、ARG） |
| `lecture-notes/04-docker-compose.md` | 讲义 | Docker Compose（服务定义、网络、卷、环境配置） |
| `lecture-notes/05-container-networking.md` | 讲义 | 容器网络（网络模式、端口映射、DNS 名称解析） |
| `lecture-notes/06-container-operations.md` | 讲义 | 容器运维（卷管理、资源限制、日志与调试） |
| `exercises/01-docker-installation-setup.md` | 练习 | Docker 安装与基本操作练习 |
| `exercises/02-dockerfile-basics.md` | 练习 | Dockerfile 编写练习 |
| `exercises/03-dockerfile-multi-stage.md` | 练习 | 多阶段构建练习 |
| `exercises/04-docker-image-optimization.md` | 练习 | 镜像优化练习 |
| `exercises/05-docker-compose-services.md` | 练习 | Docker Compose 多服务编排练习 |
| `exercises/06-volumes-and-persistence.md` | 练习 | 卷与数据持久化练习 |
| `exercises/07-networking-security.md` | 练习 | 容器网络与安全加固练习 |
| `exercises/08-mini-project.md` | 练习 | 综合项目：容器化 ML 推理服务 |
| `quizzes/module-005-quiz.md` | 测验 | 模块 005 知识检测测验 |
| `resources.md` | 资源 | 推荐阅读、Docker 命令速查表与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 002 — Linux 系统管理基础](./mod-002-linux-essentials.md)、[模块 001 — Python 基础设施编程基础](./mod-001-python-fundamentals.md)
- **后续**: [模块 006 — Kubernetes 容器编排入门](./mod-006-kubernetes-intro.md)
