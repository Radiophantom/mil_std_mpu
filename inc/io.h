
#ifndef __IO_H__
#define __IO_H__

#define IORD(base,addr)       (*(uint16_t*)(base+addr))
#define IOWR(base,addr,data)  (*(uint16_t*)(base+addr) = data)

#define _SET_BITS(data,mask,offset)  ((data & mask) << offset)
#define _GET_BITS(data,mask,offset)  ((data >> offset) & mask)

#define GET_FIELD_VALUE(name,data)   _GET_BITS(data,name ## _MASK,name ## _OFST)
#define SET_FIELD_VALUE(name,data)   _SET_BITS(data,name ## _MASK,name ## _OFST)

#endif

