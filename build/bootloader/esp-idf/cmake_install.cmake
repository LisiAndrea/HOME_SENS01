# Install script for directory: /home/andrea/esp_8266/ESP8266_RTOS_SDK

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/andrea/.espressif/tools/xtensa-lx106-elf/esp-2020r3-49-gd5524c1-8.4.0/xtensa-lx106-elf/bin/xtensa-lx106-elf-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/esp8266/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/esp_common/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/log/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/partition_table/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/bootloader/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/spi_flash/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/bootloader_support/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/esptool_py/cmake_install.cmake")
  include("/home/andrea/esp_8266/projects/home_ESP8266_SENS01/build/bootloader/esp-idf/main/cmake_install.cmake")

endif()
