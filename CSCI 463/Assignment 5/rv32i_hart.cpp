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
#include "rv32i_hart.h"
#include "registerfile.h"	 

#include <vector>
#include <iomanip>      
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>     

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostringstream;
using std::dec;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::to_string;
using std::ostream;

typedef hex hexCall;

/**
* @brief		This function tells the simulator to execute any instruction if
*               hart is not halted
*
* @param hdr	header parameter that prints to the left of output
*
*******************************************************************************/
void rv32i_hart::tick (const string &hdr) 
{
    insn_counter += 4;

    if(show_registers)
    {
        regs.dump("");
    }

    if(show_registers) 
    {
        cout << " pc " << hexCall::to_hex32(pc) << endl; 
    }

    uint32_t insn = mem.get32(pc);

    if(show_instructions)
    {
        cout << hdr << setw(8) << setfill('0') << right << hexCall::to_hex32(pc) << ": " << hexCall::to_hex32(insn) << "  ";
        exec(insn, &cout);
    }
    
    else
    {
        exec(insn, nullptr);
    }

}

/**
* @brief		This function dumps the entire state of the hart. Each line
*               starts with the hdr and then dump GP regs, followed by a 
*               dump of the pc register
*
* @param hdr	header parameter that prints to the left of output
*
*******************************************************************************/
void rv32i_hart::dump(const string &hdr) const
{
    regs.dump(hdr);   
    cout << " pc " << hexCall::to_hex32(pc) << endl; 
}

/**
* @brief		This function resets the rv32i object and the registerfile
*
*******************************************************************************/
void rv32i_hart::reset() 
{
    pc = 0;
    regs.reset();          
    insn_counter = 0;    
    halt = false; 
    halt_reason = "none";
}

/**
* @brief		This function executes the given RV32I instruction by using the 
*               funct3 and funct7 as well as opcode to execute the correct
*               instruction to be ran
*
* @param insn	address of the instruction
* @param pos	string output  
*
*******************************************************************************/
void rv32i_hart::exec(uint32_t insn, ostream *pos)
{
    uint32_t f3 = get_funct3(insn);
    uint32_t f7 = get_funct7(insn);
    uint32_t opcode = get_opcode(insn);

    switch(opcode)
	{
	    case opcode_lui:   exec_lui(insn, pos); 
        return;
		case opcode_auipc: exec_auipc(insn, pos);
        return;
		case opcode_jal:   exec_jal(insn, pos); 
        return;
        case opcode_jalr:  exec_jalr(insn, pos); 
        return;
        case opcode_system:
		    switch(f3)
			{
				case funct3_beq:
					switch(insn)
                    {
					    case insn_ecall:    exec_ecall(pos); 
                        return;
					    case insn_ebreak:   exec_ebreak(pos); 
                        return;
						default:            exec_illegal_insn(insn, pos); 
                        return;
				    }
                    break;
                
                case funct3_csrrs:  exec_csrrs(insn, pos);
                return;
		        default:            exec_illegal_insn(insn,pos); 
                return;
			}
            break;

		case opcode_btype:
			switch(f3)
			{
				case funct3_beq:	exec_beq(insn, pos); 
                return;
				case funct3_bne:    exec_bne(insn, pos); 
                return;
				case funct3_blt:	exec_blt(insn, pos); 
                return;
				case funct3_bge:	exec_bge(insn, pos); 
                return;
				case funct3_bltu:   exec_bltu(insn, pos); 
                return;
				case funct3_bgeu:	exec_bgeu(insn, pos);  
                return;
				default:            exec_illegal_insn(insn,pos); 
                return;
			}
            break;

		case opcode_load_imm:
			switch(f3)
			{
				case funct3_lb:	  exec_lb(insn,pos); 
                return;
				case funct3_lh:   exec_lh(insn,pos); 
                return;
				case funct3_lw:	  exec_lw(insn,pos); 
                return;
				case funct3_lbu:	exec_lbu(insn,pos);
                return;
				case funct3_lhu: 	exec_lhu(insn,pos); 
                return;
				default:          exec_illegal_insn(insn,pos);
                return;
			}
            break;

		case opcode_stype:
			switch(f3)
			{
			    case funct3_sb:	   exec_sb(insn,pos); 
                return;
				case funct3_sh:    exec_sh(insn,pos); 
                return;
				case funct3_sw:	   exec_sw(insn,pos); 
                return;
				default:           exec_illegal_insn(insn,pos); 
                return;
			}
            break;

		case opcode_alu_imm:
			switch(f3)
			{
				case funct3_add:	    exec_addi(insn, pos); 
                return;
				case funct3_slt:	    exec_slti(insn, pos); 
                return;
				case funct3_sltu:	    exec_sltiu(insn, pos); 
                return;
				case funct3_xor:      exec_xori(insn, pos); 
                return;
				case funct3_or:	    	exec_ori(insn, pos); 
                return;
				case funct3_sll:	    exec_slli(insn, pos); 
                return;
				case funct3_and:	    exec_andi(insn, pos); 
                return;
				case funct3_srx:	   
					switch(f7)
					{
						case funct7_srl: exec_srli(insn,pos); 
                        return;
						case funct7_sra: exec_srai(insn,pos); 
                        return;
						default:         exec_illegal_insn(insn,pos); 
                        return;
					}
                    break;

				default:  exec_illegal_insn(insn,pos); 
                return;
			}
            break;

		case opcode_rtype:
			switch(f3)
			{
				case funct3_add:	    
					switch(f7)
					{
						case funct7_add: exec_add(insn,pos); 
                        return;
						case funct7_sub: exec_sub(insn,pos); 
                        return;
						default: 		     exec_illegal_insn(insn,pos); 
                        return;
					}
                    break;

				case funct3_sll:	    exec_sll(insn, pos); 
                return;
				case funct3_slt:      exec_slt(insn, pos); 
                return;
				case funct3_sltu:	    exec_sltu(insn, pos); 
                return;
				case funct3_xor:	    exec_xor(insn, pos); 
                return;
				case funct3_and:	    exec_and(insn, pos); 
                return;
				case funct3_or:	      exec_or(insn, pos); 
                return;
				case funct3_srx:	    
					switch(f7)
					{
						case funct7_srl: exec_srl(insn, pos); 
                        return;
						case funct7_sra: exec_sra(insn, pos); 
                        return;
						default:         exec_illegal_insn(insn,pos); 
                        return;
					}
                    break;

			    default: exec_illegal_insn(insn,pos); 
                return;
			}
        break;
	}
}

/**
* @brief		This function is run when there is no opcode that correlates with
*               the given instruction
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_illegal_insn (uint32_t insn , std :: ostream *pos)
{
    halt = true;
    halt_reason = " ILLEGAL instruction ";       

    if(pos != nullptr)
    {
        string str = render_illegal_insn(insn);     
        *pos << setw(instruction_width) << setfill(' ') << left << str << ": " << hexCall::to_hex0x32(insn);
    }
}

/**
* @brief		This function executes the lui instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_lui(uint32_t insn, std :: ostream *pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_u = get_imm_u(insn);
    regs.set(rd, imm_u);    

    if(pos)
    {
        string str = render_lui(insn);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(imm_u) << endl;
    }
    pc += 4; 
}

/**
* @brief		This function executes the aui instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_auipc(uint32_t insn, std :: ostream *pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_u = get_imm_u(insn); 
    regs.set(rd, pc + imm_u);     

    if(pos)
    {
        string str = render_auipc(insn);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(pc) << " + " << hexCall::to_hex0x32(imm_u) << " = " << hexCall::to_hex0x32(imm_u + pc) << endl;
    }

    pc = pc + 4; 
}

/**
* @brief		This function executes the ecall by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_ecall(std::ostream* pos)
{
    if(pos)
    {
        string str = render_ecall(0);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// ECALL" << endl;
    }
    halt = true;    
}

/**
* @brief		This function executes the ebreak by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_ebreak(std::ostream* pos)
{

    if (pos)
    {
        string str = render_ebreak(0);
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// HALT " << endl;
    }

    halt = true ;
    halt_reason = " EBREAK instruction ";
}

/**
* @brief		This function executes the jal instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_jal(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_j = get_imm_j(insn);
    regs.set(rd, pc + 4);      

    if(pos)
    {
        string str = render_jal(pc,insn);   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(pc + 4) << ",  pc = " << hexCall::to_hex0x32(pc) << " + " << hexCall::to_hex0x32(imm_j) << " = " << hexCall::to_hex0x32(pc + imm_j) << endl;
    }

    pc = pc + imm_j;   
}

/**
* @brief		This function executes the jalr instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_jalr(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t val = (regs.get(rs1) + imm_i) & ~1;  
    
    if(pos)
    {
        string str = render_jalr(insn);   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(pc + 4)  << ",  pc = (" << hexCall::to_hex0x32(imm_i) << " + " << hexCall::to_hex0x32(regs.get(rs1)) << ") & " << "0xfffffffe" << " = " << hexCall::to_hex0x32(val) << endl;
    }

    regs.set(rd, pc + 4);    
    pc = val;            
}

/**
* @brief		This function executes the beq instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_beq(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t val = (regs.get(rs1) == regs.get(rs2))? imm_b : 4;  

    if(pos)
    {
        string str = render_btype(pc, insn, "beq");  
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// pc += (" << hexCall::to_hex0x32(regs.get(rs1)) << " == " <<  hexCall::to_hex0x32(regs.get(rs2)) << " ? " << hexCall::to_hex0x32(imm_b) << " : 4) = " << hexCall::to_hex0x32(pc + val) << std::endl;
    }

    pc += val;    
}

/**
* @brief		This function executes the bne instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_bne(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t val = (regs.get(rs1) != regs.get(rs2))? imm_b : 4;

    if(pos){
        string str = render_btype(pc, insn, "bne");  
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// pc += (" << hexCall::to_hex0x32(regs.get(rs1)) << " != " <<  hexCall::to_hex0x32(regs.get(rs2)) << " ? " << hexCall::to_hex0x32(imm_b) << " : 4) = " << hexCall::to_hex0x32(pc + val) << std::endl;
    }

    pc += val;     
}

/**
* @brief		This function executes the blt instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_blt(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t val = (regs.get(rs1) < regs.get(rs2))? imm_b : 4;

    if(pos)
    {
        string str = render_btype(pc, insn, "blt");   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// pc += (" << hexCall::to_hex0x32(regs.get(rs1)) << " < " <<  hexCall::to_hex0x32(regs.get(rs2)) << " ? "<< hexCall::to_hex0x32(imm_b) << " : 4) = " << hexCall::to_hex0x32(pc + val) << std::endl;
    }

    pc += val;      
}

/**
* @brief		This function executes the bge instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_bge(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t val = (regs.get(rs1) >= regs.get(rs2))? imm_b : 4;

    if(pos)
    {
        string str = render_btype(pc, insn, "bge");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// pc += (" << hexCall::to_hex0x32(regs.get(rs1)) << " >= " <<  hexCall::to_hex0x32(regs.get(rs2)) << " ? "<< hexCall::to_hex0x32(imm_b)<< " : 4) = " << hexCall::to_hex0x32(pc + val) << std::endl;
    }

    pc += val;     
}

/**
* @brief		This function executes the bltu instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_bltu(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t val = ((uint32_t) regs.get(rs1) < (uint32_t) regs.get(rs2))? imm_b : 4;;

    if(pos)
    {
        string str = render_btype(pc, insn, "bltu");   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// pc += (" << hexCall::to_hex0x32(regs.get(rs1)) << " <U " <<  hexCall::to_hex0x32(regs.get(rs2)) << " ? " << hexCall::to_hex0x32(imm_b)<< " : 4) = " << hexCall::to_hex0x32(pc + val) << std::endl;
    }
    
    pc += val;     
}

/**
* @brief		This function executes the bgeu instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_bgeu(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t val = ((uint32_t) regs.get(rs1) >= (uint32_t) regs.get(rs2))? imm_b : 4;

    if(pos)
    {
        string str = render_btype(pc, insn, "bgeu");   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// pc += (" << hexCall::to_hex0x32(regs.get(rs1)) << " >=U " <<  hexCall::to_hex0x32(regs.get(rs2)) << " ? " << hexCall::to_hex0x32(imm_b) << " : 4) = " << hexCall::to_hex0x32(pc + val) << std::endl;
    }

    pc += val;       
}

/**
* @brief		This function executes the add instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_add(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t val = regs.get(rs1)+regs.get(rs2);

    if(pos)
    {
        string str = render_rtype(insn, "add"); 
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(regs.get(rs2)) << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);  
    pc += 4;    
}

/**
* @brief		This function executes the sub instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sub(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);

    if(pos)
    {
        string str = render_rtype(insn, "sub");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " - " << hexCall::to_hex0x32(regs.get(rs2)) << " = " << hexCall::to_hex0x32(regs.get(rs1) - regs.get(rs2)) << std::endl;
    }

    regs.set(rd, regs.get(rs1) - regs.get(rs2));   
    pc += 4;   
}

/**
* @brief		This function executes the srl instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_srl(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t val = (uint32_t)regs.get(rs1)>>(regs.get(rs2) & 0x01f);
    
    if(pos)
    {
        string str = render_rtype(insn, "srl");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " >> " << (uint32_t)regs.get(rs2)%32 << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the sra instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sra(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t val = regs.get(rs1)>>((regs.get(rs2) & 0x01f));

    if(pos)
    {
        string str = render_rtype(insn, "sra");   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " >> " << ((uint32_t)regs.get(rs2))%32 << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);  
    pc += 4;     
}

/**
* @brief		This function executes the sll instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sll(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t val = regs.get(rs1)<<((regs.get(rs2)& 0x01f));

    if(pos)
    {
        string str = render_rtype(insn, "sll");  
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " << " << (uint32_t) regs.get(rs2)%32 << " = " << hexCall::to_hex0x32(val) << std::endl;
    } 

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the slt instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_slt(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t val = (regs.get(rs1)<regs.get(rs2) ? 1 : 0);

    if(pos)
    {
        string str = render_rtype(insn, "slt");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = (" << hexCall::to_hex0x32(regs.get(rs1)) << " < " << hexCall::to_hex0x32(regs.get(rs2)) << ") ? " << "1 " << ": " << "0 " << "= " << hexCall::to_hex0x32(val) << std::endl; 
    }

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the sltu instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sltu(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t val = ((uint32_t)regs.get(rs1)<(uint32_t)regs.get(rs2) ? 1 : 0);

    if(pos)
    {
        string str = render_rtype(insn, "sltu");   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = (" << hexCall::to_hex0x32(regs.get(rs1)) << " <U " << hexCall::to_hex0x32(regs.get(rs2)) << ") ? " << "1 " << ": " << "0" << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);  
    pc += 4;    
}

/**
* @brief		This function executes the xor instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_xor(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t val = ((regs.get(rs1)^regs.get(rs2)));

    if(pos)
    {
        string str = render_rtype(insn, "xor");  
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " <<  hexCall::to_hex0x32(regs.get(rs1)) << " ^ " << hexCall::to_hex0x32(regs.get(rs2)) << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);  
    pc += 4;   
}

/**
* @brief		This function executes the or instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_or(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t rd = get_rd(insn);
    uint32_t val = regs.get(rs1) | regs.get(rs2);

    if(pos)
    {
        string str = render_rtype(insn, "or");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " | " << hexCall::to_hex0x32(regs.get(rs2)) << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd,val);  
    pc += 4;     
}

/**
* @brief		This function executes the and instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_and(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    uint32_t rd = get_rd(insn);
    uint32_t val = regs.get(rs1) & regs.get(rs2);

    if(pos)
    {
        string str = render_rtype(insn, "and");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " & " << hexCall::to_hex0x32(regs.get(rs2)) << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd,val);   
    pc += 4;      
}

/**
* @brief		This function executes the sb instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sb(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    uint32_t val = mem.get8(regs.get(rs1) + imm_s);
    mem.set8(regs.get(rs1) + imm_s, regs.get(rs2)&0x000000ff);

    if(pos)
    {
        string str = render_stype(insn, "sb");   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// m8(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_s) << ") = " << hexCall::to_hex0x32(val) << std::endl;
    }

    pc += 4;   
}

/**
* @brief		This function executes the sh instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sh(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    uint32_t val = mem.get16(regs.get(rs1) + imm_s);
    mem.set16(regs.get(rs1) + imm_s, regs.get(rs2)&0x0000ffff);

    if(pos)
    {
        string str = render_stype(insn, "sh");  
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// m16(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_s) << ") = " << hexCall::to_hex0x32(val) << std::endl;
    }

    pc += 4;   
}

/**
* @brief		This function executes the sw instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sw(uint32_t insn, std::ostream* pos)
{
    uint32_t rs1 = get_rs1(insn);
    uint32_t rs2 = get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    uint32_t val = mem.get32(regs.get(rs1) + imm_s);
    mem.set32(regs.get(rs1) + imm_s, regs.get(rs2));

    if(pos)
    {
        string str = render_stype(insn, "sw");   
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// m32(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_s) << ") = " << hexCall::to_hex0x32(val) << std::endl;    
    }

    pc += 4;   
}

/**
* @brief		This function executes the lb instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_lb(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    int8_t val = mem.get8(imm_i + regs.get(rs1));

    if(pos)
    {
        string str = render_itype_load(insn, "lb");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = sx(m8(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_i) << "))" << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;   
}

/**
* @brief		This function executes the lh instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_lh(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    int16_t val = mem.get16(regs.get(rs1) + imm_i);

    if(pos)
    {
        string str = render_itype_load(insn, "lh");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = sx(m16(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_i) << "))" << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;   
}

/**
* @brief		This function executes the lw instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_lw(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val = mem.get32(regs.get(rs1) + imm_i);

    if(pos)
    {
        string str = render_itype_load(insn, "lw");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = sx(m32(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_i) << ")) = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the lbu instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_lbu(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint8_t val = mem.get8(regs.get(rs1) + imm_i)&0x000000ff;

    if(pos)
    {
        string str = render_itype_load(insn, "lbu");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = zx(m8(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_i) << "))" << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);  
    pc += 4;    
}

/**
* @brief		This function executes the lhu instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_lhu(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint16_t val = mem.get16(regs.get(rs1) + imm_i)&0x0000ffff;

    if(pos)
    {
        string str = render_itype_load(insn, "lhu");    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = zx(m16(" << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_i) << "))" << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the addi instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_addi(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);

    if(pos)
    {
        string str = render_itype_alu(insn, "addi", imm_i);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " + " << hexCall::to_hex0x32(imm_i) << " = " << hexCall::to_hex0x32(regs.get(rs1) + imm_i) << std::endl;
    }

    regs.set(rd, regs.get(rs1) + imm_i);   
    pc += 4;    
}

/**
* @brief		This function executes the slti instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_slti(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val = (regs.get(rs1) < imm_i)? 1 : 0;

    if(pos)
    {
        string str = render_itype_alu(insn, "slti", imm_i);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = (" << hexCall::to_hex0x32(regs.get(rs1)) << " < " << imm_i << ") ? " << "1 " << ": " << "0" << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;      
}

/**
* @brief		This function executes the sltiu instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_sltiu(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val = ((uint32_t) regs.get(rs1) <  imm_i)? 1 :0;

    if(pos)
    {
        string str = render_itype_alu(insn, "sltiu", imm_i);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = (" <<  hexCall::to_hex0x32(regs.get(rs1)) << " <U " << imm_i << ") ? " << "1 " << ": " << "0" << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the xori instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_xori(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val = ((regs.get(rs1)^imm_i));

    if(pos)
    {
        string str = render_itype_alu(insn, "xori", imm_i);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " ^ " << hexCall::to_hex0x32(imm_i) << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the ori instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_ori(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val =  ((regs.get(rs1) | imm_i));

    if(pos)
    {
        string str = render_itype_alu(insn, "ori", imm_i);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " | " << hexCall::to_hex0x32(imm_i) << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;   
}

/**
* @brief		This function executes the andi instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_andi(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val = ((regs.get(rs1) & imm_i));

    if(pos)
    {
        string str = render_itype_alu(insn, "andi", imm_i);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " & " << hexCall::to_hex0x32(imm_i) << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;    
}

/**
* @brief		This function executes the slli instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_slli(uint32_t insn, std::ostream* pos)
{
    int32_t imm_i = get_imm_i(insn);
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val = regs.get(rs1) << imm_i;

    if(pos)
    {
        string str = render_itype_alu(insn, "slli", imm_i % XLEN);
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " << " << imm_i << " = " << hexCall::to_hex0x32(val) << std::endl;
    }
    regs.set(rd, val);
    pc += 4;
}

/**
* @brief		This function executes the srli instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_srli(uint32_t insn, std::ostream* pos)
{
    int32_t imm_i = get_imm_i(insn);
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t val = (uint32_t)regs.get(rs1) >> imm_i;

    if(pos)
    {
        string str = render_itype_alu(insn, "srli", imm_i%XLEN);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(regs.get(rs1)) << " >> " << imm_i << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;     
}

/**
* @brief		This function executes the srai instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_srai(uint32_t insn, std::ostream* pos)
{
    uint32_t shamt = (insn & 0x01ffffff);
    int32_t imm_i = get_imm_i(shamt);
    uint32_t rd = get_rd(insn);
    int32_t rs1 = regs.get(get_rs1(insn));
    uint32_t val = rs1 >> imm_i;

    if(pos)
    {
        string str = render_itype_alu(insn, "srai", imm_i%XLEN);    
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// x" << rd << " = " << hexCall::to_hex0x32(rs1) << " >> " << imm_i << " = " << hexCall::to_hex0x32(val) << std::endl;
    }

    regs.set(rd, val);   
    pc += 4;     
}

/**
* @brief		This function executes the csrrs instruction by calling the render 
*               function and outputting to pos
*
* @param insn	address of the instruction
* @param pos	string output 
*
*******************************************************************************/
void rv32i_hart::exec_csrrs(uint32_t insn, std::ostream* pos)
{
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t csr = get_imm_i(insn) & 0x00000fff;

    if (csr != 0xf14 || rs1 != 0)
    {
        halt = true;
        halt_reason = "Illegal CSR in CRRSS instruction";
    }
    if (pos)
    {
        string str = render_csrrx(insn, "csrrs");
        *pos << setw(instruction_width) << setfill(' ') << left << str << "// " << render_reg(rd) << " = " << std::dec << mhartid << std::endl;
    }
    if (!halt)
    {
        regs.set(rd, mhartid);
        pc += 4;
    }
}