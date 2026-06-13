# 模块 010 — 云平台

> **时长**: 20 小时 | **难度**: 入门+ | **前置知识**: Linux 基础（模块 002）、Docker/K8s（模块 005/006 推荐）

---

## 模块概述

云平台是现代 AI 基础设施运行的物理载体。本模块从云计算的核心服务模型出发，系统性地覆盖计算、存储、网络和安全管理四大领域，以 AWS / GCP / Azure 三家主流云厂商的服务为参照，帮助你建立平台无关的云架构思维。学完本模块后，你将能够在云上部署和管理 AI 基础设施服务，并做出合理的云服务选型决策。

---

## 主题分解

### 1. 云基础（4小时）

- **IaaS / PaaS / SaaS**: 三种服务模型的责任边界划分——IaaS 提供底层计算与网络资源、PaaS 抽象掉操作系统管理、SaaS 提供完整的应用服务，Serverless 与 FaaS（Function as a Service）的进一步抽象
- **区域与可用区（Region / Availability Zone）**: 区域选择的多重考虑因素（延迟、合规、服务可用性、成本），可用区的隔离与冗余设计（单 AZ vs 多 AZ 部署），边缘位置（Edge Locations / CDN 节点）的加速作用
- **IAM 访问管理**: 最小权限原则（Least Privilege）的实践，用户 / 组 / 角色（Role）的差异与用途，基于资源的策略与基于身份的策略，跨账户访问的角色扮演（Assume Role），服务账户（Service Account）与短期凭证的安全实践
- **成本管理**: 按需实例（On-Demand）vs 预留实例（Reserved）vs 竞价实例（Spot / Preemptible）的成本模型对比，成本标签（Cost Tags）的资源归属与账单拆分，预算告警（Budget Alert）的设置与异常检测，FinOps 的成本优化理念（使用权 vs 所有权）

### 2. 计算服务（5小时）

- **虚拟机 EC2 / Compute Engine / Azure VM**: 实例类型族（通用型 / 计算优化型 / 内存优化型 / GPU 加速型）的选择策略，AMI / Image 镜像的管理与定制，启动模板（Launch Template）的标准化部署，Auto Scaling Group 的弹性扩缩容配置，竞价实例在 ML 训练中的成本优化
- **容器服务 ECS / GKE / AKS**: ECS（Elastic Container Service）的 Fargate（Serverless）与 EC2 两种启动类型的对比，GKE（Google Kubernetes Engine）的 Autopilot 模式与节点自动扩缩容，AKS（Azure Kubernetes Service）的集成特性，各托管 K8s 服务的集群升级策略与维护窗口
- **无服务器 Lambda / Cloud Functions / Azure Functions**: 事件驱动的执行模型——HTTP 请求、消息队列、定时触发、对象存储事件等触发源，冷启动（Cold Start）的原因与优化（预留并发、轻量化依赖），执行超时与内存的配置限制，无服务器在 ML 推理中的适用边界

### 3. 存储与数据库（5小时）

- **对象存储 S3 / Cloud Storage / Blob Storage**: 存储类别（Standard / Infrequent Access / Archive / Glacier）的生命周期策略，版本控制（Versioning）与对象锁定（Object Lock），静态网站托管能力，预签名 URL（Pre-signed URL）的临时访问授权，跨区域复制（CRR）的容灾方案
- **托管数据库 RDS / Cloud SQL / Azure DB**: 托管关系数据库的自动备份、多 AZ 高可用、只读副本扩展，性能 Insights 的慢查询分析与自动调优建议，参数组（Parameter Group）的定制配置，数据库代理（RDS Proxy / Cloud SQL Auth Proxy）的连接管理
- **缓存服务 ElastiCache / Memorystore / Azure Cache for Redis**: Redis 与 Memcached 的托管对比，集群模式（Cluster Mode）的分片策略，自动故障转移（Auto-Failover）与多可用区部署，缓存策略的常见模式（Cache-Aside / Read-Through / Write-Behind）
- **AI 专用存储**: EFS / Filestore 的共享文件存储与分布式训练，S3 的模型权重与数据集存储方案，向量数据库的云托管服务对比，数据湖（Data Lake）在 ML 流水线中的定位（S3 + Glue + Athena / BigQuery）

### 4. 网络与安全（6小时）

- **VPC 与子网**: CIDR 地址规划的考虑（避免重叠、预留增长空间），公有子网与私有子网的划分与通信路径，NAT Gateway / NAT Instance 的出站访问方案，VPC Peering 与 Transit Gateway 的多 VPC 互联，VPC Endpoint 的私有服务访问（免公网暴露）
- **负载均衡**: ALB（Application Load Balancer / Layer 7）的路径与主机名路由，NLB（Network Load Balancer / Layer 4）的低延迟 TCP/UDP 分发，健康检查的配置与后端自动摘除，SSL Termination 与证书管理，Global Load Balancer 的跨区域流量调度
- **安全组与防火墙**: 安全组（Security Group）的状态化规则与实例级防火墙，网络 ACL（NACL）的无状态子网级访问控制，WAF（Web Application Firewall）的常见攻击防御（SQL 注入、XSS、Bot 管理），DDoS 防护方案的选择
- **密钥管理**: KMS（Key Management Service）的加密密钥创建与轮转，信封加密（Envelope Encryption）的密钥分层管理，Secrets Manager / Secret Manager / Key Vault 的敏感凭据存储与自动轮转，环境变量与代码中硬编码凭证的安全反模式
- **SSL/TLS 证书**: ACM（AWS Certificate Manager）/ Certificate Manager 的免费公共证书签发与自动续期，通配符证书（*.example.com）的使用与限制，mTLS（Mutual TLS）双向认证在服务间通信的应用，证书到期前的监控与告警

---

## 学习目标

完成本模块后，你应当能够：

1. 理解 IaaS / PaaS / SaaS 的差异，并根据场景选择合适服务模型
2. 在云平台上选择、配置和优化计算资源（VM、容器、无服务器）
3. 为 AI 工作负载选择合适的存储方案（对象存储、托管数据库、缓存）
4. 设计安全的网络架构（VPC、子网、负载均衡、防火墙）
5. 实施云安全最佳实践（IAM、密钥管理、SSL/TLS 证书）
6. 理解云成本优化策略并进行成本管控

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/lecture-01-cloud-fundamentals.md` | 讲义 | 云基础（IaaS/PaaS/SaaS、区域/AZ、IAM、成本管理） |
| `lecture-notes/lecture-02-compute-services.md` | 讲义 | 计算服务（EC2/VM、ECS/GKE/AKS、Lambda/Functions） |
| `lecture-notes/lecture-03-storage-and-databases.md` | 讲义 | 存储与数据库（S3/Cloud Storage、RDS/Cloud SQL、缓存、AI 专用存储） |
| `lecture-notes/lecture-04-networking-part1.md` | 讲义 | 网络与安全（上）：VPC、子网、负载均衡 |
| `lecture-notes/lecture-05-networking-part2.md` | 讲义 | 网络与安全（下）：安全组、密钥管理、SSL/TLS 证书 |
| `exercises/01-cloud-basics-iam.md` | 练习 | 云基础操作与 IAM 权限配置练习 |
| `exercises/02-compute-instances.md` | 练习 | 计算实例创建与配置练习 |
| `exercises/03-container-services.md` | 练习 | 托管容器服务部署练习 |
| `exercises/04-object-storage.md` | 练习 | 对象存储配置与生命周期管理练习 |
| `exercises/05-managed-database.md` | 练习 | 托管数据库部署与连接练习 |
| `exercises/06-vpc-networking.md` | 练习 | VPC 网络架构搭建练习 |
| `exercises/07-security-hardening.md` | 练习 | 安全加固综合练习 |
| `quizzes/quiz-01-cloud-platforms.md` | 测验 | 模块 010 知识检测测验 |
| `resources.md` | 资源 | 推荐阅读、云服务对比表与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 006 — Kubernetes 容器编排入门](./mod-006-kubernetes-intro.md)、[模块 009 — 监控与日志基础](./mod-009-monitoring-basics.md)
- **后续**: 学习路径完成——可进入 AI 基础设施中高级阶段学习
