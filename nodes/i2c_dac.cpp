#include "i2c_dac.h"
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <abmt/os.h>

using namespace std;
using namespace test_scope_pic;

i2c_dac::i2c_dac(){
    fd = open("/dev/i2c-1", O_RDWR);
}

void i2c_dac::tick(){
    static bool toggle = false;
    int res;
    
    uint8_t data_x[] = {0x44, (uint8_t)(in_x * 255)};
    uint8_t data_y[] = {0x44, (uint8_t)(in_y * 255)};

    i2c_msg messages[] = {
            { 72, 0, 2, data_x },
            { 74, 0, 2, data_y },
    };
    
    if(toggle){
        messages[0] =  { 74, 0, 2, data_y };
        messages[1] =  { 72, 0, 2, data_x };
    }
    toggle = !toggle;
    
    i2c_rdwr_ioctl_data ioctl_data = { messages, 2 };
 
    res = ioctl(fd, I2C_RDWR, &ioctl_data);
    if (res < 0){
        abmt::os::die("unable to write dac data.");
    }
}

i2c_dac::~i2c_dac(){
    if(fd > 0){
        close(fd);
    }
}