makefilesToRun='
	src/btstack/ios-armv7.mk

	src/libogg/ios-armv7.mk
	
	src/tremor/ios-armv7.mk
	
	src/libsndfile/ios-armv7.mk
	
	src/minizip/ios-armv7.mk
	
	src/boost/ios-armv7.mk
'

source runMakefiles.sh

runMakefiles $@

