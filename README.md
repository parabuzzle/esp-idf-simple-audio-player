# Simple ESP-IDF WAV Audio Player

I spent waaaaaaay too much time trying to get ESP-IDF to play a wav file to an external DAC using I2S.

The biggest problem I had was there was no working example of doing exactly this in its simplest form. Most examples are Arduino based, ESP-ADF based, or rely on the legacy ESP-IDF <=4.x APIs. I'm usig ESP-IDF 5.x with my project and I don't have a need for any of the ESP-ADF tools or fancy player pipelines. I just wanted a bare bones example of streaming a WAV file from the SD card to the DAC so that I could better understand the protocols and apis.

I hope by sharing this simple project, others in my position can benefit by seeing a working example and expand on it as I did.

_Note: this project plays a single WAV file encoded in 44.1kHz 16bit stereo off of the SD card and then reboots_

**This uses the ESP-IDF V5 apis and will not work on older IDF versions!**

## How to use example

Clone this repo and make sure your path settings are correct for your local ESP-IDF installation. _ref a working project .vscode directory ;-)_

Run menuconfig and set the chip and what not. _I did this all with an ESP32-WROVER-E series module_

Open [configuration.h](main/configuration.h) and make sure you adjust the pin defines to your setup.

Run Build, Flash, monitor :)

### Hardware setup

The setup I'm using for this example is an ESP32-WROVER-E-N8R8 module on a custom board connected to a PCM5102a DAC chip.

### Connections

SD is a microSD card connected to the default SDMMC (4bit) pins from the datasheet. (Pin config is found in the [configuration.h](main/configuration.h) file.)
All the pins are pulled up to 3.3v using 10k resistors (SD spec calls for 10K but the Espressif datasheet calls for 1K.. 10K works just fine)

The PCM5102a DAC is connected using the Bit clock, Word clock, and Data in pins.
These can be arbitrary pins as there is no "dedicated I2S bus" pins on the ESP32.

- Bit clock is connected to GPIO pin 5
- Word clock is connected to GPIO pin 19
- Data Out is connected to GPIO pin 23

_again you can change this in [configuration.h](main/configuration.h)_

### WAV File settings

**This example only support 44.1kHz 16bit Stereo WAV files. Beyond that, you're on your own.**

## Folder contents

The project **esp-idf-wav-player** is a C based project with `app_main` found in [main.c](main/main.c). The file is located in folder [main](main).

There are a couple header files to move some boiler plate out of the main file to keep the project a bit easier to read.

The [configuration.h](main/configuration.h) file contains general configuration items like pin configuration definitions as well as a helper to print out system information.

The [sdcard.h](main/sdcard.h) file contains the logic required to initialize an SDMMC peripheral as well as a helper function to log data about the card.

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both).

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c                 app_main and i2s stuff is here
|   └── configuration.h        general system configuratoin is here
|   └── sdcard.h               sdcard initialization logic is here
└── README.md                  This is the file you are currently reading
```

## Sample Serial Console Output

```
entry 0x4008064c
I (29) boot: ESP-IDF v5.0.2 2nd stage bootloader
I (29) boot: compile time 13:02:40
I (29) boot: chip revision: v3.0
I (32) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (46) boot: Enabling RNG early entropy source...
I (51) boot: Partition Table:
I (55) boot: ## Label            Usage          Type ST Offset   Length
I (62) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (70) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (77) boot:  2 factory          factory app      00 00 00010000 00100000
I (85) boot: End of partition table
I (89) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=0cbe4h ( 52196) map
I (116) esp_image: segment 1: paddr=0001cc0c vaddr=3ffb0000 size=01f84h (  8068) load
I (119) esp_image: segment 2: paddr=0001eb98 vaddr=40080000 size=01480h (  5248) load
I (124) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=25300h (152320) map
I (185) esp_image: segment 4: paddr=00045328 vaddr=40081480 size=0ad28h ( 44328) load
I (210) boot: Loaded app from partition at offset 0x10000
I (210) boot: Disabling RNG early entropy source...
I (222) cpu_start: Pro cpu up.
I (222) cpu_start: Starting app cpu, entry point is 0x400810c8
0x400810c8: call_start_cpu1 at C:/Users/parab/esp/esp-idf/components/esp_system/port/cpu_start.c:141

I (208) cpu_start: App cpu up.
I (236) cpu_start: Pro cpu start user code
I (236) cpu_start: cpu freq: 160000000 Hz
I (236) cpu_start: Application information:
I (241) cpu_start: Project name:     esp-idf-wav-player
I (247) cpu_start: App version:      1
I (251) cpu_start: Compile time:     Jun 20 2023 09:43:54
I (257) cpu_start: ELF file SHA256:  60eb6d98ab7bf36c...
I (263) cpu_start: ESP-IDF:          v5.0.2
I (268) cpu_start: Min chip rev:     v0.0
I (273) cpu_start: Max chip rev:     v3.99
I (278) cpu_start: Chip rev:         v3.0
I (283) heap_init: Initializing. RAM available for dynamic allocation:
I (290) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (296) heap_init: At 3FFB2950 len 0002D6B0 (181 KiB): DRAM
I (302) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (308) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (315) heap_init: At 4008C1A8 len 00013E58 (79 KiB): IRAM
I (322) spi_flash: detected chip: generic
I (326) spi_flash: flash io: dio
I (343) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (354) esp-idf-wav-player: Starting up
I (354) conf: IDF version: v5.0.2
I (364) conf: Chip Model: esp32
I (364) conf: This is ESP32 chip with 2 CPU cores, WiFi/BT/BLE,
I (374) conf: silicon revision 300,
I (374) conf: default mac: 24:4c:ab:f2:12:f0
I (384) sdcard: Initializing SD card
I (384) gpio: GPIO[13]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (424) sdcard: SD card info:
I (424) sdcard: Name: SD16G
I (424) sdcard: Speed: High Speed
I (424) sdcard: Frequency: 20000kHz
I (434) sdcard: Log Bus Width: 2
I (434) sdcard: Read Block Length: 9
I (444) esp-idf-wav-player: Setting up i2s
I (444) esp-idf-wav-player: Playing wav file
I (221924) esp-idf-wav-player: Rebooting in 5000 ms...
```
