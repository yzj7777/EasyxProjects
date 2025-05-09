# EasyX 游戏项目 (Project1)

这是一个使用 EasyX 图形库和 C++ 开发的简单 2D 游戏项目。

## 游戏描述

这是一款基础的 2D 游戏，玩家控制一个角色在窗口内移动，躲避不断生成的敌人。游戏中包含简单的动画、碰撞检测和得分系统。游戏开始时会显示一个菜单，包含开始游戏和退出游戏的选项。

## 控制方式
切换英文输入法
*   **W:** 向上移动
*   **S:** 向下移动
*   **A:** 向左移动
*   **D:** 向右移动


## 主要功能

*   **玩家控制:** 使用键盘控制角色在屏幕上移动。
*   **敌人生成:** 敌人会周期性地在屏幕上生成。
*   **敌人行为:** 敌人会朝着玩家的方向移动。
*   **碰撞检测:**
    *   玩家与敌人碰撞会导致游戏结束。
    *   子弹与敌人碰撞会消灭敌人并增加分数。
*   **得分系统:** 实时显示玩家得分。
*   **动画效果:** 玩家和敌人具有简单的移动动画。
*   **音效:** 包含背景音乐和击中音效。
*   **菜单系统:** 提供开始游戏和退出游戏的选项。

## 如何构建和运行

### 依赖项

*   **Visual Studio:** 需要安装 Visual Studio2022
*   **EasyX 图形库:** 需要安装 EasyX 图形库并正确配置到 Visual Studio 项目中。请访问 [EasyX 官网](https://easyx.cn/) 获取安装说明。

## 注意

*   确保 EasyX 库已正确安装并配置在 Visual Studio 环境中。
*   资源文件（图片、音乐）需要位于 `res` 目录下，或者根据代码中的路径进行调整。
