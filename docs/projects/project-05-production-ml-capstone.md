# 项目 05 — 生产级 ML 系统综合项目

**时长:** 120 小时  
**难度:** 中级+

---

## 项目概述

这是整个学习路径的综合顶点项目（Capstone）。你需要将前四个项目中构建的所有能力整合为一个完整的生产级 ML 系统。不同于之前的单个专项项目，本项目要求你从零开始设计、部署和运维一个企业级的 ML 基础设施——涵盖 CI/CD 自动化流水线、基础设施即代码（Terraform IaC）、安全加固（TLS 证书管理与密钥管理）、多环境 Kubernetes 部署（dev/staging/production）、集群备份与灾难恢复，以及服务质量目标（SLO）的全方位监控。

完成本项目后，你将具备独立设计和运维生产级 ML 平台的能力，能够应对真实企业环境中的复杂需求——从代码提交到模型上线的全自动化，从单集群到多环境多区域的高可用架构。

---

## 前置条件

- 所有前置模块（模块 001-009）已完成
- 项目 01：简单模型 API 部署（已完成）
- 项目 02：Kubernetes 模型服务（已完成）
- 项目 03：ML 流水线与实验追踪（已完成）
- 项目 04：监控告警系统（已完成）

---

## 核心交付物

1. **端到端 ML 系统架构** — 从前端请求到模型推理的完整技术架构，包含 CI/CD 流水线、多环境 K8s 集群、监控告警、安全层和灾备方案的顶层设计
2. **GitHub Actions CI/CD 流水线** — `.github/workflows/ci.yml`（构建 → 单元测试 → 代码检查 → 镜像构建推送）和 `cd.yml`（部署到 dev/staging/production 三环境，含审批关卡和回滚能力）
3. **Terraform 基础设施即代码** — 4 个可复用模块（VPC 网络、EKS 集群、RDS 数据库、IAM 权限），支持 3 个独立环境（dev/staging/prod）的差异化配置，`terraform plan/apply` 一键创建或更新全部云资源
4. **安全实现** — `cert-manager` 自动管理 TLS 证书（Let's Encrypt 自动签发与续期）、HashiCorp Vault 集中管理数据库密码和 API 密钥等敏感信息（静态加密 + 动态凭据）
5. **Kustomize 多环境 K8s 部署** — base 目录定义公共资源，overlays/dev、overlays/staging、overlays/production 按环境覆盖（副本数、资源限制、域名、TLS 配置），`kustomize build` 生成最终清单
6. **Velero 集群备份与灾难恢复** — 定期备份 K8s 资源（所有命名空间或指定标签）和持久卷数据到 S3 兼容存储，含备份调度、保留策略和一键恢复流程
7. **SLO 定义与监控** — 定义核心服务的 SLI/SLO（可用性 >= 99.9%、P95 延迟 < 200ms），集成 Grafana 仪表盘监控 SLO 合规状态和错误预算
8. **完整文档** — 部署指南（从零到生产环境完整可用）、灾难恢复计划（RTO/RPO 目标、恢复步骤、演练计划）、架构决策记录（ADR）

---

## 技术栈

| 类别 | 技术 |
|------|------|
| CI/CD | GitHub Actions |
| 基础设施即代码 | Terraform（HashiCorp Configuration Language） |
| 容器编排 | Kubernetes (EKS/GKE/AKS) |
| K8s 配置管理 | Kustomize（多环境覆盖） |
| TLS 证书 | cert-manager + Let's Encrypt |
| 密钥管理 | HashiCorp Vault（静态加密 + 动态数据库凭据） |
| 备份与灾备 | Velero（备份到 S3） |
| 所有前置技术 | Flask/FastAPI, Docker, Helm, Airflow, MLflow, DVC, Great Expectations, Prometheus, Grafana, ELK, Alertmanager |

---

## 评分标准（100 分）

| 评分项 | 分值 | 说明 |
|--------|------|------|
| 系统集成 | 30 分 | 各子系统（ML 流水线、模型服务、监控、告警、日志）成功集成且协同工作；端到端流程可从代码提交自动走到生产部署；多环境隔离正确 |
| CI/CD | 20 分 | CI 流水线包含完整的构建-测试-镜像推送流程；CD 流水线实现多环境渐进式部署（dev → staging → production）；有审批机制和自动回滚能力 |
| 安全性 | 20 分 | cert-manager 自动管理 TLS 证书且未过期；Vault 正确注入密钥到 Pod；网络策略限制东西向流量；RBAC 最小权限原则；Secret 不存储在 Git 中 |
| 文档 | 20 分 | 部署指南步骤完整且可复现；灾难恢复计划含明确的 RTO/RPO 和操作步骤；架构文档含系统上下文图和组件交互图；ADR 记录关键决策及理由 |
| 展示 | 10 分 | 能够演示从 Git Push 到生产部署的完整流程；可展示灾难恢复流程（模拟故障后恢复）；可解释架构设计决策的理由 |

---

## 文件清单

```
project-05-production-ml-capstone/
├── README.md                       # 项目总览：系统架构全图、各子系统说明、环境要求、快速开始（含架构决策摘要）
├── requirements.md                 # 需求规格说明书：系统整体需求、各子系统集成需求、安全需求、SLO 定义、灾备需求
├── architecture.md                 # 架构设计文档：系统上下文图（C4 Level 1/2）、容器图、部署拓扑图、网络架构、数据流、ADR（3+ 条关键决策）
├── .env.example                    # 环境变量模板：GitHub Actions Secrets 清单、Terraform 变量模板、Vault 初始化参数、证书相关配置
├── src/
│   └── main.py                     # 系统主入口：统一的 FastAPI 应用，集成模型预测、健康检查、指标暴露、日志中间件
├── cicd/
│   └── .github/
│       └── workflows/
│           ├── ci.yml              # CI 流水线：代码检出 → Python 环境设置 → 依赖安装 → 代码格式检查（black/flake8）→ 单元测试（pytest + 覆盖率）→ 安全扫描（bandit/trivy）→ Docker 镜像构建 → 推送镜像到 ECR/GCR/ACR
│           └── cd.yml              # CD 流水线：触发条件（push to main/按标签）→ 部署到 dev（自动）→ 集成测试 → 部署到 staging（自动）→ 冒烟测试 → 部署到 production（需审批）→ 部署后监控（等待 N 分钟验证指标正常）→ 失败自动回滚
├── kubernetes/
│   ├── base/                       # Kustomize Base：所有环境共享的 K8s 资源定义
│   │   ├── kustomization.yaml      # Base kustomization：声明公共资源（deployment、service、configmap、hpa）和公共标签
│   │   ├── deployment.yaml         # Deployment 基础定义（不含环境特定副本数和资源）
│   │   ├── service.yaml            # Service 基础定义
│   │   ├── configmap.yaml          # ConfigMap 基础定义（环境无关配置）
│   │   └── hpa.yaml                # HPA 基础定义（扩缩容逻辑，具体值由 overlay 覆盖）
│   └── overlays/
│       ├── dev/                    # 开发环境 Overlay
│       │   ├── kustomization.yaml  # Dev overlay：引用 base、设置命名空间、应用 patches、配置镜像 tag
│       │   ├── replica_count.yaml  # 副本数补丁（dev: 1 副本）
│       │   └── resource_limits.yaml # 资源限制补丁（dev: 低配置 256Mi/0.25CPU）
│       ├── staging/                # 预发布环境 Overlay
│       │   ├── kustomization.yaml  # Staging overlay：引用 base、模拟生产配置
│       │   ├── replica_count.yaml  # 副本数补丁（staging: 2 副本）
│       │   └── resource_limits.yaml # 资源限制补丁（staging: 中配置 512Mi/0.5CPU）
│       └── production/             # 生产环境 Overlay
│           ├── kustomization.yaml  # Production overlay：引用 base、生产级配置
│           ├── replica_count.yaml  # 副本数补丁（prod: 3+ 副本，多 AZ 分布）
│           └── resource_limits.yaml # 资源限制补丁（prod: 高配置 2Gi/2CPU）
├── terraform/
│   ├── README.md                   # Terraform 使用指南：前置条件（AWS CLI/GCP SDK 配置）、模块说明、初始化/计划/应用命令、状态管理（远程 backend 配置）、变量说明表
│   ├── modules/
│   │   ├── vpc/                    # VPC 网络模块
│   │   │   ├── main.tf             # VPC、子网（公有/私有）、NAT 网关、Internet 网关、路由表
│   │   │   ├── variables.tf        # 输入变量：CIDR 块、可用区列表、子网划分参数、标签
│   │   │   └── outputs.tf          # 输出：VPC ID、子网 ID 列表、NAT 网关 IP
│   │   ├── eks/                    # EKS 集群模块
│   │   │   ├── main.tf             # EKS 集群、托管节点组（实例类型、磁盘大小、扩缩容范围）、IAM 角色、安全组规则
│   │   │   ├── variables.tf        # 输入变量：集群版本、节点组配置、子网 ID、VPC ID
│   │   │   └── outputs.tf          # 输出：集群端点、集群名称、OIDC Provider ARN、节点组 IAM 角色 ARN
│   │   ├── rds/                    # RDS 数据库模块
│   │   │   ├── main.tf             # RDS 实例（引擎/版本/实例类/存储）、子网组、参数组、安全组规则
│   │   │   ├── variables.tf        # 输入变量：引擎类型、实例规格、存储配置、备份策略、子网 ID、VPC ID
│   │   │   └── outputs.tf          # 输出：数据库端点、端口、数据库名称、连接字符串模板
│   │   └── iam/                    # IAM 权限模块
│   │       ├── main.tf             # IAM 角色（EKS 节点、Velero、ExternalDNS、cert-manager、Vault）、策略文档、信任关系
│   │       ├── variables.tf        # 输入变量：OIDC Provider ARN、集群名称、AWS 账户 ID
│   │       └── outputs.tf          # 输出：各 IAM 角色 ARN
│   └── environments/
│       ├── dev/                    # 开发环境
│       │   ├── main.tf             # 调用 4 个模块（dev 规格：单 AZ、小实例、低成本）
│       │   ├── variables.tf        # 环境变量定义
│       │   ├── terraform.tfvars    # 环境变量值（dev 具体配置）
│       │   └── backend.tf          # 远程状态存储（S3 backend，dev 独立 state 文件）
│       ├── staging/                # 预发布环境
│       │   ├── main.tf             # 调用 4 个模块（staging 规格：多 AZ、中型实例）
│       │   ├── variables.tf        # 环境变量定义
│       │   ├── terraform.tfvars    # 环境变量值（staging 具体配置）
│       │   └── backend.tf          # 远程状态存储
│       └── prod/                   # 生产环境
│           ├── main.tf             # 调用 4 个模块（prod 规格：多 AZ、大型实例、多副本）
│           ├── variables.tf        # 环境变量定义
│           ├── terraform.tfvars    # 环境变量值（prod 具体配置）
│           └── backend.tf          # 远程状态存储
├── security/
│   ├── cert-manager.yaml           # cert-manager 部署配置：ClusterIssuer（Let's Encrypt staging/prod）、Certificate 资源（域名列表、密钥存储为 K8s Secret）、自动续期配置
│   └── vault-config.yaml           # Vault 配置：初始化与解封、K8s Auth Method（ServiceAccount 认证）、Secret Engine（KV v2 静态密钥 + Database 动态凭据引擎）、Policy（按服务限制访问路径）、Sidecar Injector 注解
├── monitoring/
│   └── slos.yaml                   # SLO 定义文件（作为 K8s ConfigMap 或 Prometheus 规则）：服务可用性 SLO（99.9% 月度）、P95 延迟 SLO（< 200ms）、错误预算计算规则、SLO 燃烧率告警（1h 消耗 2% 错误预算 → critical, 6h 消耗 5% → warning）
├── velero/
│   ├── values.yaml                 # Velero Helm values：备份存储位置（S3 bucket + region）、备份调度（每日全量、每小时增量）、保留策略（日备保留 7 天、周备保留 4 周、月备保留 3 个月）、快照配置、排除命名空间
│   └── README.md                   # Velero 使用指南：安装步骤（helm install）、备份创建与列出、模拟灾难恢复流程（删除命名空间 → 从备份恢复 → 验证服务和数据恢复）、RTO/RPO 指标验证
├── docs/
│   ├── DEPLOYMENT.md               # 部署指南：从零开始部署完整系统的分步操作手册（1. 配置云提供商凭证 2. Terraform 创建基础设施 3. 部署 K8s 基础组件（cert-manager/Vault/Velero）4. Kustomize 部署应用到各环境 5. 配置 DNS 和 Ingress 6. 验证所有端点可达 7. 配置监控告警）
│   └── DISASTER_RECOVERY.md        # 灾难恢复计划：灾难场景分类（部分故障/全集群故障/区域故障）、RTO 目标（< 1h）/ RPO 目标（< 15min）、分步恢复流程（1. 确认故障范围 2. Terraform 重建基础设施 3. Velero 恢复 K8s 资源和 PV 4. Vault 解封与恢复 5. 验证服务正常 6. 切换 DNS 流量）、定期演练计划（每月演练一次）
└── tests/
    └── integration/
        └── test_e2e.py             # 端到端集成测试：CI/CD 流水线触发 → 等待部署完成 → 调用生产 API 端点验证推理 → 检查 Prometheus 指标 → 验证 Grafana 仪表盘可访问 → 验证日志出现在 Kibana → 检查 Vault 密钥注入 → 验证 TLS 证书有效
```

### 文件说明

- **README.md** — 项目总入口。需包含：系统架构全图（C4 模型 Context 和 Container 级别）、子系统概览表（每个子系统的功能、技术栈、入口地址）、架构决策摘要表（关键技术选型及理由）、快速开始（最小化部署到生产需要的最少步骤）、与前置项目的关联说明。
- **requirements.md** — 综合需求规格说明书。需包含：系统整体需求（端到端响应延迟 < 500ms、可用性 >= 99.9%）、集成需求（ML 流水线训练完成自动触发 CI/CD 更新模型服务）、安全需求（所有外部端点 TLS 1.3、密钥不落盘、RBAC 最小权限）、SLO 矩阵（可用性、延迟、吞吐量）、灾难恢复需求（RTO < 1h、RPO < 15min、跨区域恢复能力）。
- **architecture.md** — 架构设计文档。需包含：C4 Level 1 系统上下文图（用户 → ML 平台 → 外部系统）、C4 Level 2 容器图（Web API / ML Pipeline / Model Store / Monitoring / Logging 等容器及交互）、部署拓扑图（多环境 K8s 集群 + 共享服务）、网络架构（VPC、子网、安全组、网络策略）、数据流图（训练数据→特征→模型→预测的完整路径）、ADR 记录（至少 3 条：选择 Kustomize 而非 Helm 部署多环境、选择 Vault 而非 Sealed Secrets、选择 Velero 而非 etcd 快照的理由）。
- **.env.example** — 环境变量模板。内容覆盖：GitHub Actions Secrets（`AWS_ACCESS_KEY_ID`、`AWS_SECRET_ACCESS_KEY`、`ECR_REPOSITORY`）、Terraform 变量（`aws_region`、`cluster_name`、`environment`）、Vault 配置（`VAULT_ADDR`、`VAULT_TOKEN`）、cert-manager 配置（`LETSENCRYPT_EMAIL`）、Velero 配置（`BUCKET_NAME`、`REGION`）。
- **src/main.py** — 统一的应用入口。集成：FastAPI 应用工厂模式、模型预测路由（`/predict`、`/batch-predict`）、健康检查（`/healthz`、`/ready`）、Prometheus 指标（`/metrics`）、结构化日志中间件、请求追踪 ID 注入、全局异常处理、CORS 和限流中间件。
- **cicd/.github/workflows/ci.yml** — CI 流水线定义。触发条件：`push` 到 `main` 或 PR 到 `main`。Job 步骤：`checkout` → `setup-python` → `install-deps` → `lint`（black + flake8 + mypy）→ `unit-test`（pytest + coverage report）→ `security-scan`（bandit 代码安全 + trivy 镜像漏洞扫描）→ `docker-build-push`（build + tag + push to ECR/GCR）。矩阵策略可并行测试多 Python 版本。
- **cicd/.github/workflows/cd.yml** — CD 流水线定义。触发条件：CI 通过 + push to main。Job 步骤：`deploy-dev`（kustomize build dev overlay → kubectl apply）→ `integration-test-dev`（运行集成测试套件）→ `deploy-staging`（kustomize build staging → kubectl apply）→ `smoke-test-staging`（运行冒烟测试）→ `deploy-prod`（需要 GitHub Environment protection rules 审批）→ `health-check-prod`（等待并周期性检查生产指标，如异常则触发自动回滚）→ `notify`（Slack 通知部署结果）。
- **kubernetes/base/** — Kustomize Base。`kustomization.yaml` 声明所有环境公共的 K8s 资源：Deployment（不含副本数和资源限制）、Service、ConfigMap（环境无关项如日志级别）、HPA（基本规则）。使用 `commonLabels` 为所有资源注入公共标签。
- **kubernetes/overlays/dev/**、**staging/**、**production/** — 环境特定覆盖。每个 overlay 的 `kustomization.yaml` 通过 `patchesStrategicMerge` 覆盖副本数、资源限制、镜像标签、域名、TLS 配置。各环境的差异化：dev（单副本、最小资源、调试日志）、staging（2 副本、中等资源、模拟真实流量）、production（3+ 副本、高配资源、多 AZ 亲和性、限制日志级别为 INFO）。
- **terraform/modules/vpc/** — VPC 网络模块。创建：VPC（CIDR 块分配）、公有子网（托管 Ingress Controller）、私有子网（托管 EKS 节点和 RDS）、NAT 网关（私有子网出站访问）、Internet 网关（公有子网入站流量）、路由表（公有子网 → IGW、私有子网 → NAT）、网络 ACL 和标签。
- **terraform/modules/eks/** — EKS 集群模块。创建：EKS 控制平面（版本、日志类型、加密配置）、托管节点组（实例类型、最小/最大/期望节点数、磁盘大小、标签和污点）、IAM 角色（节点角色含 AmazonEKSWorkerNodePolicy、AmazonEKS_CNI_Policy、AmazonEC2ContainerRegistryReadOnly）、安全组（控制平面到节点通信、节点间通信）。
- **terraform/modules/rds/** — RDS 数据库模块。创建：RDS 实例（PostgreSQL/MySQL 引擎、多 AZ 部署 production 环境）、数据库子网组、参数组（连接数、字符集）、安全组（仅允许 EKS 节点安全组访问）、备份配置（自动化备份窗口、保留期 7-35 天按环境变化）。
- **terraform/modules/iam/** — IAM 权限模块。创建：EKS 节点角色（已有策略）、Velero IAM 角色（S3 读写 + EBS 快照权限）、ExternalDNS IAM 角色（Route53 记录管理）、cert-manager IAM 角色（Route53 DNS-01 验证）、Vault IAM 角色（KMS 解封密钥管理 + DynamoDB 存储后端）。使用 OIDC Provider 实现 IRSA（IAM Roles for Service Accounts）。
- **terraform/environments/{dev,staging,prod}/** — 环境配置。每个环境目录包含：独立 `backend.tf`（S3 State 文件隔离）、`main.tf` 调用模块并传入环境特定参数、`terraform.tfvars` 定义环境配置值（`environment = "dev"/"staging"/"prod"`、`instance_type = "t3.small"/"t3.medium"/"t3.large"`、`min_nodes = 1/2/3`、`db_multi_az = false/false/true`）。
- **terraform/README.md** — Terraform 使用指南。内容：前置条件（AWS CLI 配置、S3 桶创建用于远程状态）、目录结构说明、模块职责描述、变量说明表（变量名、类型、默认值、描述）、`terraform init/plan/apply` 在每个环境中运行的完整命令、状态锁定机制（DynamoDB）、如何添加新环境、安全注意事项（敏感变量用 `sensitive = true` 标记）。
- **security/cert-manager.yaml** — TLS 证书自动化。内容：cert-manager 安装（Helm values 或静态清单）、`ClusterIssuer` 定义（Let's Encrypt Production ACME Server、HTTP-01 或 DNS-01 Challenge、Email 通知）、`Certificate` 资源（通配符域名、密钥编码 PKCS#1、密钥算法 RSA 2048、续期窗口 30 天）。
- **security/vault-config.yaml** — 密钥管理配置。内容：Vault 安装（Helm values：HA 模式、Raft 存储后端、自动解封使用 KMS）、Kubernetes Auth Method 配置（ServiceAccount Token Review）、KV v2 Secret Engine（静态密钥如 API Keys、数据库密码）、Database Secret Engine（动态生成临时数据库凭据、TTL 和最大 TTL）、Policy（每个微服务只能读取自己的密钥路径）、Sidecar Injector 注解说明（`vault.hashicorp.com/agent-inject`）。
- **monitoring/slos.yaml** — SLO 定义。作为 PrometheusRule CRD 或 ConfigMap 存储。定义：`slo:availability`（`sum(rate(http_requests_total{status!~"5.."}[30d])) / sum(rate(http_requests_total[30d]))`）、`slo:latency_p95`（`histogram_quantile(0.95, rate(inference_duration_seconds_bucket[30d]))`）、错误预算燃烧率告警（`(1 - slo:availability) / (1 - 0.999)` 以 1h/6h/24h 窗口计算）、多窗口燃烧率告警（6h 消耗 2% 和 1h 消耗 5% → critical）。
- **velero/values.yaml** — Velero Helm values。配置：`configuration.backupStorageLocation.bucket`（S3 桶名）、`configuration.backupStorageLocation.config.region`、`configuration.volumeSnapshotLocation.config.region`、`schedules.daily.schedule: "0 0 * * *"`（每日午夜全量备份）、`schedules.daily.ttl: "168h"`（日备保留 7 天）、`schedules.weekly.schedule: "0 0 * * 0"`（每周日）、`schedules.weekly.ttl: "672h"`（周备保留 28 天）、快照卷配置、排除 `kube-system` 等系统命名空间。
- **velero/README.md** — Velero 灾备指南。内容：安装步骤（`helm install velero vmware-tanzu/velero -f values.yaml`）、查看备份状态（`velero backup get`）、创建即时备份（`velero backup create pre-maintenance --from-schedule daily`）、完整灾难恢复演练流程（1. 模拟灾难：`kubectl delete namespace production` 2. 恢复：`velero restore create --from-backup <name>` 3. 验证：`kubectl get all -n production` 和 API 健康检查）、RTO/RPO 测量方法（记录删除时间和完全恢复时间）。
- **docs/DEPLOYMENT.md** — 部署指南。从零到生产环境的完整操作手册，每个步骤含具体命令和预期输出。章节：环境准备（CLI 工具安装列表和版本要求）、云服务商账户配置、Terraform 创建基础设施（dev → staging → prod 逐步）、部署 K8s 基础组件（cert-manager、Vault、Velero、Ingress Controller）、配置 DNS 和 TLS、使用 Kustomize 部署应用、执行冒烟测试验证、接入监控告警、生产环境 Checklist。
- **docs/DISASTER_RECOVERY.md** — 灾难恢复计划。章节：灾难场景矩阵（控制平面故障、节点池故障、数据库故障、区域故障、人为误删、TLS 证书过期）及对应的恢复方案；RTO（恢复时间目标 < 1h）和 RPO（恢复点目标 < 15min）定义；分步恢复 SOP（快速评估 → 基础设施重建 → 数据恢复 → 应用恢复 → 流量切换 → 验证）；演练计划（每月一次完整灾备演练，脚本化执行并记录耗时）；联系人和升级路径；灾备资源清单（备份位置、Terraform State 位置、DNS 管理后台）。
- **tests/integration/test_e2e.py** — 端到端测试。使用 pytest 实现：`test_ci_cd_pipeline`（验证  CI 流水线最近一次运行状态为 success）、`test_model_api_health`（调用生产 API `/healthz` 返回 200）、`test_model_prediction`（调用 `/predict` 并验证响应格式和值合理性）、`test_prometheus_metrics`（抓取 `/metrics` 验证关键指标存在）、`test_grafana_dashboards`（通过 Grafana API 验证仪表盘可访问）、`test_kibana_logs`（通过 ES API 验证最近日志存在）、`test_vault_secrets`（验证 Pod 环境变量包含 Vault 注入的密钥）、`test_tls_certificate`（验证 API 端点 TLS 证书有效且未过期）。

---

## 附加说明

**CI/CD 流水线阶段概览：**

```
Git Push → CI (Build + Test + Scan + Push Image)
                ↓
         Deploy to DEV (Auto)
                ↓
         Integration Tests
                ↓
         Deploy to STAGING (Auto)
                ↓
         Smoke Tests
                ↓
      [Manual Approval Gate] ← Quality Gate (all tests passed, no critical vulnerabilities)
                ↓
         Deploy to PRODUCTION
                ↓
      Post-Deploy Health Check (monitor for 10min)
                ↓ (on failure)
         Auto-Rollback to previous version
```

**Terraform 模块依赖关系：**

```
VPC ──────┬──→ EKS ────→ IAM
           │
           └──→ RDS
```

EKS 和 RDS 模块依赖 VPC 模块输出的子网 ID；IAM 模块依赖 EKS 模块输出的 OIDC Provider ARN 来实现 IRSA（服务账户的 IAM 角色）。

**多环境 Kustomize 覆盖策略：**

| 配置项 | dev | staging | production |
|--------|-----|---------|------------|
| 副本数 | 1 | 2 | 3+ |
| CPU 请求/限制 | 250m/500m | 500m/1000m | 2000m/4000m |
| 内存请求/限制 | 256Mi/512Mi | 512Mi/1Gi | 2Gi/4Gi |
| HPA 最小/最大 | 1/3 | 2/5 | 3/10 |
| 日志级别 | DEBUG | INFO | WARN |
| TLS | staging 证书 | staging 证书 | production 证书 |
| 数据库实例 | db.t3.micro | db.t3.small | db.t3.medium (Multi-AZ) |
| EKS 节点类型 | t3.medium | t3.large | t3.xlarge |
| 节点数（最小/最大） | 1/3 | 2/5 | 3/10 |
| 备份保留 | 7 天 | 14 天 | 35 天 |
