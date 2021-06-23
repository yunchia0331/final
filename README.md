# final
兩個檔案都在final資料夾內!
# main.cpp
* line()
** 收openmv傳回來的資訊，沿著線走
```C++
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
            xbee.write("detectline\n", 12);
            car.goStraight(20);
            ThisThread::sleep_for(1s);
            car.stop();
        }
        inlinefun++;
        if(inlinefun>5){ 

            break;
        }
    }
```
** xbee 回傳轉彎
```C++
    xbee.write("turn\n", 6);
```
** 轉彎
```C++
      car.turn(35, -0.2);
      ThisThread::sleep_for(3s);
      car.stop();
      ThisThread::sleep_for(1s);
```
** xbee 傳
```C++
    xbee.write("gotoapril\n", 11);
```
** openmv看apriltag喬角度， Ping測距離(走到<35公分停下, 大於35公分就繼續走並且會亮LED燈)
```C++
while(1) {
        printf("IN");
        if((float)ping1>35) {
            led3=1;
            printf("ping>35");
            car.goStraight(30);
            if(uart.readable()){
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
            } 
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
```

* XBEE.py讀main的指令並print出，五個指令分別為:
> start\n  
> detectline\n  
> turn\n  
> gotoapril\n  
> stop\n  
``` py
import serial
# XBee setting
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

import serial

line = s.read(7)
print('0:', line.decode())
line = s.read(12)
print('1:', line.decode())

line = s.read(6)
print('2:', line.decode())

line = s.read(11)
print('3:', line.decode())
line = s.read(6)
print('4:', line.decode())

s.close()
```
