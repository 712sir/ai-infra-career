# 项目 02 — Kubernetes 模型服务

**时长:** 80 小时  
**难度:** 入门+

---

## 项目概述

本项目将你在项目 01 中构建的模型 API 服务部署到 Kubernetes 集群，实现生产级的容器编排能力。你将学习如何使用原生的 Kubernetes 资源清单（Deployment、Service、Ingress）来管理服务，并通过 Helm 实现可复用的打包与发布。此外，你还需要配置水平自动伸缩（HPA）以应对流量波动，集成 Prometheus 和 Grafana 进行指标监控与可视化，最后使用 Locust 进行系统化的负载测试来验证整个部署的可靠性和性能。

通过本项目，你将具备在 Kubernetes 上运维 ML 模型服务的实战能力，这是 MLOps 工程师最核心的技能之一。

---

## 前置条件

- 项目 01：简单模型 API 部署（已完成）
- 模块 006：Kubernetes 基础与容器编排

---

## 核心交付物

1. **Kubernetes 原生清单** — 完整的 Deployment、Service、ConfigMap、Ingress、Secret、HPA 资源定义文件，可直接 `kubectl apply` 部署
2. **Helm Chart** — 生产级 Helm Chart，包含 8 个模板文件（deployment、service、configmap、secret、hpa、ingress、serviceaccount、pdb）和可配置的 values.yaml，支持 HPA 和 ServiceMonitor 集成
3. **HPA 水平自动伸缩** — 基于 CPU 和内存利用率的自动伸缩策略，含扩缩容阈值和冷却窗口配置
4. **Prometheus 指标集成** — 自定义应用指标（推理延迟直方图、请求计数、错误率）通过 `/metrics` 端点暴露，由 Prometheus 采集
5. **Grafana 监控仪表盘** — 完整的 JSON 仪表盘定义，可视化模型服务的 QPS、延迟分布、错误率、资源使用和 HPA 状态
6. **Locust 负载测试** — 包含冒烟测试、爬坡测试、浸泡测试和尖峰测试四种场景的完整负载测试脚本与结果分析

---

## 技术栈

| 类别 | 技术 |
|------|------|
| 容器编排 | Kubernetes (kubectl, kubeadm 或 minikube/kind) |
| 包管理 | Helm 3 |
| 指标监控 | Prometheus (含 ServiceMonitor CRD) |
| 可视化 | Grafana |
| 入口控制器 | NGINX Ingress Controller |
| 负载测试 | Locust |
| 服务网格 | 可选：Istio / Linkerd |

---

## 评分标准（100 分）

| 评分项 | 分值 | 说明 |
|--------|------|------|
| 基础设施 | 30 分 | K8s 清单语法正确、资源定义完整（请求/限制、探针、Pod 反亲和性）；Helm Chart 结构规范、values.yaml 可配置化程度高、模板无硬编码 |
| 功能实现 | 25 分 | 服务可成功部署并对外提供预测 API；HPA 在负载增加时能自动扩容、负载降低时缩容；滚动更新零停机，回滚操作正常 |
| 监控配置 | 20 分 | Prometheus 成功采集自定义指标；Grafana 仪表盘包含核心面板（QPS、延迟 P50/P95/P99、错误率、CPU/内存、副本数）；告警规则已配置 |
| 文档质量 | 15 分 | Helm Chart README 包含参数说明表；部署文档覆盖从集群初始化到服务上线的全流程；负载测试报告含图表和结论 |
| 可扩展性 | 10 分 | 架构支持多模型版本并行部署（金丝雀/蓝绿）；PDB 配置防止自愿性中断导致服务不可用；考虑了多可用区部署 |

---

## 文件清单

```
project-02-kubernetes-serving/
├── README.md                       # 项目指南：架构说明、前置要求（kubectl/helm/k8s 集群）、部署步骤、验证方法
├── requirements.md                 # 需求规格说明书：功能需求、非功能需求（SLA 目标）、容量规划、安全要求
├── architecture.md                 # 架构设计文档：K8s 集群拓扑、网络策略、流量路径、扩缩容策略、监控架构
├── .env.example                    # 环境变量模板：模型路径、副本数、资源限制、HPA 参数、镜像仓库地址
├── src/
│   └── app.py                      # 模型服务 API：在项目 01 基础上增加 /metrics 端点（Prometheus 格式）、就绪探针和存活探针端点
├── kubernetes/
│   ├── deployment.yaml             # Deployment 定义：副本数、资源请求/限制、存活/就绪探针、卷挂载、节点选择器、Pod 反亲和性
│   ├── service.yaml                # Service 定义：ClusterIP 类型、端口映射、会话亲和性配置
│   ├── configmap.yaml              # ConfigMap 定义：非敏感配置项（模型路径、日志级别、批处理大小等）
│   ├── hpa.yaml                    # HPA 定义：最小/最大副本数、CPU/内存目标利用率、扩缩容行为策略
│   ├── ingress.yaml                # Ingress 定义：域名路由规则、TLS 终止、路径重写、CORS 配置
│   └── secrets.example.yaml        # Secret 模板：镜像拉取凭证、API 密钥等敏感信息（不含真实凭证）
├── helm/
│   └── model-api/
│       ├── Chart.yaml              # Chart 元数据：名称、版本、描述、依赖项
│       ├── values.yaml             # 默认配置值：副本数、镜像、资源、HPA、Ingress、监控、探针等全部可配置参数
│       ├── templates/
│       │   ├── deployment.yaml     # Deployment 模板
│       │   ├── service.yaml        # Service 模板
│       │   ├── configmap.yaml      # ConfigMap 模板
│       │   ├── secret.yaml         # Secret 模板
│       │   ├── hpa.yaml            # HPA 模板（可通过 values 开关控制）
│       │   ├── ingress.yaml        # Ingress 模板
│       │   ├── serviceaccount.yaml # ServiceAccount 模板（含 RBAC 角色绑定）
│       │   └── pdb.yaml            # PodDisruptionBudget 模板
│       └── README.md               # Helm Chart 使用说明：参数表、安装/升级/回滚命令、自定义示例
├── grafana/
│   └── model-api-dashboard.json    # Grafana 仪表盘 JSON：QPS 面板、延迟分布直方图、错误率时序图、CPU/内存使用面板、副本数/HPA 状态面板、4 个黄金信号概览
├── monitoring/
│   └── servicemonitor.yaml         # Prometheus ServiceMonitor：选择器标签、采集间隔、指标路径、重标记规则
├── loadtest/
│   ├── locustfile.py               # 负载测试脚本：定义 User 行为类（模拟 /predict 请求）、四种测试场景（冒烟 10 并发、爬坡 10→100、浸泡 100 稳态 30min、尖峰 10→500 突发）
│   └── README.md                   # 负载测试说明：环境准备、运行命令、场景参数、结果解读指南、性能基线数据记录模板
└── tests/
    └── test_k8s.py                 # K8s 集成测试：使用 pytest + kubernetes-client 验证资源创建、服务可达性、HPA 状态、探针响应、ConfigMap 挂载正确性
```

### 文件说明

- **README.md** — 项目入口文档。需包含：整体架构图（K8s 资源关系图）、前置环境要求（kubectl、helm、可用的 K8s 集群）、从零部署到验证的完整操作步骤、如何访问服务、故障排查常见问题。
- **requirements.md** — 需求规格说明书。需包含：服务可用性 SLO（如 99.9%）、延迟 SLO（P95 < 200ms）、容量规划（预期 QPS 与副本数关系）、安全要求（网络策略、TLS、Secret 管理）、扩容策略（触发条件和响应时间目标）。
- **architecture.md** — 架构设计文档。需包含：K8s 集群拓扑图、Pod 内部容器关系、流量从 Ingress 到 Pod 的完整路径、HPA 决策逻辑、监控数据流（应用 → Prometheus → Grafana）、网络策略设计、高可用考虑。
- **.env.example** — 环境变量模板。含模型配置、K8s 资源配置（requests/limits）、HPA 参数（minReplicas/maxReplicas/targetCPUUtilization）、镜像仓库地址、Ingress 域名等。
- **src/app.py** — 模型服务 API。在项目 01 基础上扩展：添加 `/metrics` 端点使用 `prometheus_client` 库暴露直方图和计数器指标；添加 `/ready` 和 `/healthz` 端点用于 K8s 探针；支持优雅关闭（SIGTERM 处理）。
- **kubernetes/deployment.yaml** — 核心工作负载定义。需配置：`replicas`（副本数）、`resources.requests/limits`（资源限制）、`livenessProbe`（存活探针，检测应用是否僵死）、`readinessProbe`（就绪探针，检测是否可接受流量）、`podAntiAffinity`（Pod 反亲和性，分散到不同节点）、`terminationGracePeriodSeconds`（优雅终止宽限期）。
- **kubernetes/service.yaml** — 服务暴露定义。`ClusterIP` 类型（集群内部访问），通过 `selector` 关联 Deployment 的 Pod，定义 `ports` 映射（如 80→8000），可配置 `sessionAffinity`。
- **kubernetes/configmap.yaml** — 配置分离。将非敏感配置（模型文件路径、日志级别、批处理大小、超时时间等）从镜像中解耦，通过环境变量或卷挂载注入 Pod，实现配置热更新（需配合应用重载）。
- **kubernetes/hpa.yaml** — 水平自动伸缩。定义 `scaleTargetRef` 指向目标 Deployment，`minReplicas/maxReplicas` 设定伸缩边界，`metrics` 定义触发指标（CPU 利用率、内存利用率），`behavior` 定义扩缩容速率（稳定窗口、步长策略）。
- **kubernetes/ingress.yaml** — 外部流量入口。定义域名路由规则将外部请求转发到内部 Service，配置 TLS 终止，可添加 Nginx 注解实现限流、CORS、重写等高级功能。
- **kubernetes/secrets.example.yaml** — 敏感信息模板。展示 Secret 的结构但不含真实值，说明如何创建和管理 Secret（如镜像拉取凭证 `docker-registry` 类型）。
- **helm/model-api/** — 生产级 Helm Chart。通过 `helm install` 一键部署完整服务栈，`values.yaml` 中所有参数均可覆盖。Chart 遵循 Helm 最佳实践：使用命名模板、`_helpers.tpl`、NOTES.txt 安装后提示信息。
- **helm/model-api/values.yaml** — 集中配置。涵盖：`replicaCount`、`image.repository/tag/pullPolicy`、`service.type/port`、`ingress.enabled/hosts/tls`、`resources.requests/limits`、`autoscaling.enabled/minReplicas/maxReplicas/targetCPUUtilization`、`monitoring.enabled/serviceMonitor`、`podSecurityContext`、`nodeSelector`、`tolerations`、`affinity`。
- **helm/model-api/templates/** — 模板文件集合。每个模板使用 Go template 语法引用 `.Values` 中的配置，支持条件渲染（如 `{{ if .Values.ingress.enabled }}`），确保生成的清单文件符合 K8s API 规范。
- **grafana/model-api-dashboard.json** — 仪表盘定义。使用 Grafana JSON 模型定义面板：`query_rate`（QPS 时序图）、`latency_heatmap`（延迟分布热力图）、`error_rate`（错误率百分比）、`cpu_memory`（资源使用趋势）、`replica_status`（副本数变化 + HPA 事件）、`four_golden_signals`（延迟/流量/错误/饱和度摘要行）。
- **monitoring/servicemonitor.yaml** — Prometheus Operator 集成。定义 `selector.matchLabels` 匹配 Service 标签，`endpoints` 指定采集路径 `/metrics`、端口和采集间隔（如 30s），`relabelings` 进行指标标签重写。
- **loadtest/locustfile.py** — 负载测试脚本。定义 `ModelApiUser` 类继承 `HttpUser`，实现 `predict` 任务调用 `/predict` 端点。四种场景通过 `--headless` 模式参数化运行，输出 CSV 统计和 HTML 报告。
- **loadtest/README.md** — 负载测试指南。包含环境准备（安装 Locust）、运行冒烟测试的命令、逐步增加负载的脚本、如何解读 Locust 输出的百分位延迟和 RPS 图表、性能基线记录的空白模板。
- **tests/test_k8s.py** — K8s 集成测试。使用 `kubernetes` Python 客户端和 pytest 验证：Deployment 已创建且就绪副本数达标、Service 存在且端点可解析、HPA 资源已创建且当前指标正常、ConfigMap 挂载到 Pod 的路径正确、健康检查端点返回 200。
