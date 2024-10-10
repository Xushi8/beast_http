#pragma once

#include <beast_http/common/common.hpp>
#include <cstddef>
#include <atomic>
#include <chrono>
#include <memory>
#include <boost/beast.hpp>
#include <beast_http/common/log.hpp>
#include <fmt/format.h>

BEAST_HTTP_BEGIN_NAMESPACE

size_t request_count()
{
    static std::atomic<size_t> cnt = 0;
    return cnt.fetch_add(1, std::memory_order_relaxed) + 1;
}

auto now()
{
    return std::chrono::system_clock::now();
}

struct http_connection : public std::enable_shared_from_this<http_connection>
{
    http_connection(boost::asio::ip::tcp::socket socket) :
        m_socket(std::move(socket))
    {
    }

    void start()
    {
        read_request();
        check_deadline();
    }

private:
    void read_request()
    {
        boost::beast::http::async_read(m_socket, m_buffer, m_request, [self = shared_from_this()](boost::system::error_code ec, size_t bytes_transferred [[maybe_unused]])
            {
                if (ec)
                {
                    spdlog::warn("read request failed, value: {}, message: {}", ec.value(), ec.message());
                    return;
                }

                self->process_request();
            });
    }

    void check_deadline()
    {
        m_deadline.async_wait([self = shared_from_this()](boost::system::error_code ec)
            {
                if (ec)
                {
                    if (ec.value() == boost::asio::error::operation_aborted)
                        return;
                    spdlog::warn("check_deadline failed, value: {}, message: {}", ec.value(), ec.message());
                    return;
                }

                spdlog::info("client timeout");
                ec = self->m_socket.close(ec);
                if (ec)
                {
                    spdlog::warn("check_deadline socket close failed, value: {}, message: {}", ec.value(), ec.message());
                    return;
                }
            });
    }

    void process_request()
    {
        m_response.version(m_request.version());
        m_response.keep_alive(false);
        switch (m_request.method())
        {
        case boost::beast::http::verb::get: [[fallthrough]];
        case boost::beast::http::verb::post:
            m_response.result(boost::beast::http::status::ok);
            m_response.set(boost::beast::http::field::server, "Beast");
            create_response();
            break;
        default:
            m_response.set(boost::beast::http::field::content_type, "text/plain");
            boost::beast::ostream(m_response.body()) << fmt::format("Invalid request-method '{}'", std::string_view(m_request.method_string()));
            break;
        }

        write_response();
    }

    void create_response()
    {
        if (m_request.target() == "/count")
        {
            m_response.set(boost::beast::http::field::content_type, "text/html");
            boost::beast::ostream(m_response.body())
                << "<html>\n"
                << "<head><title>Request count</title></head>\n"
                << "<body>\n"
                << "<h1>Request count</h1>\n"
                << "<p>There have been "
                << request_count()
                << " requests so far.</p>\n"
                << "</body>\n"
                << "</html>\n";
        }
        else if (m_request.target() == "/time")
        {
            m_response.set(boost::beast::http::field::content_type, "text/html");
            boost::beast::ostream(m_response.body())
                << "<html>\n"
                << "<head><title>Current time</title></head>\n"
                << "<body>\n"
                << "<h1>Current time</h1>\n"
                << "<p>The current time is "
                << now().time_since_epoch().count()
                << " nanoseconds since the epoch.</p>\n"
                << "</body>\n"
                << "</html>\n";
        }
        else
        {
            m_response.result(boost::beast::http::status::not_found);
            m_response.set(boost::beast::http::field::content_type, "text/html");
            boost::beast::ostream(m_response.body()) << "File not found\r\n";
        }
    }

    void write_response()
    {
        m_response.content_length(m_response.body().size());
        boost::beast::http::async_write(
            m_socket,
            m_response,
            [self = shared_from_this()](boost::system::error_code ec, size_t)
            {
                if (ec)
                {
                    spdlog::warn("write_response failed, value: {}, message: {}", ec.value(), ec.message());
                    return;
                }

                ec = self->m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
                if (ec)
                {
                    spdlog::warn("http connection shutdown failed, value: {}, message: {}", ec.value(), ec.message());
                    return;
                }

                self->m_deadline.cancel(ec);
                if (ec)
                {
                    spdlog::warn("http connection deadline cancel failed, value: {}, message: {}", ec.value(), ec.message());
                    return;
                }
            });
    }

    boost::asio::ip::tcp::socket m_socket;

    static constexpr size_t http_buffer_size = 8192;
    boost::beast::flat_buffer m_buffer{http_buffer_size};

    boost::beast::http::request<boost::beast::http::dynamic_body> m_request;
    boost::beast::http::response<boost::beast::http::dynamic_body> m_response;

    static constexpr auto deadline_time = std::chrono::seconds(5);
    boost::asio::steady_timer m_deadline{m_socket.get_executor(), deadline_time};
};

void http_server(boost::asio::ip::tcp::acceptor& acceptor, boost::asio::ip::tcp::socket& socket)
{
    acceptor.async_accept(socket, [&](boost::system::error_code ec)
        {
            if (ec)
            {
                spdlog::warn("Accept failed, value: {}, message: {}", ec.value(), ec.message());
            }
            else
            {
                spdlog::info("Accept ok");
                std::make_shared<http_connection>(std::move(socket))->start();
            }

            http_server(acceptor, socket);
        });
}

BEAST_HTTP_END_NAMESPACE