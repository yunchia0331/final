#include"mbed.h"
#include "bbcar.h"
#include "mbed_rpc.h"
#include "bbcar_rpc.h"
#include <math.h>

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
DigitalInOut pin10(D11);
DigitalOut led3(LED3);

using namespace std;
BufferedSerial pc(STDIO_UART_TX, STDIO_UART_RX);
//BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
BufferedSerial xbee(D10, D9);

BBCar car(pin5, pin6, servo_ticker);
//Thread t;

// RPC control
/*
void linedet(Arguments *in, Reply *out);
RPCFunction Linedet(&linedet, "linedet");
void Control(Arguments *in, Reply *out);
RPCFunction rpcControl(&Control, "Control");
*/

void line();
void XBEE();

int inlinefun=0;


void line(){
    int x;
    printf("line");
    while(1){
        if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            pc.write(recv, sizeof(recv));
            printf("rot= %c\n",recv[0]);
            x = int(recv[0]);
        }   

        printf("x=%d", x);

        if(x<6){
            xbee.write("detectline", 10);
            car.goStraight(20);
            ThisThread::sleep_for(1s);
            car.stop();
        }
        inlinefun++;
        if(inlinefun>5){ 

            break;
        }
    }
//    xbee.write("straight", 8);         
/*    uart.set_baud(9600);
    char buf[256], outbuf[256];
    FILE *devin = fdopen(&uart, "r");
    FILE *devout = fdopen(&uart, "w");
    while (k==1) {
        printf("inlinefun=%d",inlinefun);
        if(inlinefun>5){ 
            k=2;
            break;
        }   
        memset(buf, 0, 256);
        for( int i = 0; ; i++ ) {
            char recv = fgetc(devin);
            if(recv == '\n') {
                printf("\r\n");
                break;
            }
            buf[i] = fputc(recv, devout);
        }
        RPC::call(buf, outbuf);
        printf("%s\r\n", outbuf);
    }
    printf("\r\n");
//    fclose(devin);
//    fclose(devout);
*/
}

/*
void XBEE(){
    k=2;
    printf("XBEE");

    pc.set_baud(9600);

    char buf[256], outbuf[256];
    FILE *devin = fdopen(&xbee, "r");
    FILE *devout = fdopen(&xbee, "w");
//    fprintf(devin, "%s\n", "xbeedevin!");
//    fprintf(devin, "%s\n", "xbeedevout!");
    while (k==2) {
        printf("k=%d",k);
        memset(buf, 0, 256);
        for( int i = 0; ; i++ ) {
            char recv = fgetc(devin);
            if(recv == '\n') {
                printf("\r\n");
                    break;
            }
            buf[i] = fputc(recv, devout);
        }
        RPC::call(buf, outbuf);
    }
*/

int main(){
    uart.set_baud(9600);
    parallax_ping  ping1(pin10);
    xbee.write("start", 5);
/*    line();
        car.goStraight(20);
        ThisThread::sleep_for(1s);
        car.stop();
                car.goStraight(20);
        ThisThread::sleep_for(1s);
        car.stop();
                car.goStraight(20);
        ThisThread::sleep_for(1s);
        car.stop();
                car.goStraight(20);
        ThisThread::sleep_for(1s);
        car.stop();
                car.goStraight(20);
        ThisThread::sleep_for(1s);
        car.stop();
*/    
 //   XBEE();
    xbee.write("turn", 4);
/*    car.turn(35, -0.2);
      ThisThread::sleep_for(3s);
      car.stop();
      ThisThread::sleep_for(1s);
 */   
    xbee.write("gotoapril", 9);
    while(1) {
        printf("IN");
        if((float)ping1>35) {
            led3=1;
            printf("ping>35");
            car.goStraight(30);
/*            if(uart.readable()){
                char recv[1];
                uart.read(recv, sizeof(recv));
                pc.write(recv, sizeof(recv));
                printf("rot= %c\n",recv[0]);
                if (recv[0]=='3') {
                    printf("pingRT");
                    car.goStraight(20);
                    ThisThread::sleep_for(1s);
                    car.turn(30, 0.9);  // turn right
                    ThisThread::sleep_for(1s);
                }else if (recv[0]=='1') {
                    printf("pingLT");
                    car.goStraight(20);
                    ThisThread::sleep_for(1s);
                    car.turn(20, -0.7);  // turn left
                    ThisThread::sleep_for(1s);
                } else if(recv[0]=='2'){
                    printf("straight!!");
                    car.goStraight(30);
                    ThisThread::sleep_for(2s);
                   
                }
            } */
        } else {
            xbee.write("Stop", 4);
            printf("ping<30");
            led3 = 0;
            car.stop();
            break;
        }
        ThisThread::sleep_for(100ms);
    }
    
}
/*
void linedet(Arguments *in, Reply *out){
    inlinefun++;
    printf("RPClinedet");
  int x1 = in->getArg<double>();
    int y1 = in->getArg<double>();
    int x2 = in->getArg<double>();
    int y2 = in->getArg<double>();

    int x = in->getArg<int>();
//    double x = abs(x1-x2);
    printf("x=%f", x);

    if(x<6){
        xbee.write("Straight", 8);
        car.goStraight(20);
        ThisThread::sleep_for(1s);
        car.stop();
    //       ThisThread::sleep_for(500ms);
   }
   
}
*/
/*
void Control (Arguments *in, Reply *out)   {
printf("RPCControl");
    xbee.write("turnandstop", 11);
      car.turn(30, 0.1);
      ThisThread::sleep_for(2s);
      car.stop();
      ThisThread::sleep_for(1s);
    k=3;
   }
*/
