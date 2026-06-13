# 项目 03 — ML 流水线与实验追踪

**时长:** 100 小时  
**难度:** 中级

---

## 项目概述

本项目要求你构建一个端到端的机器学习流水线，覆盖从数据摄取、预处理、模型训练、评估到最终部署的完整生命周期。你将使用 Apache Airflow 编排流水线任务，借助 MLflow 进行实验追踪与模型注册管理，利用 DVC（Data Version Control）对数据和模型进行版本控制，并通过 Great Expectations 确保数据质量。此外，你还需要实现一套基于周调度和模型漂移检测的自动重训练机制。

完成本项目后，你将具备设计和管理生产级 ML 流水线的能力，能够追溯每一次实验的参数、指标和产物，并确保数据质量始终在可接受范围内。

---

## 前置条件

- 项目 01：简单模型 API 部署（已完成）
- 项目 02：Kubernetes 模型服务（已完成）
- 模块 007：ML 流水线编排与 Airflow
- 模块 008：ML 实验管理与模型注册

---

## 核心交付物

1. **Airflow DAG（训练流水线）** — 完整的数据摄取 → 预处理 → 训练 → 评估 → 模型注册的流水线 DAG，含任务依赖、失败重试和告警回调
2. **Airflow DAG（自动重训练）** — 基于周调度和模型漂移检测触发的自动重训练流水线，含条件分支（漂移超过阈值才触发完整训练）
3. **MLflow 实验追踪与模型注册** — 训练过程中自动记录超参数、指标、模型产物和运行环境（conda 环境文件）；注册最佳模型并标记阶段（Staging/Production/Archived）
4. **DVC 数据与模型版本管理** — 5 阶段 DVC 流水线（数据摄取、预处理、特征工程、训练、评估），含参数文件 `params.yaml` 和远程存储配置
5. **Great Expectations 数据验证** — 不少于 13 条数据期望规则，涵盖列级（类型、范围、非空、唯一性）、表级（行数、列数）和跨表级（引用完整性），生成数据文档（Data Docs）
6. **PostgreSQL 元数据存储** — 为 MLflow 和 Airflow 提供持久化元数据存储，确保实验记录和任务状态不丢失
7. **自动化重训练流水线** — 结合 Airflow 周调度与模型漂移检测（基于数据分布变化或模型性能退化），实现有条件触发的自动重训练

---

## 技术栈

| 类别 | 技术 |
|------|------|
| 流水线编排 | Apache Airflow (CeleryExecutor 或 KubernetesExecutor) |
| 实验追踪 | MLflow (Tracking Server + Model Registry) |
| 数据版本 | DVC (Data Version Control) + 远程存储（S3/GCS/本地 NAS） |
| 数据验证 | Great Expectations |
| 元数据存储 | PostgreSQL |
| 容器化 | Docker, Docker Compose |
| 可选部署 | Kubernetes（Airflow on K8s） |

---

## 评分标准（100 分）

| 评分项 | 分值 | 说明 |
|--------|------|------|
| 流水线设计 | 25 分 | DAG 结构合理、任务拆分粒度过细或过粗均扣分；错误处理完善（重试、回调、SLA）；无循环依赖；流水线可复现 |
| 实验追踪 | 20 分 | MLflow 完整记录了每次运行的全部参数、指标和产物；模型注册表中有明确的版本管理和阶段标记；可通过 MLflow UI 对比实验 |
| 数据版本 | 15 分 | DVC 流水线文件定义清晰、各阶段输入输出明确；参数文件管理规范；远程存储配置正确且可正常推送/拉取数据 |
| 代码质量 | 20 分 | 数据处理和训练代码模块化、可测试；有适当的日志记录；except 处理不吞咽异常；遵循项目结构约定 |
| 文档质量 | 20 分 | 流水线架构图清晰；DVC 和 MLflow 使用指南详细；Great Expectations 规则说明完整；重训练策略有设计文档 |

---

## 文件清单

```
project-03-ml-pipeline-tracking/
├── README.md                       # 项目指南：整体架构、环境搭建（Airflow + MLflow + DVC）、运行流水线步骤、查看实验结果
├── requirements.md                 # 需求规格说明书：流水线功能需求、数据质量要求、重训练触发条件、SLA 定义
├── architecture.md                 # 架构设计文档：流水线 DAG 拓扑图、组件交互图、数据流图、MLflow 架构、DVC 远程存储方案
├── .env.example                    # 环境变量模板：数据库连接串、MLflow Tracking URI、DVC 远程存储地址、AWS/GCP 凭证
├── docker-compose.yml              # 完整服务编排：Airflow（Webserver/Scheduler/Worker/Redis/Postgres）、MLflow Server、PostgreSQL、MinIO（DVC 模拟 S3）
├── dags/
│   ├── ml_pipeline_dag.py          # ML 训练 DAG：数据摄取 → 数据验证 → 预处理 → 训练 → 评估 → 模型注册 → 条件部署通知，含重试、SLA、回调配置
│   └── retraining_dag.py           # 自动重训练 DAG：漂移检测（数据分布/性能）→ 条件分支 → 完整重训练或跳过，含周调度 cron 表达式
├── dvc/
│   ├── dvc.yaml                    # DVC 5 阶段流水线：ingest → validate → preprocess → train → evaluate，每阶段定义 cmd、deps、outs、metrics
│   └── params.yaml                 # 参数管理：训练超参数、数据分割比例、特征列表、模型架构参数、评估阈值
├── mlflow/
│   └── MLproject                   # MLflow 项目定义：conda 环境、入口点（main/train/evaluate）、参数声明
├── great_expectations/
│   ├── great_expectations.yml      # GE 全局配置：数据源定义、存储后端、Data Docs 配置
│   ├── expectations/               # 期望规则目录（13+ 条规则）
│   │   ├── column_type_expectations.json      # 列类型期望：数据类型校验（3 条以上）
│   │   ├── column_range_expectations.json     # 列范围期望：数值范围、字符串长度（3 条以上）
│   │   ├── column_null_expectations.json      # 非空期望：必填字段检查（2 条以上）
│   │   ├── table_level_expectations.json      # 表级期望：行数范围、列数、主键唯一性（3 条以上）
│   │   └── cross_table_expectations.json      # 跨表期望：引用完整性、值集合一致性（2 条以上）
│   └── checkpoint.yml              # 检查点配置：批量验证运行定义
├── src/
│   ├── data_ingestion.py           # 数据摄取：从源系统（数据库/文件/API）拉取原始数据，写入暂存区
│   ├── preprocessing.py            # 数据预处理：缺失值处理、特征编码、归一化/标准化、数据集划分
│   ├── training.py                 # 模型训练：加载预处理数据、使用 MLflow autolog 或手动记录、保存模型产物
│   └── evaluation.py               # 模型评估：计算评估指标（准确率/F1/AUC 等）、生成混淆矩阵/ROC 曲线、与基线/前版本对比
└── tests/
    └── test_pipeline.py            # 流水线测试：DAG 结构验证（无循环依赖）、各阶段输入输出校验、GE 规则有效性、MLflow 记录完整性
```

### 文件说明

- **README.md** — 项目总览文档。需包含：ML 流水线整体架构图（Mermaid 或图片）、各组件（Airflow、MLflow、DVC、GE）的关系说明、完整的环境搭建步骤（本地开发使用 docker-compose 一键启动）、如何触发流水线运行、如何在 MLflow UI 查看实验结果、如何使用 DVC 拉取和推送数据。
- **requirements.md** — 需求规格说明书。需包含：流水线各阶段的输入/输出规格、数据质量验收标准（所有 GE 规则通过才算数据就绪）、模型评估通过标准（如 AUC > 0.85 才允许注册）、重训练触发条件（数据漂移 KL 散度 > 0.1 或模型性能下降 > 5%）、流水线 SLA（每个阶段的预期耗时和总耗时目标）。
- **architecture.md** — 架构设计文档。需包含：Airflow DAG 拓扑图（任务依赖关系）、MLflow 架构图（Tracking Server + Backend Store + Artifact Store）、DVC 工作流图（各阶段依赖与产出）、数据存储分层（原始层 → 清洗层 → 特征层 → 模型层）、重训练决策流程图、容器编排方案。
- **.env.example** — 环境变量模板。含 `AIRFLOW__CORE__SQL_ALCHEMY_CONN`（Airflow 元数据库）、`MLFLOW_TRACKING_URI`（MLflow 服务地址）、`MLFLOW_S3_ENDPOINT_URL`（制品存储）、`DVC_REMOTE`（远程存储地址）、`AWS_ACCESS_KEY_ID/AWS_SECRET_ACCESS_KEY`（MinIO 凭证）等。
- **docker-compose.yml** — 全栈本地开发环境。包含：`postgres`（Airflow 元数据库）、`redis`（Airflow Celery Broker）、`airflow-webserver`、`airflow-scheduler`、`airflow-worker`、`mlflow-server`、`minio`（模拟 S3 作为 MLflow 制品库和 DVC 远程存储）。
- **dags/ml_pipeline_dag.py** — 核心训练 DAG。定义任务：`ingest_data` → `validate_data`（调用 GE checkpoint）→ `preprocess_data` → `train_model`（MLflow autolog context）→ `evaluate_model` → `register_model`（比较指标后注册最佳模型）→ `notify`（Slack/邮件通知结果）。需配置 `default_args`（retries、retry_delay、on_failure_callback、sla）。
- **dags/retraining_dag.py** — 自动重训练 DAG。定义任务：`detect_data_drift`（对比当前数据分布与训练基线，计算 KL 散度或 PSI）或 `check_model_performance`（评估当前模型在新数据上的表现）→ `branch_retrain`（条件分支操作符）→ 漂移超阈值时触发完整重训练子 DAG 或直接运行训练任务。调度频率为 `@weekly` 或自定义 cron。
- **dvc/dvc.yaml** — DVC 流水线定义。5 个阶段（stages）：`ingest`（deps: 数据源配置，outs: raw/）、`validate`（deps: raw/ + GE expectations/，outs: validation_report.html）、`preprocess`（deps: raw/ + params.yaml，outs: processed/）、`train`（deps: processed/ + params.yaml + src/training.py，outs: models/ + metrics.json）、`evaluate`（deps: models/ + processed/，metrics: metrics.json，plots: roc_curve.json + confusion_matrix.json）。
- **dvc/params.yaml** — 集中参数管理。示例内容：`train.batch_size: 32`、`train.learning_rate: 0.001`、`train.epochs: 50`、`data.train_split: 0.7`、`data.val_split: 0.15`、`data.test_split: 0.15`、`features.numerical: [age, income, ...]`、`features.categorical: [gender, region, ...]`、`evaluate.metric_primary: accuracy`、`evaluate.threshold: 0.85`。
- **mlflow/MLproject** — MLflow 项目文件。定义 conda 环境依赖和入口点，如 `main` 入口运行完整流水线、`train` 入口仅运行训练、`evaluate` 入口仅评估已有模型。参数声明示例：`learning_rate: {type: float, default: 0.001}`、`batch_size: {type: int, default: 32}`。
- **great_expectations/** — 数据验证套件。`great_expectations.yml` 配置数据源（Pandas/Spark/SQL）、Checkpoint Store 和 Data Docs 托管位置。期望规则 JSON 文件按类型分组：列类型检查（如 `expect_column_values_to_be_of_type`）、列范围检查（如 `expect_column_values_to_be_between`）、非空检查（如 `expect_column_values_to_not_be_null`）、唯一性检查（如 `expect_column_values_to_be_unique`）、表级检查（如 `expect_table_row_count_to_be_between`、`expect_table_column_count_to_equal`）、跨表检查（如 `expect_column_values_to_be_in_set` 引用维表）。
- **src/data_ingestion.py** — 数据摄取模块。从配置文件读取数据源（CSV/Parquet 本地路径、数据库连接、HTTP API），下载或读取原始数据，写入统一格式（Parquet 推荐）到暂存目录，记录数据统计信息（行数、列数、文件大小）到日志。
- **src/preprocessing.py** — 数据预处理模块。执行缺失值填充（均值/中位数/众数/自定义策略）、类别特征编码（One-Hot/Label/Target Encoding）、数值特征缩放（StandardScaler/MinMaxScaler）、数据集划分（train/val/test 随机分层分割）、输出处理后的 Parquet 文件。
- **src/training.py** — 模型训练模块。使用 MLflow `start_run()` 上下文管理器，通过 `mlflow.log_params()` 记录超参数、`mlflow.log_metrics()` 记录训练过程指标（每 epoch 的 loss/accuracy）、`mlflow.log_model()` 保存最终模型（含签名和输入示例）、`mlflow.log_artifact()` 保存训练曲线图和特征重要性图。
- **src/evaluation.py** — 模型评估模块。在测试集上计算评估指标（准确率、精确率、召回率、F1、AUC-ROC），生成并保存混淆矩阵和 ROC 曲线图，与当前生产模型指标对比（如有），计算指标变化百分比，输出评估报告。
- **tests/test_pipeline.py** — 流水线集成测试。验证：Airflow DAG 定义加载成功且无循环依赖；DVC 流水线每阶段的 `deps` 文件存在、`outs` 目录可写入；GE Checkpoint 可成功运行；MLflow 运行结束后可在 Tracking Server 查询到；端到端运行完整流水线并验证最终模型产物。

---

## 附加说明

**数据验证期望规则最低要求（13 条）：**

| 编号 | 类别 | 规则描述 |
|------|------|----------|
| GE-01 | 列类型 | 验证 `age` 列为整数类型 |
| GE-02 | 列类型 | 验证 `income` 列为浮点数类型 |
| GE-03 | 列类型 | 验证 `category` 列为字符串类型 |
| GE-04 | 列范围 | 验证 `age` 取值在 0-120 之间 |
| GE-05 | 列范围 | 验证 `income` 取值非负 |
| GE-06 | 列范围 | 验证 `gender` 列值属于 {M, F, Other} 集合 |
| GE-07 | 非空 | 验证 `user_id` 列无空值 |
| GE-08 | 非空 | 验证 `timestamp` 列无空值 |
| GE-09 | 唯一性 | 验证 `user_id` 列值唯一 |
| GE-10 | 表级 | 验证数据表行数在 1000-1000000 之间 |
| GE-11 | 表级 | 验证数据表列数等于预期值 |
| GE-12 | 表级 | 验证 `user_id` 为主键（非空 + 唯一） |
| GE-13 | 跨表 | 验证 `user_id` 值均存在于用户维表中（引用完整性） |
