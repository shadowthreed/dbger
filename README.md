## 简介
1. 本项目是简单的嵌入式日志输出管理模块；
2. 可以通过`MCU Uart`或者是`JLink RTT`输出日志；
3. 可以配置日志输出级别；

## 使用说明
1. 如果是通过`Uart`输出日志，通过`CubeMX`生成工程代码时，在`Project Manager --> Advanced Settings`中，在日志串口相应的初始化函数`MX_USARTx_UART_Init`后面的`Do Not Generate Function Call`打勾；
2. 通过`git submodule add https://github.com/ShadowThree/dbger.git ThirdUtils/dbger`添加本项目到工程指定目录；
3. 配置`dbger.h`；
4. 在`main.c`中调用：
```c
#include "dbger.h"

int main(void)
{
    // ...
    LOG_INIT();
    LOG_DBG("dbger test\n");
    // ...
}
```