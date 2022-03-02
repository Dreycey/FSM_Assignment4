################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/FSM_StopLight.c \
../source/LEDPWM.c \
../source/UART.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/stoplight_fsm.c \
../source/timer.c \
../source/tsi_module.c 

OBJS += \
./source/FSM_StopLight.o \
./source/LEDPWM.o \
./source/UART.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/stoplight_fsm.o \
./source/timer.o \
./source/tsi_module.o 

C_DEPS += \
./source/FSM_StopLight.d \
./source/LEDPWM.d \
./source/UART.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/stoplight_fsm.d \
./source/timer.d \
./source/tsi_module.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/dreyceyalbin/Documents/MCUXpressoIDE_11.2.1/workspace/FSM_StopLight/board" -I"/Users/dreyceyalbin/Documents/MCUXpressoIDE_11.2.1/workspace/FSM_StopLight/source" -I"/Users/dreyceyalbin/Documents/MCUXpressoIDE_11.2.1/workspace/FSM_StopLight" -I"/Users/dreyceyalbin/Documents/MCUXpressoIDE_11.2.1/workspace/FSM_StopLight/drivers" -I"/Users/dreyceyalbin/Documents/MCUXpressoIDE_11.2.1/workspace/FSM_StopLight/CMSIS" -I"/Users/dreyceyalbin/Documents/MCUXpressoIDE_11.2.1/workspace/FSM_StopLight/utilities" -I"/Users/dreyceyalbin/Documents/MCUXpressoIDE_11.2.1/workspace/FSM_StopLight/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


