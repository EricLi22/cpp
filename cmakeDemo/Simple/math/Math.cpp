#include "Math.h"
#include <iostream>
using namespace std;
long pow(int base,int power){
        cout<<"my math"<<endl;
        long res=1;
        for(int i=0; i<power; i++) {
                res*=base;
        }
        return res;
}
