#include <beast_http/common/common.hpp>
#include <beast_http/common/log.hpp>
#include <beast_http/http/http_connection.hpp>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    setlocale(LC_ALL, ".utf-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#elif  defined __linux__
    setlocale(LC_ALL, "C.UTF-8");
#elif defined __APPLE__
    setlocale(LC_ALL, "UTF-8");
#endif

    beast_http::set_default_log();

    boost::asio::io_context ctx;
    boost::asio::ip::tcp::acceptor acceptor{ctx, {boost::asio::ip::tcp::v6(), 9999}};
    boost::asio::ip::tcp::socket socket{ctx};
    beast_http::http_server(acceptor, socket);

    ctx.run();

    return 0;
}