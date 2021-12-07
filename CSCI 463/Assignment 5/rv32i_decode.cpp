////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #5	Semester: Spring 2021
//
//	Due: Tuesday, March 23, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "hex.h"
#include "memory.h"
#include "rv32i_decode.h"

#include <iostream> 
#include <cassert>
#include <iomanip>
#include <sstream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
using std::dec;
using std::setw;
using std::setfill;
using std::left;
using std::right;

typedef hex hexCall;

/**
* @brief		This function extracts and returns the disassembled 
*			instruction text, capable of handling any instruction
*			value. 
*
* @param addr		Address of simulated memory
* @param insn		Address of the instruction
*
* @return		Will return a string with disassembled instruction
*******************************************************************************/
string rv32i_decode::decode(uint32_t addr, uint32_t insn)
{
	if(insn == insn_ecall)
	{
		return render_ecall(insn);
	}
	else if (insn == insn_ebreak)
	{
		return render_ebreak(insn);
	}

	switch(get_opcode(insn))
	{
		default: return render_illegal_insn(insn);

		case opcode_lui: return render_lui(insn);
		case opcode_auipc: return render_auipc(insn);

		case opcode_jal: return render_jal(addr, insn);
		case opcode_jalr: return render_jalr(insn);

		case opcode_btype:
			switch(get_funct3(insn))
			{
				default: return render_illegal_insn(insn);
				case funct3_beq: return render_btype(addr, insn, "beq");
				case funct3_bne: return render_btype(addr, insn, "bne");
				case funct3_blt: return render_btype(addr, insn, "blt");
				case funct3_bge: return render_btype(addr, insn, "bge");
				case funct3_bltu: return render_btype(addr, insn, "bltu");
				case funct3_bgeu: return render_btype(addr, insn, "bgeu");				
			}
			assert(0 && "unrecognized funct3"); // impossible

		case opcode_load_imm:
			switch(get_funct3(insn))
			{
				default: return render_illegal_insn(insn);
				case funct3_lb: return render_itype_load(insn, "lb");
				case funct3_lh: return render_itype_load(insn, "lh");
				case funct3_lw: return render_itype_load(insn, "lw");
				case funct3_lbu: return render_itype_load(insn, "lbu");
				case funct3_lhu: return render_itype_load(insn, "lhu");
			}

		case opcode_stype:
			switch(get_funct3(insn))
			{
				default: return render_illegal_insn(insn);
				case funct3_sb: return render_stype(insn, "sb");
				case funct3_sh: return render_stype(insn, "sh");
				case funct3_sw: return render_stype(insn, "sw");
			}
			assert(0 && "unrecognized funct3"); //impossible


		case opcode_alu_imm:
			switch (get_funct3(insn))
			{
				default: return render_illegal_insn(insn);
				case funct3_add: return render_itype_alu(insn, "addi", get_imm_i(insn));
				case funct3_slt: return render_itype_alu(insn, "slti", get_imm_i(insn));
				case funct3_sltu: return render_itype_alu(insn, "sltiu", get_imm_i(insn));
				case funct3_xor: return render_itype_alu(insn, "xori", get_imm_i(insn));
				case funct3_or: return render_itype_alu(insn, "ori", get_imm_i(insn));
				case funct3_and: return render_itype_alu(insn, "andi", get_imm_i(insn));
				case funct3_sll: return render_itype_alu(insn, "slli", get_imm_i(insn)%XLEN);
				case funct3_srx:
					switch(get_funct7(insn))
					{
						default: return render_illegal_insn(insn);
						case funct7_sra: return render_itype_alu(insn, "srai", get_imm_i(insn)%XLEN);
						case funct7_srl: return render_itype_alu(insn, "srli", get_imm_i(insn)%XLEN);
					}
					assert(0 && "unrecognized funct7"); // impossible
			}
			assert(0 && "unrecognized funct3"); // impossible

		case opcode_rtype:
			switch (get_funct3(insn))
			{
				default: return render_illegal_insn(insn);
				case funct3_add: 
					switch (get_funct7(insn))
					{
						default: return render_illegal_insn(insn);
						case funct7_add: return render_rtype(insn, "add");
						case funct7_sub: return render_rtype(insn, "sub");
					}
					assert(0 && "unrecognized funct7");
				case funct3_sll: return render_rtype(insn, "sll");
				case funct3_slt: return render_rtype(insn, "slt");
				case funct3_sltu: return render_rtype(insn, "sltu");
				case funct3_xor: return render_rtype(insn, "xor");
				case funct3_srx:
					switch(get_funct7(insn))
					{
						default: return render_illegal_insn(insn);
						case funct7_srl: return render_rtype(insn, "srl");
						case funct7_sra: return render_rtype(insn, "sra");						
					}
					assert(0 && "unrecognized funct7"); // impossible				
				case funct3_or: return render_rtype(insn, "or");
				case funct3_and: return render_rtype(insn, "and");
			}
			assert(0 && "unrecognized funct3"); // impossible
			
		case opcode_system:
			switch (get_funct3(insn))
			{
				default: return render_illegal_insn(insn);	
				case funct3_csrrw: return render_csrrx(insn, "csrrw");
				case funct3_csrrs: return render_csrrx(insn, "csrrs");				
				case funct3_csrrc: return render_csrrx(insn, "csrrc");
				case funct3_csrrwi: return render_csrrx(insn, "csrrwi");
				case funct3_csrrsi: return render_csrrx(insn, "csrrsi");
				case funct3_csrrci: return render_csrrx(insn, "csrrci");			
			}
			assert(0 && "unrecognized funct3"); // impossible

	}
	assert(0 && "unrecognized opcode"); // It should be impossible to ever get here!
}

/**
* @brief	This function extracts and returns the opcode from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the opcode of the given instruction
*******************************************************************************/
uint32_t rv32i_decode::get_opcode(uint32_t insn)
{
	return (insn & 0x0000007f);
}

/**
* @brief	This function extracts and returns the rd from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the rd of the given instruction
*******************************************************************************/
uint32_t rv32i_decode::get_rd(uint32_t insn)
{
	return ((insn & 0x00000f80) >> 7);
}

/**
* @brief	This function extracts and returns the funct3 from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the funct3 of the given instruction
*******************************************************************************/
uint32_t rv32i_decode::get_funct3(uint32_t insn)
{
	uint32_t funct3 = (insn & 0x00007000);
	funct3 >>= 12;

	return funct3;
}

/**
* @brief	This function extracts and returns the rs1 from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the rs1 of the given instruction
*******************************************************************************/
uint32_t rv32i_decode::get_rs1(uint32_t insn)
{
	uint32_t rs1 = (insn & 0x000f8000);
	rs1 >>= 15;

	return rs1;
}

/**
* @brief	This function extracts and returns the rs2 from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the rs2 of the given instruction
*******************************************************************************/
uint32_t rv32i_decode::get_rs2(uint32_t insn)
{
	uint32_t rs2 = (insn & 0x01f00000);
	rs2 >>= 20;

	return rs2;
}

/**
* @brief	This function extracts and returns the funct7 from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the funct7 of the given instruction
*******************************************************************************/
uint32_t rv32i_decode::get_funct7(uint32_t insn)
{
	uint32_t funct7 = (insn & 0xfe000000);
	funct7 >>= 25;

	return funct7;
}

/**
* @brief	This function extracts and returns the imm_i from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the imm_i of the given instruction
*******************************************************************************/
int32_t rv32i_decode::get_imm_i(uint32_t insn)
{
//	int32_t imm_i = ((insn & 0xfff00000) >> 20);
//
//	if (insn & 0x80000000)
//	{
//		imm_i |= 0xfffff000;
//	}
//	
//	return imm_i;

    int32_t imm_i = (insn & 0x01f00000) >> (20 - 0);
    imm_i |= (insn & 0xfe000000) >> (25 - 5);

    if (insn & 0x80000000)
        imm_i |= 0xfffff000;

    return imm_i;

}

/**
* @brief	This function extracts and returns the imm_u from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return		Returns the imm_u of the given instruction
*******************************************************************************/
int32_t rv32i_decode::get_imm_u(uint32_t insn)
{
	return (insn & 0xfffff000);
}

/**
* @brief	This function extracts and returns the imm_b from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the imm_b of the given instruction
*******************************************************************************/
int32_t rv32i_decode::get_imm_b(uint32_t insn)
{
	int32_t imm_b = 0;
	if (insn & 0x80000000)
	{
		imm_b |= 0xfffff000;
	}
	imm_b |= ((insn & 0x7e000000) >> (25 - 5));
	imm_b |= ((insn & 0x00000f00) >> (8 - 1));
	imm_b |= ((insn & 0x00000080) << 4);
	return imm_b;
}

/**
* @brief	This function extracts and returns the imm_s from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the imm_s of the given instruction
*******************************************************************************/
int32_t rv32i_decode::get_imm_s(uint32_t insn)
{
	int32_t imm_s = ((insn & 0xfe000000) >> (25-5));
	if (insn & 0x80000000)
	{
		imm_s |= 0xfffff000; // sign-extend the left
	}
	imm_s |= ((insn & 0x00000f80) >> (7 - 0));
	return imm_s;
}

/**
* @brief	This function extracts and returns the imm_j from the given
*		instruction
*
* @param insn	Address of the instruction
*
* @return	Returns the imm_j of the given instruction
*******************************************************************************/
int32_t rv32i_decode::get_imm_j(uint32_t insn)
{
	int32_t imm_j = (insn & 0x000ff000);
	if (insn & 0x80000000)
	{
		imm_j |= 0xfff00000;
	}
	imm_j |= (insn & 0x7fe00000) >> (21 - 1);
	imm_j |= (insn & 0x00100000) >> (20 - 11);
	return imm_j;
}

/**
* @brief		This function will void the instruction and return 
*
* @param insn		Address of the instruction
*
* @return		Returns comment saying there has been an error
*******************************************************************************/
string rv32i_decode::render_illegal_insn(uint32_t insn)
{
	(void) insn;
	return "ERROR: UNIMPLEMENTED INSTRUCTION"; 
}

/**
* @brief		This function renders the lui instruction and creates the 
*			proper output for display 
*
* @param insn		Address of the instruction
*
* @return		Returns string output of formatted lui instruction
*******************************************************************************/
string rv32i_decode::render_lui(uint32_t insn)
{
	uint32_t rd = get_rd(insn);
	int32_t imm_u = get_imm_u(insn);
	ostringstream os;

	os << render_mnemonic("lui") << render_reg(rd) << "," << hex::to_hex0x20((imm_u >> 12) & 0x0fffff);
	return os.str();
}

/**
* @brief		This function renders the auipc instruction and creates the 
*			proper output for display 
*
* @param insn		Address of the instruction
*
* @return		Returns string output of formatted auipc instruction
*******************************************************************************/
string rv32i_decode::render_auipc(uint32_t insn)
{
	uint32_t rd = get_rd(insn);
	int32_t imm_u = get_imm_u(insn);
	ostringstream os;

	os << render_mnemonic("auipc") << render_reg(rd) << "," << hex::to_hex0x20((imm_u >> 12) & 0x0fffff);
	return os.str();
}

/**
* @brief		This function renders the jal instruction and creates the 
*			proper output for display
*
* @param insn		Address of the instruction
*
* @return		Returns string output of formatted jal instruction
*******************************************************************************/
string rv32i_decode::render_jal(uint32_t addr, uint32_t insn)
{
	uint32_t rd = get_rd(insn);
	int32_t imm_j = get_imm_j(insn);
	ostringstream os;

	os << render_mnemonic("jal") << render_reg(rd) << "," << hex::to_hex0x32(imm_j + addr);
	return os.str();
}

/**
* @brief		This function renders the jalr instruction and creates the 
*			proper output for display 
*
* @param insn		Address of the instruction
*
* @return		Returns string output of formatted jalr instruction
*******************************************************************************/
string rv32i_decode::render_jalr(uint32_t insn)
{
	uint32_t rd = get_rd(insn);
	int32_t imm_i = get_imm_i(insn);
	uint32_t rs1 = get_rs1(insn);
	ostringstream os;

	os << render_mnemonic("jalr") << render_reg(rd) << "," << render_base_disp(imm_i, rs1) ;
	return os.str();
}

/**
* @brief		This function renders the btype instruction and creates the 
*			proper output for display
*
* @param addr		address of simulated memory
* @param insn		Address of the instruction
* @param mnemonic   	label for given instruction
*
* @return		Returns string output of the formatted btype instruction
*******************************************************************************/
string rv32i_decode::render_btype(uint32_t addr, uint32_t insn, const char *mnemonic)
{
	uint32_t rs1 = get_rs1(insn);
	uint32_t rs2 = get_rs2(insn);
	int32_t imm_b = get_imm_b(insn);
	ostringstream os;

	os << render_mnemonic(mnemonic) << "x" << dec << rs1 << ",x" << rs2 << ",0x" << setfill('0') << setw(8) << right << std::hex << (imm_b + addr);
	return os.str();
}

/**
* @brief		This function renders the itype load instruction and creates the 
*			proper output for display
*
* @param insn		Address of the instruction
* @param mnemonic  	 label for given instruction
*
* @return		Returns string output of the formatted itype load instruction
*******************************************************************************/
string rv32i_decode::render_itype_load(uint32_t insn, const char *mnemonic)
{
	int32_t rd = get_rd(insn);
	int32_t imm_i = get_imm_i(insn);
	uint32_t rs1 = get_rs1(insn);
	ostringstream os;

	os << render_mnemonic(mnemonic) << render_reg(rd) << "," << imm_i << "(" << render_reg(rs1) << ")";
	return os.str();
}

/**
* @brief		This function renders the stype instruction and creates the 
*			proper output for display
*
* @param insn		Address of the instruction
* @param mnemonic   	label for given instruction
*
* @return		Returns string output of the formatted stype instruction
*******************************************************************************/
string rv32i_decode::render_stype(uint32_t insn, const char *mnemonic)
{
	uint32_t rs1 = get_rs1(insn);
	uint32_t rs2 = get_rs2(insn);
	int32_t imm_s = get_imm_s(insn);
	ostringstream os;

	os << render_mnemonic(mnemonic) << render_reg(rs2) << "," << render_base_disp(imm_s, rs1);

	return os.str();
}

/**
* @brief		This function renders the itype alu instruction and creates the 
*			proper output for display
*
* @param insn		Address of the instruction
* @param mnemonic   	label for given instruction
* @param imm_i      	immediate i value
*
* @return		Returns string output of the formatted itype alu instruction
*******************************************************************************/
string rv32i_decode::render_itype_alu(uint32_t insn, const char *mnemonic, int32_t imm_i)
{
	uint32_t rs1 = get_rs1(insn);
	uint32_t rd = get_rd(insn);
	ostringstream os;

	os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_reg(rs1) << "," << imm_i;

	return os.str();
}

/**
* @brief		This function renders the rtype instruction and creates the 
*			proper output for display
*
* @param insn		Address of the instruction
* @param mnemonic   	label for given instruction
*
* @return		Returns string output of the formatted rtype instruction
*******************************************************************************/
string rv32i_decode::render_rtype(uint32_t insn, const char *mnemonic)
{
	uint32_t rs1 = get_rs1(insn);
	uint32_t rs2 = get_rs2(insn);
	int32_t rd = get_rd(insn);
	ostringstream os;

	os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_reg(rs1) << "," << render_reg(rs2);
	return os.str();
}

/**
* @brief		This function renders the ecall 
*
* @param insn		address of the instruction
*
* @return		Returns the call to render_mnemonic with ecall as param
*******************************************************************************/
string rv32i_decode::render_ecall(uint32_t insn)
{
	(void) insn;
	return render_mnemonic("ecall");
}

/**
* @brief		This function renders the ebreak 
*
* @param insn		address of the instruction
*
* @return		Returns the call to render_mnemonic with ebreak as param
*******************************************************************************/
string rv32i_decode::render_ebreak(uint32_t insn)
{
	(void) insn;
	return render_mnemonic("ebreak");
}

/**
* @brief		This function renders the cssrx load instruction
*
* @param insn		address of instruction
* @param mnemonic	label for given instruction
*
* @return		returns string output of formatted csrrx load instruction
*******************************************************************************/
string rv32i_decode::render_csrrx(uint32_t insn, const char *mnemonic)
{
	uint32_t rs1 = get_rs1(insn);
	uint32_t rd = get_rd(insn);
	int32_t csr = get_imm_i(insn);
	ostringstream os;

	os << render_mnemonic(mnemonic) << render_reg(rd) << "," << hexCall::to_hex0x12(csr) << "," << render_reg(rs1);
	return os.str();
}

/**
* @brief		This function renders the cssrxi instruction
*
* @param insn		address of instruction
* @param mnemonic	label for given instruction
*
* @return		returns string output of formatted csrrxi instruction
*******************************************************************************/
string rv32i_decode::render_csrrxi(uint32_t insn, const char *mnemonic)
{
	uint32_t rs1 = get_rs1(insn);
	uint32_t rd = get_rd(insn);
	int32_t csr = get_imm_i(insn);
	ostringstream os;

	os << render_mnemonic(mnemonic) << render_reg(rd) << ","  << hexCall::to_hex0x12(csr) << "," << render_reg(rs1);
	//std::dec << rs1;
	return os.str();
}

/**
* @brief		This function will render the registers with given number r
*
* @param r		register
*
* @return		Returns string output of the formatted register
*******************************************************************************/
string rv32i_decode::render_reg(int r)
{
	ostringstream os;
	os << "x" << r;
	return os.str();
}

/**
* @brief		This function will render the operands for the instructions that 
*			have and addressing mode
*
* @param base		the immediate value
* @param disp		the displacement
*
* @return		Returns a string with both the base and the disp
*******************************************************************************/
string rv32i_decode::render_base_disp(uint32_t base, int32_t disp)
{
	ostringstream os;

	os << dec << static_cast<int>(base) << "(x" << disp << ")";
	return os.str();
}

/**
* @brief		This function renders the label as well as the spacing for 
*			visual display
*
* @param m		mnemoinic aka label of instruction
*
* @return		Returns string output of the formatted mnemonic 
*******************************************************************************/
string rv32i_decode::render_mnemonic(const string &m)
{
	ostringstream os;
	os << left << setw(mnemonic_width) << setfill(' ') << m;
	return os.str();
}
