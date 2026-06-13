# Lessons 学习模块说明

> 本文档描述 `ai-infra-junior-engineer-learning` 项目中 `lessons/` 目录的完整内容与结构，涵盖 10 个学习模块（mod-001 至 mod-010），总学时约 160 小时。

---

## 一、模块总览

| 模块编号 | 模块名称 | 学时 | 难度 | 路径 |
|---------|---------|------|------|------|
| mod-001 | Python Fundamentals（Python 基础） | 15h | Beginner | `lessons/mod-001-python-fundamentals/` |
| mod-002 | Linux Essentials（Linux 基础） | 15h | Beginner | `lessons/mod-002-linux-essentials/` |
| mod-003 | Git Version Control（Git 版本控制） | 10h | Beginner | `lessons/mod-003-git-version-control/` |
| mod-004 | ML Basics（机器学习基础） | 20h | Beginner | `lessons/mod-004-ml-basics/` |
| mod-005 | Docker Containers（Docker 容器） | 15h | Beginner | `lessons/mod-005-docker-containers/` |
| mod-006 | Kubernetes Intro（Kubernetes 入门） | 20h | Beginner+ | `lessons/mod-006-kubernetes-intro/` |
| mod-007 | APIs & Web Services（API 与 Web 服务） | 15h | Beginner | `lessons/mod-007-apis-web-services/` |
| mod-008 | Databases & SQL（数据库与 SQL） | 15h | Beginner | `lessons/mod-008-databases-sql/` |
| mod-009 | Monitoring Basics（监控基础） | 15h | Beginner+ | `lessons/mod-009-monitoring-basics/` |
| mod-010 | Cloud Platforms（云平台） | 20h | Beginner+ | `lessons/mod-010-cloud-platforms/` |

---

## 二、标准模块子目录结构

每个模块（mod-XXX）内部采用统一的标准子目录结构：

```
lessons/mod-XXX-模块名/
├── README.md                 # 模块概述、学习目标、前置要求
├── lecture-notes/            # 课程讲义（Markdown 文档）
│   └── 01-xxx.md
├── exercises/                # 课后练习
│   └── exercise-01-xxx.md
├── quizzes/                  # 测验与考核
│   └── module-XXX-quiz.md
└── resources/                # 补充资源、推荐阅读
    └── resources.md
```

| 子目录 | 说明 |
|--------|------|
| `README.md` | 模块概述文档，包含学习目标、前置知识要求、学时分配、关键概念索引 |
| `lecture-notes/` | 课程讲义，按主题拆分为多个 Markdown 文件，编号递增 |
| `exercises/` | 动手练习，每讲对应 1-2 个练习，注重实操 |
| `quizzes/` | 模块测验，用于检验学习成果，通常为 1 个综合测验文件 |
| `resources/` | 拓展阅读、参考链接、推荐书单等补充材料 |

---

## 三、各模块详细文件清单

### Module 001：Python Fundamentals（Python 基础）

**学时**：15h | **难度**：Beginner

本模块覆盖 Python 开发环境搭建、高级语法特性、DevOps 相关编程、异步编程以及测试与代码质量，为后续 AI Infra 工作打下扎实的 Python 基础。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-python-environment.md` | Python 环境搭建：虚拟环境、包管理、IDE 配置 |
| `02-advanced-python.md` | 高级 Python：类型提示、日志、配置管理 |
| `03-python-devops.md` | Python DevOps：子进程、文件操作、JSON/YAML 解析 |
| `04-async-programming.md` | 异步编程：async/await |
| `05-testing-code-quality.md` | 测试与代码质量：pytest / black / pylint |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-environment-setup.md` | 搭建开发环境 |
| `exercise-02-data-structures.md` | 数据结构操作 |
| `exercise-03-functions-modules.md` | 函数与模块 |
| `exercise-04-file-io.md` | 文件 IO |
| `exercise-05-error-handling.md` | 错误处理 |
| `exercise-06-async-programming.md` | 异步编程 |
| `exercise-07-testing.md` | 编写测试 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `module-001-quiz.md` | 模块 001 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources.md` | 推荐资源与拓展阅读 |

---

### Module 002：Linux Essentials（Linux 基础）

**学时**：15h | **难度**：Beginner

掌握 Linux 命令行操作、文件系统、权限管理、系统管理、Shell 脚本、文本处理和网络基础，是 AI Infra 工程师必备的操作系统技能。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-intro-to-linux.md` | Linux 简介：发行版、命令行基础 |
| `02-file-system-navigation.md` | 文件系统导航：目录结构、路径、常用命令 |
| `03-permissions-security.md` | 权限与安全：用户/组、chmod、sudo |
| `04-system-administration.md` | 系统管理：进程、服务、包管理、定时任务 |
| `05-intro-shell-scripting.md` | Shell 脚本入门：变量、条件、循环 |
| `06-advanced-shell-scripting.md` | 高级 Shell 脚本：函数、调试、错误处理 |
| `07-text-processing.md` | 文本处理：grep、sed、awk、正则表达式 |
| `08-networking-fundamentals.md` | 网络基础：TCP/IP、DNS、curl、ssh |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-navigation.md` | 文件系统导航练习 |
| `exercise-02-permissions.md` | 权限管理练习 |
| `exercise-03-processes.md` | 进程管理练习 |
| `exercise-04-scripting.md` | Shell 脚本编写练习 |
| `exercise-05-package-mgmt.md` | 包管理练习 |
| `exercise-06-logs.md` | 日志查看与分析练习 |
| `exercise-07-troubleshooting.md` | 故障排查练习 |
| `exercise-08-system-automation.md` | 系统自动化练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `module-002-quiz.md` | 模块 002 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources/recommended-reading.md` | 推荐阅读书单 |
| `EXERCISE_TO_LECTURE_MAPPING.md` | 练习与讲义对应关系 |

---

### Module 003：Git Version Control（Git 版本控制）

**学时**：10h | **难度**：Beginner

掌握 Git 的基本操作、分支管理、协作工作流、高级用法，以及与 ML 项目结合的最佳实践。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-git-fundamentals.md` | Git 基础：仓库、暂存区、提交、日志 |
| `02-branching-merging.md` | 分支与合并：创建分支、切换、合并策略 |
| `03-collaboration.md` | 协作：远程仓库、Pull Request、Code Review |
| `04-advanced-git.md` | 高级 Git：rebase、cherry-pick、stash、bisect |
| `05-git-for-ml-projects.md` | ML 项目中的 Git：数据版本控制、模型管理 |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-first-repo.md` | 创建第一个仓库 |
| `exercise-02-commits-history.md` | 提交与历史管理 |
| `exercise-03-branching.md` | 分支操作练习 |
| `exercise-04-merging-conflicts.md` | 合并与冲突解决 |
| `exercise-05-collaboration.md` | 协作工作流模拟 |
| `exercise-06-ml-workflows.md` | ML 项目工作流练习 |
| `exercise-07-advanced.md` | 高级 Git 操作练习 |
| `exercise-08-git-lfs-ml-projects.md` | Git LFS 与 ML 项目管理 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `module-003-quiz.md` | 模块 003 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources.md` | 推荐资源与拓展阅读 |

---

### Module 004：ML Basics（机器学习基础）

**学时**：20h | **难度**：Beginner

机器学习入门，包括 ML 概念概览、PyTorch 基础、TensorFlow 基础、模型格式与转换，为 AI Infra 工作提供必要的 ML 背景知识。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-ml-overview.md` | 机器学习概览：监督/无监督学习、评估指标 |
| `02-pytorch-basics.md` | PyTorch 基础：张量、自动微分、模型定义 |
| `03-tensorflow-basics.md` | TensorFlow 基础：计算图、Keras API |
| `04-model-formats.md` | 模型格式：ONNX、TensorRT、SavedModel 转换 |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-pytorch-inference.md` | PyTorch 推理练习 |
| `exercise-02-tensorflow-inference.md` | TensorFlow 推理练习 |
| `exercise-03-model-conversion.md` | 模型格式转换练习 |
| `exercise-04-llm-basics.md` | 大语言模型基础练习 |
| `exercise-05-gpu-basics.md` | GPU 基础操作练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `quiz-01-ml-basics.md` | 模块 004 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources.md` | 推荐资源与拓展阅读 |

---

### Module 005：Docker Containers（Docker 容器）

**学时**：15h | **难度**：Beginner

系统学习 Docker 容器技术：基础概念、Dockerfile 编写、Docker Compose 编排、网络与存储、最佳实践、高级主题，以及 ML 场景下的容器化应用。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-docker-fundamentals.md` | Docker 基础：镜像、容器、仓库、生命周期 |
| `02-dockerfiles-basics.md` | Dockerfile 编写基础：指令、层缓存、多阶段构建 |
| `03-docker-compose.md` | Docker Compose：多容器应用编排 |
| `04-networking-volumes.md` | 网络与数据卷：bridge/host 网络、卷挂载 |
| `05-best-practices.md` | 最佳实践：镜像优化、安全、日志 |
| `06-advanced-docker-topics.md` | 高级主题：多架构构建、Docker-in-Docker |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-container-operations.md` | 容器基本操作练习 |
| `exercise-02-building-custom-images.md` | 构建自定义镜像练习 |
| `exercise-03-docker-compose.md` | Docker Compose 编排练习 |
| `exercise-04-networking-scenarios.md` | 网络场景练习 |
| `exercise-05-volume-management.md` | 数据卷管理练习 |
| `exercise-06-production-deployment.md` | 生产环境部署练习 |
| `exercise-07-ml-containerization.md` | ML 模型容器化练习 |
| `exercise-08-production-ml-deployment.md` | 生产 ML 部署练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `module-005-quiz.md` | 模块 005 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources.md` | 推荐资源与拓展阅读 |

---

### Module 006：Kubernetes Intro（Kubernetes 入门）

**学时**：20h | **难度**：Beginner+

学习 Kubernetes 核心架构、应用部署、Helm 包管理、运维操作，以及如何在 K8s 上运行 ML 工作负载。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-k8s-architecture.md` | K8s 架构：控制平面、节点、Pod、控制器 |
| `02-deploying-apps.md` | 应用部署：Deployment、Service、ConfigMap |
| `03-helm.md` | Helm 包管理：Chart 结构、模板、Release 管理 |
| `04-k8s-operations.md` | K8s 运维：监控、日志、扩缩容、故障排查 |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-first-deployment.md` | 首次部署练习 |
| `exercise-02-helm-chart.md` | Helm Chart 编写练习 |
| `exercise-03-debugging.md` | 调试与故障排查练习 |
| `exercise-04-statefulsets-storage.md` | StatefulSet 与存储练习 |
| `exercise-05-configmaps-secrets.md` | ConfigMap 与 Secret 管理练习 |
| `exercise-06-ingress-load-balancing.md` | Ingress 与负载均衡练习 |
| `exercise-07-ml-workloads.md` | ML 工作负载部署练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `module-006-quiz.md` | 模块 006 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources/recommended-reading.md` | 推荐阅读书单 |

---

### Module 007：APIs & Web Services（API 与 Web 服务）

**学时**：15h | **难度**：Beginner

学习 REST API 设计原则、FastAPI 和 Flask 框架、认证与安全、高级 API 模式，以及 ML 模型服务化实践。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-api-fundamentals-rest.md` | API 基础与 REST 设计原则 |
| `02-fastapi-framework.md` | FastAPI 框架：路由、验证、自动文档 |
| `03-authentication-security.md` | 认证与安全：JWT、OAuth2、CORS |
| `04-advanced-api-patterns.md` | 高级 API 模式：限流、分页、版本控制 |
| `05-flask-framework.md` | Flask 框架：路由、蓝图、扩展生态 |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-basic-rest-api.md` | 构建基础 REST API |
| `exercise-02-model-serving-api.md` | ML 模型服务 API 练习 |
| `exercise-03-rate-limiting-cors.md` | 限流与 CORS 配置练习 |
| `exercise-04-background-tasks-async.md` | 后台任务与异步处理练习 |
| `exercise-05-api-documentation.md` | API 文档生成练习 |
| `exercise-06-production-ml-api.md` | 生产级 ML API 部署练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `quiz-01-apis-web-services.md` | 模块 007 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources.md` | 推荐资源与拓展阅读 |

---

### Module 008：Databases & SQL（数据库与 SQL）

**学时**：15h | **难度**：Beginner

学习关系型数据库基础、SQL 查询、数据库设计与规范化、ORM 集成、数据库扩展及 NoSQL 入门，为 AI Infra 中的数据管理打下基础。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `01-database-fundamentals-sql-basics.md` | 数据库基础与 SQL 入门：CRUD、过滤、排序 |
| `02-database-design-normalization.md` | 数据库设计与规范化：ER 图、范式、键 |
| `03-advanced-sql-query-optimization.md` | 高级 SQL 与查询优化：JOIN、索引、执行计划 |
| `04-orms-database-integration.md` | ORM 与数据库集成：SQLAlchemy、迁移 |
| `05-database-scaling-ml-workloads.md` | 数据库扩展与 ML 工作负载：读写分离、分片 |
| `06-nosql-basics.md` | NoSQL 基础：MongoDB、Redis、适用场景 |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-sql-basics-crud.md` | SQL 基础 CRUD 练习 |
| `exercise-02-database-design-ml-registry.md` | 数据库设计：ML 模型注册表 |
| `exercise-03-advanced-sql-joins.md` | 高级 SQL：JOIN 操作练习 |
| `exercise-04-sqlalchemy-orm-integration.md` | SQLAlchemy ORM 集成练习 |
| `exercise-05-optimization-indexing.md` | 查询优化与索引练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `quiz-01-databases-sql.md` | 模块 008 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources.md` | 推荐资源与拓展阅读 |

---

### Module 009：Monitoring Basics（监控基础）

**学时**：15h | **难度**：Beginner+

学习可观测性三大支柱（Metrics / Logs / Traces）、Prometheus 指标采集、Grafana 可视化、日志管道、告警与 ML 监控。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `lecture-01-observability-fundamentals.md` | 可观测性基础：Metrics、Logs、Traces 概念 |
| `lecture-02-prometheus-metrics-pipeline.md` | Prometheus 指标管道：数据模型、PromQL、采集 |
| `lecture-03-grafana-dashboards-visualization.md` | Grafana 仪表盘与可视化：面板、变量、告警 |
| `lecture-04-logging-alerting-ml-monitoring.md` | 日志、告警与 ML 监控：ELK、Alertmanager、模型漂移 |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-observability-foundations-lab.md` | 可观测性基础实验 |
| `exercise-02-prometheus-stack.md` | Prometheus 技术栈搭建练习 |
| `exercise-03-grafana-dashboards.md` | Grafana 仪表盘构建练习 |
| `exercise-04-logging-pipeline.md` | 日志管道搭建练习 |
| `exercise-05-alerting-incident-response.md` | 告警与事件响应练习 |
| `exercise-06-airflow-workflow-monitoring.md` | Airflow 工作流监控练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `quiz-01-monitoring-observability.md` | 模块 009 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources/module-009-resource-pack.md` | 模块 009 资源包 |

---

### Module 010：Cloud Platforms（云平台）

**学时**：20h | **难度**：Beginner+

学习云计算基础概念、AWS 核心服务、网络与安全、ML 工作负载部署、多云与成本优化、Terraform 基础设施即代码。

#### lecture-notes/

| 文件名 | 中文说明 |
|--------|---------|
| `lecture-01-cloud-fundamentals.md` | 云计算基础：IaaS/PaaS/SaaS、区域、计费模型 |
| `lecture-02-aws-core-services.md` | AWS 核心服务：EC2、S3、Lambda、IAM |
| `lecture-03-networking-security.md` | 网络与安全：VPC、安全组、私有链接 |
| `lecture-04-deployment-ml-workloads.md` | ML 工作负载部署：SageMaker、EKS、Batch |
| `lecture-05-multicloud-cost-optimization.md` | 多云策略与成本优化：预留实例、Spot、FinOps |

#### exercises/

| 文件名 | 中文说明 |
|--------|---------|
| `exercise-01-aws-account-iam.md` | AWS 账户与 IAM 配置练习 |
| `exercise-02-compute-storage.md` | 计算与存储服务练习 |
| `exercise-03-networking-security.md` | 网络与安全配置练习 |
| `exercise-04-containerized-deployment.md` | 容器化部署练习（ECS/EKS） |
| `exercise-05-sagemaker-cost-optimization.md` | SageMaker 与成本优化练习 |
| `exercise-06-ml-infrastructure-aws.md` | AWS ML 基础设施搭建练习 |
| `exercise-07-terraform-basics.md` | Terraform 基础设施即代码入门练习 |

#### quizzes/

| 文件名 | 中文说明 |
|--------|---------|
| `quiz-01-cloud-platforms.md` | 模块 010 综合测验 |

#### resources/

| 文件名 | 中文说明 |
|--------|---------|
| `resources.md` | 推荐资源与拓展阅读 |

---

## 四、学习路径推荐

建议按照以下五个阶段循序渐进地完成所有模块：

```
Phase 1（基础工具链）       Phase 2（ML 与容器）       Phase 3（容器编排）
┌─────────────────┐       ┌─────────────────┐       ┌─────────────────┐
│ mod-001 Python   │       │ mod-004 ML      │       │                 │
│ mod-002 Linux    │ ────> │     Basics      │ ────> │ mod-006 K8s     │
│ mod-003 Git      │       │ mod-005 Docker  │       │                 │
└─────────────────┘       └─────────────────┘       └─────────────────┘
   ~40h / 约 2.5 周          ~35h / 约 2 周            ~20h / 约 1.5 周

       │                          │                          │
       └──────────────────────────┴──────────────────────────┘
                                  │
                                  ▼
       ┌─────────────────────────────────────────────────────┐
       │ Phase 4（服务与运维）                                  │
       │                                                     │
       │ mod-007 APIs & Web Services                         │
       │ mod-008 Databases & SQL                             │
       │ mod-009 Monitoring Basics                           │
       │ mod-010 Cloud Platforms                             │
       └─────────────────────────────────────────────────────┘
          ~65h / 约 4 周
                                  │
                                  ▼
       ┌─────────────────────────────────────────────────────┐
       │ Phase 5（综合实战）                                    │
       │                                                     │
       │ 综合项目：端到端 ML Infra 平台搭建                     │
       └─────────────────────────────────────────────────────┘
          ~40h / 约 2.5 周
```

### 各阶段说明

| 阶段 | 包含模块 | 核心目标 |
|------|---------|---------|
| **Phase 1：基础工具链** | mod-001 Python, mod-002 Linux, mod-003 Git | 建立 AI Infra 工程师的编程、操作系统和版本控制基本功 |
| **Phase 2：ML 与容器** | mod-004 ML Basics, mod-005 Docker | 理解 ML 基本概念与模型格式，掌握容器化技术 |
| **Phase 3：容器编排** | mod-006 Kubernetes Intro | 学习 K8s 核心概念与 ML 工作负载编排 |
| **Phase 4：服务与运维** | mod-007 ~ mod-010 | 全面掌握 API 开发、数据库、监控与云平台四大服务化技能 |
| **Phase 5：综合实战** | 综合项目 | 将前四阶段知识融会贯通，完成端到端 ML 基础设施平台搭建 |

### 学习建议

1. **严格按顺序推进**：Phase 1 是后续所有模块的基石，务必扎实掌握。
2. **动手优先**：每个模块的 exercises 是学习重点，建议 lecture 和 exercise 时间配比为 4:6。
3. **测验检验**：每个模块结束后完成 quizzes，确保关键概念掌握到位。
4. **及时回顾**：跨模块内容存在依赖关系（如 Docker 依赖 Linux，K8s 依赖 Docker），遇到问题及时回顾前置模块。

---

> 文档版本：v1.0 | 最后更新：2026-06-13
