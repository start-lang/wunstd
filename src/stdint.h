#ifndef STDINT_H
#define STDINT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	__int8_t_defined
#define int8_t char
#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint64_t unsigned long long
#endif

#ifdef __cplusplus
}
#endif

#endif