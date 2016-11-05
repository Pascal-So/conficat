CFLAGS=-Wall -Wextra -D_GLIBCXX_DEBUG

conficat: conficat.cpp argparse.cpp argparse.h
	g++ $(CFLAGS) -std=c++11 -o conficat conficat.cpp argparse.cpp argparse.h
