################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DFRDM_KE16Z -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\source" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\utilities" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\drivers" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\device" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\component\uart" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\component\lists" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\CMSIS" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\board" -I"C:\Users\ADMIN\Documents\MCUXpressoIDE_24.9.25\workspace\MCU_FTP\moc2_assignment\frdmke16z\driver_examples\gpio\led_output" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o ./utilities/fsl_str.d ./utilities/fsl_str.o

.PHONY: clean-utilities

