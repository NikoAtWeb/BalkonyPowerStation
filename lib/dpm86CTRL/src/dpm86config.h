#ifndef __DPM86CONFIG_H__
#define __DPM86CONFIG_H__


/** 
 * Define DEBUG_SERIAL_ENABLE to enable debug serial. 
 * Comment it to disable debug serial. 
 */
#define DEBUG_SERIAL_ENABLE

/**
 * Define debugSerial for the output of debug messages. 
 */
#define debugSerial Serial

/**
 * Define dpmSerial for communicate with dpm86xxx in HardwareSerial or SoftwareSerial. 
 * Comment following define
 */
//#define HARDWARE_SERIAL_ENABLE

#ifdef HARDWARE_SERIAL_ENABLE
    #define dpmSerialHard Serial2
#else
    #include <SoftwareSerial.h>
    extern SoftwareSerial SoftSerial;
    #define dpmSerialSoft SoftSerial
#endif

#ifdef DEBUG_SERIAL_ENABLE
    #define debugSerialPrint(a)    debugSerial.print(a)
    #define debugSerialPrintln(a)  debugSerial.println(a)
    #define debugSerialBegin(a)    debugSerial.begin(a)
#else
    #define debugSerialPrint(a)    do{}while(0)
    #define debugSerialPrintln(a)  do{}while(0)
    #define debugSerialBegin(a)    do{}while(0)
#endif

#endif /* #ifndef __DPM86CONFIG_H__ */