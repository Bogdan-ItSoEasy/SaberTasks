add_library(List "")

target_sources(
        List
        PRIVATE
            List.cpp
            NodeSerializer.cpp
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/List.h
            ${CMAKE_CURRENT_LIST_DIR}/ListNode.h
)

target_include_directories(
        List
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
