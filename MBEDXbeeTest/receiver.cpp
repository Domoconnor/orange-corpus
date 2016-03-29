#include "mbed.h"
#include "C12832.h"

DigitalOut gpo(D0);
DigitalOut led(LED_RED);
DigitalOut myled(D7);

Serial xbee(D1, D0); // Ignore
Serial out (USBTX, USBRX);

C12832 lcd (D11, D13, D12, D7, D10);

int x;
int y = 0;
int chars = 0;

void onReceive()
{
    lcd.cls();
    lcd.locate(1,10);
    char c = xbee.getc();
    lcd.printf("Got: ");
    lcd.putc(c);
    lcd.printf(" %d", x++);
    xbee.putc(c);
}
int main()
{
    lcd.printf("Starting receiver...");
    xbee.attach(&onReceive);

    while(true) {
        sleep();

    }
}