// srec.c
#include "srec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t hex_to_byte(const char *hex) {
    uint8_t value = 0;
    for (int i = 0; i < 2; i++) {
        char c = hex[i];
        value <<= 4;
        if (c >= '0' && c <= '9') {
            value |= (c - '0');
        } else if (c >= 'A' && c <= 'F') {
            value |= (c - 'A' + 10);
        } else if (c >= 'a' && c <= 'f') {
            value |= (c - 'a' + 10);
        }
    }
    return value;
}

int parse_srec_line(const char *line, SREC_Record *record) {
    if (line[0] != 'S') {
        return -1; // Không phải bản ghi hợp lệ
    }

    record->type = line[1];
    record->byte_count = hex_to_byte(line + 2);

    int address_length = 0;
    switch (record->type) {
        case '0': // Header record
        case '1':
            address_length = 4; // 16-bit address
            break;
        case '2':
            address_length = 6; // 24-bit address
            break;
        case '3':
            address_length = 8; // 32-bit address
            break;
        default:
            return -1; // Không hỗ trợ loại bản ghi
    }

    record->address = 0;
    for (int i = 0; i < address_length; i += 2) {
        record->address = (record->address << 8) | hex_to_byte(line + 4 + i);
    }

    int data_start = 4 + address_length;
    int data_length = (record->byte_count - (address_length / 2) - 1);

    for (int i = 0; i < data_length; i++) {
        record->data[i] = hex_to_byte(line + data_start + (i * 2));
    }

    record->checksum = hex_to_byte(line + data_start + (data_length * 2));

    return 0;
}

int verify_checksum(const SREC_Record *record) {
    uint8_t sum = record->byte_count;

    for (int i = 0; i < (record->type == '1' ? 2 : record->type == '2' ? 3 : 4); i++) {
        sum += (record->address >> (8 * (3 - i))) & 0xFF;
    }

    for (int i = 0; i < record->byte_count - (record->type == '1' ? 3 : record->type == '2' ? 4 : 5); i++) {
        sum += record->data[i];
    }

    sum += record->checksum;

    return (sum == 0xFF);
}

void read_srec_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return;
    }

    char line[MAX_RECORD_LENGTH];
    SREC_Record record;

    while (fgets(line, sizeof(line), file)) {
        parse_srec_line(line, &record);
    }

    fclose(file);
}

