#include <stdint.h>
#include <stdio.h>

enum State {
    WAIT_START,
    READ_ID,
    READ_HIGH,
    READ_LOW,
    READ_CHECKSUM
};

void process_packet(uint8_t id, uint8_t high, uint8_t low) {
    uint16_t speed = (high << 8) | low;
    printf("Valid Packet ID: %d | Speed: %d\n", id, speed);
}

void parse_byte(uint8_t byte) {
    static enum State state = WAIT_START;
    static uint8_t id,high,low;
    switch(state) {
        case WAIT_START:
            if (byte == 0xAA){
                state= READ_ID;
            }
            break;
        case READ_ID:
            id = byte;
            state = READ_HIGH;
            break;
        case READ_HIGH:
            high = byte;
            state = READ_LOW;
            break;
        case READ_LOW:
            low = byte;
            state= READ_CHECKSUM;
            break;
        case READ_CHECKSUM:
            uint8_t calc = id ^ high ^ low;
            if (calc==byte) {
                process_packet(id,high,low);
            }
            else {
                printf("Packet discarded due to invalid checksum.");
            }
            state = WAIT_START;
            break;
    }
}

int main() {
    uint8_t stream[] = {
        0x00, 0xAA, 0x01, 0x00, 0x64, 0x65,
        0xAA, 0x02, 0x00, 0x32, 0x00,
        0xAA, 0x03, 0x01, 0xF4, 0xF6
    };
    int size = sizeof(stream)/sizeof(stream[0]);
    for (int i=0; i<size; i++) {
        parse_byte(stream[i]);
    }
    return 0;
}