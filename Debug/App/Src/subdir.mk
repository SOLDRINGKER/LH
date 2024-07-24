################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/Emm_V5.c \
../App/Src/buzzer.c \
../App/Src/data.c \
../App/Src/data_type.c 

C_DEPS += \
./App/Src/Emm_V5.d \
./App/Src/buzzer.d \
./App/Src/data.d \
./App/Src/data_type.d 

OBJS += \
./App/Src/Emm_V5.o \
./App/Src/buzzer.o \
./App/Src/data.o \
./App/Src/data_type.o 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o App/Src/%.su App/Src/%.cyclo: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/wx/Desktop/LH/App" -I"C:/Users/wx/Desktop/LH/App/Inc" -I"C:/Users/wx/Desktop/LH/App/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/Emm_V5.cyclo ./App/Src/Emm_V5.d ./App/Src/Emm_V5.o ./App/Src/Emm_V5.su ./App/Src/buzzer.cyclo ./App/Src/buzzer.d ./App/Src/buzzer.o ./App/Src/buzzer.su ./App/Src/data.cyclo ./App/Src/data.d ./App/Src/data.o ./App/Src/data.su ./App/Src/data_type.cyclo ./App/Src/data_type.d ./App/Src/data_type.o ./App/Src/data_type.su

.PHONY: clean-App-2f-Src

