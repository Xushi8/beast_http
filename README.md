
# Boost Beast HTTP 服务器

本项目实现了一个简单的异步 HTTP 服务器，基于 Boost Beast 库构建。服务器支持处理 HTTP GET 和 POST 请求，并能够返回请求计数或当前时间等信息。

## 目标

异步操作能够显著提升高并发场景下的性能。然而，异步编程本身通常较为复杂且容易出错。因此，本项目提供了一个基于 Boost Asio 和 Beast 库的 Reactor 异步框架实现的最小 HTTP 服务器示例，旨在帮助开发者理解 C++ 中的异步操作。由于 C++ 需要自己管理内存，而异步代码分配和释放内存的时机是分开的，极其容易出现内存泄露或者访问野指针的情况，因此本项目提供一个基于 shared_ptr 的内存安全的示例。通过使用 C++ 的 Lambda 表达式，我们可以以接近同步的方式编写异步代码，从而在不牺牲可读性的前提下提升性能。该方法几乎不产生任何额外开销，仅有的代价是少数几次函数调用以及原子变量的加减，每次切换的时间在几十纳秒左右。

## 特性

- 支持 HTTP GET 和 POST 请求。
- 提供以下两个端点：
  - `/count`：返回服务器接收到的请求总数。
  - `/time`：返回自纪元以来的当前时间（单位：纳秒）。
- 使用 Boost 的异步 I/O 实现高效的连接处理。
- 实现了请求计数和客户端超时机制。

## 前置条件

在构建并运行服务器之前，请确保您已经安装了以下依赖：

- 支持 C++20 的编译器
- [Boost](https://www.boost.org/) 库（版本 1.70 或更高）
- [CMake](https://cmake.org/)（用于构建项目）
- 可选：[Ninja](https://ninja-build.org/)（跨平台构建系统，性能优越）

## 构建项目

1. **克隆代码库**：

   ```bash
   git clone https://github.com/Xushi8/beast-http.git
   cd beast-http
   ```

2. **安装 Boost**：按照 Boost 官网的安装说明进行操作。由于本项目使用的 Asio 和 Beast 组件是 header-only 库，因此只需将 Boost 源码中的 `include` 文件夹以及 CMake 相关文件配置到环境变量中，无需编译。

3. **使用 CMake 构建项目**：

   ```bash
   cmake -B build -G Ninja
   cmake --build build
   ```

## 运行服务器

构建完成后，使用以下命令运行服务器：

```bash
./build/bin/main
```

服务器将默认监听端口（可在代码中调整端口号，默认是 9999）。

## 使用方法

### 端点说明

- **GET `/count`**：返回一个包含请求总数的 HTML 响应。
- **GET `/time`**：返回自纪元以来当前时间的 HTML 响应。
- **其他请求**：返回 404 未找到响应。

### 示例用法

您可以使用 `curl` 命令测试服务器：

```bash
# 获取请求计数
curl http://localhost:port/count

# 获取当前时间
curl http://localhost:port/time
```

当然也可以直接使用浏览器访问这些地址。

## 实现细节

### 关键类与函数

- **http_connection**：管理单个 HTTP 连接，处理请求读取、请求处理和响应发送。
- **request_count()**：静态函数，利用原子计数器跟踪服务器接收到的请求数量。
- **now()**：返回当前时间。
- **check_deadline()**：实现截止时间定时器，用于关闭空闲连接。

### 异步行为

服务器利用 Boost 的异步 I/O 实现并发处理多个连接，避免了阻塞操作。读取请求和写入响应的核心函数（`async_read` 和 `async_write`）都是异步执行的，从而使服务器能够在等待 I/O 操作完成时继续处理其他连接。

## 缺陷与待办事项

尽管使用 Lambda 表达式的异步调用提高了性能并尽可能避免了回调地狱问题，依然存在一定的可读性问题，尤其是在调用层级较深时。此外，异步调用需要通过 `shared_ptr` 延长对象的生命周期，这会带来原子计数加减的开销。

C++20 的协程可以更好地解决这些问题，能够以同步的形式编写异步代码。由于 C++ 使用的是无栈协程，相比 Go 的有栈协程，跳转速度要快得多，约有 2-3 个数量级的性能提升。因此，本项目计划在将来实现协程的示例。

## 项目依赖

本项目依赖以下开源库：

- [Boost Beast](https://www.boost.org/doc/libs/release/libs/beast/doc/html/index.html)：一个用于实现 HTTP 和 WebSocket 协议的 C++ 库。
- [fmt](https://fmt.dev/latest/index.html)：一个现代 C++ 格式化库。
- [spdlog](https://github.com/gabime/spdlog)：一个快速、简单的 C++ 日志库。