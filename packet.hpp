#include <string.h>
#include <iostream>
#include <bitset>
#include <thread>
#include <atomic>
#include <mutex>

#include "cpuinfo.hpp"

//#define NUM_PACKET 5000000
//#define NUM_PACKET 10000000
//#define NUM_PACKET 20000000
#define NUM_PACKET 100000000
#define SIZE_PACKET 16

void do_none();

constexpr uint_fast16_t DUMMY_SIZE = SIZE_PACKET - sizeof(uint32_t) - sizeof(uint32_t) - sizeof(uint16_t);

class packet {
public:
	uint_fast32_t id;
	uint_fast8_t len;
	char dummy[DUMMY_SIZE];
	uint_fast32_t verification;

	packet();
	packet(uint_fast32_t);
	packet(uint_fast32_t, const char*);

	void print();
	void set_verification();

};
#include "cpacket.hpp"
