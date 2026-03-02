cmake_minimum_required(VERSION 3.5)
project(minecraftpe08decomp LANGUAGES CXX)
#evil jsoncpp overring this thing </3
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)

if(ANDROID)

else()
	find_package(OpenGL REQUIRED)

	if(WIN32)

	else()
		find_package(OpenAL REQUIRED)
	endif()

	find_package(SDL REQUIRED)
endif()

find_package(ZLIB REQUIRED)


if(ANDROID)
	add_compile_options(-fpermissive -Wno-out-of-line-declaration -Wno-write-strings -Winfinite-recursion -Werror=return-type -g -DUSEGLES -DIMTOOLAZYTOFIX16ERRS -DPCTWEAKS)
else()
	add_compile_options(-fpermissive -Wno-out-of-line-declaration -Wno-write-strings -Winfinite-recursion -Werror=return-type -g0 -DIMTOOLAZYTOFIX16ERRS -DPCTWEAKS)
endif()

file(GLOB_RECURSE IMPLCPP *.cpp)
file(GLOB_RECURSE IMPLC *.c)
file(GLOB_RECURSE HEADC *.h)
file(GLOB_RECURSE HEADCPP *.hpp)

if(ANDROID)
	add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

	add_library(minecraftpe SHARED ${IMPLCPP} ${IMPLC} ${HEADC} ${HEADCPP})
	target_include_directories(minecraftpe PUBLIC "headers/" ${ANDROID_NDK}/sources/android/native_app_glue/)
	target_link_libraries(minecraftpe ZLIB::ZLIB EGL GLESv1_CM RakNetLibStatic native_app_glue jsoncpp_lib utf8proc log native_app_glue android)
else()
	add_executable(minecraftpe08decomp ${IMPLCPP} ${IMPLC} ${HEADC} ${HEADCPP})

	target_include_directories(minecraftpe08decomp PUBLIC "headers/")
	target_link_libraries(minecraftpe08decomp)
	if(WIN32)
		target_link_libraries(minecraftpe08decomp pthread dsound dxguid)
	else()
		target_link_libraries(minecraftpe08decomp ${OPENAL_LIBRARY})
	endif()
	target_link_libraries(minecraftpe08decomp ZLIB::ZLIB ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} RakNetLibStatic jsoncpp_lib utf8proc)
endif()
