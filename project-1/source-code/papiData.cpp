#include <papi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include "papiData.h"

using namespace std;

PapiData::PapiData() {
	EventSet = PAPI_NULL;
	
	for (int i = 0; i < 108; i++)
		values[i] = -1;
}

PapiData::~PapiData() {
	return;
}

void PapiData::handleError (int retval)
{
	printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
	exit(1);
}

void PapiData::initPapi() {
	int retval = PAPI_library_init(PAPI_VER_CURRENT);
	
	if (retval != PAPI_VER_CURRENT && retval < 0) {
		printf("PAPI library version mismatch!\n");
		exit(1);
	}
	if (retval < 0)
		handleError(retval);

	std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
			<< " MINOR: " << PAPI_VERSION_MINOR(retval)
			<< " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

void PapiData::startPapi() {
	ret = PAPI_start(EventSet);
	if (ret != PAPI_OK)
		cout << "ERRO: Start PAPI" << endl;
}

void PapiData::stopPapi() {
	ret = PAPI_stop(EventSet, values);
	if (ret != PAPI_OK)
		cout << "ERRO: Stop PAPI" << endl;
}

void PapiData::resetPapi() {
	ret = PAPI_reset(EventSet);
	if (ret != PAPI_OK)
		std::cout << "FAIL reset PAPI" << endl;
}

void PapiData::setPapiEvents()
{
	ret = PAPI_create_eventset(&EventSet);				if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;
	
	strcpy (header,"Dimension\tTime(s)\t");
		
	ret = PAPI_add_event(EventSet, PAPI_L1_DCM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;		else strcat(header, "L1_DCM\t");		// [0	] 	Level 1 data cache misses
	ret = PAPI_add_event(EventSet, PAPI_L1_ICM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_ICM" << endl;		else strcat(header, "L1_ICM\t");		// [1	] 	Level 1 instruction cache misses
	ret = PAPI_add_event(EventSet, PAPI_L2_DCM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;		else strcat(header, "L2_DCM\t");		// [2	] 	Level 2 data cache misses
	ret = PAPI_add_event(EventSet, PAPI_L2_ICM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_ICM" << endl;		else strcat(header, "L2_ICM\t");		// [3	] 	Level 2 instruction cache misses
	ret = PAPI_add_event(EventSet, PAPI_L3_DCM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_DCM" << endl;		else strcat(header, "L3_DCM\t");		// [4	] 	Level 3 data cache misses
	ret = PAPI_add_event(EventSet, PAPI_L3_ICM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_ICM" << endl;		else strcat(header, "L3_ICM\t");		// [5	] 	Level 3 instruction cache misses
	ret = PAPI_add_event(EventSet, PAPI_L1_TCM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_TCM" << endl;		else strcat(header, "L1_TCM\t");		// [6	] 	Level 1 cache misses
	ret = PAPI_add_event(EventSet, PAPI_L2_TCM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_TCM" << endl;		else strcat(header, "L2_TCM\t");		// [7	] 	Level 2 cache misses
	ret = PAPI_add_event(EventSet, PAPI_L3_TCM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_TCM" << endl;		else strcat(header, "L3_TCM\t");		// [8	] 	Level 3 cache misses
	ret = PAPI_add_event(EventSet, PAPI_CA_SNP);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CA_SNP" << endl;		else strcat(header, "CA_SNP\t");		// [9	] 	Requests for a snoop
	ret = PAPI_add_event(EventSet, PAPI_CA_SHR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CA_SHR" << endl;		else strcat(header, "CA_SHR\t");		// [10	] 	Requests for exclusive access to shared cache line
	ret = PAPI_add_event(EventSet, PAPI_CA_CLN);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CA_CLN" << endl;		else strcat(header, "CA_CLN\t");		// [11	] 	Requests for exclusive access to clean cache line
	ret = PAPI_add_event(EventSet, PAPI_CA_INV);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CA_INV" << endl;		else strcat(header, "CA_INV\t");		// [12	] 	Requests for cache line invalidation
	ret = PAPI_add_event(EventSet, PAPI_CA_ITV);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CA_ITV" << endl;		else strcat(header, "CA_ITV\t");		// [13	] 	Requests for cache line intervention
	ret = PAPI_add_event(EventSet, PAPI_L3_LDM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_LDM" << endl;		else strcat(header, "L3_LDM\t");		// [14	] 	Level 3 load misses
	ret = PAPI_add_event(EventSet, PAPI_L3_STM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_STM" << endl;		else strcat(header, "L3_STM\t");		// [15	] 	Level 3 store misses
	ret = PAPI_add_event(EventSet, PAPI_BRU_IDL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BRU_IDL" << endl;		else strcat(header, "BRU_IDL\t");		// [16	] 	Cycles branch units are idle
	ret = PAPI_add_event(EventSet, PAPI_FXU_IDL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FXU_IDL" << endl;		else strcat(header, "FXU_IDL\t");		// [17	] 	Cycles integer units are idle
	ret = PAPI_add_event(EventSet, PAPI_FPU_IDL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FPU_IDL" << endl;		else strcat(header, "FPU_IDL\t");		// [18	] 	Cycles floating point units are idle
	ret = PAPI_add_event(EventSet, PAPI_LSU_IDL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_LSU_IDL" << endl;		else strcat(header, "LSU_IDL\t");		// [19	] 	Cycles load/store units are idle
	ret = PAPI_add_event(EventSet, PAPI_TLB_DM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_TLB_DM" << endl;		else strcat(header, "TLB_DM\t");		// [20	] 	Data translation lookaside buffer misses
	ret = PAPI_add_event(EventSet, PAPI_TLB_IM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_TLB_IM" << endl;		else strcat(header, "TLB_IM\t");		// [21	] 	Instruction translation lookaside buffer misses
	ret = PAPI_add_event(EventSet, PAPI_TLB_TL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_TLB_TL" << endl;		else strcat(header, "TLB_TL\t");		// [22	] 	Total translation lookaside buffer misses
	ret = PAPI_add_event(EventSet, PAPI_L1_LDM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_LDM" << endl;		else strcat(header, "L1_LDM\t");		// [23	] 	Level 1 load misses
	ret = PAPI_add_event(EventSet, PAPI_L1_STM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_STM" << endl;		else strcat(header, "L1_STM\t");		// [24	] 	Level 1 store misses
	ret = PAPI_add_event(EventSet, PAPI_L2_LDM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_LDM" << endl;		else strcat(header, "L2_LDM\t");		// [25	] 	Level 2 load misses
	ret = PAPI_add_event(EventSet, PAPI_L2_STM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_STM" << endl;		else strcat(header, "L2_STM\t");		// [26	] 	Level 2 store misses
	ret = PAPI_add_event(EventSet, PAPI_BTAC_M);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BTAC_M" << endl;		else strcat(header, "BTAC_M\t");		// [27	] 	Branch target address cache misses
	ret = PAPI_add_event(EventSet, PAPI_PRF_DM);		if (ret != PAPI_OK) cout << "ERRO: PAPI_PRF_DM" << endl;		else strcat(header, "PRF_DM\t");		// [28	] 	Data prefetch cache misses
	ret = PAPI_add_event(EventSet, PAPI_L3_DCH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_DCH" << endl;		else strcat(header, "L3_DCH\t");		// [29	] 	Level 3 data cache hits
	ret = PAPI_add_event(EventSet, PAPI_TLB_SD);		if (ret != PAPI_OK) cout << "ERRO: PAPI_TLB_SD" << endl;		else strcat(header, "TLB_SD\t");		// [30	] 	Translation lookaside buffer shootdowns
	ret = PAPI_add_event(EventSet, PAPI_CSR_FAL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CSR_FAL" << endl;		else strcat(header, "CSR_FAL\t");		// [31	] 	Failed store conditional instructions
	ret = PAPI_add_event(EventSet, PAPI_CSR_SUC);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CSR_SUC" << endl;		else strcat(header, "CSR_SUC\t");		// [32	] 	Successful store conditional instructions
	ret = PAPI_add_event(EventSet, PAPI_CSR_TOT);		if (ret != PAPI_OK) cout << "ERRO: PAPI_CSR_TOT" << endl;		else strcat(header, "CSR_TOT\t");		// [33	] 	Total store conditional instructions
	ret = PAPI_add_event(EventSet, PAPI_MEM_SCY);		if (ret != PAPI_OK) cout << "ERRO: PAPI_MEM_SCY" << endl;		else strcat(header, "MEM_SCY\t");		// [34	] 	Cycles Stalled Waiting for memory accesses
	ret = PAPI_add_event(EventSet, PAPI_MEM_RCY);		if (ret != PAPI_OK) cout << "ERRO: PAPI_MEM_RCY" << endl;		else strcat(header, "MEM_RCY\t");		// [35	] 	Cycles Stalled Waiting for memory Reads
	ret = PAPI_add_event(EventSet, PAPI_MEM_WCY);		if (ret != PAPI_OK) cout << "ERRO: PAPI_MEM_WCY" << endl;		else strcat(header, "MEM_WCY\t");		// [36	] 	Cycles Stalled Waiting for memory writes
	ret = PAPI_add_event(EventSet, PAPI_STL_ICY);		if (ret != PAPI_OK) cout << "ERRO: PAPI_STL_ICY" << endl;		else strcat(header, "STL_ICY\t");		// [37	] 	Cycles with no instruction issue
	ret = PAPI_add_event(EventSet, PAPI_FUL_ICY);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FUL_ICY" << endl;		else strcat(header, "FUL_ICY\t");		// [38	] 	Cycles with maximum instruction issue
	ret = PAPI_add_event(EventSet, PAPI_STL_CCY);		if (ret != PAPI_OK) cout << "ERRO: PAPI_STL_CCY" << endl;		else strcat(header, "STL_CCY\t");		// [39	] 	Cycles with no instructions completed
	ret = PAPI_add_event(EventSet, PAPI_FUL_CCY);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FUL_CCY" << endl;		else strcat(header, "FUL_CCY\t");		// [40	] 	Cycles with maximum instructions completed
	ret = PAPI_add_event(EventSet, PAPI_HW_INT);		if (ret != PAPI_OK) cout << "ERRO: PAPI_HW_INT" << endl;		else strcat(header, "HW_INT\t");		// [41	] 	Hardware interrupts
	ret = PAPI_add_event(EventSet, PAPI_BR_UCN);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BR_UCN" << endl;		else strcat(header, "BR_UCN\t");		// [42	] 	Unconditional branch instructions
	ret = PAPI_add_event(EventSet, PAPI_BR_CN);			if (ret != PAPI_OK) cout << "ERRO: PAPI_BR_CN" << endl;			else strcat(header, "BR_CN\t");		// [43	] 	Conditional branch instructions
	ret = PAPI_add_event(EventSet, PAPI_BR_TKN);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BR_TKN" << endl;		else strcat(header, "BR_TKN\t");		// [44	] 	Conditional branch instructions taken
	ret = PAPI_add_event(EventSet, PAPI_BR_NTK);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BR_NTK" << endl;		else strcat(header, "BR_NTK\t");		// [45	] 	Conditional branch instructions not taken
	ret = PAPI_add_event(EventSet, PAPI_BR_MSP);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BR_MSP" << endl;		else strcat(header, "BR_MSP\t");		// [46	] 	Conditional branch instructions mispredicted
	ret = PAPI_add_event(EventSet, PAPI_BR_PRC);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BR_PRC" << endl;		else strcat(header, "BR_PRC\t");		// [47	] 	Conditional branch instructions correctly predicted
	ret = PAPI_add_event(EventSet, PAPI_FMA_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FMA_INS" << endl;		else strcat(header, "FMA_INS\t");		// [48	] 	FMA instructions completed
	ret = PAPI_add_event(EventSet, PAPI_TOT_IIS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_TOT_IIS" << endl;		else strcat(header, "TOT_IIS\t");		// [49	] 	Instructions issued
	ret = PAPI_add_event(EventSet, PAPI_TOT_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_TOT_INS" << endl;		else strcat(header, "TOT_INS\t");		// [50	] 	Instructions completed
	ret = PAPI_add_event(EventSet, PAPI_INT_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_INT_INS" << endl;		else strcat(header, "INT_INS\t");		// [51	] 	Integer instructions
	ret = PAPI_add_event(EventSet, PAPI_FP_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FP_INS" << endl;		else strcat(header, "FP_INS\t");		// [52	] 	Floating point instructions
	ret = PAPI_add_event(EventSet, PAPI_LD_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_LD_INS" << endl;		else strcat(header, "LD_INS\t");		// [53	] 	Load instructions
	ret = PAPI_add_event(EventSet, PAPI_SR_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_SR_INS" << endl;		else strcat(header, "SR_INS\t");		// [54	] 	Store instructions
	ret = PAPI_add_event(EventSet, PAPI_BR_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_BR_INS" << endl;		else strcat(header, "BR_INS\t");		// [55	] 	Branch instructions
	ret = PAPI_add_event(EventSet, PAPI_VEC_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_VEC_INS" << endl;		else strcat(header, "VEC_INS\t");		// [56	] 	Vector/SIMD instructions (could include integer)
	ret = PAPI_add_event(EventSet, PAPI_RES_STL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_RES_STL" << endl;		else strcat(header, "RES_STL\t");		// [57	] 	Cycles stalled on any resource
	ret = PAPI_add_event(EventSet, PAPI_FP_STAL);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FP_STAL" << endl;		else strcat(header, "FP_STAL\t");		// [58	] 	Cycles the FP unit(s) are stalled
	ret = PAPI_add_event(EventSet, PAPI_TOT_CYC);		if (ret != PAPI_OK) cout << "ERRO: PAPI_TOT_CYC" << endl;		else strcat(header, "TOT_CYC\t");		// [59	] 	Total cycles
	ret = PAPI_add_event(EventSet, PAPI_LST_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_LST_INS" << endl;		else strcat(header, "LST_INS\t");		// [60	] 	Load/store instructions completed
	ret = PAPI_add_event(EventSet, PAPI_SYC_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_SYC_INS" << endl;		else strcat(header, "SYC_INS\t");		// [61	] 	Synchronization instructions completed
	ret = PAPI_add_event(EventSet, PAPI_L1_DCH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCH" << endl;		else strcat(header, "L1_DCH\t");		// [62	] 	Level 1 data cache hits
	ret = PAPI_add_event(EventSet, PAPI_L2_DCH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCH" << endl;		else strcat(header, "L2_DCH\t");		// [63	] 	Level 2 data cache hits
	ret = PAPI_add_event(EventSet, PAPI_L1_DCA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCA" << endl;		else strcat(header, "L1_DCA\t");		// [64	] 	Level 1 data cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L2_DCA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCA" << endl;		else strcat(header, "L2_DCA\t");		// [65	] 	Level 2 data cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L3_DCA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_DCA" << endl;		else strcat(header, "L3_DCA\t");		// [66	] 	Level 3 data cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L1_DCR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCR" << endl;		else strcat(header, "L1_DCR\t");		// [67	] 	Level 1 data cache reads
	ret = PAPI_add_event(EventSet, PAPI_L2_DCR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCR" << endl;		else strcat(header, "L2_DCR\t");		// [68	] 	Level 2 data cache reads
	ret = PAPI_add_event(EventSet, PAPI_L3_DCR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_DCR" << endl;		else strcat(header, "L3_DCR\t");		// [69	] 	Level 3 data cache reads
	ret = PAPI_add_event(EventSet, PAPI_L1_DCW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCW" << endl;		else strcat(header, "L1_DCW\t");		// [70	] 	Level 1 data cache writes
	ret = PAPI_add_event(EventSet, PAPI_L2_DCW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCW" << endl;		else strcat(header, "L2_DCW\t");		// [71	] 	Level 2 data cache writes
	ret = PAPI_add_event(EventSet, PAPI_L3_DCW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_DCW" << endl;		else strcat(header, "L3_DCW\t");		// [72	] 	Level 3 data cache writes
	ret = PAPI_add_event(EventSet, PAPI_L1_ICH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_ICH" << endl;		else strcat(header, "L1_ICH\t");		// [73	] 	Level 1 instruction cache hits
	ret = PAPI_add_event(EventSet, PAPI_L2_ICH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_ICH" << endl;		else strcat(header, "L2_ICH\t");		// [74	] 	Level 2 instruction cache hits
	ret = PAPI_add_event(EventSet, PAPI_L3_ICH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_ICH" << endl;		else strcat(header, "L3_ICH\t");		// [75	] 	Level 3 instruction cache hits
	ret = PAPI_add_event(EventSet, PAPI_L1_ICA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_ICA" << endl;		else strcat(header, "L1_ICA\t");		// [76	] 	Level 1 instruction cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L2_ICA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_ICA" << endl;		else strcat(header, "L2_ICA\t");		// [77	] 	Level 2 instruction cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L3_ICA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_ICA" << endl;		else strcat(header, "L3_ICA\t");		// [78	] 	Level 3 instruction cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L1_ICR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_ICR" << endl;		else strcat(header, "L1_ICR\t");		// [79	] 	Level 1 instruction cache reads
	ret = PAPI_add_event(EventSet, PAPI_L2_ICR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_ICR" << endl;		else strcat(header, "L2_ICR\t");		// [80	] 	Level 2 instruction cache reads
	ret = PAPI_add_event(EventSet, PAPI_L3_ICR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_ICR" << endl;		else strcat(header, "L3_ICR\t");		// [81	] 	Level 3 instruction cache reads
	ret = PAPI_add_event(EventSet, PAPI_L1_ICW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_ICW" << endl;		else strcat(header, "L1_ICW\t");		// [82	] 	Level 1 instruction cache writes
	ret = PAPI_add_event(EventSet, PAPI_L2_ICW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_ICW" << endl;		else strcat(header, "L2_ICW\t");		// [83	] 	Level 2 instruction cache writes
	ret = PAPI_add_event(EventSet, PAPI_L3_ICW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_ICW" << endl;		else strcat(header, "L3_ICW\t");		// [84	] 	Level 3 instruction cache writes
	ret = PAPI_add_event(EventSet, PAPI_L1_TCH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_TCH" << endl;		else strcat(header, "L1_TCH\t");		// [85	] 	Level 1 total cache hits
	ret = PAPI_add_event(EventSet, PAPI_L2_TCH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_TCH" << endl;		else strcat(header, "L2_TCH\t");		// [86	] 	Level 2 total cache hits
	ret = PAPI_add_event(EventSet, PAPI_L3_TCH);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_TCH" << endl;		else strcat(header, "L3_TCH\t");		// [87	] 	Level 3 total cache hits
	ret = PAPI_add_event(EventSet, PAPI_L1_TCA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_TCA" << endl;		else strcat(header, "L1_TCA\t");		// [88	] 	Level 1 total cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L2_TCA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_TCA" << endl;		else strcat(header, "L2_TCA\t");		// [89	] 	Level 2 total cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L3_TCA);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_TCA" << endl;		else strcat(header, "L3_TCA\t");		// [90	] 	Level 3 total cache accesses
	ret = PAPI_add_event(EventSet, PAPI_L1_TCR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_TCR" << endl;		else strcat(header, "L1_TCR\t");		// [91	] 	Level 1 total cache reads
	ret = PAPI_add_event(EventSet, PAPI_L2_TCR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_TCR" << endl;		else strcat(header, "L2_TCR\t");		// [92	] 	Level 2 total cache reads
	ret = PAPI_add_event(EventSet, PAPI_L3_TCR);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_TCR" << endl;		else strcat(header, "L3_TCR\t");		// [93	] 	Level 3 total cache reads
	ret = PAPI_add_event(EventSet, PAPI_L1_TCW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_TCW" << endl;		else strcat(header, "L1_TCW\t");		// [94	] 	Level 1 total cache writes
	ret = PAPI_add_event(EventSet, PAPI_L2_TCW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_TCW" << endl;		else strcat(header, "L2_TCW\t");		// [95	] 	Level 2 total cache writes
	ret = PAPI_add_event(EventSet, PAPI_L3_TCW);		if (ret != PAPI_OK) cout << "ERRO: PAPI_L3_TCW" << endl;		else strcat(header, "L3_TCW\t");		// [96	] 	Level 3 total cache writes
	ret = PAPI_add_event(EventSet, PAPI_FML_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FML_INS" << endl;		else strcat(header, "FML_INS\t");		// [97	] 	Floating point multiply instructions
	ret = PAPI_add_event(EventSet, PAPI_FAD_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FAD_INS" << endl;		else strcat(header, "FAD_INS\t");		// [98	] 	Floating point add instructions
	ret = PAPI_add_event(EventSet, PAPI_FDV_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FDV_INS" << endl;		else strcat(header, "FDV_INS\t");		// [99	] 	Floating point divide instructions
	ret = PAPI_add_event(EventSet, PAPI_FSQ_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FSQ_INS" << endl;		else strcat(header, "FSQ_INS\t");		// [100	] 	Floating point square root instructions
	ret = PAPI_add_event(EventSet, PAPI_FNV_INS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FNV_INS" << endl;		else strcat(header, "FNV_INS\t");		// [101	] 	Floating point inverse instructions
	ret = PAPI_add_event(EventSet, PAPI_FP_OPS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_FP_OPS" << endl;		else strcat(header, "FP_OPS\t");		// [102	] 	Floating point operations
	ret = PAPI_add_event(EventSet, PAPI_SP_OPS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_SP_OPS" << endl;		else strcat(header, "SP_OPS\t");		// [103	] 	Floating point operations; optimized to count scaled single precision vector operations
	ret = PAPI_add_event(EventSet, PAPI_DP_OPS);		if (ret != PAPI_OK) cout << "ERRO: PAPI_DP_OPS" << endl;		else strcat(header, "DP_OPS\t");		// [104	] 	Floating point operations; optimized to count scaled double precision vector operations
	ret = PAPI_add_event(EventSet, PAPI_VEC_SP);		if (ret != PAPI_OK) cout << "ERRO: PAPI_VEC_SP" << endl;		else strcat(header, "VEC_SP\t");		// [105	] 	Single precision vector/SIMD instructions
	ret = PAPI_add_event(EventSet, PAPI_VEC_DP);		if (ret != PAPI_OK) cout << "ERRO: PAPI_VEC_DP" << endl;		else strcat(header, "VEC_DP\t");		// [106	] 	Double precision vector/SIMD instructions
	ret = PAPI_add_event(EventSet, PAPI_REF_CYC);		if (ret != PAPI_OK) cout << "ERRO: PAPI_REF_CYC" << endl;		else strcat(header, "REF_CYC\t");		// [107	] 	Reference clock cycles
	
	strcat(header, "\n");
}

void PapiData::printHeader()
{
	printf("%s", header);
}

void PapiData::printPapiResults()
{
	for (int i = 0; i < 108; i++)
		if(values[i] != -1)
			printf("%lld\t", values[i]);
	std::cout << endl;
}

void PapiData::removeAndDestoyPapi()
{
	ret = PAPI_remove_event(EventSet, PAPI_L1_DCM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_DCM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_ICM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_ICM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_DCM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_DCM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_ICM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_ICM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_DCM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_DCM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_ICM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_ICM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_TCM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_TCM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_TCM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_TCM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_TCM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_TCM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CA_SNP);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CA_SNP event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CA_SHR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CA_SHR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CA_CLN);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CA_CLN event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CA_INV);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CA_INV event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CA_ITV);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CA_ITV event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_LDM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_LDM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_STM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_STM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BRU_IDL);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BRU_IDL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FXU_IDL);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FXU_IDL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FPU_IDL);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FPU_IDL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_LSU_IDL);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_LSU_IDL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_TLB_DM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_TLB_DM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_TLB_IM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_TLB_IM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_TLB_TL);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_TLB_TL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_LDM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_LDM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_STM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_STM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_LDM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_LDM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_STM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_STM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BTAC_M);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BTAC_M event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_PRF_DM);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_PRF_DM event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_DCH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_DCH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_TLB_SD);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_TLB_SD event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CSR_FAL);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CSR_FAL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CSR_SUC);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CSR_SUC event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_CSR_TOT);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_CSR_TOT event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_MEM_SCY);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_MEM_SCY event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_MEM_RCY);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_MEM_RCY event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_MEM_WCY);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_MEM_WCY event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_STL_ICY);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_STL_ICY event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FUL_ICY);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FUL_ICY event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_STL_CCY);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_STL_CCY event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FUL_CCY);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FUL_CCY event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_HW_INT);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_HW_INT event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BR_UCN);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BR_UCN event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BR_CN);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BR_CN event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BR_TKN);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BR_TKN event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BR_NTK);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BR_NTK event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BR_MSP);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BR_MSP event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BR_PRC);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BR_PRC event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FMA_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FMA_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_TOT_IIS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_TOT_IIS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_TOT_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_TOT_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_INT_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_INT_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FP_INS);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FP_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_LD_INS);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_LD_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_SR_INS);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_SR_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_BR_INS);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_BR_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_VEC_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_VEC_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_RES_STL);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_RES_STL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FP_STAL);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FP_STAL event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_TOT_CYC);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_TOT_CYC event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_LST_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_LST_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_SYC_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_SYC_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_DCH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_DCH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_DCH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_DCH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_DCA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_DCA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_DCA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_DCA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_DCA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_DCA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_DCR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_DCR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_DCR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_DCR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_DCR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_DCR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_DCW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_DCW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_DCW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_DCW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_DCW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_DCW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_ICH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_ICH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_ICH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_ICH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_ICH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_ICH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_ICA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_ICA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_ICA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_ICA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_ICA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_ICA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_ICR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_ICR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_ICR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_ICR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_ICR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_ICR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_ICW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_ICW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_ICW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_ICW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_ICW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_ICW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_TCH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_TCH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_TCH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_TCH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_TCH);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_TCH event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_TCA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_TCA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_TCA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_TCA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_TCA);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_TCA event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_TCR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_TCR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_TCR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_TCR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_TCR);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_TCR event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L1_TCW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L1_TCW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L2_TCW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L2_TCW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_L3_TCW);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_L3_TCW event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FML_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FML_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FAD_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FAD_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FDV_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FDV_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FSQ_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FSQ_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FNV_INS);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FNV_INS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_FP_OPS);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_FP_OPS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_SP_OPS);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_SP_OPS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_DP_OPS);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_DP_OPS event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_VEC_SP);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_VEC_SP event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_VEC_DP);		if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_VEC_DP event" << endl;
	ret = PAPI_remove_event(EventSet, PAPI_REF_CYC);	if (ret != PAPI_OK)			std::cout << "FAIL remove PAPI_REF_CYC event" << endl;
	
	ret = PAPI_destroy_eventset( &EventSet );			if (ret != PAPI_OK)			std::cout << "FAIL destroy" << endl;
}