#include <iostream>
#include "config.h"

#ifdef USE_MYMATH
  #include "math/Math.h"
#else
  #include <math.h>
#endif

using namespace std;
int main(){
    cout<<"Version "<<Demo_VERSION_MAJOR<<"."<<Demo_VERSION_MINOR<<endl;
        int x=10;
        int y=3;
        int res=pow(10,3);
        cout<<res<<endl;
        return 0;
}
