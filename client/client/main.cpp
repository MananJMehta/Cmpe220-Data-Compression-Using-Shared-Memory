
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
    
    using namespace std;
    using namespace boost::interprocess;
    
    int main(int argc, char** argv)
    {
        shared_memory_object shm(open_only, "MySharedMemory", read_write);
        
        //Map the whole shared memory in this process
        mapped_region region(shm, read_write);
        
        //    char input[10];
        //    cout<<"Enter input";
        //    for (int i=0; i<8; i++)
        //        cin>>input[i];
        //char input[2] = "a";
        
        string input;
        cout<<"Enter input\n";
        cin>>input;
        const char *str3=input.c_str();
        cout<<"\nSize Of Input String " <<sizeof(input)<<"\nSize of Converted Pointer "<<sizeof(str3)<<"\n";
        cout<<"\nLength of Input "<<input.length()<<"\nLength of Converted pointer "<<strlen(str3);
        
        
        //memset(region.get_address(), 1, region.get_size());
        memcpy(region.get_address(), str3, strlen(str3));
        
        //    //Check that memory was initialized to 1
        //    char *mem = static_cast<char*>(region.get_address());
        //
        //    for(size_t i = 0; i < region.get_size(); ++i)
        //        cout << (int)*mem++ << endl;
        
        cout << "\nExiting Client Program" << endl;
    }



