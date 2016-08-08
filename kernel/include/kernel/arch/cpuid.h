#ifndef _KERNEL_ARCH_CPUID_H
#define _KERNEL_ARCH_CPUID_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define CPUID_BRAND_LENGTH 49

enum {
	CPUID_VENDOR_AMD,
	CPUID_VENDOR_INTEL,
	CPUID_VENDOR_UNKNOWN,
	CPUID_VENDOR_LENGTH
};

enum {
	CPUID_FEATURE_FPU,
	CPUID_FEATURE_VME,
	CPUID_FEATURE_DE,
	CPUID_FEATURE_PSE,
	CPUID_FEATURE_TSC,
	CPUID_FEATURE_MSR,
	CPUID_FEATURE_PAE,
	CPUID_FEATURE_MCE,
	CPUID_FEATURE_CX8,
	CPUID_FEATURE_APIC,
	CPUID_FEATURE_SEP,
	CPUID_FEATURE_MTRR,
	CPUID_FEATURE_PGE,
	CPUID_FEATURE_MCA,
	CPUID_FEATURE_CMOV,
	CPUID_FEATURE_PAT,
	CPUID_FEATURE_PSE36,
	CPUID_FEATURE_PSN,
	CPUID_FEATURE_CLFSH,
	CPUID_FEATURE_DS,
	CPUID_FEATURE_ACPI,
	CPUID_FEATURE_MMX,
	CPUID_FEATURE_FXSR,
	CPUID_FEATURE_SSE,
	CPUID_FEATURE_SSE2,
	CPUID_FEATURE_SS,
	CPUID_FEATURE_HTT,
	CPUID_FEATURE_TM,
	CPUID_FEATURE_PBE,
	CPUID_FEATURE_SSE3,
	CPUID_FEATURE_PCLMULQDQ,
	CPUID_FEATURE_DTES64,
	CPUID_FEATURE_MONITOR,
	CPUID_FEATURE_DSCPL,
	CPUID_FEATURE_VMX,
	CPUID_FEATURE_SMX,
	CPUID_FEATURE_EST,
	CPUID_FEATURE_TM2,
	CPUID_FEATURE_SSSE3,
	CPUID_FEATURE_CNXTID,
	CPUID_FEATURE_FMA,
	CPUID_FEATURE_CMPXCHG16B,
	CPUID_FEATURE_XTPR,
	CPUID_FEATURE_PDCM,
	CPUID_FEATURE_PCID,
	CPUID_FEATURE_DCA,
	CPUID_FEATURE_SSE41,
	CPUID_FEATURE_SSE42,
	CPUID_FEATURE_X2APIC,
	CPUID_FEATURE_MOVBE,
	CPUID_FEATURE_POPCNT,
	CPUID_FEATURE_TSCD,
	CPUID_FEATURE_AESNI,
	CPUID_FEATURE_XSAVE,
	CPUID_FEATURE_OSXSAVE,
	CPUID_FEATURE_AVX,
	CPUID_FEATURE_RDTSCP,
	CPUID_FEATURE_NX,
	CPUID_FEATURE_GBP,
	CPUID_FEATURE_SYSCALL,
	CPUID_FEATURE_X86_64,
	CPUID_FEATURE_INV_TSC,
	CPUID_FEATURE_LENGTH
};

bool cpuid_feature(int);
const char *cpuid_feature_string(int);
int cpuid_vendor(void);
const char *cpuid_vendor_string(int);
void cpuid_brand(char *buffer, size_t length);
void cpuid_address_size(uint8_t *physical, uint8_t *virtual);

#endif