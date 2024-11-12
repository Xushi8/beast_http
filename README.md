# Boost Beast HTTP 服务器

该项目使用Boost Beast库实现了一个简单的异步HTTP服务器。服务器能够处理基本的HTTP GET和POST请求，并返回请求计数或当前时间。

## 目的
异步操作可以为高并发场景带来可观的性能提升，然而异步操作本身往往非常复杂、容易出错。因此本项目提供一个基于 Boost asio、beast 的 Reactor 异步框架的最小的 HTTP 服务器实现，便于理解 C++ 的异步操作。通过 C++ 的 Lambda 表达式，可以将异步操作的代码写成近似于同步操作，不牺牲可读性的情况下提升性能，且这种异步几乎为零成本开销，浪费的仅仅是几次函数调用的时间，一次切换大约在几十纳秒。

## 特性

- 支持HTTP GET和POST请求。
- 提供两个端点：
  - `/count`：返回服务器接收到的请求总数。
  - `/time`：返回自纪元以来的当前时间（以纳秒为单位）。
- 采用Boost的异步I/O实现高效的连接处理。
- 实现请求计数和客户端超时机制。

## 前置条件

在构建和运行服务器之前，请确保您已安装以下依赖项：

- 支持C++20的编译器
- [Boost](https://www.boost.org/) 库（版本1.70或更高）
- [CMake](https://cmake.org/) 用于构建
- [ninja](https://ninja-build.org/) 可选，跨平台的构建系统，性能优越

## 构建项目

1. **克隆代码库**：

   ```bash
   git clone https://github.com/Xushi8/beast-http.git
   cd beast-http
   ```

2. **安装Boost**，请参考网站上的说明进行操作。本项目依赖的 asio 和 beast 组件均为 header-only 的库，因此直接将 Boost 源码的 include 文件夹以及 Cmake 相关的文件设置到环境变量即可，无需编译。

3. **使用CMake构建项目**：

   ```bash
   cmake -B build -G Ninja
   cmake --build build
   ```

## 运行服务器

构建完成后，可以使用以下命令运行服务器：

```bash
./build/bin/main
```

服务器将监听默认端口（请在代码中调整以指定不同端口，默认是9999）。

## 使用方法

### 端点

- **GET `/count`**: 
  - 返回一个包含请求总数的HTML响应。
  
- **GET `/time`**: 
  - 返回一个显示自纪元以来当前时间的HTML响应。

- **任何其他请求**:
  - 返回404未找到响应。

### 示例用法

您可以使用 `curl` 测试服务器：

```bash
# 获取请求计数
curl http://localhost:port/count

# 获取当前时间
curl http://localhost:port/time
```

也可以直接使用浏览器访问该地址

## 实现细节

### 关键类和函数

- **http_connection**: 
  - 管理单个HTTP连接，处理读取请求、处理请求和发送响应。

- **request_count()**: 
  - 静态函数，使用原子计数器跟踪服务器接收到的请求数量。

- **now()**: 
  - 返回当前时间。

- **check_deadline()**: 
  - 实现截止时间定时器，用于关闭空闲连接。

### 异步行为

服务器利用Boost的异步I/O并发处理多个连接，避免阻塞。读取请求和写入响应的核心函数（`async_read` 和 `async_write`）异步执行，使得服务器可以在等待I/O操作完成时处理其他连接。


## 缺陷 & TODO

使用 Lambda 的异步调用虽然实现了性能上的提高以及尽可能避免了回调地狱，实现了可读性的尽可能保留。但是在调用层级较多的情况下依旧会造成嵌套过多导致可读性地下，且异步调用需要使用 `shared_ptr` 延长生命周期，每次执行异步操作都会有原子计数加减的开销。
C++20 的协程则可以完美地解决这些问题，真正地实现以同步的形式写异步代码。并且 C++ 使用的是无栈协程，相较于 go 的有栈协程速度会更快，对于协程的函数跳转方面大约有 2-3 个数量级的性能提升。


## 项目依赖

本项目依赖以下开源库：

- [Boost Beast](https://www.boost.org/doc/libs/release/libs/beast/doc/html/index.html)：用于实现HTTP和WebSocket协议的C++库。
- [fmt](https://fmt.dev/latest/index.html)：一个现代的C++格式化库。
- [spdlog](https://github.com/gabime/spdlog)：一个快速、简单的C++日志库。
