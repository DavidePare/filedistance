cmake_minimum_required(VERSION 3.16)
project(filedistance C)
add_compile_options("-fstack-protector-all")
set(CMAKE_C_STANDARD 99)

add_executable(filedistance main.c filepath.h filepath.c filedistance.h filedistance.c utility.h utility.c operationfile.h operationfile.c applymodify.h applymodify.c generatefilem.h generatefilem.c)