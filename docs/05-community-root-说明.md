# 05 - Community（社区）与根目录配置文件说明

## 目录概览

本文档涵盖两个方面的内容：(1) `community/` 目录——社区协作与交流板块；(2) 项目根目录下的关键配置文件——定义项目规范、技术约束和协作流程。两者共同构成了本学习项目的"软环境"与"硬规则"。

---

## 第一部分：Community（社区）— `community/`

社区是学习者的协作空间。AI Infra 学习不仅有技术难度，更需要同伴互助、导师指引和经验分享。社区板块提供了提问、组队、答疑的完整渠道。

### 社区文件清单

| 文件名 | 内容简介 |
|---|---|
| `README.md` | **社区板块总览与参与指南**：介绍社区的组织结构（学习小组、答疑办公室、讨论区）、社区礼仪与行为期望、如何从"提问者"逐步成长为"回答者"、贡献者荣誉体系与积分规则 |
| `FAQ.md` | **常见问题解答**：按主题分为四大类——<br> (1) **环境配置**：Python 版本选择、虚拟环境搭建、Docker 安装问题、GPU 驱动配置<br> (2) **学习路线**：能不能跳课？能不能按自己的兴趣重新排序？全职 vs 在职学习建议<br> (3) **项目提交**：作业提交流程、迟交政策、代码抄袭判定标准<br> (4) **技术支持**：遇到报错怎么办？如何正确提 Issue？在哪里获取实时帮助？ |
| `office-hours.md` | **答疑时间安排与预约方式**：列出社区维护者和导师的每周固定答疑时段（含时区对照表）、预约流程（通过 GitHub Discussion 提前提交问题）、答疑形式（文字 + 语音 + 屏幕共享）、以及"紧急问题"的快速通道说明 |
| `study-groups.md` | **学习小组组建指南**：包含四个板块——<br> (1) **如何找到伙伴**：按时区/语言/学习进度匹配队友<br> (2) **协作方式**：推荐的协作工具（GitHub Projects、Discord、飞书/钉钉）、例会频率建议、分工模式<br> (3) **小组任务模版**：代码互审流程、结对编程指南、小组项目选题建议<br> (4) **成功案例**：往期优秀学习小组的经验分享与成果展示 |

---

## 第二部分：根目录配置文件

根目录下的配置文件定义了项目的技术规范、行为准则、协作流程和课程蓝图。无论是学习者还是贡献者，在参与项目前都应了解这些文件的用途。

### 技术规范类

| 文件名 | 内容简介 |
|---|---|
| `.gitignore` | **Git 忽略规则**：定义了不应纳入版本控制的文件与目录，包括——Python 虚拟环境（`venv/`、`.venv/`、`__pycache__/`）、IDE 配置文件（`.vscode/`、`.idea/`）、敏感信息文件（`.env`、`*.key`、`credentials.json`）、DVC 数据缓存（`.dvc/cache/`）、Jupyter Notebook 检查点（`.ipynb_checkpoints/`）、操作系统临时文件 |
| `.markdownlint.jsonc` | **Markdown 格式检查规则配置**：基于 markdownlint 工具的自定义规则集，针对教育类文档的特殊需求做了定制，例如——放宽行长度限制（MD013 设为 120 字符）、允许重复标题（MD024 在必要时豁免）、禁止内联 HTML（MD033 开启以保持文档的纯 Markdown 可移植性）、以及其他文档质量规则的启用/禁用与参数调整 |
| `requirements.txt` | **Python 依赖包清单**：列出了所有 Module 中会用到的核心 Python 包及其推荐版本范围，包括——Web 框架（fastapi、uvicorn）、机器学习（torch、tensorflow、scikit-learn）、数据处理（pandas、numpy）、MLOps（mlflow、bentoml）、数据库驱动（psycopg2、redis）、监控客户端（prometheus-client）、测试框架（pytest、httpx）等。建议使用虚拟环境安装：`python -m venv venv && pip install -r requirements.txt` |
| `VERSIONS.md` | **技术版本指南**：为课程中涉及的所有技术栈提供推荐的版本范围与兼容性说明，包括——Python（3.10+）、Docker（24.x+）、Kubernetes（1.28+）、ML 框架（PyTorch 2.x、TensorFlow 2.x）、监控工具（Prometheus 2.x、Grafana 10.x）。同时标注了各版本之间的已知兼容性问题与规避方案 |

### 协作规范类

| 文件名 | 内容简介 |
|---|---|
| `CODE_OF_CONDUCT.md` | **社区行为准则**：基于 Contributor Covenant 2.1 版本，定义了社区中不可接受的行为（骚扰、歧视、人身攻击）、举报与处理流程、以及维护者的执行责任。所有参与者（学习者、导师、贡献者、访客）均须遵守 |
| `CONTRIBUTING.md` | **贡献指南**：为想要改进课程内容、修复错误、添加资源的贡献者提供完整流程指引——<br> (1) Issue 提交规范（Bug 报告模板、功能建议模板、内容修正模板）<br> (2) Pull Request 流程（Fork → 创建特性分支 → 编写清晰 Commit Message → 提交 PR → 等待 Review）<br> (3) 代码规范（Python 代码遵循 PEP 8、YAML 缩进使用 2 空格、Markdown 通过 markdownlint 检查）<br> (4) 文档规范（中文文档使用全角标点、代码块标注语言类型、章节标题层级不超过三级） |
| `LICENSE` | **MIT 开源许可证全文**：明确声明项目的许可条款，允许自由使用、复制、修改、分发，但需保留原始版权声明。MIT 许可证的选择意味着学习者可以将本课程的项目代码用于任何目的，包括商业用途 |

### 课程规划类

| 文件名 | 内容简介 |
|---|---|
| `BUILD_ROADMAP.md` | **构建路线图**：可视化追踪各 Module 的开发与完善状态（Planning / In Progress / Review / Done / Published），附 Sprint 计划模板（每 Sprint 2 周）、质量检查清单（内容准确性审核、代码示例验证、链接有效性检查），以及社区贡献者的任务认领板 |
| `CURRICULUM.md` | **完整课程大纲**：每个 Module 的详细主题分解——学习目标、核心知识点列表、配套练习项目拆解（每个项目包含：功能描述、技术要点、预计耗时、可交付物清单）、评分策略（自动评分脚本 vs 人工评审的分配）、以及与职业岗位技能的映射关系（每个模块对应哪些 JD 中的关键词） |
| `CURRICULUM_INDEX.md` | **课程索引**：快速导航工具——<br> (1) **学习路径图**：一张可视化的技能树，展示 10 个 Module 之间的依赖关系和推荐学习顺序<br> (2) **进度追踪清单**：可打印的 Checklist，供学习者逐项打勾<br> (3) **技能检查表**：按"入门/熟练/精通"三级自评，帮助学习者在每个阶段确认自己的水平<br> (4) **快速索引**：按主题关键词（如"容器""监控""模型部署"）快速跳转到对应的 Module 和文件 |

### 项目入口

| 文件名 | 内容简介 |
|---|---|
| `README.md` | **项目主页**：面向新访客的综合介绍页——<br> (1) **学习目标**：本课程完成后你将具备什么能力（独立搭建 ML 推理服务、容器化部署、基础监控体系、CI/CD Pipeline）<br> (2) **课程概览**：10 个 Module 的目录与简介<br> (3) **快速开始**：三步起步指南（克隆仓库 → 安装依赖 → 阅读 CURRICULUM_INDEX.md 开始学习）<br> (4) **技术栈总览**：一张图展示课程涵盖的所有技术及其关系<br> (5) **职业发展**：完成课程后的岗位方向（ML Infra Engineer / MLOps Engineer / AI Platform Engineer）及对应薪资参考 |

---

## 新学员入门路线图

如果你是刚加入的学员，建议按以下顺序了解项目：

```
README.md ──→ CURRICULUM_INDEX.md ──→ community/FAQ.md
    │                                        │
    ├──→ requirements.txt                     ├──→ community/office-hours.md
    ├──→ VERSIONS.md                          └──→ community/study-groups.md
    ├──→ CURRICULUM.md
    └──→ CONTRIBUTING.md
```

1. 从 `README.md` 了解项目全貌
2. 通过 `CURRICULUM_INDEX.md` 快速定位想要开始学习的模块
3. 使用 `requirements.txt` 和 `VERSIONS.md` 搭建本地开发环境
4. 阅读 `community/FAQ.md` 了解常见问题的答案
5. 加入学习小组（参考 `community/study-groups.md`）或预约答疑（参考 `community/office-hours.md`）
6. 当你想要贡献改进时，参考 `CONTRIBUTING.md` 和 `BUILD_ROADMAP.md`

---

> **提示**：根目录配置文件不仅定义了规则，更是项目运作的"说明书"。在提交第一个 Issue 或 PR 之前，请务必阅读 `CONTRIBUTING.md` 和 `CODE_OF_CONDUCT.md`。良好的社区氛围需要每一位成员共同维护。
