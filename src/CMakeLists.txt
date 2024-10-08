find_library(MOTOR_PROTO_LIB Motor_proto)
if (NOT MOTOR_PROTO_LIB)
    message(FATAL_ERROR "Not found Motor_proto library")
endif()

find_library(POWER_PROTO_LIB Power_proto)
if (NOT POWER_PROTO_LIB)
    message(FATAL_ERROR "Not found Power_proto library")
endif()

add_executable(DataPubTest DataPubTest.cpp)
target_link_libraries(DataPubTest ${_CORE_LIBRARIES} ${MOTOR_PROTO_LIB} ${POWER_PROTO_LIB})

add_executable(DataSubTest DataSubTest.cpp)
target_link_libraries(DataSubTest ${_CORE_LIBRARIES} ${MOTOR_PROTO_LIB} ${POWER_PROTO_LIB})
