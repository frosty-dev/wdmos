#include "opcodes.h"
#include "opcodes_enum.h"
#include "instruction.h"
#include "disassembler.h"
#include "context.h"
#include "instr_custom.h"

static_assert(BYTECODE_END == Bytecode::END);
static_assert(BYTECODE_RET == Bytecode::RET);
static_assert(BYTECODE_DBG_LINENO == Bytecode::DBG_LINENO);
static_assert(BYTECODE_UNK == Bytecode::UNK);

const std::unordered_map<DataType, std::string> datatype_names = {
	{ DataType::NULL_D, "NULL" },
	{ DataType::TURF, "TURF" },
	{ DataType::OBJ, "OBJ" },
	{ DataType::MOB, "MOB" },
	{ DataType::AREA, "AREA" },
	{ DataType::CLIENT, "CLIENT" },
	{ DataType::STRING, "STRING" },
	{ DataType::MOB_TYPEPATH, "MOB_TYPEPATH" },
	{ DataType::OBJ_TYPEPATH, "OBJ_TYPEPATH" },
	{ DataType::TURF_TYPEPATH, "TURF_TYPEPATH" },
	{ DataType::AREA_TYPEPATH, "AREA_TYPEPATH" },
	{ DataType::RESOURCE, "RESOURCE"},
	{ DataType::IMAGE, "IMAGE" },
	{ DataType::WORLD_D, "WORLD" },
	{ DataType::DATUM, "DATUM" },
	{ DataType::SAVEFILE, "SAVEFILE" },
	{ DataType::LIST_TYPEPATH, "LIST_TYPEPATH" },
	{ DataType::NUMBER, "NUMBER" },
	{ DataType::CLIENT_TYPEPATH, "CLIENT_TYPEPATH" },
	{ DataType::LIST, "LIST" },
	{ DataType::LIST_ARGS, "LIST_ARGS" },
	{ DataType::LIST_VERBS, "LIST_VERBS" },
	{ DataType::LIST_CONTENTS, "LIST_CONTENTS" },
	{ DataType::DATUM_TYPEPATH, "DATUM_TYPEPATH" },
	{ DataType::LIST_TURF_CONTENTS, "LIST_TURF_CONTENTS" },
};

// ----------------------------------------------------------------------------
// Mnemonic lookup

static const char* const get_mnemonic_raw(Bytecode bytecode)
{
    switch (bytecode)
    {
#define I(NUMBER, NAME, DIS) \
    case Bytecode::NAME: \
        return #NAME;
#include "opcodes_table.inl"
#undef I
	default:
		break;
    }
    return "???";
}

const char* const get_mnemonic(Bytecode bytecode)
{
    switch (bytecode)
    {
        // These string mnemonics differ from their code names.
        case Bytecode::DBG_FILE:
            return "DBG FILE";
        case Bytecode::DBG_LINENO:
            return "DBG LINENO";
        default:
            return get_mnemonic_raw(bytecode);
    }
}

// ----------------------------------------------------------------------------
// Stock disassemble callbacks

// ADD_INSTR(op) becomes dis_none
static DisassembleCallback dis_none = nullptr;

// ADD_INSTR_ARG(op, arg) becomes dis_arg<arg>
template<int COUNT>
void dis_arg(Instruction* instruction, Context* context, Disassembler* dism)
{
    for (unsigned int i = 0; i < COUNT; i++)
    {
        context->eat_add(instruction);
    }
}

// ADD_INSTR_VAR(op) becomes dis_var
void dis_var(Instruction* instruction, Context* context, Disassembler* dism)
{
    dism->disassemble_var(*instruction);
}

template<int COUNT>
void dis_arg_var(Instruction* instruction, Context* context, Disassembler* dism)
{
    dis_arg<COUNT>(instruction, context, dism);
    dis_var(instruction, context, dism);
}

// ADD_INSTR_JUMP(op, argcount) becomes dis_jump<argcount>
template<int COUNT>
void dis_jump(Instruction* instruction, Context* context, Disassembler* dism)
{
    instruction->add_jump(context->eat(instruction));
    for (unsigned int i = 1; i < COUNT; i++)
    {
        context->eat_add(instruction);
    }
}

// ----------------------------------------------------------------------------
// Disassemble callback lookup

DisassembleCallback get_disassemble_callback(std::uint32_t opcode)
{
    switch (opcode)
    {
#define I(NUMBER, NAME, DIS) \
    case NUMBER: \
        return DIS;
#include "opcodes_table.inl"
#undef I
    }
    return nullptr;
}
