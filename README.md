### UART Byte-by-Byte Parser (State Machine)



##### Overview:

This project implements a robust byte-by-byte UART parser using a finite state machine in C. It processes a continuous stream of incoming data and extracts valid packets while handling noise and corrupted data gracefully.



##### Packet Structure:

0xAA--->ID--->HIGH--->LOW--->CHECKSUM

for example: 0xAA--->0x03--->0x01--->0xF4--->0xF6



* Start Byte: 0xAA (always)
* CHECKSUM = ID ^ HIGH ^ LOW



##### Design Approach:

* Implemented a **finite state machine** using *enum* and *switch-case*.
* Used **static variables** to maintain state across function calls.
* Ensured **non-blocking behavior** (no delays or loops).
* Reset state machine safely on invalid packets.



##### Features:

* Handles noisy input streams
* Detects invalid checksum and discards corrupted packets
* Processes data byte-by-byte (real embedded system behavior)



##### Sample Output:

Valid Packet ID: 1 | Speed: 100

Invalid checksum. Packet discarded.

Valid Packet ID: 3 | Speed: 500

