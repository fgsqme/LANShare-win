cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        "src/include"
        "tools/include"
)

set(
        SORCES
        tools/DataDec.cpp
        tools/DataEnc.cpp
        tools/ByteUtils.cpp
        tools/UDPServer.cpp
        tools/TCPServer.cpp
        tools/TCPClient.cpp
        tools/NetWorldUtils.cpp
        tools/IOUtils.cpp)

add_executable(
        LANShare
        ${SORCES}
        src/LANShare.cpp)

add_executable(
        test
        src/test.cpp)
add_executable(
        gui
        src/gui.cpp)


if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(LANShare wsock32)
    target_link_libraries(test wsock32 iphlpapi)
    target_link_libraries(gui wsock32 iphlpapi)
endif ()


