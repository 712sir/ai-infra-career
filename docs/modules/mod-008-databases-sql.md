# 模块 008 — 数据库与 SQL

> **时长**: 15 小时 | **难度**: 入门 | **前置知识**: Python 编程基础（模块 001 推荐）

---

## 模块概述

数据库是 AI 基础设施中数据持久化和管理的核心组件。本模块从 SQL 语言基础出发，深入 PostgreSQL 的关系数据库实战，兼顾 MongoDB、Redis 等 NoSQL 技术的应用场景，最后讲解 Python 生态中 ORM 和数据库迁移工具的使用。学完本模块后，你将能够为不同的业务场景选择合适的数据库技术并高效集成。

---

## 主题分解

### 1. SQL 基础（5小时）

- **SELECT 查询**: 基本查询结构（SELECT / FROM / WHERE），列别名（AS）与计算字段，DISTINCT 去重，LIKE 模糊匹配与通配符，BETWEEN / IN / IS NULL 条件过滤，ORDER BY 排序与 LIMIT / OFFSET 分页
- **JOIN 与聚合**: INNER JOIN / LEFT JOIN / RIGHT JOIN / FULL OUTER JOIN / CROSS JOIN 的连接类型与使用场景，自连接（Self Join）的高级用法，GROUP BY 分组聚合，聚合函数（COUNT / SUM / AVG / MIN / MAX），HAVING 对分组结果的过滤，子查询与 CTE（Common Table Expression）
- **索引与优化**: B-Tree / Hash / GIN / GiST 索引类型与选择，单列索引与复合索引（联合索引）的最左前缀原则，EXPLAIN / EXPLAIN ANALYZE 查询执行计划分析，慢查询的识别（pg_stat_statements）与优化策略，覆盖索引（Covering Index）与索引唯一扫描（Index Only Scan）
- **事务（Transaction）**: ACID（原子性 / 一致性 / 隔离性 / 持久性）的含义与重要性，BEGIN / COMMIT / ROLLBACK 的事务控制，隔离级别（READ UNCOMMITTED / READ COMMITTED / REPEATABLE READ / SERIALIZABLE）与并发问题（脏读 / 不可重复读 / 幻读），死锁的产生原因与预防

### 2. PostgreSQL 实战（5小时）

- **安装与配置**: 不同平台（Linux / macOS / Docker）的安装方式，postgresql.conf 核心配置参数（shared_buffers / work_mem / effective_cache_size），pg_hba.conf 客户端认证配置，常用扩展的安装（pg_stat_statements / pg_trgm / uuid-ossp）
- **数据库设计**: 范式化（1NF / 2NF / 3NF）与反范式化的平衡，主键（UUID vs Serial vs Identity）与外键约束的选用，CHECK / UNIQUE / NOT NULL 约束，表分区（Range / List / Hash Partitioning）在大数据场景的应用，物化视图（Materialized View）与普通视图的区别
- **性能调优**: VACUUM / ANALYZE / AUTOVACUUM 的机制与配置，连接池（PgBouncer / pgpool-II）的部署与参数优化，查询缓存的策略，读写分离与复制（Streaming Replication）的架构
- **备份与恢复**: pg_dump / pg_dumpall 的逻辑备份，pg_basebackup 的物理备份，WAL（Write-Ahead Log）与 PITR（Point-In-Time Recovery），备份的自动化脚本与保留策略

### 3. NoSQL 基础（3小时）

- **MongoDB 文档数据库**: 文档（JSON/BSON）模型与关系模型的对齐（Embedding vs Referencing），CRUD 操作（insertOne / find / updateOne / deleteOne），聚合管道（Aggregation Pipeline）的阶段操作（$match / $group / $project / $lookup），索引策略与查询优化
- **Redis 键值存储**: 核心数据结构（String / Hash / List / Set / Sorted Set / Stream）的使用场景，过期策略（TTL）与淘汰策略（LRU / LFU），持久化方式（RDB 快照 vs AOF 日志），缓存穿透 / 缓存击穿 / 缓存雪崩的防御方案
- **向量数据库**: 向量嵌入（Embedding）的存储概念，近似最近邻（ANN）搜索的原理，Milvus / Pinecone / pgvector 等方案的对比与选择，RAG（Retrieval-Augmented Generation）应用中向量数据库的角色
- **多模型持久化**: 为不同类型的查询选择合适的存储技术，CQRS（Command Query Responsibility Segregation）模式，数据同步与最终一致性的保障策略

### 4. Python 数据库集成（2小时）

- **SQLAlchemy ORM**: Engine 与 Session 的创建与配置，声明式模型（declarative_base / Mapped / mapped_column）的定义，关系的定义与查询（relationship / back_populates），Session 的事务管理与上下文使用
- **连接池**: QueuePool 的连接复用与管理，pool_size / max_overflow / pool_timeout 的参数调优，连接泄漏的检测与预防（pool_pre_ping），异步连接引擎（create_async_engine）的配置
- **Alembic 数据库迁移**: 迁移环境的初始化（alembic init），自动生成迁移脚本（--autogenerate），升级（upgrade）与回滚（downgrade）的操作，迁移脚本的手动修改注意事项，多分支迁移的历史管理
- **数据库测试**: 测试数据库的隔离策略（事务回滚 vs 模板数据库），pytest fixture 创建与销毁测试数据，Factory Boy / Faker 生成测试数据，集成测试中的数据库状态验证

---

## 学习目标

完成本模块后，你应当能够：

1. 编写高效、语义清晰的 SQL 查询语句
2. 设计与规范化关系数据库的表结构
3. 对查询性能进行分析、优化和调优
4. 选择合适的 NoSQL 技术（MongoDB / Redis / 向量数据库）
5. 在 Python 中使用 SQLAlchemy 进行数据库操作
6. 使用 Alembic 管理数据库 Schema 的版本迁移
7. 实施数据库的备份与恢复策略

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/01-sql-fundamentals.md` | 讲义 | SQL 基础（SELECT、过滤、排序、分页） |
| `lecture-notes/02-sql-joins-aggregation.md` | 讲义 | JOIN 与聚合查询 |
| `lecture-notes/03-indexes-and-optimization.md` | 讲义 | 索引与查询优化 |
| `lecture-notes/04-postgresql-practice.md` | 讲义 | PostgreSQL 实战（安装配置、数据库设计） |
| `lecture-notes/05-nosql-basics.md` | 讲义 | NoSQL 基础（MongoDB、Redis、向量数据库） |
| `lecture-notes/06-python-database-integration.md` | 讲义 | Python 数据库集成（SQLAlchemy、Alembic、连接池） |
| `exercises/01-sql-queries.md` | 练习 | SQL 查询练习 |
| `exercises/02-joins-aggregation.md` | 练习 | JOIN 与聚合练习 |
| `exercises/03-database-design.md` | 练习 | 数据库设计练习 |
| `exercises/04-sqlalchemy-orm.md` | 练习 | SQLAlchemy ORM 练习 |
| `exercises/05-integration-project.md` | 练习 | 综合项目：构建完整的数据持久层 |
| `quizzes/quiz-01-databases-sql.md` | 测验 | 模块 008 知识检测测验 |
| `resources.md` | 资源 | 推荐阅读、SQL 速查表与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 001 — Python 基础设施编程基础](./mod-001-python-fundamentals.md)、[模块 007 — API 与 Web 服务开发](./mod-007-apis-web-services.md)
- **后续**: [模块 009 — 监控与日志基础](./mod-009-monitoring-basics.md)
