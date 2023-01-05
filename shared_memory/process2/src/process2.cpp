#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    using namespace boost::interprocess;

    if (false) {  //Parent process
        //Create a native windows shared memory object.
        windows_shared_memory shm(create_only, "MySharedMemory", read_write, 1000);

        //Map the whole shared memory in this process
        mapped_region region(shm, read_write);

        //Write all the memory to 1
        std::memset(region.get_address(), 1, region.get_size());

        //Launch child process
        std::string s(argv[0]); s += " child ";
        if (0 != std::system(s.c_str()))
            return 1;
        //windows_shared_memory is destroyed when the last attached process dies...
    }
    else {
        std::cout << "\nEnter to read shared memory.\n";
        std::cin.get();//Open already created shared memory object.
        windows_shared_memory shm(open_only, "MySharedMemory", read_only);

        //Map the whole shared memory in this process
        mapped_region region(shm, read_only);

        //Check that memory was initialized to 1
        char* mem = static_cast<char*>(region.get_address());
        std::cout << "Getting data of address " << region.get_address() << std::endl;

        for (std::size_t i = 0; i < region.get_size(); ++i)
            if (*mem++ != 1) {
                std::cout << "Error, data is not 1. \n";
            }
            else {
                std::cout << "Read successfully, data is 1. \n";
            }
        std::cin.get();
    }
    return 0;
}
