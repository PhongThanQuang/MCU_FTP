// srec.h
#ifndef SREC_H
#define SREC_H

#include <stdint.h>

#define MAX_RECORD_LENGTH 512

// Struct để lưu trữ một bản ghi SREC
typedef struct {
    char type;          // Loại bản ghi (S0, S1, S2, ...)
    uint8_t byte_count; // Số byte trong bản ghi
    uint32_t address;   // Địa chỉ nạp dữ liệu
    uint8_t data[32];   	// Dữ liệu
    uint8_t checksum;   // Checksum
} SREC_Record;

// Hàm để chuyển đổi hex sang số nguyên
uint8_t hex_to_byte(const char *hex);

// Hàm để phân tích một dòng SREC
int parse_srec_line(const char *line, SREC_Record *record);

// Hàm để xác minh checksum
int verify_checksum(const SREC_Record *record);

// Hàm đọc file SREC
void read_srec_file(const char *filename);




#endif // SREC_H
