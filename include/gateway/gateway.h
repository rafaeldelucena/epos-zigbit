// Meshbean 2 GATEWAY

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#ifndef _ATMEGA_1281_GATEWAY_H_
#define _ATMEGA_1281_GATEWAY_H_

#include <mach/atmega1281/uart.h>
#include <mach/atmega1281/machine.h>
#include <mach/atmega1281/config.h>

__BEGIN_SYS


class ATMega1281_Gateway
{
    public:
        ATMega1281_Gateway::ATMega1281_Gateway(void) {
            buffer = new char[nic.mtu()+1];
            ledsOn(1 << 6);
        };

        ATMega1281_Gateway::~ATMega1281_Gateway(void) {
            delete[] buffer;
        };

        void ATMega1281_Gateway::listenNetwork(void) {
            char buf[nic.mtu()+1];

            ledsOn(1 << 7);
            nic.receive(&src, &prot, buf, nic.mtu());
            ledsOff(1 << 7);

            strcpy(buffer, buf);
        };

        char* ATMega1281_Gateway::getBuffer(void)
        {
            return buffer;
        };

        void ATMega1281_Gateway::sendSerialMessage(char* str) {
            while(*str != '\0') {
                ledsOn(1 << 5);
                uart.put(*str);
                Alarm::delay(1000);
                str++;
            }
            ledsOff(1 << 5);
        };

    private:
        void ATMega1281_Gateway::ledsInit(unsigned char value) {
            CPU::out8(Machine::IO::DDRB, CPU::in8(Machine::IO::DDRB) | value);
        };

        void ATMega1281_Gateway::ledsOn(unsigned char value) {
            ledsInit(value);
            CPU::out8(Machine::IO::PORTB, CPU::in8(Machine::IO::PORTB) | value);
        };

        void ATMega1281_Gateway::ledsOff(unsigned char value) {
            CPU::out8(Machine::IO::PORTB, CPU::in8(Machine::IO::PORTB) & ~value);
        };

        NIC nic;
        NIC::Address src;
        NIC::Protocol prot;
        UART uart;
        char* buffer;
};


__END_SYS

#endif // _ATMEGA_1281_GATEWAY_H_
