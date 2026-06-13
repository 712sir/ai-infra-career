# 模块 009 — 监控与日志基础

> **时长**: 15 小时 | **难度**: 入门+ | **前置知识**: Linux 基础（模块 002 推荐）、K8s 基础（模块 006 推荐）

---

## 模块概述

可观测性（Observability）是生产环境中 AI 基础设施稳定运行的基石。本模块从监控的核心三大支柱（Metrics / Logs / Traces）出发，深入讲解 Prometheus 指标采集与告警、Grafana 可视化仪表盘的创建，以及结构化日志的最佳实践。学完本模块后，你将能够为 AI 服务建立完善的监控与告警体系。

---

## 主题分解

### 1. 监控基础（3小时）

- **Metrics / Logs / Traces**: 可观测性三大支柱的定位与协作关系——Metrics 提供量化指标的聚合视图、Logs 记录离散事件的详细上下文、Traces 追踪请求在分布式系统中的完整链路
- **SLI / SLO / SLA**: Service Level Indicator（服务等级指标）的选取（可用性、延迟、错误率、吞吐量），Service Level Objective（服务等级目标）的合理设定（如 99.9% 可用性、P99 延迟 < 200ms），Service Level Agreement（服务等级协议）的业务承诺与违约后果，误差预算（Error Budget）的管理理念
- **监控策略**: 黄金信号（The Four Golden Signals）——延迟（Latency）、流量（Traffic）、错误（Errors）、饱和度（Saturation），USE 方法论（Utilization / Saturation / Errors）用于资源监控，RED 方法论（Rate / Errors / Duration）用于服务监控，告警的阈值设定与去噪策略
- **告警设计**: 告警的严重级别定义（Critical / Warning / Info），告警的收敛与分组（避免告警风暴），值班与 on-call 轮转机制，告警的升级路径与 Runbook 应急手册的编写，告警疲劳（Alert Fatigue）的预防

### 2. Prometheus（5小时）

- **架构与组件**: Prometheus Server 的抓取（Scrape）模型——主动拉取（Pull）vs 被动推送（Push），Pushgateway 的短任务指标收集，Service Discovery（服务发现）的 Kubernetes / Consul / File-based 集成方式，Alertmanager 的告警路由与分组
- **指标采集**: 指标类型（Counter / Gauge / Histogram / Summary）的语义与适用场景，Prometheus Client Library（Python client_python）的指标注册与暴露（/metrics 端点），Exporters（Node Exporter / Blackbox Exporter / PostgreSQL Exporter）的部署与使用
- **PromQL 查询语言**: 即时向量（Instant Vector）与范围向量（Range Vector）的选择器，聚合操作符（sum / avg / max / min / count / topk），内置函数（rate / irate / increase / histogram_quantile / predict_linear），子查询与范围向量的嵌套，查询性能优化
- **Recording Rules 与告警规则**: Recording Rules 的预计算与查询加速，告警规则的定义结构（alert / expr / for / labels / annotations），告警规则的最佳实践（聚合避免多次触发），PrometheusRule CRD 在 K8s 环境的管理

### 3. Grafana（4小时）

- **仪表盘创建**: 数据源（Data Source）的配置与连接（Prometheus / Loki / PostgreSQL / CloudWatch），Panel 的概念与类型选择（Time Series / Stat / Gauge / Table / Bar Chart），查询编辑器的使用与转换（Transformations）操作，时间范围选择器与刷新间隔
- **可视化类型**: 时序图（Time Series）的趋势分析，Stat Panels 的单一指标摘要显示，Gauge 的容量与饱和度展示，Heatmap 的密度分布分析，Table 的多维数据明细查看，Dashboard Links 的导航串联
- **变量与模板**: 自定义变量（Custom / Query / Data Source / Interval）的创建，变量的多值选择与全部（All）选项，变量间的级联依赖（例如：先选集群，再选命名空间），重复（Repeat）Panel 的多实例渲染
- **告警集成**: Grafana Alerting 的统一告警管理（与 Prometheus Alertmanager 的选择），告警规则的定义与评估，通知渠道（Contact Points）的配置（Email / Slack / PagerDuty / Webhook），告警静默期（Silence）与通知策略

### 4. 日志最佳实践（3小时）

- **结构化日志**: 非结构化日志 vs 结构化日志（JSON 格式）的对比，标准字段的定义（timestamp / level / service / trace_id / message），Python logging 的结构化输出配置（python-json-logger），K8s 环境中的 stdout/stderr 日志输出
- **日志级别与格式**: DEBUG / INFO / WARNING / ERROR / CRITICAL 级别的使用规范与场景划分，日志格式的标准化设计（时间戳、服务名、请求 ID 的统一），敏感信息的脱敏处理（手机号 / 密码 / API Key）
- **集中日志管理**: EFK Stack（Elasticsearch + Fluentd + Kibana）的架构与组件职责，Loki Stack（Loki + Promtail + Grafana）的轻量级替代方案，日志的采集管道（Log Pipeline）的数据流向，日志索引与保留策略
- **ELK Stack 实战**: Elasticsearch 的分片与副本配置，Fluentd / Logstash 的输入、过滤、输出插件链，Kibana 的 Discover 日志搜索、Visualize 可视化与 Dashboard 汇总，常见的查询语法（Lucene / KQL）

---

## 学习目标

完成本模块后，你应当能够：

1. 理解可观测性的核心概念与监控策略的设计方法
2. 使用 Prometheus 采集、存储和查询应用与基础设施指标
3. 编写 PromQL 查询语句进行指标分析与异常检测
4. 在 Grafana 中创建专业、可交互的运维仪表盘
5. 设计和配置有效的告警规则，避免告警疲劳
6. 实践结构化日志并构建集中日志管理方案

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/lecture-01-monitoring-fundamentals.md` | 讲义 | 监控基础（Metrics/Logs/Traces、SLI/SLO/SLA、告警设计） |
| `lecture-notes/lecture-02-prometheus.md` | 讲义 | Prometheus（架构、指标采集、PromQL） |
| `lecture-notes/lecture-03-grafana.md` | 讲义 | Grafana（仪表盘创建、可视化、变量、告警集成） |
| `lecture-notes/lecture-04-logging-best-practices.md` | 讲义 | 日志最佳实践（结构化日志、集中管理、ELK Stack） |
| `exercises/01-monitoring-concepts.md` | 练习 | 监控基础概念与策略规划练习 |
| `exercises/02-prometheus-setup.md` | 练习 | Prometheus 部署与指标采集练习 |
| `exercises/03-promql-queries.md` | 练习 | PromQL 查询语言练习 |
| `exercises/04-grafana-dashboards.md` | 练习 | Grafana 仪表盘创建练习 |
| `exercises/05-alerting-rules.md` | 练习 | 告警规则配置练习 |
| `exercises/06-structured-logging.md` | 练习 | 结构化日志实践练习 |
| `quizzes/quiz-01-monitoring-observability.md` | 测验 | 模块 009 知识检测测验 |
| `resources/module-009-resource-pack.md` | 资源 | 推荐阅读、工具速查表与延伸学习资源包 |

---

## 关联模块

- **前序**: [模块 006 — Kubernetes 容器编排入门](./mod-006-kubernetes-intro.md)、[模块 007 — API 与 Web 服务开发](./mod-007-apis-web-services.md)
- **后续**: [模块 010 — 云平台](./mod-010-cloud-platforms.md)
