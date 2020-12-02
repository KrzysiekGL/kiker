################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/Line.cpp \
../src/Mesh.cpp \
../src/Model.cpp \
../src/Rectangle.cpp \
../src/ShaderProgram.cpp \
../src/Shape.cpp \
../src/main.cpp 

OBJS += \
./src/Camera.o \
./src/Line.o \
./src/Mesh.o \
./src/Model.o \
./src/Rectangle.o \
./src/ShaderProgram.o \
./src/Shape.o \
./src/main.o 

CPP_DEPS += \
./src/Camera.d \
./src/Line.d \
./src/Mesh.d \
./src/Model.d \
./src/Rectangle.d \
./src/ShaderProgram.d \
./src/Shape.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Wl,--no-as-needed "$<" -o "$@" -D_DEBUG -I/home/code/Data/IT/Programming/libraries/OpenGL-ultimate/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"
	@echo 'Finished building: $<'
	@echo ' '


