#!/bin/bash
set -e

find_ndk() {
	for var in ANDROID_NDK_HOME ANDROID_NDK NDK_HOME; do
		val="${!var}"
		if [ -n "$val" ] && [ -d "$val" ]; then
			echo "$val"
			return
			fi
			done
			
			SDK_CANDIDATES=(
				"${ANDROID_HOME}"
				"${ANDROID_SDK_ROOT}"
				"${ANDROID_SDK}"
				"$HOME/Android/Sdk"
				"$HOME/android-sdk"
				"/opt/android-sdk"
				"$HOME/Library/Android/sdk"
			)
			
			for sdk in "${SDK_CANDIDATES[@]}"; do
				if [ -d "$sdk/ndk" ]; then
					# Pick the latest version directory
					latest=$(ls -1vd "$sdk/ndk"/*/ 2>/dev/null | tail -n1)
					if [ -n "$latest" ] && [ -d "$latest" ]; then
						echo "${latest%/}"
						return
						fi
						fi
						# Side-by-side ndk-bundle
						if [ -d "$sdk/ndk-bundle" ]; then
							echo "$sdk/ndk-bundle"
							return
							fi
							done
							
							# 3. ndk-build on PATH -> derive NDK root
							if command -v ndk-build &>/dev/null; then
								ndk_dir=$(dirname "$(command -v ndk-build)")
								if [ -d "$ndk_dir" ]; then
									echo "$ndk_dir"
									return
									fi
									fi
									
									return 1
}

NDK=$(find_ndk) || { echo "ERROR: Could not find Android NDK. Set ANDROID_NDK_HOME or install NDK via SDK Manager."; exit 1; }
echo "Using NDK: $NDK"

LLVM="$NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++"
if [ ! -f "$LLVM" ]; then
	echo "ERROR: clang++ not found at $LLVM"
	exit 1
	fi
	
	SRC="$1"
	if [ -z "$SRC" ]; then
		echo "Usage: $0 <source.cpp>"
		exit 1
		fi
		
		NAME=$(basename "$SRC" .cpp)
		
		INCLUDES="-I./minecraftpe/headers -I./jsoncpp/jsoncpp/include -I./RakNet/Source -I./utf8proc -I./glm -I./stb -I."
		FLAGS="-std=c++11 -fPIC -shared -D__ANDROID_API__=21 -DUSEGLES -DANDROID -Wl,--unresolved-symbols=ignore-all"
		STL="-isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/include -isystem $NDK/sources/cxx-stl/gnu-libstdc++/4.9/include/backward"
		
		# 32-bit ARM
		echo "Building armeabi-v7a..."
		$LLVM --target=armv7-none-linux-androideabi21 \
		--gcc-toolchain="$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64" \
		--sysroot="$NDK/sysroot" \
		-isystem "$NDK/sysroot/usr/include/arm-linux-androideabi" \
		-isystem "$NDK/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include" \
		$STL $FLAGS $INCLUDES -o "${NAME}-armeabi-v7a.so" "$SRC"
		
		# 64-bit ARM
		echo "Building arm64-v8a..."
		$LLVM --target=aarch64-none-linux-android21 \
		--gcc-toolchain="$NDK/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64" \
		--sysroot="$NDK/sysroot" \
		-isystem "$NDK/sysroot/usr/include/aarch64-linux-android" \
		-isystem "$NDK/sources/cxx-stl/gnu-libstdc++/4.9/libs/arm64-v8a/include" \
		$STL $FLAGS $INCLUDES -o "${NAME}-arm64-v8a.so" "$SRC"
		
		echo "Built: ${NAME}-armeabi-v7a.so and ${NAME}-arm64-v8a.so"
