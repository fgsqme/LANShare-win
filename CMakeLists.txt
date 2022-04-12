cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 11)

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
        tools/UDPClient.cpp
        tools/TCPServer.cpp
        tools/TCPClient.cpp
        tools/NetWorldUtils.cpp
        tools/TimeTools.cpp
        tools/IOUtils.cpp
        tools/CodeUtils.cpp
        src/Utils.cpp)

add_executable(
        LANShare
        ${SORCES}
        src/Device.cpp
        src/LANShare.cpp
        src/main.cpp)

add_executable(
        test
        src/test.cpp)
add_executable(
        gui
        ${SORCES}
        src/gui.cpp)

add_executable(
        guitest
        ${SORCES}
        src/guitest.cpp)

add_executable(
        LGui
        ${SORCES}
        src/LGui.cpp
        src/Device.cpp
        src/LANShare.cpp
)

add_executable(
        MFCGui
        ${SORCES}
        src/MFCGui.cpp
)


if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(LANShare wsock32)
    target_link_libraries(test wsock32 iphlpapi)
    target_link_libraries(gui wsock32 iphlpapi)
    target_link_libraries(guitest wsock32 iphlpapi)
    target_link_libraries(LGui wsock32 iphlpapi)
    target_link_libraries(MFCGui wsock32 iphlpapi)
endif ()


