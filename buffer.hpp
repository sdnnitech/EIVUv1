#pragma once

#include "packet.hpp"
#include "option.hpp"
#include "random.hpp"

#define PROC_CLT_S 0
#define PROC_CLT_R 1
#define PROC_SRV 2
#define TOTAL_CLT 3
#define TOTAL_SRV 4
#define NONE 5

#define INFO_CPU NONE

#define CPU_BIND

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

constexpr int32_t SIZE_RING = 256;
//constexpr int_fast32_t SIZE_POOL = 256;
constexpr int32_t SIZE_POOL = 163456;
//constexpr int_fast32_t NUM_PMOD = SIZE_POOL / 2;
constexpr int32_t AVAIL_FLAG = 0b0000000100000000;
constexpr int32_t USED_FLAG = 0b0000000000000001;

class desc {
public:
	int64_t entry_index;
	int32_t len;
	int16_t id;
	int16_t flags;

	void set_param(int32_t);
	void set_param_avoid(int16_t);
	void delete_info();
	void delete_info_avoid();
};

class ring {
private:
	int32_t pindex;
	int16_t size;
	int16_t rsrv_idx;
	int16_t recv_idx;
	int16_t proc_idx;
public:
	desc* descs;

private:
	void wait_push(int32_t);
	void wait_pull(int32_t);

public:
	void init_descs();
	ring();
	void operator=(ring&&);

	void zero_push(buf*, int32_t, bool);

	void ipush(packet**, buf*, int32_t, bool);
	void ipush_avoid(int32_t, bool);
	void pull(packet**, buf*, int32_t, bool);
	void pull_avoid(int32_t);
#if defined(AVOID_SRV)
	void move_packet(ring*, int32_t);
#else
	void move_packet(ring*, buf*, int32_t);
#endif
	void move_packet_read(ring*, packet[], int32_t);
	void set_ringaddr(ring*);
	void set_pooladdr(packet*);
};

#include "cbuffer.hpp"
