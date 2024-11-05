# Boost Beast HTTP 服务器

该项目使用Boost Beast库实现了一个简单的异步HTTP服务器。服务器能够处理基本的HTTP GET和POST请求，并返回请求计数或当前时间。

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
   git clone https://github.com/Xushi8/beast-websocket.git
   cd beast-http
   ```

2. **安装Boost**，请参考网站上的说明进行操作。本项目依赖的 asio 和 beast 组件均为 header-only 的库，因此直接将 Boost 源码的 include 文件夹设置到环境变量即可，无需编译。

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


## 项目依赖

本项目依赖以下开源库：

- [Boost Beast](https://www.boost.org/doc/libs/release/libs/beast/doc/html/index.html)：用于实现HTTP和WebSocket协议的C++库。
- [fmt](https://fmt.dev/latest/index.html)：一个现代的C++格式化库。
- [spdlog](https://github.com/gabime/spdlog)：一个快速、简单的C++日志库。
