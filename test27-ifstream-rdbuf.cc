#include <fstream>
#include <iostream>

/* wrong revison
int main()
{
    std::ofstream log("oops.log");
    std::cout.rdbuf(log.rdbuf());
    std::cout << "Woo Oops!\n";
    return 0;
}
*/

// RAII method of restoring a buffer
struct buffer_restorer {
    std::ios &m_s;
    std::streambuf *m_buf;

    buffer_restorer(std::ios &s, std::streambuf *buf) : m_s(s), m_buf(buf) {}
    ~buffer_restorer() { m_s.rdbuf(m_buf); }
};

int main()
{
    std::ofstream log("oops.log");
    buffer_restorer r(std::cout, std::cout.rdbuf(log.rdbuf()));
    std::cout << "Woo Oops!\n";
    return 0;
}
