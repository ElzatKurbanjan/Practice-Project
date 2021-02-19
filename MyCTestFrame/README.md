# My C Language Test Frame
## 一. 简单说明

本项目参考google测试框架实现了一个简单的c语言测试框架

用法可参考example.c文件



程序运行方式：

```bash
make run
```



## 二. TODO List

- 函数存储方式

可参考内核list实现一个通用链表list.c，采用链表形式存储所有的TEST函数

- test.h的拆分

根据功能，将test.h拆分成多个文件，要求模块分工清晰明确，同时对外提供test_api.h文件，其中只能包含开放给用户的接口

- 功能完善

目前只包含EXPECT系列函数，可扩充更丰富的测试函数系列

- README完善

代码足够完善后可更新README，增加一些效果展示