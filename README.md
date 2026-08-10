# Real-Time Embedded Monitoring & Data Acquisition System

A real-time embedded monitoring and data acquisition system developed using **STM32F401RBT6**. The project demonstrates both **Register-Level Programming** and **STM32 HAL-based development** for sensor interfacing, real-time scheduling, LCD display, ADC-based temperature measurement, and UART communication with ESP8266.

## Hardware & Technologies

* **Microcontroller:** STM32F401RBT6
* **Programming Language:** Embedded C
* **Development Tools:** Keil / STM32CubeIDE
* **Temperature Sensor:** LM35
* **Wi-Fi Module:** ESP8266
* **Display:** 16x2 LCD
* **Protocols:** UART
* **Peripherals:** GPIO, ADC, UART, RTC, SYSTICK TIMER
* **Programming Approaches:**

  * Register-Level Programming
  * STM32 HAL Library

## Project Structure

```text
Real-Time-Embedded-Monitoring-Data-Acquisition-System/
│
├── HAL/
│   ├── Core/
│   ├── Drivers/
│   ├── STM32F401RBTX_FLASH.ld
│   ├── SWMS_3.0.ioc
│   └── ...
│
├── Register-Level/
│   ├── INC/
│   ├── SRC/
│   ├── main.c
│   ├── main.uvprojx
│   └── ...
│
└── README.md
```

## Features

### Real-Time Clock

* Displays real-time clock information on the LCD.
* Clock is updated every second.
* Uses STM32 scheduling and timing logic for periodic task execution.

### Temperature Monitoring

* LM35 temperature sensor is interfaced with the STM32 ADC.
* Temperature is sampled periodically.
* Temperature values are displayed on the LCD.

### Wi-Fi Communication

* ESP8266 is interfaced with STM32 through UART.
* Temperature data is transmitted to a local server.
* Enables remote monitoring of sensor data.

### LCD Display

The LCD is used to display:

* Real-time clock
* Temperature values
* System status information

## Register-Level Programming

The `Register-Level` directory contains the implementation using direct STM32 peripheral register access.

It demonstrates programming of:

* GPIO
* ADC
* UART
* Timers
* RTC
* Interrupts
* Scheduling logic

This section helps understand the STM32F401RBT6 peripheral registers and bit-level configuration without depending on the HAL abstraction layer.

## HAL Programming

The `HAL` directory contains the STM32 HAL-based implementation.

It demonstrates:

* HAL GPIO configuration
* HAL ADC
* HAL UART
* HAL Timers
* HAL RTC
* Interrupt handling
* LCD interfacing
* ESP8266 communication

## System Flow

```text
             ┌──────────────────┐
             │   STM32F401RBT6  │
             │                  │
             │  Real-Time Tasks │
             └────────┬─────────┘
                      │
          ┌───────────┼───────────┐
          │           │           │
          ▼           ▼           ▼
       LM35          RTC        LCD
          │           │           ▲
          ▼           ▼           │
         ADC ──────> Processing ──┘
          │
          ▼
        UART
          │
          ▼
       ESP8266
          │
          ▼
    Local Server
```

## Key Learning Outcomes

* STM32F401RBT6 peripheral programming
* Register-level embedded programming
* STM32 HAL library usage
* ADC-based sensor interfacing
# Real-Time Embedded Monitoring & Data Acquisition System

A real-time embedded monitoring and data acquisition system developed using **STM32F401RBT6**. The project demonstrates both **Register-Level Programming** and **STM32 HAL-based development** for sensor interfacing, real-time scheduling, LCD display, ADC-based temperature measurement, and UART communication with ESP8266.

## Hardware & Technologies

* **Microcontroller:** STM32F401RBT6
* **Programming Language:** Embedded C
* **Development Tools:** Keil / STM32CubeIDE
* **Temperature Sensor:** LM35
* **Wi-Fi Module:** ESP8266
* **Display:** 16x2 LCD
* **Protocols:** UART
* **Peripherals:** GPIO, ADC, UART, RTC, Timers
* **Programming Approaches:**

  * Register-Level Programming
  * STM32 HAL Library

## Project Structure

```text
Real-Time-Embedded-Monitoring-Data-Acquisition-System/
* LCD interfacing
* Embedded C firmware development

* Environmental temperature monitoring
* IoT-based embedded systems
* Industrial monitoring systems
* Real-time data acquisition systems

## Author

**Jayasimha Reddy**

Embedded Systems | STM32 | Embedded C | Register-Level Programming | STM32 HAL
* Remote sensor monitoring

## Applications
* Real-time task scheduling
* Interrupt-based programming
* ADC-based sensor interfacing
* UART communication
* ESP8266 interfacing
│
├── HAL/
│   ├── Core/
## Key Learning Outcomes

* STM32F401RBT6 peripheral programming
* Register-level embedded programming
* STM32 HAL library usage
│   ├── Drivers/
│   ├── STM32F401RBTX_FLASH.ld
│   ├── SWMS_3.0.ioc
│   └── ...
│
          │
    Local Server
```

          ▼
       ESP8266
          │
          ▼
├── Register-Level/
│   ├── INC/
          ▼
        UART
│   ├── SRC/
│   ├── main.c
          ▼           ▼           │
         ADC ──────> Processing ──┘
          │
│   ├── main.uvprojx
│   └── ...
│
└── README.md
```

## Features

### Real-Time Clock
          │           │           ▲

* Displays real-time clock information on the LCD.
* Clock is updated every second.
* Uses STM32 scheduling and timing logic for periodic task execution.

### Temperature Monitoring

* LM35 temperature sensor is interfaced with the STM32 ADC.
          ┌───────────┼───────────┐
          │           │           │
          ▼           ▼           ▼
       LM35          RTC        LCD
* Temperature is sampled periodically.
* Temperature values are displayed on the LCD.

### Wi-Fi Communication

             │   STM32F401RBT6  │
             │                  │
                      │
             │  Real-Time Tasks │
             └────────┬─────────┘
## System Flow

```text
             ┌──────────────────┐
* ESP8266 is interfaced with STM32 through UART.
* Temperature data is transmitted to a local server.
* Enables remote monitoring of sensor data.

### LCD Display


The LCD is used to display:

* Real-time clock
* ESP8266 communication
* Temperature values
* System status information

* Interrupt handling
* LCD interfacing
## Register-Level Programming

The `Register-Level` directory contains the implementation using direct STM32 peripheral register access.

It demonstrates programming of:

* HAL UART
* HAL Timers
* HAL RTC
It demonstrates:

* HAL GPIO configuration
* HAL ADC
* GPIO
* ADC
* UART
* Timers

* RTC
* Interrupts
* Scheduling logic
The `HAL` directory contains the STM32 HAL-based implementation.

This section helps understand the STM32F401RBT6 peripheral registers and bit-level configuration without depending on the HAL abstraction layer.

## HAL Programming
