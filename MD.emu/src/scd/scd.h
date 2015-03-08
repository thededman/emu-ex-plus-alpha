#pragma once

#include "m68k.h"
#include "cell_map.c"
#include "LC89510.h"
#include "cd_sys.h"
#include "gfx_cd.h"
#include <genplus-gx/m68k/musashi/InstructionCycleTableSCD.hh>
#include <mednafen/cdrom/CDAccess.h>
#include <imagine/util/builtins.h>

struct SegaCD
{
	constexpr SegaCD(): cpu(m68kCyclesSCD, 1) {}
	M68KCPU cpu;
	bool isActive = 0;
	uchar busreq = 0;
	uint stopwatchTimer = 0;
	uint counter75hz = 0;
	int timer_int3 = 0;
	uint volume = 1024;

	uchar gate[0x200]{};

	_scd_toc TOC;
	int32 cddaLBA = 0;
	uint16 cddaDataLeftover = 0;
	bool CDD_Complete = 0;
	uint Status_CDD = 0;
	uint Status_CDC = 0;
	int Cur_LBA = 0;
	uint Cur_Track = 0;
	int File_Add_Delay = 0;
	CDC cdc;
	CDD cdd;

	union PrgRam
	{
		constexpr PrgRam() {}
		uchar b[512 * 1024]{};
		uchar bank[4][128 * 1024];
	};
	PrgRam prg;

	union WordRam
	{
		constexpr WordRam() { }
		uchar ram2M[0x40000]{};
		uchar ram1M[2][0x20000];
	};
	WordRam word;

	Rot_Comp rot_comp;

	union PCMRam
	{
		constexpr PCMRam() {}
		uchar b[0x10000]{};
		uchar bank[0x10][0x1000];
	};
	PCMRam pcmMem;

	struct PCM
	{
		constexpr PCM() {}
		uchar control = 0; // reg7
		uchar enabled = 0; // reg8
		uchar cur_ch = 0;
		uchar bank = 0;

		struct Channel // 08, size 0x10
		{
			constexpr Channel() {}
			uchar regs[8]{};
			uint  addr = 0;	// .08: played sample address
		} ch[8];
	};
	PCM pcm;

	uchar bcramReg = 0;
	uchar audioTrack = 0;
	bool subResetPending = 0;
	bool delayedDMNA = 0;
};

extern SegaCD sCD;

// Pre-formatted internal BRAM
static const uchar fmtBram[4*0x10] =
{
	0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x00, 0x7d, 0x00, 0x7d, 0x00, 0x7d, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x53, 0x45, 0x47, 0x41, 0x5f, 0x43, 0x44, 0x5f, 0x52, 0x4f, 0x4d, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x52, 0x41, 0x4d, 0x5f, 0x43, 0x41, 0x52, 0x54, 0x52, 0x49, 0x44, 0x47, 0x45, 0x5f, 0x5f, 0x5f,
	// SEGA_CD_ROM.....RAM_CARTRIDGE___
};

// Pre-formatted 64K SRAM cart
static const uchar fmt64kSram[4*0x10] =
{
	0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x03, 0xfd, 0x03, 0xfd, 0x03, 0xfd, 0x03, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x53, 0x45, 0x47, 0x41, 0x5f, 0x43, 0x44, 0x5f, 0x52, 0x4f, 0x4d, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x52, 0x41, 0x4d, 0x5f, 0x43, 0x41, 0x52, 0x54, 0x52, 0x49, 0x44, 0x47, 0x45, 0x5f, 0x5f, 0x5f,
	// SEGA_CD_ROM.....RAM_CARTRIDGE___
};

extern uchar bram[0x2000];

void scd_interruptSubCpu(uint irq);
void scd_resetSubCpu();
void scd_runSubCpu(uint cycles);
void scd_init();
void scd_deinit();
void scd_reset();
void scd_memmap();
void scd_update();
void scd_checkDma();
void scd_updateCddaVol();
int scd_saveState(uint8 *state);
int scd_loadState(uint8 *state, uint exVersion);

int Insert_CD(CDAccess *cd);
void Stop_CD();
