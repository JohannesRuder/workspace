
# https://cmake.org/cmake/help/v3.5/variable/CMAKE_CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 14)

# https://cmake.org/cmake/help/v3.5/variable/CMAKE_CXX_STANDARD_REQUIRED.html
set(CMAKE_CXX_STANDARD_REQUIRED On)

# https://cmake.org/cmake/help/v3.5/variable/CMAKE_CXX_EXTENSIONS.html
set(CMAKE_CXX_EXTENSIONS Off)

# generate a JSON compile database for include-what-you-use
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Global compiler flags, which are manadatory for all targets
add_compile_options(
        #$<$<CXX_COMPILER_ID:GNU>:-Werror>
        $<$<CXX_COMPILER_ID:GNU>:-Wall>
        $<$<CXX_COMPILER_ID:GNU>:-Wextra>
        $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
        $<$<CXX_COMPILER_ID:GNU>:-Wshadow>
        $<$<CXX_COMPILER_ID:GNU>:-Wold-style-cast>
        $<$<CXX_COMPILER_ID:GNU>:-Woverloaded-virtual>
        #$<$<CXX_COMPILER_ID:GNU>:-Wsuggest-override>
        $<$<CXX_COMPILER_ID:GNU>:-Wfloat-equal>
        $<$<CXX_COMPILER_ID:GNU>:-Wconversion>
        #$<$<CXX_COMPILER_ID:GNU>:-Wsign-conversion>
        $<$<CXX_COMPILER_ID:GNU>:-Wno-error=deprecated-declarations>
        $<$<CXX_COMPILER_ID:GNU>:-Wformat-security>
        $<$<CXX_COMPILER_ID:GNU>:-pipe>
)

# Debug compiler flags, which are manadatory for all targets
add_compile_options(
        $<$<CONFIG:Debug>:$<$<CXX_COMPILER_ID:GNU>:-g>>
        $<$<CONFIG:Debug>:$<$<CXX_COMPILER_ID:GNU>:-fno-omit-frame-pointer>>
        $<$<CONFIG:Debug>:$<$<CXX_COMPILER_ID:GNU>:-fstack-protector-strong>>
)

# Release compiler flags, which are manadatory for all targets
add_compile_options(
        $<$<CONFIG:Release>:$<$<CXX_COMPILER_ID:GNU>:-O2>>
)

# Callback for CMAKE_CXX_STANDARD to verify version is 14.
function(toolchain_ad_watch_cxx_standard _variable _access _value _current_list_file _stack)
    if(_access MATCHES "MODIFIED_ACCESS" AND NOT _value MATCHES "14")
        message(WARNING "Illegal write access of '${_variable}=${_value}' in ${_current_list_file}")
    endif()
endfunction()

# Callback for CMAKE_CXX_STANDARD_REQUIRED to verify it will not be disabled.
function(toolchain_ad_watch_cxx_standard_required _variable _access _value _current_list_file _stack)
    if(_access MATCHES "MODIFIED_ACCESS" AND NOT _value MATCHES "^(1|O[Nn]|T[Rr][Uu][Ee])$")
        message(WARNING "Illegal write access of '${_variable}=${_value}' in ${_current_list_file}")
    endif()
endfunction()

# Callback for CMAKE_CXX_EXTENSIONS to verify it will not be enabled.
function(toolchain_ad_watch_cxx_extensions _variable _access _value _current_list_file _stack)
    if(_access MATCHES "MODIFIED_ACCESS" AND NOT _value MATCHES "^(0|O[Ff][Ff]|F[Aa][Ll][Ss][Ee])$")
        message(WARNING "Illegal write access of '${_variable}=${_value}' in ${_current_list_file}")
    endif()
endfunction()

# https://cmake.org/cmake/help/v3.5/command/variable_watch.html
variable_watch(CMAKE_CXX_STANDARD toolchain_ad_watch_cxx_standard)
variable_watch(CMAKE_CXX_STANDARD_REQUIRED toolchain_ad_watch_cxx_standard_required)
variable_watch(CMAKE_CXX_EXTENSIONS toolchain_ad_watch_cxx_extensions)

