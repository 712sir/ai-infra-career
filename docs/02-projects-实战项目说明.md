# 02 — 实战项目说明

本文档详细描述 ai-infra-junior-engineer-learning 仓库中 `projects/` 目录下的全部 5 个实战项目，涵盖项目概述、文件结构、学习目标和前置依赖。

---

## 项目概览总表

| 项目编号 | 项目名称 | 预估学时 | 难度 | 核心主题 |
|---------|---------|---------|------|---------|
| 01 | Simple Model API Deployment | 60h | 入门 | 模型 API 部署、Docker 容器化 |
| 02 | Kubernetes Model Serving | 80h | 中级 | K8s 编排、Helm 打包、负载测试 |
| 03 | ML Pipeline with Experiment Tracking | 100h | 中级 | ML 流水线、实验追踪、数据验证 |
| 04 | Monitoring & Alerting System | 80h | 中级 | 可观测性、告警体系、Runbook 运维 |
| 05 | Production ML Capstone | 120h | 高级 | 全栈生产化、CI/CD、IaC、灾备 |

---

## Project 01: Simple Model API Deployment（60h, Beginner）

**路径：** `projects/project-01-simple-model-api/`

**项目简介：** 本项目引导学员将一个已训练好的机器学习模型封装为 RESTful API，并通过 Docker 容器化部署。学员将掌握模型服务化的完整流程，包括 API 设计、模型加载与缓存、配置管理和自动化测试。

### 文件清单

| 文件路径 | 说明 |
|---------|------|
| `README.md` | 项目指南与总览 |
| `requirements.md` | 需求规格说明书（含功能需求、非功能需求、验收标准） |
| `architecture.md` | 架构设计文档（系统组件、数据流、部署拓扑） |
| `.env.example` | 环境变量配置模板 |
| `docker/Dockerfile` | 多阶段 Docker 镜像构建文件 |
| `docker/docker-compose.yml` | Docker Compose 编排（API + 数据库） |
| `src/README.md` | 源代码结构说明 |
| `src/app.py` | 主应用入口（Flask/FastAPI 路由、请求处理、中间件） |
| `src/config.py` | 配置管理模块（支持环境变量、YAML、多环境） |
| `src/model_loader.py` | 模型加载与缓存模块（支持 PyTorch/TensorFlow） |
| `tests/test_app.py` | API 端点功能测试（pytest） |
| `tests/test_model.py` | 模型推理正确性测试 |

### 学习目标

- 使用 Flask 或 FastAPI 构建模型推理 RESTful API
- 掌握多阶段 Docker 镜像构建与优化
- 使用 Docker Compose 编排多服务应用
- 编写 pytest 单元测试与集成测试
- 理解配置管理最佳实践（环境变量、YAML、多环境）

---

## Project 02: Kubernetes Model Serving（80h, Intermediate）

**路径：** `projects/project-02-kubernetes-serving/`

**项目简介：** 在 Project 01 的基础上，将模型服务迁移至 Kubernetes 集群。学员将学习原生 K8s 资源清单编写、Helm Chart 打包、Grafana 监控仪表盘配置，以及使用 Locust 进行系统化负载测试。

### 文件清单

| 文件路径 | 说明 |
|---------|------|
| `README.md` | 项目指南与总览 |
| `requirements.md` | 需求规格说明书 |
| `architecture.md` | 架构设计文档 |
| `.env.example` | 环境变量配置模板 |
| `src/app.py` | 模型服务 API 主程序 |
| `kubernetes/deployment.yaml` | K8s Deployment 清单（教学用原始 YAML） |
| `kubernetes/service.yaml` | K8s Service 清单（ClusterIP/LoadBalancer） |
| `kubernetes/configmap.yaml` | K8s ConfigMap（应用配置与模型路径） |
| `kubernetes/hpa.yaml` | HorizontalPodAutoscaler（CPU/内存自动扩缩） |
| `kubernetes/ingress.yaml` | Ingress 入口流量路由规则 |
| `kubernetes/secrets.yaml.example` | Secret 配置模板（API密钥/数据库密码） |
| `helm/model-api/Chart.yaml` | Helm Chart 元数据定义 |
| `helm/model-api/values.yaml` | Helm 默认配置值（副本数、资源限制、镜像） |
| `helm/model-api/README.md` | Helm Chart 使用文档 |
| `helm/model-api/templates/_helpers.tpl` | Helm 模板辅助函数 |
| `helm/model-api/templates/deployment.yaml` | Helm Deployment 模板 |
| `helm/model-api/templates/service.yaml` | Helm Service 模板 |
| `helm/model-api/templates/configmap.yaml` | Helm ConfigMap 模板 |
| `helm/model-api/templates/hpa.yaml` | Helm HPA 模板 |
| `helm/model-api/templates/ingress.yaml` | Helm Ingress 模板 |
| `helm/model-api/templates/serviceaccount.yaml` | Helm ServiceAccount 模板 |
| `helm/model-api/templates/servicemonitor.yaml` | Helm ServiceMonitor（Prometheus Operator 集成） |
| `grafana/model-api-dashboard.json` | Grafana 模型 API 监控仪表盘 JSON 模型 |
| `monitoring/servicemonitor.yaml` | Prometheus ServiceMonitor 独立配置 |
| `loadtest/locustfile.py` | Locust 负载测试脚本（冒烟/爬坡/浸泡/尖峰四场景） |
| `loadtest/README.md` | 负载测试执行说明与验收标准 |
| `tests/test_k8s.py` | K8s 部署集成测试 |

### 学习目标

- 编写 Kubernetes 原生 YAML 清单（Deployment、Service、ConfigMap、HPA、Ingress）
- 使用 Helm 模板化 K8s 资源并管理 Chart 版本
- 配置 Prometheus ServiceMonitor 与 Grafana 仪表盘
- 使用 Locust 执行冒烟测试、爬坡测试、浸泡测试和尖峰测试
- 理解自动扩缩容（HPA）的配置与调优

---

## Project 03: ML Pipeline with Experiment Tracking（100h, Intermediate）

**路径：** `projects/project-03-ml-pipeline-tracking/`

**项目简介：** 本项目构建完整的机器学习训练流水线，集成 Airflow 任务调度、MLflow 实验追踪和 DVC 数据版本控制。学员将实现数据摄取、预处理、验证、训练到评估的 5 阶段 ML 流水线，并配置自动重训练与模型晋级门控。

### 文件清单

| 文件路径 | 说明 |
|---------|------|
| `README.md` | 项目指南与总览 |
| `requirements.md` | 需求规格说明书 |
| `architecture.md` | 架构设计文档 |
| `.env.example` | 环境变量配置模板 |
| `docker-compose.yml` | 完整 ML 平台编排（MLflow/Airflow/PostgreSQL/MinIO） |
| `dags/ml_pipeline_dag.py` | Airflow ML 训练流水线 DAG（5 阶段：摄取→预处理→验证→训练→评估） |
| `dags/retraining_dag.py` | Airflow 自动重训练 DAG（周调度+漂移检测+MLflow 晋级门控） |
| `dvc/dvc.yaml` | DVC 5 阶段流水线定义（ingest→preprocess→validate→train→evaluate） |
| `dvc/params.yaml` | DVC 参数管理（训练超参、数据版本、模型配置） |
| `dvc/.dvcignore` | DVC 跟踪忽略规则 |
| `dvc/.gitignore` | DVC 目录 Git 忽略规则 |
| `mlflow/MLproject` | MLflow 项目定义（conda 环境、入口点、参数） |
| `great_expectations/great_expectations.yml` | GE 全局配置（数据源、存储后端） |
| `great_expectations/expectations/training_data_suite.json` | 13 条数据验证期望规则 |
| `great_expectations/README.md` | GE 数据验证使用说明 |
| `src/data_ingestion.py` | 数据摄取模块（支持 S3/GCS/本地多数据源） |
| `src/preprocessing.py` | 数据预处理模块（特征工程、数据清洗、标准化） |
| `src/training.py` | 模型训练模块（支持 PyTorch/TensorFlow/sklearn） |
| `src/evaluation.py` | 模型评估模块（准确率/F1/AUC、混淆矩阵、漂移分析） |
| `tests/test_pipeline.py` | 流水线集成测试 |

### 学习目标

- 使用 Airflow 构建 5 阶段 ML 训练 DAG
- 配置 MLflow 进行实验追踪、模型注册与晋级门控
- 使用 DVC 管理数据版本与流水线可复现性
- 使用 Great Expectations 定义 13 条数据质量验证规则
- 实现自动重训练流水线（周调度 + 漂移检测）

---

## Project 04: Monitoring & Alerting System（80h, Intermediate）

**路径：** `projects/project-04-monitoring-alerting/`

**项目简介：** 本项目构建全面的 ML 系统可观测性平台。学员将搭建 Prometheus + Grafana + ELK + Alertmanager 监控体系，编写告警规则与 Runbook 运维手册，并集成 OpenTelemetry 应用埋点，实现端到端的 ML 服务监控。

### 文件清单

| 文件路径 | 说明 |
|---------|------|
| `README.md` | 项目指南与总览 |
| `requirements.md` | 需求规格说明书 |
| `architecture.md` | 架构设计文档 |
| `.env.example` | 环境变量配置模板 |
| `docker-compose.yml` | 监控平台编排（Prometheus/Grafana/ELK/Alertmanager） |
| `prometheus/prometheus.yml` | Prometheus 主配置（scrape targets、rule files） |
| `prometheus/alerts.yml` | Prometheus 告警规则（高错误率/延迟/漂移/资源） |
| `alertmanager/alertmanager.yml` | Alertmanager 配置（路由树、Slack/PagerDuty 接收器） |
| `alertmanager/templates.tmpl` | Alertmanager 通知消息模板 |
| `grafana/datasources.yml` | Grafana 数据源配置（Prometheus/Elasticsearch） |
| `grafana/dashboards/ml-overview.json` | ML 系统概览仪表盘（QPS/延迟/错误率/资源） |
| `grafana/dashboards/ml-drift.json` | ML 特征漂移监控仪表盘 |
| `grafana/dashboards/sli-slo.json` | SLI/SLO 错误预算追踪仪表盘 |
| `elasticsearch/logstash.conf` | Logstash 日志采集管道配置 |
| `elasticsearch/kibana-dashboard.ndjson` | Kibana 日志分析仪表盘 |
| `runbooks/README.md` | Runbook 目录说明与使用方法 |
| `runbooks/high-error-rate.md` | Runbook：高错误率处理流程 |
| `runbooks/log-ingestion-lag.md` | Runbook：日志摄取延迟处理流程 |
| `runbooks/model-drift.md` | Runbook：模型漂移检测与回滚流程 |
| `runbooks/slow-response.md` | Runbook：响应缓慢排查流程 |
| `runbooks/target-down.md` | Runbook：服务下线应急流程 |
| `src/custom_metrics.py` | 自定义 Prometheus 指标导出器 |
| `src/instrumentation.py` | 应用埋点（OpenTelemetry 集成） |
| `tests/test_metrics.py` | 指标采集与告警测试 |

### 学习目标

- 搭建 Prometheus + Grafana + Alertmanager 监控告警体系
- 编写 Prometheus 告警规则（高错误率、延迟、漂移、资源）
- 配置 Alertmanager 路由树与多通道通知（Slack/PagerDuty）
- 构建 ML 专属仪表盘（系统概览、特征漂移、SLI/SLO 错误预算）
- 编写结构化 Runbook 运维手册（5 类常见故障处理流程）
- 集成 OpenTelemetry 实现应用级可观测性埋点

---

## Project 05: Production ML Capstone（120h, Advanced）

**路径：** `projects/project-05-production-ml-capstone/`

**项目简介：** 这是整个学习路径的综合顶点项目。学员需要将前四个项目积累的技能整合为一个完整的生产级 ML 系统，涵盖 CI/CD 流水线、Kustomize 多环境管理、Terraform 基础设施即代码、TLS 证书管理、密钥管理、SLO 定义和灾难恢复计划。

### 文件清单

#### 应用与 CI/CD

| 文件路径 | 说明 |
|---------|------|
| `README.md` | 项目指南与总览 |
| `requirements.md` | 需求规格说明书 |
| `architecture.md` | 架构设计文档 |
| `.env.example` | 环境变量配置模板 |
| `src/main.py` | 综合 ML 系统主入口（API + 流水线 + 监控） |
| `cicd/.github/workflows/ci.yml` | GitHub Actions CI（lint/test/build/scan） |
| `cicd/.github/workflows/cd.yml` | GitHub Actions CD（deploy to dev→staging→prod） |

#### Kubernetes 多环境管理（Kustomize）

| 文件路径 | 说明 |
|---------|------|
| `kubernetes/base/kustomization.yaml` | Kustomize 基础层（通用资源配置） |
| `kubernetes/overlays/dev/kustomization.yaml` | Kustomize 开发环境覆盖 |
| `kubernetes/overlays/staging/kustomization.yaml` | Kustomize 预发布环境覆盖 |
| `kubernetes/overlays/production/kustomization.yaml` | Kustomize 生产环境覆盖 |

#### 基础设施即代码（Terraform）

| 文件路径 | 说明 |
|---------|------|
| `terraform/modules/vpc/main.tf` | VPC 网络基础设施模块 |
| `terraform/modules/vpc/variables.tf` | VPC 模块输入变量 |
| `terraform/modules/vpc/outputs.tf` | VPC 模块输出 |
| `terraform/modules/eks/main.tf` | EKS K8s 集群模块 |
| `terraform/modules/eks/variables.tf` | EKS 模块输入变量 |
| `terraform/modules/eks/outputs.tf` | EKS 模块输出 |
| `terraform/modules/rds/main.tf` | RDS 托管数据库模块 |
| `terraform/modules/rds/variables.tf` | RDS 模块输入变量 |
| `terraform/modules/rds/outputs.tf` | RDS 模块输出 |
| `terraform/modules/iam/main.tf` | IAM 权限管理模块 |
| `terraform/modules/iam/variables.tf` | IAM 模块输入变量 |
| `terraform/modules/iam/outputs.tf` | IAM 模块输出 |
| `terraform/environments/dev/main.tf` | 开发环境 Terraform 入口 |
| `terraform/environments/dev/variables.tf` | 开发环境变量 |
| `terraform/environments/staging/main.tf` | 预发布环境 Terraform 入口 |
| `terraform/environments/staging/variables.tf` | 预发布环境变量 |
| `terraform/environments/prod/main.tf` | 生产环境 Terraform 入口 |
| `terraform/environments/prod/variables.tf` | 生产环境变量 |
| `terraform/environments/prod/outputs.tf` | 生产环境输出 |
| `terraform/README.md` | Terraform IaC 使用说明 |

#### 安全与 SLO

| 文件路径 | 说明 |
|---------|------|
| `security/cert-manager.yaml` | cert-manager TLS 证书自动化管理 |
| `security/vault-config.yaml` | HashiCorp Vault 密钥管理配置 |
| `monitoring/slos.yaml` | SLO 服务水平目标定义（可用性/延迟/准确性） |

#### 灾备与文档

| 文件路径 | 说明 |
|---------|------|
| `velero/values.yaml` | Velero 集群备份 Helm Values（每日全量+每小时增量+季度恢复演练） |
| `velero/README.md` | Velero 备份与灾难恢复说明 |
| `docs/DEPLOYMENT.md` | 完整部署指南 |
| `docs/DISASTER_RECOVERY.md` | 灾难恢复计划 |
| `tests/integration/test_e2e.py` | 端到端集成测试 |

### 学习目标

- 设计并实现 GitHub Actions CI/CD 流水线（lint → test → build → scan → deploy）
- 使用 Kustomize 实现多环境（dev/staging/production）配置管理
- 使用 Terraform 编写模块化基础设施即代码（VPC、EKS、RDS、IAM）
- 配置 cert-manager 自动化 TLS 证书管理与 HashiCorp Vault 密钥管理
- 定义并监控 SLO 服务水平目标（可用性、延迟、准确性）
- 制定 Velero 集群备份策略与灾难恢复计划

---

## 项目依赖关系图

各项目之间存在严格的递进依赖关系，建议按顺序完成。下图展示了项目间的先修关系以及对应的模块学习前提。

```
Module 001-005 (基础模块)
       │
       ▼
┌─────────────────────────────────┐
│  Project 01                      │
│  Simple Model API Deployment     │
│  (60h, Beginner)                 │
│  独立启动，无项目前置依赖          │
└──────────────┬──────────────────┘
               │
               │  + Module 006
               ▼
┌─────────────────────────────────┐
│  Project 02                      │
│  Kubernetes Model Serving        │
│  (80h, Intermediate)             │
│  前置：Project 01 + Module 006   │
└──────────────┬──────────────────┘
               │
               │  + Modules 007-008
               ▼
┌─────────────────────────────────┐
│  Project 03                      │
│  ML Pipeline with                │
│  Experiment Tracking             │
│  (100h, Intermediate)            │
│  前置：Projects 01-02            │
│       + Modules 007-008          │
└──────────────┬──────────────────┘
               │
               │  + Module 009
               ▼
┌─────────────────────────────────┐
│  Project 04                      │
│  Monitoring & Alerting System    │
│  (80h, Intermediate)             │
│  前置：Projects 01-03            │
│       + Module 009               │
└──────────────┬──────────────────┘
               │
               │  + Module 010
               ▼
┌─────────────────────────────────┐
│  Project 05                      │
│  Production ML Capstone          │
│  (120h, Advanced)                │
│  前置：Projects 01-04            │
│       + Module 010               │
└─────────────────────────────────┘
```

### 依赖关系总结

| 项目 | 前置项目 | 前置模块 | 说明 |
|------|---------|---------|------|
| Project 01 | 无 | Modules 001-005 | 独立启动，基础 API 与容器化 |
| Project 02 | Project 01 | Module 006 | 需要已掌握 API 开发与 Docker，引入 K8s 编排 |
| Project 03 | Projects 01-02 | Modules 007-008 | 需要已掌握容器化与 K8s，引入 ML 流水线与实验管理 |
| Project 04 | Projects 01-03 | Module 009 | 需要已有可监控的 ML 服务，引入可观测性体系 |
| Project 05 | Projects 01-04 | Module 010 | 综合前述所有技能，引入 CI/CD、IaC 与灾备 |

### 学习路径建议

1. **初学者路径（约 440 小时）：** 按 Project 01 → 02 → 03 → 04 → 05 顺序完成全部项目
2. **加速路径（约 320 小时）：** 如有 Docker/K8s 经验，Project 01 可压缩至 30h、Project 02 至 50h
3. **聚焦路径：** 仅需模型部署能力则完成 Project 01-02（140h）；仅需 ML 流水线则完成 Project 01 + 03（160h）；仅需运维监控则完成 Project 01 + 02 + 04（220h）

---

*本文档为 ai-infra-junior-engineer-learning 学习仓库的实战项目说明部分，建议配合 `00-项目总览说明.md` 和模块学习文档共同使用。*
