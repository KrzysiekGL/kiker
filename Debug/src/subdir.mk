################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/Mesh.cpp \
../src/Model.cpp \
../src/ShaderProgram.cpp \
../src/main.cpp 

OBJS += \
./src/Camera.o \
./src/Mesh.o \
./src/Model.o \
./src/ShaderProgram.o \
./src/main.o 

CPP_DEPS += \
./src/Camera.d \
./src/Mesh.d \
./src/Model.d \
./src/ShaderProgram.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Wl,--no-as-needed "$<" -o "$@" -D_DEBUG -I/home/code/Data/IT/Programming/libraries/OpenGL-ultimate/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"
	@echo 'Finished building: $<'
	@echo ' '


