
OBJS = image.o png.o rgbapixel.o testimage.o scene.o testscene.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -c -g -O0 -Wall 
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : testimage testscene

testscene : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o testscene

testimage : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o testimage

rgbapixel.o : rgbapixel.cpp rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

image.o : image.cpp image.h png.h 
	$(CXX) $(CXXFLAGS) image.cpp

testimage.o : testimage.cpp image.h rgbapixel.h png.h 
	$(CXX) $(CXXFLAGS) testimage.cpp

scene.o : scene.cpp scene.h png.h image.h
	$(CXX) $(CXXFLAGS) scene.cpp

testscene.o : testscene.cpp scene.h image.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) testscene.cpp

clean :
	-rm -f *.o $(EXENAME)
