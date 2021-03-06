################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/camera_app.c \
../src/ddr_init.c \
../src/ff.c \
../src/fmc_imageon_utils.c \
../src/fsbl_hooks.c \
../src/gs_to_color.c \
../src/image_mover.c \
../src/main.c \
../src/md5.c \
../src/mmc.c \
../src/nand.c \
../src/nor.c \
../src/pcap.c \
../src/ps7_init.c \
../src/qspi.c \
../src/rsa.c \
../src/sd.c \
../src/video_detector.c \
../src/video_frame_buffer.c \
../src/video_generator.c \
../src/video_resolution.c \
../src/xtpg_app.c 

LD_SRCS += \
../src/lscript.ld 

S_UPPER_SRCS += \
../src/fsbl_handoff.S 

OBJS += \
./src/camera_app.o \
./src/ddr_init.o \
./src/ff.o \
./src/fmc_imageon_utils.o \
./src/fsbl_handoff.o \
./src/fsbl_hooks.o \
./src/gs_to_color.o \
./src/image_mover.o \
./src/main.o \
./src/md5.o \
./src/mmc.o \
./src/nand.o \
./src/nor.o \
./src/pcap.o \
./src/ps7_init.o \
./src/qspi.o \
./src/rsa.o \
./src/sd.o \
./src/video_detector.o \
./src/video_frame_buffer.o \
./src/video_generator.o \
./src/video_resolution.o \
./src/xtpg_app.o 

C_DEPS += \
./src/camera_app.d \
./src/ddr_init.d \
./src/ff.d \
./src/fmc_imageon_utils.d \
./src/fsbl_hooks.d \
./src/gs_to_color.d \
./src/image_mover.d \
./src/main.d \
./src/md5.d \
./src/mmc.d \
./src/nand.d \
./src/nor.d \
./src/pcap.d \
./src/ps7_init.d \
./src/qspi.d \
./src/rsa.d \
./src/sd.d \
./src/video_detector.d \
./src/video_frame_buffer.d \
./src/video_generator.d \
./src/video_resolution.d \
./src/xtpg_app.d 

S_UPPER_DEPS += \
./src/fsbl_handoff.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../system_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../system_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


