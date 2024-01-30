set(HEADERS
        slot_map_low_complexity.h
        slot_map.h
        ordered_slot_map.h
)

add_library(slot_map INTERFACE)
target_include_directories(slot_map INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(slot_map INTERFACE cxx_std_17)
