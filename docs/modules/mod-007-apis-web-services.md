# 模块 007 — API 与 Web 服务开发

> **时长**: 15 小时 | **难度**: 入门 | **前置知识**: Python 编程基础（模块 001 必备）

---

## 模块概述

API 是 AI 基础设施中连接模型与外部世界的桥梁。本模块从 REST API 的设计原理出发，覆盖 FastAPI 和 Flask 两大主流 Python Web 框架的使用，并讲解 API 的认证、测试与文档化方法。学完本模块后，你将能够构建生产级的模型推理 API 服务。

---

## 主题分解

### 1. REST API 基础（3小时）

- **HTTP 方法与状态码**: GET / POST / PUT / PATCH / DELETE 的语义与幂等性，2xx（成功）/ 3xx（重定向）/ 4xx（客户端错误）/ 5xx（服务端错误）状态码的正确选用，自定义错误响应的结构化设计
- **API 设计原则**: 资源导向的 URL 设计（名词复数、层级关系、避免动词），请求与响应体的 JSON 格式规范，分页、过滤与排序的标准化实践（offset/limit、cursor-based pagination），API 版本管理策略（URL 前缀 vs Header vs Query 参数）
- **认证与授权**: HTTP Basic Auth 的原理与局限性，Bearer Token（JWT）的结构（Header / Payload / Signature）与签发验证流程，API Key 的管理方式，OAuth 2.0 授权码流程的概念（Authorization Code / Client Credentials），RBAC 基于角色的访问控制
- **限流（Rate Limiting）**: 令牌桶（Token Bucket）与漏桶（Leaky Bucket）算法原理，固定窗口与滑动窗口计数器的差异，限流响应头（X-RateLimit-*）的标准实践，防止滥用与 DDoS 的基础策略

### 2. FastAPI 框架（6小时）

- **路由**: 路径操作装饰器（@app.get / @app.post / @app.put / @app.delete），路径参数与查询参数的类型声明、校验与默认值，路由分组与 APIRouter 的模块化组织，路径操作的排序与优先级
- **Pydantic 请求/响应模型**: BaseModel 的数据验证与序列化，Field 的详细约束（min_length / max_length / gt / lt / regex），嵌套模型的组合与复用（List / Optional / Union），response_model 的响应过滤与 exclude/include 控制
- **依赖注入（Dependency Injection）**: Depends() 的声明方式，依赖的复用与链式调用，数据库连接、认证用户、配置对象等常见依赖场景，全局依赖（app.dependency_overrides）与测试 mock
- **异步支持**: async def 与 def 路由的差异与选择，async 数据库驱动（asyncpg / Motor），并发请求处理与线程池（run_in_executor），异步后台任务（BackgroundTasks 与 Celery）
- **OpenAPI 文档**: 自动生成的 Swagger UI（/docs）与 ReDoc（/redoc），文档的自定义（title / description / tags / examples），响应模型驱动的 Schema 自动生成，额外的 OpenAPI 元数据配置

### 3. Flask 框架（3小时）

- **Flask vs FastAPI 选择**: Flask 的同步生态与成熟稳定优势（SQLAlchemy / Flask-Login / Flask-Admin），FastAPI 的异步性能与自动文档优势，框架选择决策树
- **路由与视图**: @app.route() 的 URL 规则与变量规则（<int:id> / <string:name>），视图函数的请求对象（request）与响应对象（make_response / jsonify），蓝图（Blueprint）的模块化组织
- **请求处理**: 查询参数（request.args）、表单数据（request.form）、JSON 请求体（request.get_json()）的获取，文件上传（request.files）的处理方式，请求钩子（before_request / after_request / teardown_request）
- **Flask 扩展**: Flask-SQLAlchemy 数据库集成，Flask-Migrate 数据库迁移，Flask-JWT-Extended 身份认证，Flask-CORS 跨域支持，Flask-Limiter 限流配置

### 4. API 测试（3小时）

- **pytest 单元测试**: 测试客户端（TestClient / app.test_client()）的使用，fixture 创建测试数据与数据库状态，依赖 mock（dependency_overrides），状态码、响应体、响应头的全面断言
- **集成测试**: 数据库测试的事务回滚策略（每个测试独立隔离），外部服务 mock（httpretty / responses / WireMock），端到端测试的测试环境构建
- **locust 负载测试**: 用户行为脚本（HttpUser / task）的编写，并发用户数与孵化率（spawn rate）的配置，报表分析（请求成功率、响应时间分布、RPS），性能瓶颈的识别
- **API 文档生成**: OpenAPI 规范的自动生成（FastAPI 内置 / Flask + apispec），Postman Collection 的导出与团队协作，API 变更的版本化文档管理

---

## 学习目标

完成本模块后，你应当能够：

1. 设计符合 RESTful 规范、语义清晰的 API 接口
2. 使用 FastAPI 构建高性能的异步 API 服务
3. 使用 Flask 构建稳定可靠的传统 Web 服务
4. 实现 JWT、API Key 等常见的 API 认证与授权机制
5. 编写完整的 API 单元测试、集成测试和负载测试
6. 自动生成并维护专业的 API 文档

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/01-rest-api-fundamentals.md` | 讲义 | REST API 基础（HTTP、设计原则、认证、限流） |
| `lecture-notes/02-fastapi-basics.md` | 讲义 | FastAPI 基础（路由、Pydantic 模型） |
| `lecture-notes/03-fastapi-advanced.md` | 讲义 | FastAPI 进阶（依赖注入、异步、文档） |
| `lecture-notes/04-flask-framework.md` | 讲义 | Flask 框架（Flask vs FastAPI、路由、请求处理、扩展） |
| `lecture-notes/05-api-testing.md` | 讲义 | API 测试（pytest、集成测试、负载测试、文档生成） |
| `exercises/01-rest-api-design.md` | 练习 | REST API 设计练习 |
| `exercises/02-fastapi-crud.md` | 练习 | FastAPI CRUD 服务构建练习 |
| `exercises/03-fastapi-auth.md` | 练习 | FastAPI 认证与授权练习 |
| `exercises/04-flask-app.md` | 练习 | Flask 应用构建练习 |
| `exercises/05-api-testing.md` | 练习 | API 自动化测试练习 |
| `exercises/06-mini-project.md` | 练习 | 综合项目：构建 ML 模型推理 API 服务 |
| `quizzes/quiz-01-apis-web-services.md` | 测验 | 模块 007 知识检测测验 |
| `resources.md` | 资源 | 推荐阅读、API 设计规范与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 001 — Python 基础设施编程基础](./mod-001-python-fundamentals.md)、[模块 004 — 机器学习基础](./mod-004-ml-basics.md)
- **后续**: [模块 008 — 数据库与 SQL](./mod-008-databases-sql.md)、[模块 009 — 监控与日志基础](./mod-009-monitoring-basics.md)
