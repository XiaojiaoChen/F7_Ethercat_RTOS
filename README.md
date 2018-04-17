#STM32-FreeRTOS-EtherCAT

This project is a realtime data-acquisition, control and PC-transmission platform desigend as a centralized driver for a 4-DOF pneumatic robotic arm.

It is based on a STM32F767ZI-Nucleo board running FreeRTOS, and an ethercat expansion board I-NUCLEO-NETX providing realtime data transmittion with PC. 

Currently it is still under construction.

### Features
The platform has the following features:

Input:
 * 8-channel 16-bit AD input (-10~10V) (using an ADS8588 board from TI)
 * 4-channel Angular information (using AS5048A and AS5311 from AMS, SCC2130-D08 from muRata, Mini4096j)
 * 8-channel pressure information (using HSCDANN060PGSA3 and  SSCDNNN060PAAA5 from HoneyWell)

Output:
 * 16-channel 16-bit DA output (0~10V) (using a LTC2668 board from Linear Technology).

Data Transmission:
 * 1KHz realtime transmission with PC through ethernet (using EtherCAT expansion board I-NUCLEO-NETX)
 * Non-blocking serial transmission (using DMA and output buffers)
 * Non-blocking variable size serial receving (using DMA and input idleline Detection) 

control:
 * Simple Kalman filter (Using CMSIS DSP library, who exploits fast hardware computation)
 * Advanced PID controller
 * simple Sliding mode controller



## Getting Started

This project is still on going, and currently the portability is not considered too much.
 
### Prerequisites

Hardware:
 * STM32F767ZI-Nucleo board
 * I-NUCLEO-NETX
 * ADS8588 board
 * LTC2668 board
 * other sensors
 
Software:
 * STM32CubeMX
 * SW4STM32
 * cifX toolkit form Hilscher
 
 
### Installing

## Deployment

## Authors

* **Xiaojiao Chen** 

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
