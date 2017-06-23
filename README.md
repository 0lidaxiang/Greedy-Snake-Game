# Greedy-Snake-Game
> Author : 大祥  
> StartTime: 2017-06-23 ，ModifyTime：2017-06-24

This is a homework of Operating Systems in 2016 at NTUST and using C++ to practive threads, ASNI, curses library in Linux enviroment.

## 预备
### 开发与运行环境:
development eviriment is Ubuntu 16.04 LTS (Xenial Xerus)  

### 编译命令:
```
$ g++ -std=c++11 greedy-snake-game.cpp -lcurses -lpthread -o gsg.o
```

如果提示或遇到 `curses.h: No such file or directory Problem`，则需要安装 curse 库。
If you use Ubuntu, you can excute this command :
```
$ sudo apt-get install libncurses5-dev libncursesw5-dev
```
If you use Fedora 25, you can excute this command :
```
$ dnf install ncurses-devel ncurses
```

### 执行命令:
当然已经上传了该文件,所以应该可以直接执行以下一条命令,而不需要编译过程。
```
$ ./gsg.o
```

## 操作说明
'#' 代表不能吃的石头，'@' 代表可以吃的苹果。

SPACE:空格键开始游戏。  
H:当横向移动时向上拐弯。  
N:当横向移动时向下拐弯。  
B:当纵向移动时向左拐弯。  
M:当纵向移动时向右拐弯。  
A:贪吃蛇加速,小心不要加太多奥。按键一次是加速一倍。  
S:贪吃蛇减速,最低限是3秒钟移动一次。按键一次是减速一倍。  
P:暂停游戏。  
ESC:正常状态下用户自己操作退出游戏,并计算得分。  

## 程式说明
1.只有一个文件。主函数在最后。里面重要的函数都会有写注解。其他浅显易懂的意思都是函数名的意思。

2.每次吃掉苹果后,得分加1,而且会重新产生新的三个石头和一个苹果。

**3.重要的 function 和 variable:**  
struct stone 产生石头。  
struct apple 产生苹果。  
struct snakeObj 产生贪吃蛇。  
start() 功能是启动游戏,让游戏从静止 state 恢复到开始游戏state 。  
draw() 功能是画出文字图。  
moveNormal() 功能是保持上一次移动状态,正常移动。  
keysInputHandle() 功能是处理主要的键盘事件。  
initSnake() 功能是初始化贪吃蛇的 data。  
main() 用 STL 里的 thread 产生两个子 thread,绑定到 draw() 和 keysInputHandle()。  
