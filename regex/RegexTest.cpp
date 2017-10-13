#include <iostream>
using namespace std;
#include <boost/regex.hpp>

int main(){
  string str="GET /index.html HTTP/1.1 \r\nContent-Type: application/json\r\n\r\n";
  cout<<str<<"=="<<endl;
  boost::regex reg("^(\\w+) /(\\w*([.]\\w+)?)\\s*HTTP/1.\\w\\s*");
  boost::smatch sm;
  regex_search(str,sm,reg);
  cout<<sm.size()<<endl;
  for(int i=0;i<sm.size();i++){
    cout<<sm[i]<<endl;
  }

  // std::string str = "192.168.1.1";
  //
  // boost::regex expression("\\d+");
  // boost::smatch what;
  //
  // std::string::const_iterator start = str.begin();
  // std::string::const_iterator end = str.end();
  // while ( boost::regex_search(start, end, what, expression) )
  // {
  //     std::cout << what[0] << std::endl;
  //     start = what[0].second;
  // }
  return 0;
}
