################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC_Mcal.c \
../source/BootLoader_Handle.c \
../source/GPIO_Control.c \
../source/GPIO_Mcal.c \
../source/KE16_Flash.c \
../source/LPIT_Control.c \
../source/LPIT_Mcal.c \
../source/NVIC_Mcal.c \
../source/PCC_Mcal.c \
../source/Port_Mcal.c \
../source/Srec.c \
../source/UART_Mcal.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/ADC_Mcal.d \
./source/BootLoader_Handle.d \
./source/GPIO_Control.d \
./source/GPIO_Mcal.d \
./source/KE16_Flash.d \
./source/LPIT_Control.d \
./source/LPIT_Mcal.d \
./source/NVIC_Mcal.d \
./source/PCC_Mcal.d \
./source/Port_Mcal.d \
./source/Srec.d \
./source/UART_Mcal.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/ADC_Mcal.o \
./source/BootLoader_Handle.o \
./source/GPIO_Control.o \
./source/GPIO_Mcal.o \
./source/KE16_Flash.o \
./source/LPIT_Control.o \
./source/LPIT_Mcal.o \
./source/NVIC_Mcal.o \
./source/PCC_Mcal.o \
./source/Port_Mcal.o \
./source/Srec.o \
./source/UART_Mcal.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DFRDM_KE16Z -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\source" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\utilities" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\drivers" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\device" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\component\uart" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\component\lists" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\CMSIS" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\board" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\frdmke16z\driver_examples\gpio\led_output" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ADC_Mcal.d ./source/ADC_Mcal.o ./source/BootLoader_Handle.d ./source/BootLoader_Handle.o ./source/GPIO_Control.d ./source/GPIO_Control.o ./source/GPIO_Mcal.d ./source/GPIO_Mcal.o ./source/KE16_Flash.d ./source/KE16_Flash.o ./source/LPIT_Control.d ./source/LPIT_Control.o ./source/LPIT_Mcal.d ./source/LPIT_Mcal.o ./source/NVIC_Mcal.d ./source/NVIC_Mcal.o ./source/PCC_Mcal.d ./source/PCC_Mcal.o ./source/Port_Mcal.d ./source/Port_Mcal.o ./source/Srec.d ./source/Srec.o ./source/UART_Mcal.d ./source/UART_Mcal.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

