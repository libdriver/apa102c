### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOSI GPIO11/GPIO10.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(apa102c REQUIRED)
```


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
./apa102c -i

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
./apa102c -p

apa102c: SPI interface SCK connected to GPIO11(BCM).
apa102c: SPI interface MOSI connected to GPIO10(BCM).
```

```shell
./apa102c -t write --number=12 --times=10

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
./apa102c -e write --number=12 --color=16711680

apa102c: number is 12 and written color is 0xFF0000.
```

```shell
./apa102c -h

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

