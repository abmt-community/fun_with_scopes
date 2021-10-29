#ifndef TEST_SCOPE_PIC_I2C_DAC_H
#define TEST_SCOPE_PIC_I2C_DAC_H TEST_SCOPE_PIC_I2C_DAC_H

namespace test_scope_pic{

//@node: auto
struct i2c_dac{
  double in_x;
  double in_y;
  
  int fd;
  
  i2c_dac();
  
  void tick();
  
  ~i2c_dac();
  
};


} // namespace test_scope_pic

#endif // TEST_SCOPE_PIC_I2C_DAC_H
