find_library(GRPC_PROTO_LIB grpc_proto_lib)
if (NOT GRPC_PROTO_LIB)
    message(FATAL_ERROR "Not found GRPC_PROTO Library.")
endif()

add_executable(DataPubTest DataPubTest.cpp)
target_link_libraries(DataPubTest ${_CORE_LIBRARIES} ${GRPC_PROTO_LIB})

add_executable(DataSubTest DataSubTest.cpp)
target_link_libraries(DataSubTest ${_CORE_LIBRARIES} ${GRPC_PROTO_LIB})
