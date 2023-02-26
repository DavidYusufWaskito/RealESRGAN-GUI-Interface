GCC = g++
SRC = src
RES = res

DEBUG_FLAG = -fdiagnostics-color=always -g -DDEBUG
RELEASE_FLAG = -static -s -O3 -Wl,--subsystem,windows
BUILD_PATH = build
DEBUG_INCLUDE_PATH = 	-I "include" \
						-I "D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets\include\wx-3.1" \
						-I "D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets\lib\wx\include\msw-unicode-3.1"

LINKING_DEBUG = 	-L "D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets\lib" \
					-l "wx_mswud_core-3.1.dll" \
					-l "wx_baseud-3.1.dll"

RELEASE_INCLUDE_PATH = 	-I "include" \
						-I "D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets release\include\wx-3.1" \
						-I "D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets release\lib\wx\include\msw-unicode-3.1"

LINKING_RELEASE = 	-L "D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets release\lib" \
					-l "wx_mswu_core-3.1.dll" \
					-l "wx_baseu-3.1.dll"

LINKING_RELEASE_STATIC =	-L "D:\\Programming liblaries\\wxWidgets-3.1.5\\INSTALL\\wxWidgets release (Static)\\lib" \
							-lwx_mswu_core-3.1 \
							-lwx_baseu-3.1 \
							-lwx_mswu_aui-3.1 \
							-lwxpng \
							-lwxzlib \
							-lwxjpeg \
							-lwxtiff \
							-lwxscintilla \
							-lwxregexu \
							-L "D:\\Programs\\Msys2\\mingw64\\x86_64-w64-mingw32\\lib" \
							-lkernel32 \
							-luser32 \
							-lgdi32 \
							-lwinspool \
							-lcomdlg32 \
							-ladvapi32 \
							-lshell32 \
							-lole32 \
							-loleaut32 \
							-luuid \
							-lcomctl32 \
							-lwsock32 \
							-lodbc32 \
							-lshlwapi \
							-lversion \
							-luxtheme \
							-loleacc \

DLL_DEBUG = D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets\lib
DLL_RELEASE = D:\Programming liblaries\wxWidgets-3.1.5\INSTALL\wxWidgets release\lib

all: debug release static_release
release: $(BUILD_PATH)\release\release.exe
debug: $(BUILD_PATH)\debug\debug.exe

static_release: $(BUILD_PATH)\release\release_static.exe

clean:
	del *.o

$(BUILD_PATH)\debug\wxbase315ud_gcc_custom.dll:	$(BUILD_PATH)\debug\debug.exe
	copy "$(DLL_DEBUG)\wxbase315ud_gcc_custom.dll" "$(BUILD_PATH)\debug\"

$(BUILD_PATH)\debug\wxmsw315ud_core_gcc_custom.dll: $(BUILD_PATH)\debug\debug.exe
	copy "$(DLL_DEBUG)\wxmsw315ud_core_gcc_custom.dll" "$(BUILD_PATH)\debug\"

$(BUILD_PATH)\release\wxbase315u_gcc_custom.dll: $(BUILD_PATH)\release\release.exe
	copy "$(DLL_RELEASE)\wxbase315u_gcc_custom.dll" "$(BUILD_PATH)\release\"

$(BUILD_PATH)\release\wxmsw315u_core_gcc_custom.dll: $(BUILD_PATH)\release\release.exe
	copy "$(DLL_RELEASE)\wxmsw315u_core_gcc_custom.dll" "$(BUILD_PATH)\release\"


$(BUILD_PATH)\debug\debug.exe: appd.o maind.o
	$(GCC) appd.o maind.o -o $(BUILD_PATH)\debug\debug.exe $(DEBUG_INCLUDE_PATH) $(LINKING_DEBUG)

$(BUILD_PATH)\release\release.exe: app.o main.o
	$(GCC) $(RELEASE_FLAG) app.o main.o -o $(BUILD_PATH)\release\release.exe $(RELEASE_INCLUDE_PATH) $(LINKING_RELEASE)

$(BUILD_PATH)\release\release_static.exe: app.o main.o
	$(GCC) $(RELEASE_FLAG) $(RES)\resource_compiled.res app.o main.o -o $(BUILD_PATH)\release\release_static.exe $(RELEASE_INCLUDE_PATH) $(LINKING_RELEASE_STATIC)
	
resource_compiled.res: $(RES)\resource.rc
	windres --include-dir "D:\\Programming liblaries\\wxWidgets-3.1.5\\INSTALL\\wxWidgets (Static)\\include\\wx-3.1" -J rc -O coff -i $(RES)\resource.rc -o $(RES)\resource_compiled.res

app.o: $(SRC)\app.cpp include/*.h
	$(GCC) $(RELEASE_FLAG) -c $(SRC)\app.cpp $(RELEASE_INCLUDE_PATH)

main.o: $(SRC)\main.cpp include/*.h
	$(GCC) $(RELEASE_FLAG) -c $(SRC)\main.cpp $(RELEASE_INCLUDE_PATH)

appd.o: $(SRC)\app.cpp include/*.h
	$(GCC) $(DEBUG_FLAG) -c $(SRC)\app.cpp $(DEBUG_INCLUDE_PATH) -o appd.o

maind.o: $(SRC)\main.cpp include/*.h
	$(GCC) $(DEBUG_FLAG) -c $(SRC)\main.cpp $(DEBUG_INCLUDE_PATH) -o maind.o
