# 模块 006 — Kubernetes 容器编排入门

> **时长**: 20 小时 | **难度**: 入门+ | **前置知识**: Docker 容器化技术（模块 005 必备）、Linux 基础（模块 002 推荐）

---

## 模块概述

Kubernetes（K8s）是当今云原生生态中容器编排的事实标准。本模块从 K8s 的架构理念出发，系统地讲解如何将容器化应用部署到 K8s 集群中，包括 YAML 清单文件编写、Helm 包管理器的使用，以及日常运维和排障技能。学完本模块后，你将具备在 K8s 上管理 AI/ML 工作负载的基础能力。

---

## 主题分解

### 1. Kubernetes 架构（4小时）

- **控制平面与节点**: API Server / etcd / Scheduler / Controller Manager 四大控制平面组件的职责与协作，Worker Node 上的 kubelet / kube-proxy / Container Runtime，集群高可用设计的基本概念
- **Pod**: K8s 最小的调度与部署单元，单容器 Pod 与多容器 Pod（Sidecar 模式），Pod 的生命周期（Pending / Running / Succeeded / Failed / CrashLoopBackOff），Init Container 初始化容器的用途
- **Service 与 Deployment**: Service 的四种类型（ClusterIP / NodePort / LoadBalancer / ExternalName），Deployment 的声明式更新与滚动升级（Rolling Update），ReplicaSet 的副本保证机制
- **ConfigMap 与 Secret**: ConfigMap 的非敏感配置注入方式（环境变量 / Volume 挂载 / 命令行参数），Secret 的敏感数据管理（Opaque / TLS / docker-registry 类型），配置的热更新与不可变性
- **Namespace**: 逻辑隔离与资源组织，default / kube-system / kube-public 等系统命名空间，ResourceQuota 与 LimitRange 的命名空间级资源管控

### 2. 部署应用（6小时）

- **YAML 清单编写**: K8s 资源清单的四要素（apiVersion / kind / metadata / spec），常用资源的完整配置模板，YAML 的缩进与结构规范，kubectl explain 在线文档查询
- **Deployment**: replicas 副本数管理，PodTemplate 模板定义与标签（labels）选择器（selectors），更新策略（RollingUpdate / Recreate），就绪探针（readinessProbe）与存活探针（livenessProbe）的配置
- **StatefulSet**: 有状态应用的编排（数据库、消息队列），稳定的网络标识（Headless Service），持久化存储的自动关联（volumeClaimTemplates），有序的扩缩容与滚动更新
- **Service 与 Ingress**: 不同 Service 类型的选择指南，Ingress 资源的规则定义（host-based / path-based），Ingress Controller（Nginx / Traefik）的安装与配置，TLS 证书的配置
- **PV 与 PVC**: PersistentVolume（PV）的静态与动态供给（StorageClass），PersistentVolumeClaim（PVC）的申请绑定流程，Access Modes（ReadWriteOnce / ReadOnlyMany / ReadWriteMany），回收策略（Retain / Delete / Recycle）

### 3. Helm 包管理器（5小时）

- **Chart 结构**: Chart.yaml 元数据文件，templates/ 模板目录的组织方式，values.yaml 默认配置值，charts/ 子 Chart 依赖，内置对象（.Release / .Values / .Chart / .Template）的使用
- **模板编写**: Go Template 语法基础，条件语句与循环结构，命名模板（define / template / include）的定义与复用，管道（pipeline）与函数的使用
- **Values 配置**: values.yaml 的多层级配置结构，helm install --set 命令行覆盖，多环境 values 文件（values-dev.yaml / values-prod.yaml），对敏感值进行加密管理
- **Chart 部署与升级**: helm install / upgrade / rollback 的操作，helm list 查看 Release 状态，helm repo 管理 Chart 仓库（添加、更新、搜索），Chart 的打包（helm package）与推送

### 4. Kubernetes 运维（5小时）

- **kubectl 命令**: 常用命令族（get / describe / logs / exec / apply / delete / scale），输出格式的控制（-o wide / -o yaml / -o json），kubectl 的上下文（context）与 kubeconfig 切换
- **Pod 调试**: kubectl exec 进入容器调试，kubectl port-forward 端口转发，kubectl cp 文件拷贝，临时调试容器（Ephemeral Container / kubectl debug），Pod 事件查看与故障分析
- **日志聚合**: kubectl logs 的常用选项（-f / --tail / --since / --previous），多副本 Pod 的标签选择器过滤（-l），Stern / kubetail 多 Pod 日志聚合工具，集中式日志方案（EFK / Loki Stack）的概念
- **资源监控**: kubectl top 查看 Pod 与节点资源使用，Metrics Server 的安装与指标采集，资源请求（requests）与限制（limits）的合理设定，资源使用可视化
- **HPA 自动伸缩**: Horizontal Pod Autoscaler 的工作原理，基于 CPU / 内存 / 自定义指标的弹性伸缩，扩缩容阈值的调优策略

---

## 学习目标

完成本模块后，你应当能够：

1. 理解 Kubernetes 的架构设计理念与核心抽象概念
2. 编写规范、可复用的 K8s YAML 资源清单文件
3. 将容器化应用部署到 K8s 集群并进行滚动更新
4. 使用 Helm 打包、配置和管理应用
5. 通过 kubectl 排查 Pod、Service、Deployment 等常见部署问题
6. 配置持久化存储和自动伸缩策略

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/01-k8s-architecture.md` | 讲义 | K8s 架构（控制平面、Pod、Service、ConfigMap、Namespace） |
| `lecture-notes/02-deploying-applications.md` | 讲义 | 部署应用（YAML 清单、Deployment、StatefulSet） |
| `lecture-notes/03-services-networking.md` | 讲义 | Service 与 Ingress 网络配置 |
| `lecture-notes/04-helm-charts.md` | 讲义 | Helm 包管理器（Chart 结构、模板、部署与升级） |
| `exercises/01-k8s-cluster-setup.md` | 练习 | K8s 集群环境搭建（minikube/kind/k3d） |
| `exercises/02-pods-and-deployments.md` | 练习 | Pod 与 Deployment 部署练习 |
| `exercises/03-services-and-networking.md` | 练习 | Service 与网络配置练习 |
| `exercises/04-configmaps-secrets.md` | 练习 | 配置注入与密钥管理练习 |
| `exercises/05-persistent-volumes.md` | 练习 | 持久化存储练习 |
| `exercises/06-helm-charts.md` | 练习 | Helm Chart 编写与部署练习 |
| `exercises/07-debugging-troubleshooting.md` | 练习 | Pod 调试与故障排障练习 |
| `quizzes/module-006-quiz.md` | 测验 | 模块 006 知识检测测验 |
| `resources/recommended-reading.md` | 资源 | 推荐阅读、Kubectl 命令速查表与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 005 — Docker 容器化技术](./mod-005-docker-containers.md)（必备）、[模块 002 — Linux 系统管理基础](./mod-002-linux-essentials.md)
- **后续**: [模块 009 — 监控与日志基础](./mod-009-monitoring-basics.md)、[模块 010 — 云平台](./mod-010-cloud-platforms.md)
