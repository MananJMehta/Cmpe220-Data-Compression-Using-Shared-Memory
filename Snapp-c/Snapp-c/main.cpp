//
//  main.cpp
//  Snapp-c
//
//  Created by manan mehta on 11/1/17.
//  Copyright © 2017 manan mehta. All rights reserved.
//
#include "snappy.h"
#include "snappy-c.h"
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
    
    //Write all the memory to 1
    memset(region.get_address(), 1, region.get_size());
    
    char *mem = static_cast<char*>(region.get_address());
    
    while(1)
    {
        if(*mem != 1)
        {
            int len = *mem;
            int i=0;
            while (len != 0)
            {
                
                cout<<*(mem+i);
                i++;
                len--;
            }
            break;
        }
        
    }
    cout<< "\nlength "<<strlen(mem);
    cout<<"\nSize of Uncompressed "<<sizeof(mem);
    
    
    char uncompressed[strlen(mem)] ;
    
    size_t length = snappy_max_compressed_length(sizeof(uncompressed));
    char *compressed = new char[length];
    
    snappy_status status = snappy_compress(mem, strlen(mem), compressed, &length);
    
    cout<<"\nstatus "<<status<<"\nSize of Compressed "<<sizeof(compressed)<<"\nLength of Data Compressed "<<length<<"\nData Compressed: "<<compressed;
    cout << "\nExiting Server Program" << endl;
    return 0;
}

