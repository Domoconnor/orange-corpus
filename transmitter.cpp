#include "mbed.h"
#include "C12832.h"                     /* for the LCD */

DigitalOut gpo(D0);
DigitalOut led(LED_RED);

Serial out (USBTX, USBRX); // Used to print out to terminal on pc
Serial xbee(D1, D0); // Ignore
DigitalOut myled(D7);

C12832 lcd (D11, D13, D12, D7, D10);   // LCD on the shield (128x32)

Ticker tick;

int x;
bool reset;

void onTick()
{
    xbee.printf("a");
    x = (x + 1) % 10;
    lcd.locate(1,1);
    lcd.printf("Sent %d", x);
}

int main()
{
    tick.attach(&onTick, 1);
    lcd.printf("Starting transmitter...");
    x=0;
    //xbee.attach(&onReceive);
    while (true) {
        sleep();
    }
}