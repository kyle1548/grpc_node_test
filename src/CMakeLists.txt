
find_library(MOTOR_PROT_LIB Motor_proto PATHS ${HOME}/corgi/lib)
if (NOT MOTOR_PROT_LIB)
    message(FATAL_ERROR "not found aaaaaaaa")
endif()


find_library(POWER_PROT_LIB Power_proto PATHS ${HOME}/corgi/lib)
if (NOT POWER_PROT_LIB)
    message(FATAL_ERROR "not found bbbbbbbbbbbbb")
endif()

add_executable(DataPubTest DataPubTest.cpp)
target_link_libraries(DataPubTest ${_CORE_LIBRARIES} ${MOTOR_PROT_LIB} ${POWER_PROT_LIB})

add_executable(DataSubTest DataSubTest.cpp)
target_link_libraries(DataSubTest ${_CORE_LIBRARIES} ${MOTOR_PROT_LIB} ${POWER_PROT_LIB})