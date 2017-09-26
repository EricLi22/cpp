#include <string>
#include <iostream>
#include <boost/regex.hpp>
int main()
{
    std::string str = "192.168.1.1";

    boost::regex expression("\\d+");
    boost::smatch what;

    std::string::const_iterator start = str.begin();
    std::string::const_iterator end = str.end();
    while ( boost::regex_search(start, end, what, expression) )
    {
        std::cout << what[0] << std::endl;
        start = what[0].second;
    }
    return 0;
}
