SET(CMAKE_VERBOSE_MAKEFILE TRUE) 

ADD_DEFINITIONS(-Wall -Iserialstream -DQT_THREAD_SUPPORT -D_REENTRANT -DQT_NO_DEBUG -DIQRMODULE)

SET(QT_MT_REQUIRED TRUE)
FIND_PACKAGE(Qt4 REQUIRED)

SET(libSrc
    serialstream/SerialStream.cc
    serialstream/SerialStreamBuf.cc
    moduleArduinoAnalog.cpp
    arduino.cc
)


INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../
  ${QT_INCLUDE_DIR}
)

ADD_LIBRARY( moduleArduinoAnalog SHARED ${libSrc})



SET_TARGET_PROPERTIES( moduleArduinoAnalog PROPERTIES PREFIX "")




TARGET_LINK_LIBRARIES( moduleArduinoAnalog m)
INSTALL(TARGETS 
   moduleArduinoAnalog
  LIBRARY DESTINATION lib/iqr/Modules/
  ARCHIVE DESTINATION lib/iqr/Modules/
  RUNTIME DESTINATION bin
)

cmake_minimum_required(VERSION 2.4)
