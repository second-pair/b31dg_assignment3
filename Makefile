TOOLCHAIN=GCC_ARM
PLATFORM=LPC1768

make: srcs

clean-libs:
	if exist lib-builds rmdir /Q /S lib-builds

libs: clean-libs
	mkdir lib-builds
	mbed compile -t $(TOOLCHAIN) -m $(PLATFORM) --build=lib-builds --library --no-archive --source=libraries

clean-srcs:
	if exist src-builds rmdir /Q /S src-builds

srcs: clean-srcs
	mkdir src-builds
	mbed compile -t $(TOOLCHAIN) -m $(PLATFORM) --build=src-builds --source=lib-builds --source=sources --source=headers
	if exist src-builds\lib-builds.bin copy /Y /B src-builds\lib-builds.bin latest-build.bin /B

clean: clean-libs clean-srcs clean-extras
	if exist BUILD rmdir /Q /S BUILD
	if exist mbed_settings.pyc del /Q mbed_settings.pyc
	if exist latest-build.bin del /Q latest-build.bin

all: libs srcs
