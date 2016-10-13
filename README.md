# TT7F-Float-Tracker

This is the main repository for [TT7F high altitude balloon tracker](http://tt7hab.blogspot.cz/2016/08/the-tt7f-hardware.html).
It includes the board and schematic Eagle files and the current state of software that is continually being worked on.

The tracker is designed around Atmel's SAM3S8B microcontroller. It acquires the current position from Ublox MAX-M8Q GPS module. As a transmitter it uses Silicon Labs Si4060 to transmit in the 70cm and 2m bands. It is also equipped with a connector and an interface for MT9D111 camera module to provide [SSDV](https://ukhas.org.uk/guides:ssdv) (Slow Scan Digital Video) capability.

The power supply consists of TPS63031 buck-boost converter providing 3.3V to the MCU, GPS module and transmitter. The MT9D111 camera module is powered by two ME6211 LDO regulators (1.8V and 2.8V). The tracker is also capable of using LTC3105 MPPC converter in connection with a pair of solar cells to charge a battery (up to 4.2V) and power the TPS63031 converter.

For programming purposes it is equipped with a USB micro B interface which can provide power to the board via MCP1700 LDO regulator as well.
