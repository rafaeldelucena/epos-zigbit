#include <alarm.h>

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.
#include <machine.h>
#include <gateway/gateway.h>

__USING_SYS


int main(void)
{
    ATMega1281_Gateway gateway;
    OStream cout;

    while(true) {
        gateway.listenNetwork();
        Alarm::delay(2000000);
        
        gateway.sendSerialMessage(gateway.getBuffer());
        Alarm::delay(1000000);
      //  cout << gateway.getBuffer();
        Alarm::delay(1000);
    }
}
