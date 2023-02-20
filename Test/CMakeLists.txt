set(TestTargetName ${TargetName}Test)
include(TestDirectory)
gen_path_to_here()

set(TestTarget_SRC
    Test1.cpp
)

include_directories(
    ${GTEST_INCLUDE}
    ${Http_INCLUDE}
    ${Sockets_INCLUDE}
    ${Utils_INCLUDE}
    ${Threads_INCLUDE}
    ${ParserBase_INCLUDE}
)

add_executable(
    ${TestTargetName}
    ${TestTarget_SRC}
)

target_link_libraries(
    ${TestTargetName} 
    ${GTEST_LIBRARY}
    ${Http_LIBRARY}
    ${Sockets_LIBRARY}
    ${Utils_LIBRARY}
    ${Threads_LIBRARY}
    ${ParserBase_LIBRARY}
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)


if (Http_AUTO_RUN_TEST)
    run_test(${TestTargetName})
endif()
