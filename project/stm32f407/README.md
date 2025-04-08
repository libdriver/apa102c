### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MOSI PA5/PA7.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. APA102C

#### 3.1 Command Instruction

1. Show apa102c chip and driver information.

   ```shell
   apa102c (-i | --information)
   ```

2. Show apa102c help.

   ```shell
   apa102c (-h | --help)
   ```

3. Show apa102c pin connections of the current board.

   ```shell
   apa102c (-p | --port)
   ```

4. Run apa102c write test, number is the apa102c chip number and num is the test times.

   ```shell
   apa102c (-t write | --test=write) [--number=<number>] [--times=<num>]
   ```

5. Run apa102c write function, number is the apa102c chip number and color is the rgb color.

   ```shell
   apa102c (-e write | --example=write) [--number=<number>] [--color=<color>]
   ```

#### 3.2 Command Example

```shell
apa102c -i

apa102c: chip is Shiji Lighting APA102C.
apa102c: manufacturer is Shiji Lighting.
apa102c: interface is SPI.
apa102c: driver version is 1.0.
apa102c: min supply voltage is 5.0V.
apa102c: max supply voltage is 5.5V.
apa102c: max current is 200.00mA.
apa102c: max temperature is 70.0C.
apa102c: min temperature is -40.0C.
```

```shell
apa102c -p

apa102c: SPI interface SCK connected to GPIOA PIN5.
apa102c: SPI interface MOSI connected to GPIOA PIN7.
```

```shell
apa102c -t write --number=12 --times=10

apa102c: chip is Shiji Lighting APA102C.
apa102c: manufacturer is Shiji Lighting.
apa102c: interface is SPI.
apa102c: driver version is 1.0.
apa102c: min supply voltage is 5.0V.
apa102c: max supply voltage is 5.5V.
apa102c: max current is 200.00mA.
apa102c: max temperature is 70.0C.
apa102c: min temperature is -40.0C.
apa102c: start write test.
apa102c: 1/10 times.
apa102c: 2/10 times.
apa102c: 3/10 times.
apa102c: 4/10 times.
apa102c: 5/10 times.
apa102c: 6/10 times.
apa102c: 7/10 times.
apa102c: 8/10 times.
apa102c: 9/10 times.
apa102c: 10/10 times.
apa102c: finish write test.
```

```shell
apa102c -e write --number=12 --color=16711680

apa102c: number is 12 and written color is 0xFF0000.
```

```shell
apa102c -h

Usage:
  apa102c (-i | --information)
  apa102c (-h | --help)
  apa102c (-p | --port)
  apa102c (-t write | --test=write) [--number=<number>] [--times=<num>]
  apa102c (-e write | --example=write) [--number=<number>] [--color=<color>]

Options:
      --color=<color>                Set the chip display color.([default: 16711680])
  -e <write>, --example=<write>      Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
      --number=<number>              Set the chip number.([default: 3])
  -p, --port                         Display the pin connections of the current board.
  -t <write>, --test=<write>         Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

