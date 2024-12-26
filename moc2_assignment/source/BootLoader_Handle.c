#include "BootLoader_Handle.h"


#define ADDRESS_VALUE_MODE 0x15000


char buffer_receive_command_char[520] ;
uint8_t length_data_command = 0;


void array_to_uint32_array(uint8_t *array, uint32_t *output) {
    if (array == NULL || output == NULL) {
        return; // Không làm gì nếu mảng NULL
    }

    for (int i = 0; i < 4; i++) {
        output[i] = 0;
        output[i] |= ((uint32_t)array[i * 4 + 0] << 24); // Byte cao nhất
        output[i] |= ((uint32_t)array[i * 4 + 1] << 16);
        output[i] |= ((uint32_t)array[i * 4 + 2] << 8);
        output[i] |= ((uint32_t)array[i * 4 + 3]);       // Byte thấp nhất
    }
}


void ReceiveData_UART(uint8_t Data, SREC_Record *record) {
    if (Data == '\n' || Data == '\r') {
        buffer_receive_command_char[length_data_command] = '\0'; // Kết thúc chuỗi
        parse_srec_line(buffer_receive_command_char,record);
        length_data_command = 0; // Đặt lại độ dài lệnh
        memset(buffer_receive_command_char, 0, sizeof(buffer_receive_command_char));
    } else {
        if (length_data_command < sizeof(buffer_receive_command_char) - 1) {
            buffer_receive_command_char[length_data_command++] = Data;
        }
    }
}

void writeNewFirware(uint32_t address, uint8_t *Data){
	//for (int i = 0 ; i < 4 ;i++){
		FLASH_Write(address,array_to_uint32(Data));
	//}

}
