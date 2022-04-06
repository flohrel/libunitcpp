#include "libunit.h"

void	save_registers(t_register *saved_reg)
{
	register uint64_t	rbx	asm("rbx");
	register uint64_t	rsp asm("rsp");
	register uint64_t	rbp asm("rbp");
	register uint64_t	r12 asm("r12");
	register uint64_t	r13 asm("r13");
	register uint64_t	r14 asm("r14");
	register uint64_t	r15 asm("r15");

	saved_reg->rbx = rbx;
	saved_reg->rsp = rsp;
	saved_reg->rbp = rbp;
	saved_reg->r12 = r12;
	saved_reg->r13 = r13;
	saved_reg->r14 = r14;
	saved_reg->r15 = r15;
}

int32_t	check_registers(t_register *saved_reg)
{
	register uint64_t	rbx	asm("rbx");
	register uint64_t	rsp asm("rsp");
	register uint64_t	rbp asm("rbp");
	register uint64_t	r12 asm("r12");
	register uint64_t	r13 asm("r13");
	register uint64_t	r14 asm("r14");
	register uint64_t	r15 asm("r15");

	if (saved_reg->rbx != rbx ||
		saved_reg->rsp != rsp ||
		saved_reg->rbp != rbp ||
		saved_reg->r12 != r12 ||
		saved_reg->r13 != r13 ||
		saved_reg->r14 != r14 ||
		saved_reg->r15 != r15)
		return (-1);
	return (0);
}