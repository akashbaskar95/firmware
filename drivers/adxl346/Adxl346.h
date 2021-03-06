/**
 * @file       Adxl346.h
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2015
 * @brief
 *
 * @copyright  Copyright 2015, OpenMote Technologies, S.L.
 *             This file is licensed under the GNU General Public License v2.
 */

#ifndef ADXL346_H_
#define ADXL346_H_

#include <stdint.h>

class I2c;
class GpioIn;
class Callback;

class Adxl346
{
public:
    Adxl346(I2c& i2c, GpioIn& gpio);
    bool enable(void);
    bool reset(void);
    bool wakeup(void);
    bool suspend(void);
    bool isPresent(void);
    void calibrate(void);
    bool selfTest(bool test);
    void setCallback(Callback* callback);
    void clearCallback(void);
    bool readSample(uint16_t* x, uint16_t* y, uint16_t* z);
    bool readSamples(uint8_t* buff, uint8_t samples);
    uint8_t samplesAvailable(void);
private:
    I2c& i2c_;
    GpioIn& gpio_;
};

#endif /* ADXL346_H_ */
