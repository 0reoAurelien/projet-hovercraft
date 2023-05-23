################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Inc/LED_BMP.s 

OBJS += \
./Core/Inc/LED_BMP.o 

S_DEPS += \
./Core/Inc/LED_BMP.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o: ../Core/Inc/%.s Core/Inc/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/LED_BMP.d ./Core/Inc/LED_BMP.o

.PHONY: clean-Core-2f-Inc

