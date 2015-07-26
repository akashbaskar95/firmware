# Project name and files to compile
PROJECT_NAME  = test-sniffer
PROJECT_FILES = main.cpp
PROJECT_DIR   = .

# Location of the root directory
PROJECT_HOME = ../..

# Include the current path
INC_PATH += -I $(PROJECT_DIR)

# Configure compiling
USE_DRIVER_TPS62730 = TRUE
USE_DRIVER_ENC28J60 = TRUE
USE_NET_IEEE802154  = TRUE
USE_NET_ETHERNET    = TRUE

# Include the Makefile in the root directory
include $(PROJECT_HOME)/Makefile.include
