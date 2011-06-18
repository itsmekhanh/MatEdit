################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GL_Window.cpp \
../src/Material_Window.cpp \
../src/main.cpp 

OBJS += \
./src/GL_Window.o \
./src/Material_Window.o \
./src/main.o 

CPP_DEPS += \
./src/GL_Window.d \
./src/Material_Window.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/covise/covise/extern_libs/src/OpenSceneGraph-2.8.2/include -I/home/covise/covise/extern_libs/src/mxml-2.6 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


