cmake_minimum_required(VERSION 3.21)
project(Financial)

set(CMAKE_CXX_STANDARD 14)

#配置数据库连接
include_directories(C:\\Program\ Files\\MySQL\\MySQL\ Server\ 8.0\\include)
link_directories(C:\\Program\ Files\\MySQL\\MySQL\ Server\ 8.0\\lib)

add_executable(Financial main.c system.h run/run.c run/run.h db/db.h db/db.c menu/menu.c
        menu/menu.h case/case.c case/case.h myHead.h financial/financial.c financial/financial.h
        user/user.c user/user.h)

link_libraries(libmysql.lib libmysql.dll)
target_link_libraries(Financial libmysql)