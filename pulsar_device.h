/* vim: set ts=4 sw=4: */

#pragma once

#include <memory>
#include "serial_device.h"
#include <stdint.h>

class TPulsarDevice: public TSerialDevice {
public:

    enum RegisterType {
        REG_DEFAULT,
        REG_SYSTIME
    };

    TPulsarDevice(PDeviceConfig device_config, PAbstractSerialPort port);
    uint64_t ReadRegister(PRegister reg);
    void WriteRegister(PRegister reg, uint64_t value);

private:
    void WriteBCD(uint64_t data, uint8_t *buffer, size_t size, bool big_endian = true);
    void WriteHex(uint64_t data, uint8_t *buffer, size_t size, bool big_endian = true);
    uint16_t CalculateCRC16(const uint8_t *buffer, size_t size);

    void WriteDataRequest(uint32_t addr, uint32_t mask, uint16_t id);
    void WriteSysTimeRequest(uint32_t addr, uint16_t id);
};

typedef std::shared_ptr<TPulsarDevice> PPulsarDevice;
