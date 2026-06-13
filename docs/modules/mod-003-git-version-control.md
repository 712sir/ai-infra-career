# 模块 003 — Git 版本控制与协作

> **时长**: 10 小时 | **难度**: 入门 | **前置知识**: 基本的命令行操作能力

---

## 模块概述

版本控制是现代软件工程中不可或缺的技能。本模块从 Git 的核心概念出发，带你掌握分布式版本控制的工作方式、团队协作的最佳流程，以及 Git 进阶操作和 GitHub 平台的使用。无论你是独立开发还是团队协作，本模块都将为你建立专业、高效的版本控制习惯。

---

## 主题分解

### 1. Git 基础（3小时）

- **仓库初始化与管理**: git init 创建仓库、git clone 克隆远程仓库、.gitignore 忽略规则的设计与维护、git config 全局与本地配置
- **Commit 与历史**: 工作区 / 暂存区 / 仓库的三角模型，git add / git commit 的精细操作，git log / git show / git diff 的历史回溯，编写高质量的 commit message（Conventional Commits 规范）
- **分支与合并**: git branch 创建与管理分支，git checkout / git switch 切换分支，git merge 合并操作与 fast-forward 策略，分支命名规范与分支策略（Git Flow / GitHub Flow）
- **远程仓库**: git remote 管理远程连接，git push / git fetch / git pull 的差异与正确使用，git push --force-with-lease 的安全强制推送，upstream 分支的追踪关系

### 2. 协作工作流（3小时）

- **Pull Request 与 Code Review**: PR 的创建、描述模板与最佳实践，Code Review 的流程与评论规范，PR 的状态管理与自动化检查（CI 集成）
- **合并策略**: merge commit、squash merge、rebase merge 三种合并方式的对比与适用场景，保护分支（protected branch）的配置
- **冲突解决**: merge conflict 的产生机制与解决步骤，git mergetool 可视化辅助工具，预防冲突的协作策略
- **Git Hooks**: 客户端 hooks（pre-commit、commit-msg、pre-push）的编写与使用，使用 husky / pre-commit 框架管理 hooks，服务端 hooks 的工作方式

### 3. Git 进阶（2小时）

- **git rebase 交互式变基**: rebase 的原理与黄金法则，交互式 rebase（-i）的 squash / reword / edit / drop 操作，rebase vs merge 的争议与选择指南
- **git cherry-pick**: 跨分支选择性提交，cherry-pick 工作流程与冲突处理
- **stash 与 clean**: git stash push / pop / apply / list 暂存工作区的变更，git clean 清理未跟踪文件
- **git bisect 调试**: 二分法快速定位引入 Bug 的提交，bisect 的自动化脚本集成
- **子模块（submodules）**: 子模块的添加、更新与克隆，subtree 替代方案对比，多仓库管理的策略选择

### 4. GitHub 工作流（2小时）

- **Issue 跟踪**: Issue 的创建与模板使用，Label / Milestone / Assignee 的项目管理功能，Issue 与 PR 的关联引用
- **项目管理**: GitHub Projects 看板的使用，自动化工作流的配置，项目进度追踪与可视化
- **GitHub Actions 入门**: CI/CD 的核心概念，Workflow YAML 文件的基本语法，常见的自动化场景（测试、构建、部署），市场 Actions 的查找与使用
- **文档规范**: README.md 的结构化编写、CONTRIBUTING.md 协作指南、CHANGELOG.md 版本变更记录、CODEOWNERS 代码审核人配置

---

## 学习目标

完成本模块后，你应当能够：

1. 专业地使用 Git 进行版本控制，管理代码的历史与分支
2. 在团队中高效协作，通过 Pull Request 与 Code Review 保证代码质量
3. 熟练使用 rebase、cherry-pick、stash 等进阶操作解决复杂场景
4. 利用 GitHub Issues、Projects 和 Actions 管理软件项目
5. 编写规范的项目文档，建立良好的开源协作文化

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/01-git-basics.md` | 讲义 | Git 基础（仓库、提交、分支、远程） |
| `lecture-notes/02-collaboration-workflow.md` | 讲义 | 协作工作流（PR、Code Review、冲突解决、Hooks） |
| `lecture-notes/03-git-advanced.md` | 讲义 | Git 进阶（rebase、cherry-pick、stash、bisect、submodules） |
| `lecture-notes/04-github-workflow.md` | 讲义 | GitHub 工作流（Issue、Projects、Actions） |
| `lecture-notes/05-documentation-standards.md` | 讲义 | 项目文档规范 |
| `exercises/01-git-basics.md` | 练习 | Git 基础操作练习 |
| `exercises/02-commits-and-history.md` | 练习 | 提交与历史管理练习 |
| `exercises/03-branching-and-merging.md` | 练习 | 分支与合并练习 |
| `exercises/04-remote-collaboration.md` | 练习 | 远程协作练习 |
| `exercises/05-conflict-resolution.md` | 练习 | 冲突解决练习 |
| `exercises/06-git-advanced.md` | 练习 | Git 进阶操作练习 |
| `exercises/07-github-workflow.md` | 练习 | GitHub 工作流练习 |
| `exercises/08-integration-project.md` | 练习 | 综合项目：模拟团队 Git 协作流程 |
| `quizzes/module-003-quiz.md` | 测验 | 模块 003 知识检测测验 |
| `resources.md` | 资源 | 推荐阅读、Git Cheat Sheet 与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 002 — Linux 系统管理基础](./mod-002-linux-essentials.md)（推荐）
- **后续**: [模块 007 — API 与 Web 服务开发](./mod-007-apis-web-services.md)、[模块 004 — 机器学习基础](./mod-004-ml-basics.md)
