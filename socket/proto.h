#ifndef PROTO_H__
#define PRORO_H__

#define NAMESIZE	11

#define RCVPORT		"26666"
#define IPSTRSIZE	40

struct msg_st
{
	uint8_t name[NAMESIZE];
	uint32_t math;
	uint32_t chinese;

}__attribute__((packed));

#endif
