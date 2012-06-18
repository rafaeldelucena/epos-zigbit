// Meshbean 2 GATEWAY

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#ifndef _ATMEGA_1281_GATEWAY_H_
#define _ATMEGA_1281_GATEWAY_H_

#include <mach/atmega1281/usart.h>
#include <mach/atmega1281/machine.h>
#include <mach/atmega1281/config.h>

__BEGIN_SYS


class ATMega1281_Gateway
{
    public:
        ATMega1281_Gateway::ATMega1281_Gateway(void) {
            _buffer[_nic.mtu()];
            leds_on(1 << 6);
        };

        ATMega1281_Gateway::~ATMega1281_Gateway(void) {

        };

        void ATMega1281_Gateway::listenNetwork(void) {
            char buffer[_nic.mtu()];

            leds_on(1 << 7);
            _nic.receive(&_src, &_prot, buffer, _nic.mtu());
            leds_off(1 << 7);

            strcpy(_buffer, buffer);
        };

        void ATMega1281_Gateway::sendSerialMessage(void) {
            int i;
            for(i = 0; i < _nic.mtu(); i++) {
                leds_on(1 << 5);
                _usart.put(_buffer[i]);
                leds_off(1 << 5);
            }
        };

    private:
        void ATMega1281_Gateway::leds_init(unsigned char value) {
            CPU::out8(Machine::IO::DDRB, CPU::in8(Machine::IO::DDRB) | value);
        };

        void ATMega1281_Gateway::leds_on(unsigned char value) {
            leds_init(value);
            CPU::out8(Machine::IO::PORTB, CPU::in8(Machine::IO::PORTB) | value);
        };

        void ATMega1281_Gateway::leds_off(unsigned char value) {
            CPU::out8(Machine::IO::PORTB, CPU::in8(Machine::IO::PORTB) & ~value);
        };

        NIC _nic;
        NIC::Address _src;
        NIC::Protocol _prot;
        USART _usart;
        char* _buffer;
};


__END_SYS

#endif // _ATMEGA_1281_GATEWAY_H_
