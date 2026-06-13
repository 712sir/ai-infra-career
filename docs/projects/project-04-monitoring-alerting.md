# 项目 04 — 监控告警系统

**时长:** 80 小时  
**难度:** 中级

---

## 项目概述

本项目要求你为 ML 基础设施部署一套全面的监控告警系统。你需要构建三层监控体系：基础设施指标通过 Prometheus 采集、日志通过 ELK Stack（Elasticsearch、Logstash、Kibana）聚合分析、告警通过 Alertmanager 实现分级路由与多通道通知。在可视化层面，你需要设计三大 Grafana 仪表盘：ML 服务全景概览、模型漂移监控、SLI/SLO 服务质量追踪。此外，还需编写 5 份结构化的应急操作手册（Runbook），覆盖最常见的生产故障场景。

完成本项目后，你将具备为 ML 系统搭建生产级可观测性平台的能力——当系统出现异常时，能够第一时间发现、定位并按照预案处理。

---

## 前置条件

- 项目 01：简单模型 API 部署（已完成）
- 项目 02：Kubernetes 模型服务（已完成）
- 项目 03：ML 流水线与实验追踪（已完成）
- 模块 009：可观测性与监控告警基础

---

## 核心交付物

1. **Prometheus 部署与自定义指标** — 部署 Prometheus Server 并配置采集目标（ML 服务、数据库、K8s 节点），实现自定义应用指标（推理延迟分布、请求计数、错误率、模型预测分布），通过 ServiceMonitor 或静态配置完成服务发现
2. **Grafana 三大仪表盘** —
   - **ML 概览仪表盘**：整体服务健康状态、QPS、延迟百分位（P50/P95/P99）、错误率趋势、CPU/内存使用率、请求量 Top-N 端点
   - **模型漂移仪表盘**：输入特征分布变化（KL 散度/PSI 时序）、预测分布变化、数据质量指标趋势
   - **SLI/SLO 仪表盘**：服务可用性（Uptime%）、请求成功率、延迟合规率（低于 SLO 阈值请求占比）、错误预算燃烧率
3. **ELK Stack 日志聚合** — Elasticsearch 集群存储日志、Logstash 管道处理与结构化日志解析、Kibana 仪表盘与日志搜索视图
4. **Alertmanager 告警配置** — 分级告警路由树（severity: critical/warning/info → team: ml/sre/dev），多渠道通知（Slack 实时通知、PagerDuty 值班呼叫），告警分组与抑制规则防止告警风暴
5. **5 份结构化 Runbook** — 覆盖高错误率、日志延迟、模型漂移、响应缓慢、服务下线五个典型生产事件的应急响应操作手册

---

## 技术栈

| 类别 | 技术 |
|------|------|
| 指标采集 | Prometheus (含 PromQL 查询语言) |
| 可视化 | Grafana (仪表盘 JSON 模型 + 变量模板) |
| 日志引擎 | Elasticsearch (存储与索引) |
| 日志管道 | Logstash (解析、过滤、路由) |
| 日志可视化 | Kibana (仪表盘、Discover 搜索、Index Patterns) |
| 告警管理 | Alertmanager (路由树、分组、抑制、静默) |
| 通知渠道 | Slack Webhook、PagerDuty Integration、Email (SMTP) |
| 指标暴露 | Prometheus Python Client / Micrometer (Java) |

---

## 评分标准（100 分）

| 评分项 | 分值 | 说明 |
|--------|------|------|
| 指标采集 | 25 分 | Prometheus 正确采集所有目标；自定义指标定义合理且命名规范（含 unit 后缀）；指标标签设计有利于查询聚合；采集间隔与保留策略合理 |
| 仪表盘质量 | 25 分 | 三大仪表盘涵盖核心监控维度；面板布局逻辑清晰（摘要行 → 时序 → 明细）；使用 Grafana 变量实现多服务/多环境切换；告警阈值线/参考区域配置 |
| 告警配置 | 20 分 | 告警规则覆盖关键场景（高错误率、高延迟、服务下线、资源不足）；Alertmanager 路由树正确分发到对应团队；分组/抑制/静默机制有效防止告警风暴 |
| 日志管理 | 20 分 | Logstash 成功解析结构化日志并写入 ES；Kibana 可搜索和过滤日志；日志仪表盘关联指标异常事件；日志保留策略合理 |
| 文档质量 | 10 分 | Runbook 格式规范、步骤可执行；架构文档包含监控数据流图；部署文档从零启动到全功能可用 |

---

## 文件清单

```
project-04-monitoring-alerting/
├── README.md                       # 项目指南：监控架构概览、一键部署（docker-compose up）、各组件访问地址、快速验证方法
├── requirements.md                 # 需求规格说明书：监控需求矩阵、告警场景清单、SLI/SLO 定义、日志保留策略、通知渠道要求
├── architecture.md                 # 架构设计文档：可观测性三层架构图（指标/日志/告警）、数据流图、组件部署拓扑、网络与存储设计
├── .env.example                    # 环境变量模板：ES 堆内存、Prometheus 保留时间、Grafana 管理员密码、Slack Webhook URL、PagerDuty Routing Key
├── docker-compose.yml              # 全栈编排：Prometheus + Alertmanager + Grafana + Elasticsearch + Logstash + Kibana + 示例 ML 服务
├── prometheus/
│   ├── prometheus.yml              # Prometheus 主配置：全局抓取间隔、评估间隔、抓取目标（ML 服务、Node Exporter、Kubelet、Alertmanager 自身）
│   └── alerts.yml                  # 告警规则文件：HighErrorRate、HighLatency、ServiceDown、ModelDriftDetected、CPUHigh、MemoryHigh、DiskFull、CertExpiring 等规则
├── alertmanager/
│   ├── alertmanager.yml            # Alertmanager 配置：路由树（match severity → team）、接收器（Slack/PagerDuty/Email）、分组等待、重复间隔、抑制规则
│   └── templates.tmpl              # 通知模板：Slack 消息模板（标题、告警摘要、严重度颜色标签、Grafana 仪表盘直达链接）、PagerDuty 负载模板
├── grafana/
│   ├── datasources.yml             # Grafana 数据源配置：Prometheus 数据源、Elasticsearch 数据源，自动在容器启动时通过 Provisioning 机制加载
│   └── dashboards/
│       ├── ml-overview.json        # ML 概览仪表盘：服务总数、在线状态摘要行 → QPS 时序图 → 延迟 P50/P95/P99 叠加图 → 错误率百分比面板 → CPU/内存/磁盘使用趋势 → 请求量 Top-5 模型列表 → 最近告警事件表
│       ├── ml-drift.json           # 模型漂移仪表盘：输入特征 PSI/KL 散度时序 → 预测值分布变化（直方图对比）→ 数据质量指标（空值率、异常值率）趋势 → 训练数据 vs 生产数据分布对比 → 漂移告警事件时间线
│       └── sli-slo.json            # SLI/SLO 仪表盘：服务可用性百分比（滚动 30 天窗口）→ 请求成功率 vs SLO 阈值线 → 延迟合规率（滚动窗口内低于 SLO 请求比例）→ 错误预算燃烧率（燃尽速率 1h/6h/24h 多粒度）→ 错误预算剩余天数
├── elasticsearch/
│   ├── logstash.conf               # Logstash 管道配置：输入（Beats/HTTP/TCP）、过滤器链（grok 解析日志格式、date 解析时间戳、geoip 地理信息、mutate 字段重命名/删除）、输出（Elasticsearch 索引模板 + 滚动策略）
│   └── kibana-dashboard.ndjson     # Kibana 仪表盘导出：日志量时序图 → 日志级别分布（ERROR/WARN/INFO/DEBUG）→ 按服务/主机过滤 → 错误日志采样表 → 请求追踪 ID 搜索
├── runbooks/
│   ├── runbook-01-high-error-rate.md       # Runbook 1：高错误率 — 现象描述、严重度分级（>1%/5%/10%）、排查步骤（1. 检查最近部署 2. 检查下游依赖 3. 检查输入数据质量 4. 检查资源使用）、缓解措施（回滚/限流/切换备用模型）、升级路径（15min无缓解→SRE值班）
│   ├── runbook-02-log-delay.md             # Runbook 2：日志延迟 — 现象描述、排查步骤（1. Logstash 管道状态 2. ES 集群健康/磁盘 3. 网络带宽）、缓解措施（调整管道 worker/批量大小、清理旧索引）、升级路径
│   ├── runbook-03-model-drift.md           # Runbook 3：模型漂移 — 现象描述、判断依据（PSI > 0.1 / KL 散度 > 0.05）、排查步骤（1. 确认漂移特征 2. 检查上游数据源 3. 查看最近数据变更）、缓解措施（A/B 测试新旧模型、触发重训练、回滚到上一版本）
│   ├── runbook-04-slow-response.md         # Runbook 4：响应缓慢 — 现象描述、排查步骤（1. 检查 P95 延迟趋势 2. 检查 CPU/内存是否打满 3. 检查数据库慢查询 4. 检查网络延迟）、缓解措施（扩容/HPA 调整/预热模型/开启缓存）、升级路径
│   └── runbook-05-service-down.md          # Runbook 5：服务下线 — 现象描述、排查步骤（1. 检查 Pod 状态/K8s 事件 2. 检查 OOMKilled/CrashLoopBackOff 3. 检查依赖服务可用性 4. 检查 TLS 证书有效性）、恢复步骤（重启/扩容/切换流量到备用集群）、事后复盘模板
├── src/
│   ├── custom_metrics.py           # 自定义指标定义：使用 prometheus_client 库定义 Counter（request_total）、Histogram（inference_duration_seconds、input_feature_value）、Gauge（model_version_info、drift_score）、Summary（request_size_bytes）
│   └── instrumentation.py          # 埋点工具：FastAPI 中间件自动记录请求指标装饰器、结构化日志格式化器（JSON 格式含 trace_id）、模型推理埋点上下文管理器（自动记录延迟和预测值分布）
└── tests/
    └── test_metrics.py             # 指标测试：验证 /metrics 端点返回格式正确、Counter 递增逻辑、Histogram 分桶范围合理、Gauge 设置与更新、日志 JSON 格式一致性
```

### 文件说明

- **README.md** — 项目入口文档。需包含：三层监控架构图（指标 + 日志 + 告警的层次关系）、所有组件的访问地址和默认凭证、一键启动命令（`docker-compose up -d`）、验证每一步是否正常工作的检查清单（Prometheus Targets Up、Grafana 可登录并加载仪表盘、Kibana 可搜索日志、Alertmanager 静默/取消静默测试）、如何在 K8s 环境中部署的指引。
- **requirements.md** — 需求规格说明书。需包含：监控需求矩阵（每个组件需监控的指标和告警条件）、SLI 定义（可用性 = 成功请求/总请求、延迟 = P95 < 200ms 请求比例）、SLO 目标（可用性 >= 99.9%、延迟合规率 >= 99%）、告警分级策略（Critical: 5min 响应；Warning: 30min 响应；Info: 下个工作日）、日志保留策略（热数据 7 天、温数据 30 天、冷归档 90 天）。
- **architecture.md** — 架构设计文档。需包含：可观测性三层架构图（指标采集层 → 存储层 → 可视化/告警层）、数据流图（应用日志 → Logstash → ES → Kibana / 应用指标 → Prometheus → Grafana + Alertmanager）、组件部署拓扑（容器/Pod 布局、端口映射、卷挂载）、网络隔离设计、存储类选择与容量规划。
- **.env.example** — 环境变量模板。主要内容：`ES_JAVA_OPTS=-Xms1g -Xmx1g`（ES 堆大小）、`PROMETHEUS_RETENTION=15d`（指标保留时间）、`GRAFANA_ADMIN_PASSWORD=admin`、`SLACK_WEBHOOK_URL=https://hooks.slack.com/services/...`、`PAGERDUTY_ROUTING_KEY=...`、`SMTP_HOST/smtp_port/smtp_user/smtp_password`。
- **docker-compose.yml** — 全栈 Docker Compose。包含服务：`prometheus`（挂载配置和规则文件）、`alertmanager`（挂载配置和模板）、`grafana`（Provisioning 自动加载数据源和仪表盘）、`elasticsearch`（单节点开发模式，设置 `discovery.type=single-node`）、`logstash`（挂载管道配置）、`kibana`（连接 ES）、`ml-api`（示例 ML 服务暴露 /metrics 端点）。共享网络 `monitoring`。
- **prometheus/prometheus.yml** — Prometheus 主配置。`global.scrape_interval: 15s`、`global.evaluation_interval: 15s`。`scrape_configs` 包含：`prometheus` 自身监控、`ml-api`（从 docker-compose 服务名发现）、`alertmanager` 自身指标、可选的 `node-exporter` 和 `kubelet` 抓取。`rule_files: ['alerts.yml']` 引用告警规则。
- **prometheus/alerts.yml** — 告警规则定义。示例规则：`HighErrorRate`（`rate(http_requests_total{status=~"5.."}[5m]) / rate(http_requests_total[5m]) > 0.01`，severity: critical）、`HighLatency`（`histogram_quantile(0.95, rate(inference_duration_seconds_bucket[5m])) > 0.2`，severity: warning）、`ServiceDown`（`up == 0`，for: 2m，severity: critical）、`ModelDriftDetected`（`drift_score > 0.1`，severity: warning）、`CPUHigh`（`cpu_usage > 0.9`，for: 10m）、`MemoryHigh`、`DiskFull`、`CertExpiring`。
- **alertmanager/alertmanager.yml** — 告警管理配置。`route` 定义路由树：顶级按 `severity` 匹配 → `critical` 发送到 `sre-team`（PagerDuty + Slack）、`warning` 发送到 `ml-team`（Slack）、`info` 发送到 `dev-team`（Email）。`group_wait: 30s`、`group_interval: 5m`、`repeat_interval: 4h`。`inhibit_rules` 抑制：同服务 `critical` 触发时抑制 `warning`。
- **alertmanager/templates.tmpl** — 通知模板。Slack 模板使用 Slack Block Kit 格式：彩色侧边栏（critical=红/warning=黄/info=蓝）、告警标题和描述、`{{ .Annotations.runbook_url }}` 链接、Grafana 仪表盘直达链接。PagerDuty 模板：`routing_key`、`event_action`、`payload.summary/severity/source`。
- **grafana/datasources.yml** — 数据源自动配置。通过 Grafana Provisioning 机制在容器启动时自动创建 `Prometheus` 数据源（URL: `http://prometheus:9090`）和 `Elasticsearch` 数据源（URL: `http://elasticsearch:9200`），无需手动添加。
- **grafana/dashboards/ml-overview.json** — ML 概览仪表盘。面向值班 SRE 和 ML 工程师的入口仪表盘。包含：`Stat` 面板显示在线服务数和总 QPS、`TimeSeries` 面板显示 QPS 趋势和延迟百分位、`Gauge` 面板显示 CPU/内存使用率百分比、`Table` 面板显示请求量最高的端点和模型、`AlertList` 面板显示当前活跃告警。
- **grafana/dashboards/ml-drift.json** — 模型漂移仪表盘。面向数据科学家和 ML 工程师。包含：`TimeSeries` 面板显示 PSI/KL 散度时序趋势、`Histogram` 面板对比训练数据和生产数据的特征分布、`Stat` 面板显示当前漂移分数和变化率、`Table` 面板列出漂移最显著的特征 Top-N、标注漂移阈值线和告警事件标记。
- **grafana/dashboards/sli-slo.json** — SLI/SLO 仪表盘。面向 SRE 和管理层。包含：`Stat` 面板显示当前可用性百分比（绿/黄/红配色）、错误预算剩余天数、燃烧率（1h/6h/24h 多时间窗口）、`TimeSeries` 面板显示可用性和延迟合规率的滚动 30 天趋势（含 SLO 目标线）、错误预算消耗趋势图。
- **elasticsearch/logstash.conf** — Logstash 日志处理管道。`input` 段监听 Beats 或 HTTP 端口接收日志。`filter` 段：`grok` 正则解析结构化日志字段（时间戳、日志级别、服务名、trace_id、消息），`date` 将时间戳字段设为 `@timestamp`，`mutate` 删除冗余字段、重命名字段。`output` 段：写入 Elasticsearch 按日期滚动的索引（`ml-logs-%{+YYYY.MM.dd}`），配置 ILM 策略自动管理索引生命周期。
- **elasticsearch/kibana-dashboard.ndjson** — Kibana 仪表盘导出文件。通过 Kibana Saved Objects API 导出/导入。包含：日志量时序面积图（按日志级别堆叠）、按服务名过滤的日志表格（含错误堆栈展开）、`trace_id` 链接跳转实现分布式追踪查看、快速过滤（ERROR/WARN/特定服务）的快捷搜索链接。
- **runbooks/** — 应急操作手册。每一份 Runbook 遵循统一结构：**标题与适用场景** → **现象与触发条件**（告警名称、PromQL 查询）→ **严重度分级** → **影响评估** → **排查步骤**（含可执行的 kubectl/curl 命令）→ **缓解措施**（含具体命令和预期效果）→ **验证恢复**（验证指标恢复正常）→ **升级路径**（什么条件下升级、联系谁）→ **事后复盘模板**（时间线、根因、行动项）。
- **src/custom_metrics.py** — Prometheus 指标定义。使用 `prometheus_client` 库创建：`Counter('http_requests_total', 'Total requests', ['method', 'endpoint', 'status'])`、`Histogram('inference_duration_seconds', 'Inference latency', ['model_name', 'model_version'], buckets=[0.01,0.05,0.1,0.25,0.5,1.0,2.5,5.0,10.0])`、`Gauge('drift_score', 'Current PSI drift score', ['feature_name'])`、`Gauge('model_version_info', 'Current model version', ['model_name'])`。
- **src/instrumentation.py** — 应用埋点工具。提供：`@track_inference` 装饰器（自动记录推理延迟和预测值）、`StructuredLogger` 类（输出 JSON 格式日志含 `trace_id`/`service`/`timestamp`/`level`）、FastAPI 中间件 `MetricsMiddleware`（自动统计每个请求的方法/路径/状态码）、上下文变量传播 `trace_id` 贯穿整个请求生命周期。
- **tests/test_metrics.py** — 指标和日志测试。验证：`/metrics` 端点返回 `Content-Type: text/plain`、Counter 在递增后数值正确、Histogram `observe()` 后 `_bucket` 和 `_count` 更新正确、结构化日志输出为合法 JSON 且包含必要字段（`timestamp`、`level`、`message`、`trace_id`）、多个请求的 `trace_id` 唯一。

---

## 附加说明

**三大仪表盘功能矩阵：**

| 功能 | ML 概览 | 模型漂移 | SLI/SLO |
|------|---------|----------|---------|
| 目标受众 | SRE / 值班 | 数据科学家 | SRE / 管理层 |
| 核心指标 | QPS、延迟、错误率、资源 | PSI、特征分布、预测分布 | 可用性、延迟合规率、错误预算 |
| 告警关联 | 当前活跃告警列表 | 漂移阈值 + 事件标注 | SLO 阈值线 + 燃尽告警 |
| 下钻能力 | 按模型/端点过滤 | 按特征名称过滤 | 按时间窗口 (7d/30d) 切换 |
| 告警状态 | 绿/黄/红状态指示 | 漂移严重度颜色编码 | 错误预算剩余天数红/黄/绿 |
