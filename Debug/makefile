################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(STOY_DEPS)),)
-include $(STOY_DEPS)
endif
ifneq ($(strip $(SAU_DEPS)),)
-include $(SAU_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(TESSCTRL_DEPS)),)
-include $(TESSCTRL_DEPS)
endif
ifneq ($(strip $(VERT_DEPS)),)
-include $(VERT_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(COMP_DEPS)),)
-include $(COMP_DEPS)
endif
ifneq ($(strip $(FRAGX_DEPS)),)
-include $(FRAGX_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(TESSEVAL_DEPS)),)
-include $(TESSEVAL_DEPS)
endif
ifneq ($(strip $(CMAP_DEPS)),)
-include $(CMAP_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(FRAG_DEPS)),)
-include $(FRAG_DEPS)
endif
ifneq ($(strip $(GEOM_DEPS)),)
-include $(GEOM_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Zbijak

# Tool invocations
Zbijak: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -Wl,--no-as-needed $(OBJS) $(USER_OBJS) $(LIBS) -o "Zbijak" -L/home/code/Data/IT/Programming/libraries/OpenGL-ultimate/lib -L/usr/lib/x86_64-linux-gnu
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(STOY_DEPS)$(SAU_DEPS)$(C_UPPER_DEPS)$(TESSCTRL_DEPS)$(VERT_DEPS)$(C_DEPS)$(COMP_DEPS)$(FRAGX_DEPS)$(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(OBJS)$(TESSEVAL_DEPS)$(CMAP_DEPS)$(CPP_DEPS)$(FRAG_DEPS)$(GEOM_DEPS) Zbijak
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
