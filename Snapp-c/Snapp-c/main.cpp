//
//  main.cpp
//  Snapp-c
//
//  Created by manan mehta on 11/1/17.
//  Copyright © 2017 manan mehta. All rights reserved.
//
/*
#include "snappy.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include "snappy-c.h"
#include <iostream>
#include "string.h"
using namespace std;

int main(int argc, const char * argv[]) {
    char uncompressed[] = "Hello      World!";
    size_t length = snappy_max_compressed_length(sizeof(uncompressed));
    char *compressed = new char[length];
    cout<<sizeof(uncompressed);
  
    snappy_status status = snappy_compress(
                                           uncompressed, 17, compressed, &length);
    cout<<"status "<<status<<"\n"<<sizeof(compressed)<<"\n"<<length<<compressed;
    return 0;
}*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
using namespace boost::interprocess;


int main(int argc, char** argv)
{
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;
    
    //Create a shared memory object.
    shared_memory_object shm (create_only, "MySharedMemory", read_write);
    
    //Set size
    shm.truncate(100);
    
    //Map the whole shared memory in this process
    mapped_region region(shm, read_write);
    
//    //Write all the memory to 1
    memset(region.get_address(), 1, region.get_size());
//
//    char *mem = static_cast<char*>(region.get_address());
//
//    for(size_t i = 0; i < region.get_size(); ++i)
//        cout << (int)*mem++ << endl;
//
//    char c;
//    cin >> c;
 volatile char *mem = static_cast<char*>(region.get_address());
    //int x= mem+9;
    while(1)
    {
        if(*mem != 1)
        {
            int len = *mem;
            while (len != 0)
            {
                cout<<*mem;
                (mem++);
                len--;
            }
            break;
        }
        
    }
    cout << "Exiting main1" << endl;
    return 0;
}
