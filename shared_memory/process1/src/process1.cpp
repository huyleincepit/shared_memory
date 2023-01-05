#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    using namespace boost::interprocess;

    if (true) {  //Parent process
        //Create a native windows shared memory object.
        windows_shared_memory shm(create_only, "MySharedMemory", read_write, 1000);

        //Map the whole shared memory in this process
        mapped_region region(shm, read_write);

        //Write all the memory to 1
        std::memset(region.get_address(), 1, region.get_size());
        
        std::cout << "Setting 0x01 to address " << region.get_address() << " and size = " << region.get_size();
        std::cout << "\nWaiting another process read shared memory.\n";
        std::cin.get();
    }
    else {
        //Open already created shared memory object.
        windows_shared_memory shm(open_only, "MySharedMemory", read_only);

        //Map the whole shared memory in this process
        mapped_region region(shm, read_only);

        //Check that memory was initialized to 1
        char* mem = static_cast<char*>(region.get_address());
        for (std::size_t i = 0; i < region.get_size(); ++i)
            if (*mem++ != 1)
                return 1;   //Error checking memory
        return 0;
    }
    std::cout << "Process finished, shared memory was cleaned.\n";
    return 0;
}
