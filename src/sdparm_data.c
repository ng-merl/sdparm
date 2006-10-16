/*
 * Copyright (c) 2005-2006 Douglas Gilbert.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <stdlib.h>
#include "sdparm.h"


/* sdparm is a utility program for the Linux OS SCSI subsystem.
 *
 * This utility fetches various attributes associated with a given
 * SCSI disk (or a disk that uses, or translates the SCSI command
 * set). In some cases these attributes can be changed.
 *
 * This file contains data tables that may be useful for other
 * programs.
 */


/* Mode pages that aren't specific to any transport protocol or vendor */
struct sdparm_values_name_t sdparm_gen_mode_pg[] = {
    {IEC_MP, MSP_BACK_CTL, 0, 0, "bc", "Background control (SBC)"},
    {CACHING_MP, 0, 0, 0, "ca", "Caching (SBC)"},
    {MMCMS_MP, 0, 5, 1, "cms", "CD/DVD (MM) capabilities and mechanical "
        "status (MMC)"},        /* read only */
    {CONTROL_MP, 0, -1, 0, "co", "Control"},
    {CONTROL_MP, MSP_SPC_CE, -1, 0, "coe", "Control extension"},
    {DATA_COMPR_MP, 0, 1, 0, "dac", "Data compression (SSC)"},
    {DEV_CONF_MP, 0, 1, 0, "dc", "Device configuration (SSC)"},
    {DEV_CONF_MP, MSP_DEV_CONF_EXT, 1, 0, "dce", "Device configuration "
        "extension (SSC)"},
    {ES_MAN_MP, 0, 0xd, 0, "esm", "Enclosure services management (SES)"},
    {FORMAT_MP, 0, 0, 0, "fo", "Format (SBC)"},
    {IEC_MP, 0, -1, 0, "ie", "Informational exceptions control"},
    {MED_CONF_MP, 0, 1, 0, "mco", "Medium configuration (SSC)"},
    {MED_PART_MP, 0, 1, 0, "mpa", "Medium partition (SSC)"},
    {MRW_MP, 0, 5, 0, "mrw", "Mount rainier reWritable (MMC)"},
    {CONTROL_MP, MSP_SAT_PATA, -1, 0, "pat", "SAT pATA control"},
    {PROT_SPEC_LU_MP, 0, -1, 0, "pl", "Protocol specific logical unit"},
    {POWER_MP, 0, -1, 0, "po", "Power condition"},
    {POWER_OLD_MP, 0, 0, 0, "poo", "Power condition - old version"},
        /* POWER_OLD_MP for disks as clashes with old MMC specs */
    {PROT_SPEC_PORT_MP, 0, -1, 0, "pp", "Protocol specific port"},
    {RBC_DEV_PARAM_MP, 0, 0xe, 0, "rbc", "RBC device parameters (RBC)"},
    {RIGID_DISK_MP, 0, 0, 0, "rd", "Rigid disk (SBC)"},
    {RW_ERR_RECOVERY_MP, 0, -1, 0, "rw", "Read write error recovery"},
        /* since in SBC, SSC and MMC treat RW_ERR_RECOVERY_MP as if in SPC */
    {TIMEOUT_PROT_MP, 0, 5, 0, "tp", "Timeout and protect (MMC)"},
    {V_ERR_RECOVERY_MP, 0, 0, 0, "ve", "Verify error recovery (SBC)"},
    {WRITE_PARAM_MP, 0, 5, 0, "wp", "Write parameters (MMC)"},
    {XOR_MP, 0, 0, 0, "xo", "XOR control (SBC)"},
    {0, 0, 0, 0, NULL, NULL},
};

/* Array for transport id, acronym and name association. */
/* Those transports commented with "none" don't have transport specific */
/* mode pages. */
struct sdparm_values_name_t sdparm_transport_id[] = {
    {TP_FCP, 0, -1, 0, "fcp", "Fibre channel (FCP)"},
    {TP_SPI, 0, -1, 0, "spi", "SCSI parallel interface (SPI)"},
    {TP_SSA, 0, -1, 0, "ssa", "Serial storage architecture (SSA)"},
    {TP_1394, 0, -1, 0, "sbp", "Serial bus (SBP)"}, /* none */
    {TP_SRP, 0, -1, 0, "srp", "SCSI remote DMA (SRP)"},
    {TP_ISCSI, 0, -1, 0, "iscsi", "Internet SCSI (iSCSI)"}, /* none */
    {TP_SAS, 0, -1, 0, "sas", "Serial attached SCSI (SAS)"},
    {TP_ADT, 0, -1, 0, "adt", "Automation/Drive interface (ADT)"},
    {TP_ATA, 0, -1, 0, "ata", "AT attachment interface (ATA/ATAPI)"},
                                                         /* none */
    {0x9, 0, -1, 0, "u0x9", NULL},      /* leading "u" so not number */
    {0xa, 0, -1, 0, "u0xa", NULL},
    {0xb, 0, -1, 0, "u0xb", NULL},
    {0xc, 0, -1, 0, "u0xc", NULL},
    {0xd, 0, -1, 0, "u0xd", NULL},
    {0xe, 0, -1, 0, "u0xe", NULL},
    {TP_NONE, 0, -1, 1, "none", "No specific"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_values_name_t sdparm_fcp_mode_pg[] = {    /* FCP-3 */
    {DISCONNECT_MP, 0, -1, 0, "dr", "Disconnect-reconnect (FCP)"},
    {PROT_SPEC_LU_MP, 0, -1, 0, "luc", "lu: control (FCP)"},
    {PROT_SPEC_PORT_MP, 0, -1, 0, "pc", "port: control (FCP)"},
    {PROT_SPEC_LU_MP, 0, -1, 0, "pl", "lu: control (generic name)"},
    {PROT_SPEC_PORT_MP, 0, -1, 0, "pp", "port: control (generic name)"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_values_name_t sdparm_spi_mode_pg[] = {    /* SPI-4 */
    {DISCONNECT_MP, 0, -1, 0, "dr", "Disconnect-reconnect (SPI)"},
    {PROT_SPEC_LU_MP, 0, -1, 0, "luc", "lu: control (SPI)"},
    {PROT_SPEC_PORT_MP, MSP_SPI_MC, -1, 0, "mc",
        "port: margin control (SPI)"},
    {PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 0, "ns",
        "port: negotiated settings (SPI)"},
    {PROT_SPEC_PORT_MP, 0, -1, 0, "psf", "port: short format (SPI)"},
    {PROT_SPEC_PORT_MP, MSP_SPI_RTC, -1, 1, "rtc",
        "port: report transfer capabilities (SPI)"},
    {PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 0, "stc",
        "port: saved training config value (SPI)"},
    /* second preference name so put out of alphabetical order */
    {PROT_SPEC_LU_MP, 0, -1, 0, "pl", "lu: control (generic name)"},
    {PROT_SPEC_PORT_MP, 0, -1, 0, "pp", "port: short format (generic name)"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_values_name_t sdparm_srp_mode_pg[] = {    /* SRP */
    {DISCONNECT_MP, 0, -1, 0, "dr", "Disconnect-reconnect (SRP)"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_values_name_t sdparm_sas_mode_pg[] = {    /* SAS-2 */
    {DISCONNECT_MP, 0, -1, 0, "dr", "Disconnect-reconnect (SAS)"},
    {PROT_SPEC_LU_MP, 0, -1, 0, "lsf", "lu: SSP short format (SAS)"},
    {PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 0, "pcd",
        "port: phy control and discover (SAS)"},
    {PROT_SPEC_PORT_MP, 0, -1, 0, "psf", "port: SSP short format (SAS)"},
    {PROT_SPEC_PORT_MP, MSP_SAS_SHA, -1, 0, "sha",
        "port: shared protocol specific (SAS)"},
    /* second preference name so put out of alphabetical order */
    {PROT_SPEC_LU_MP, 0, -1, 0, "pl", "lu: SSP short format (generic name)"},
    {PROT_SPEC_PORT_MP, 0, -1, 0, "pp",
        "port: SSP short format (generic name)"},
    {0, 0, 0, 0, NULL, NULL},
};


struct sdparm_values_name_t sdparm_vpd_pg[] = {
    {VPD_ATA_INFO, 0, -1, 1, "ai", "ATA information (SAT)"},
    {VPD_ASCII_OP_DEF, 0, -1, 1, "aod",
     "ASCII implemented operating definition (obs)"},
    {VPD_BLOCK_LIMITS, 0, 0, 1, "bl", "Block limits (SBC)"},
    {VPD_DEVICE_ID, 0, -1, 1, "di", "Device identification"},
    {VPD_DEVICE_ID, VPD_DI_SEL_AS_IS, -1, 1, "di_asis", "Like 'di' "
     "but designators ordered as found"},
    {VPD_DEVICE_ID, VPD_DI_SEL_LU, -1, 1, "di_lu", "Device identification, "
     "lu only"},
    {VPD_DEVICE_ID, VPD_DI_SEL_TPORT, -1, 1, "di_port", "Device "
     "identification, target port only"},
    {VPD_DEVICE_ID, VPD_DI_SEL_TARGET, -1, 1, "di_target", "Device "
     "identification, target device only"},
    {VPD_EXT_INQ, 0, -1, 1, "ei", "Extended inquiry data"},
    {VPD_IMP_OP_DEF, 0, -1, 1, "iod",
     "Implemented operating definition (obs)"},
    {VPD_MAN_ASS_SN, 0, 1, 1, "mas",
     "Manufacturer assigned serial number (SSC)"},
    {VPD_MAN_NET_ADDR, 0, -1, 1, "mna", "Management network addresses"},
    {VPD_MODE_PG_POLICY, 0, -1, 1, "mpp", "Mode page policy"},
    {VPD_SA_DEV_CAP, 0, 1, 1, "sad",
     "Sequential access device capabilities (SSC)"},
    {VPD_SOFTW_INF_ID, 0, -1, 1, "sii", "Software interface identification"},
    {VPD_UNIT_SERIAL_NUM, 0, -1, 1, "sn", "Unit serial number"},
    {VPD_SCSI_PORTS, 0, -1, 1, "sp", "SCSI ports"},
    {VPD_SUPPORTED_VPDS, 0, -1, 1, "sv", "Supported VPD pages"},
    {VPD_TA_SUPPORTED, 0, 1, 1, "tas", "TapeAlert supported flags (SSC)"},
    {0, 0, 0, 0, NULL, NULL},
};

/* Generic (i.e. non-transport specific) mode page items follow, */
/* sorted by mode page (then subpage) number in ascending order */
struct sdparm_mode_page_item sdparm_mitem_arr[] = {

    /* Read write error recovery mode page [0x1] sbc2, mmc5, ssc3 */
    /* treat as spc since various command sets implement variants */
    {"AWRE", RW_ERR_RECOVERY_MP, 0, -1, 2, 7, 1, MF_COMMON,
        "Automatic write reallocation enabled", NULL},
    {"ARRE", RW_ERR_RECOVERY_MP, 0, -1, 2, 6, 1, MF_COMMON,
        "Automatic read reallocation enabled", NULL},
    {"TB", RW_ERR_RECOVERY_MP, 0, -1, 2, 5, 1, 0,
        "Transfer block", NULL},
    {"RC", RW_ERR_RECOVERY_MP, 0, -1, 2, 4, 1, 0,
        "Read continuous", "0: error recovery may cause delays\t"
        "1: transfer data without waiting for error recovery"},
    {"EER", RW_ERR_RECOVERY_MP, 0, -1, 2, 3, 1, 0,
        "Enable early recovery", NULL},
    {"PER", RW_ERR_RECOVERY_MP, 0, -1, 2, 2, 1, MF_COMMON,
        "Post error", "0: do not post recovered errors\t"
        "1: report recovered errors"},
    {"DTE", RW_ERR_RECOVERY_MP, 0, -1, 2, 1, 1, 0,
        "Data terminate on error", NULL},
    {"DCR", RW_ERR_RECOVERY_MP, 0, -1, 2, 0, 1, 0,
        "Disable correction", NULL},
    {"RRC", RW_ERR_RECOVERY_MP, 0, -1, 3, 7, 8, 0,
        "Read retry count", NULL},
    {"COR_S", RW_ERR_RECOVERY_MP, 0, -1, 4, 7, 8, 0,
        "Correction span (obsolete)", NULL},
    {"HOC", RW_ERR_RECOVERY_MP, 0, -1, 5, 7, 8, 0,
        "Head offset count (obsolete)", NULL},
    {"DSOC", RW_ERR_RECOVERY_MP, 0, -1, 6, 7, 8, 0,
        "Data strobe offset count (obsolete)", NULL},
    {"EMCDR", RW_ERR_RECOVERY_MP, 0, 5, 7, 1, 2, 0, /* MMC */
        "Enhanced media certification and defect reporting", NULL},
    {"WRC", RW_ERR_RECOVERY_MP, 0, -1, 8, 7, 8, 0,
        "Write retry count", NULL},
    {"ERTL", RW_ERR_RECOVERY_MP, 0, 5, 9, 7, 24, 0, /* MMC */
        "Error reporting threshold length (blocks)", NULL},
    {"RTL", RW_ERR_RECOVERY_MP, 0, 0, 10, 7, 16, 0, /* SBC */
        "Recovery time limit (ms)", NULL},

    /* Disconnect-reconnect mode page [0x2]: see transport section */

    /* Format mode page [0x3] sbc2 (obsolete) */
    {"TPZ", FORMAT_MP, 0, 0, 2, 7, 16, 0,
        "Tracks per zone", NULL},
    {"ASPZ", FORMAT_MP, 0, 0, 4, 7, 16, 0,
        "Alternate sectors per zone", NULL},
    {"ATPZ", FORMAT_MP, 0, 0, 6, 7, 16, 0,
        "Alternate tracks per zone", NULL},
    {"ATPLU", FORMAT_MP, 0, 0, 8, 7, 16, 0,
        "Alternate tracks per logical unit", NULL},
    {"SPT", FORMAT_MP, 0, 0, 10, 7, 16, 0,
        "Sectors per track", NULL},
    {"DBPPS", FORMAT_MP, 0, 0, 12, 7, 16, 0,
        "Data bytes per physical sector", NULL},
    {"INTLV", FORMAT_MP, 0, 0, 14, 7, 16, 0,
        "Interleave", NULL},
    {"TSF", FORMAT_MP, 0, 0, 16, 7, 16, 0,
        "Track skew factor", NULL},
    {"CSF", FORMAT_MP, 0, 0, 18, 7, 16, 0,
        "Cylinder skew factor", NULL},
    {"SSEC", FORMAT_MP, 0, 0, 20, 7, 1, 0,
        "Soft sector", NULL},
    {"HSEC", FORMAT_MP, 0, 0, 20, 6, 1, 0,
        "Hard sector", NULL},
    {"RMB", FORMAT_MP, 0, 0, 20, 5, 1, 0,
        "Removable", NULL},
    {"SURF", FORMAT_MP, 0, 0, 20, 4, 1, 0,
        "Surface", NULL},

    /* Mount Rainier reWitable mode page [0x3] mmc4  */
    {"LBAS", MRW_MP, 0, 5, 3, 0, 1, 0,
        "LBA space", NULL},

    /* Rigid disk mode page [0x4] sbc2 (obsolete) */
    {"NOC", RIGID_DISK_MP, 0, 0, 2, 7, 24, 0,
        "Number of cylinders", NULL},
    {"NOH", RIGID_DISK_MP, 0, 0, 5, 7, 8, 0,
        "Number of heads", NULL},
    {"SCWP", RIGID_DISK_MP, 0, 0, 6, 7, 24, 0,
        "Starting cylinder for write precompensation", NULL},
    {"SCRWC", RIGID_DISK_MP, 0, 0, 9, 7, 24, 0,
        "Starting cylinder for reduced write current", NULL},
    {"DSR", RIGID_DISK_MP, 0, 0, 12, 7, 16, 0,
        "Device step rate", NULL},
    {"LZC", RIGID_DISK_MP, 0, 0, 14, 7, 24, 0,
        "Landing zone cylinder", NULL},
    {"RPL", RIGID_DISK_MP, 0, 0, 17, 1, 2, 0,
        "Rotational position locking", NULL},
    {"ROTO", RIGID_DISK_MP, 0, 0, 18, 7, 8, 0,
        "Rotational offset", NULL},
    {"MRR", RIGID_DISK_MP, 0, 0, 20, 7, 16, 0,
        "Medium rotation rate (rpm)", NULL},

    /* Write parameters mode page [0x5] mmc5 */
    {"BUFE", WRITE_PARAM_MP, 0, 5, 2, 6, 1, MF_COMMON,
        "Buffer underrun free recording enable", NULL},
    {"LS_V", WRITE_PARAM_MP, 0, 5, 2, 5, 1, 0,
        "Link size valid", NULL},
    {"TST_W", WRITE_PARAM_MP, 0, 5, 2, 4, 1, 0,
        "Test write", NULL},
    {"WR_T", WRITE_PARAM_MP, 0, 5, 2, 3, 4, MF_COMMON,
        "Write type",
        "0: packet/incremental; 1: track-at-once\t"
        "2: session-at-once; 3: raw; 4: layer jump recording"},
    {"MULTI_S", WRITE_PARAM_MP, 0, 5, 3, 7, 2, MF_COMMON,
        "Multi session",
        "0: next session not allowed (no BO pointer)\t"
        "1: next session not allowed\t"
        "3: next seesion allowed (indicated by BO pointer)"},
    {"FP", WRITE_PARAM_MP, 0, 5, 3, 5, 1, MF_COMMON,
        "Fixed packet type", NULL},
    {"COPY", WRITE_PARAM_MP, 0, 5, 3, 4, 1, 0,
        "Serial copy management system (SCMS) enable", NULL},
    {"TRACK_M", WRITE_PARAM_MP, 0, 5, 3, 3, 4, MF_COMMON,
        "Track mode", NULL},
    {"DBT", WRITE_PARAM_MP, 0, 5, 4, 3, 4, 0,
        "Data block type", NULL},
    {"LINK_S", WRITE_PARAM_MP, 0, 5, 5, 7, 8, 0,
        "Link size", NULL},
    {"IAC", WRITE_PARAM_MP, 0, 5, 7, 5, 6, 0,
        "Initiator application code", NULL},
    {"SESS_F", WRITE_PARAM_MP, 0, 5, 8, 7, 8, 0,
        "Session format", NULL},
    {"PACK_S", WRITE_PARAM_MP, 0, 5, 10, 7, 32, 0,
        "Packet size", NULL},
    {"APL", WRITE_PARAM_MP, 0, 5, 14, 7, 16, 0,
        "Audio pause length (blocks)", NULL},

    /* Device parameters mode page [0x6] rbc */
    {"WCD", RBC_DEV_PARAM_MP, 0, 0xe, 2, 0, 1, MF_COMMON,
        "Write cache disable", NULL},
    {"LBS", RBC_DEV_PARAM_MP, 0, 0xe, 3, 7, 16, MF_COMMON,
        "Logical block size", NULL},
    {"NLBS", RBC_DEV_PARAM_MP, 0, 0xe, 5, 7, 40, (MF_COMMON | MF_HEX),
        "Number of logical blocks", NULL},
    {"P_P", RBC_DEV_PARAM_MP, 0, 0xe, 10, 7, 8, 0,
        "Power/performance", NULL},
    {"READD", RBC_DEV_PARAM_MP, 0, 0xe, 11, 3, 1, 0,
        "Read disable", NULL},
    {"WRITED", RBC_DEV_PARAM_MP, 0, 0xe, 11, 2, 1, 0,
        "Write disable", NULL},
    {"FORMATD", RBC_DEV_PARAM_MP, 0, 0xe, 11, 1, 1, 0,
        "Format disable", NULL},
    {"LOCKD", RBC_DEV_PARAM_MP, 0, 0xe, 11, 0, 1, 0,
        "Lock disable", NULL},

    /* Verify error recovery mode page [0x7] sbc2 */
    {"V_EER", V_ERR_RECOVERY_MP, 0, 0, 2, 3, 1, 0,
        "Enable early recovery", NULL},
    {"V_PER", V_ERR_RECOVERY_MP, 0, 0, 2, 2, 1, 0,
        "Post error", NULL},
    {"V_DTE", V_ERR_RECOVERY_MP, 0, 0, 2, 1, 1, 0,
        "Data terminate on error", NULL},
    {"V_DCR", V_ERR_RECOVERY_MP, 0, 0, 2, 0, 1, 0,
        "Disable correction", NULL},
    {"V_RC", V_ERR_RECOVERY_MP, 0, 0, 3, 7, 8, 0,
        "Verify retry count", NULL},
    {"V_COR_S", V_ERR_RECOVERY_MP, 0, 0, 4, 7, 8, 0,
        "Verify correction span (obsolete)", NULL},
    {"V_RTL", V_ERR_RECOVERY_MP, 0, 0, 10, 7, 16, 0,
        "Verify recovery time limit (ms)", NULL},

    /* Caching mode page [0x8] sbc2 */
    {"IC", CACHING_MP, 0, 0, 2, 7, 1, 0,
        "Initiator control",
        "0: disk uses own adaptive caching algorithm\t"
        "1: disk caching algorithm controlled by NCS or CCS"},
    {"ABPF", CACHING_MP, 0, 0, 2, 6, 1, 0,
        "Abort pre-fetch", NULL},
    {"CAP", CACHING_MP, 0, 0, 2, 5, 1, 0,
        "Caching analysis permitted", NULL},
    {"DISC", CACHING_MP, 0, 0, 2, 4, 1, 0,
        "Discontinuity",
        "0: pre-fetch truncated or wrapped at time discontinuity\t"
        "1: pre-fetch continues across time discontinuity"},
    {"SIZE", CACHING_MP, 0, 0, 2, 3, 1, 0,
        "Size enable",
        "0: number of cache segments (NCS) controls cache segmentation\t"
        "1: the cache segment size (CCS) controls cache segmentation"},
    {"WCE", CACHING_MP, 0, 0, 2, 2, 1, MF_COMMON,
        "Write cache enable", NULL},
    {"MF", CACHING_MP, 0, 0, 2, 1, 1, 0,
        "Multiplication factor",
        "0: MIPF and MAPF specify blocks\t"
        "1: multiply MIPF and MAPF by blocks in read command"},
    {"RCD", CACHING_MP, 0, 0, 2, 0, 1, MF_COMMON,
        "Read cache disable", NULL},
    {"DRRP", CACHING_MP, 0, 0, 3, 7, 4, 0,
        "Demand read retention priority",
        "0: treat requested and other data equally\t"
        "1: replace requested data before other data\t"
        "15: replace other data before requested data"},
    {"WRP", CACHING_MP, 0, 0, 3, 3, 4, 0,
        "Write retention priority",
        "0: treat requested and other data equally\t"
        "1: replace requested data before other data\t"
        "15: replace other data before requested data"},
    {"DPTL", CACHING_MP, 0, 0, 4, 7, 16, 0,
        "Disable pre-fetch transfer length", NULL},
    {"MIPF", CACHING_MP, 0, 0, 6, 7, 16, 0,
        "Minimum pre-fetch", NULL},
    {"MAPF", CACHING_MP, 0, 0, 8, 7, 16, 0,
        "Maximum pre-fetch", NULL},
    {"MAPFC", CACHING_MP, 0, 0, 10, 7, 16, 0,
        "Maximum pre-fetch ceiling", NULL},
    {"FSW", CACHING_MP, 0, 0, 12, 7, 1, 0,
        "Force sequential write", NULL},
    {"LBCSS", CACHING_MP, 0, 0, 12, 6, 1, 0,
        "Logical block cache segment size",
        "0: CSS unit is bytes; 1: CSS unit is blocks"},
    {"DRA", CACHING_MP, 0, 0, 12, 5, 1, 0,
        "Disable read ahead", NULL},
    {"NV_DIS", CACHING_MP, 0, 0, 12, 0, 1, 0,
        "Non-volatile cache disable", NULL},
    {"NCS", CACHING_MP, 0, 0, 13, 7, 8, 0,
        "Number of cache segments", NULL},
    {"CSS", CACHING_MP, 0, 0, 14, 7, 16, 0,
        "Cache segment size", NULL},

    /* Control mode page [0xa] spc3 */
    {"TST", CONTROL_MP, 0, -1, 2, 7, 3, 0,
        "Task set type",
        "0: lu maintains one task set for all I_T nexuses\t"
        "1: lu maintains separate task sets for each I_T nexus"},
    {"TMF_ONLY", CONTROL_MP, 0, -1, 2, 4, 1, 0,
        "Task management functions only", NULL},
    {"D_SENSE", CONTROL_MP, 0, -1, 2, 2, 1, 0,
        "Descriptor format sense data", NULL},
    {"GLTSD", CONTROL_MP, 0, -1, 2, 1, 1, 0,
        "Global logging target save disable", NULL},
    {"RLEC", CONTROL_MP, 0, -1, 2, 0, 1, 0,
        "Report log exception condition", NULL},
    {"QAM", CONTROL_MP, 0, -1, 3, 7, 4, 0,
        "Queue algorithm modifier",
        "0: restricted re-ordering; 1: unrestricted"},
    {"QERR", CONTROL_MP, 0, -1, 3, 2, 2, 0,
        "Queue error management",
        "0: only affected task gets CC; 1: affected tasks aborted\t"
        "3: affected tasks aborted on same I_T nexus"},
    {"RAC", CONTROL_MP, 0, -1, 4, 6, 1, 0,
        "Report a check", NULL},
    {"UA_INTLCK", CONTROL_MP, 0, -1, 4, 5, 2, 0,
        "Unit attention interlocks control",
        "0: unit attention cleared with check condition status\t"
        "2: unit attention not cleared with check condition status\t"
        "3: as 2 plus ua on busy, task set full or reservation conflict"},
    {"SWP", CONTROL_MP, 0, -1, 4, 3, 1, MF_COMMON,
        "Software write protect", NULL},
    {"ATO", CONTROL_MP, 0, -1, 5, 7, 1, 0,
        "Application tag owner", NULL},
    {"TAS", CONTROL_MP, 0, -1, 5, 6, 1, 0,
        "Task aborted status",
        "0: tasks aborted without response to app client\t"
        "1: any other I_T nexuses receive task aborted"},
    {"AUTOLOAD", CONTROL_MP, 0, -1, 5, 2, 3, 0,
        "Autoload mode", 
        "0: medium loaded for full access;\t"
        "1: loaded for medium auxiliary access only\t"
        "2: medium shall not be loaded"},
    {"BTP", CONTROL_MP, 0, -1, 8, 7, 16, 0,
        "Busy timeout period (100us)", NULL},
    {"ESTCT", CONTROL_MP, 0, -1, 10, 7, 16, 0,
        "Extended self test completion time (sec)", NULL},

    /* Control extension mode subpage [0xa,0x1] spc3 */
    {"TCMOS", CONTROL_MP, MSP_SPC_CE, -1, 4, 2, 1, 0,
        "Timestamp changeable by methods outside standard", NULL},
    {"SCSIP", CONTROL_MP, MSP_SPC_CE, -1, 4, 1, 1, 0,
        "SCSI timestamp commands take precedence over other methods", NULL},
    {"IALUAE", CONTROL_MP, MSP_SPC_CE, -1, 4, 0, 1, 0,
        "Implicit asymmetric logical unit access enabled", NULL},

    /* SAT: pATA control mode subpage [0xa,0xf1] sat-r09 */
    /* treat as spc since could be disk or ATAPI */
    {"MWD2", CONTROL_MP, MSP_SAT_PATA, -1, 4, 6, 1, 0,
        "Multi word DMA bit 2", NULL},
    {"MWD1", CONTROL_MP, MSP_SAT_PATA, -1, 4, 5, 1, 0,
        "Multi word DMA bit 1", NULL},
    {"MWD0", CONTROL_MP, MSP_SAT_PATA, -1, 4, 4, 1, 0,
        "Multi word DMA bit 0", NULL},
    {"PIO4", CONTROL_MP, MSP_SAT_PATA, -1, 4, 1, 1, 0,
        "Parallel IO bit 4", NULL},
    {"PIO3", CONTROL_MP, MSP_SAT_PATA, -1, 4, 0, 1, 0,
        "Parallel IO bit 3", NULL},
    {"UDMA6", CONTROL_MP, MSP_SAT_PATA, -1, 5, 6, 1, 0,
        "Ultra DMA bit 6", NULL},
    {"UDMA5", CONTROL_MP, MSP_SAT_PATA, -1, 5, 5, 1, 0,
        "Ultra DMA bit 5", NULL},
    {"UDMA4", CONTROL_MP, MSP_SAT_PATA, -1, 5, 4, 1, 0,
        "Ultra DMA bit 4", NULL},
    {"UDMA3", CONTROL_MP, MSP_SAT_PATA, -1, 5, 3, 1, 0,
        "Ultra DMA bit 3", NULL},
    {"UDMA2", CONTROL_MP, MSP_SAT_PATA, -1, 5, 2, 1, 0,
        "Ultra DMA bit 2", NULL},
    {"UDMA1", CONTROL_MP, MSP_SAT_PATA, -1, 5, 1, 1, 0,
        "Ultra DMA bit 1", NULL},
    {"UDMA0", CONTROL_MP, MSP_SAT_PATA, -1, 5, 0, 1, 0,
        "Ultra DMA bit 0", NULL},

    /* Power condition mode page - obsolete block-device-only version */
    /*   [0xd] sbc (replacement page now at 0x1a) */
    {"IDLE-OLD", POWER_OLD_MP, 0, 0, 3, 1, 1, 0,
        "Idle timer active", NULL},
    {"STBY-OLD", POWER_OLD_MP, 0, 0, 3, 0, 1, 0,
        "Standby timer active", NULL},
    {"ICT-OLD", POWER_OLD_MP, 0, 0, 4, 7, 32, 0,
        "Idle condition timer (100 ms)", NULL},
    {"SCT-OLD", POWER_OLD_MP, 0, 0, 8, 7, 32, 0,
        "Standby condition timer (100 ms)", NULL},

    /* Data compression mode page [0xf] ssc3 */
    {"DCE", DATA_COMPR_MP, 0, 1, 2, 7, 1, MF_COMMON,
        "Data compression enable", NULL},
    {"DCC", DATA_COMPR_MP, 0, 1, 2, 6, 1, MF_COMMON,
        "Data compression capable", NULL},
    {"DDE", DATA_COMPR_MP, 0, 1, 3, 7, 1, MF_COMMON,
        "Data decompression enable", NULL},
    {"RED", DATA_COMPR_MP, 0, 1, 3, 6, 2, 0,
        "Report exception on decompression", NULL},
    {"COMPR_A", DATA_COMPR_MP, 0, 1, 4, 7, 32, 0,
        "Compression algorithm",
        "0: none; 5: ALDC (2048 byte): 16: IDRC; 32: DCLZ"},
    {"DCOMPR_A", DATA_COMPR_MP, 0, 1, 8, 7, 32, 0,
        "Decompression algorithm",
        "0: none; 5: ALDC (2048 byte): 16: IDRC; 32: DCLZ"},

    /* XOR control mode page [0x10] sbc2 */
    {"XORDIS", XOR_MP, 0, 0, 2, 1, 1, 0,
        "XOR disable", NULL},
    {"MXWS", XOR_MP, 0, 0, 4, 7, 32, 0,
        "Maximum XOR write size (blocks)", NULL},

    /* Device configuration mode page [0x10] ssc3 */
    {"CAF", DEV_CONF_MP, 0, 1, 2, 5, 1, 0,
        "Change active format", NULL},
    {"ACT_F", DEV_CONF_MP, 0, 1, 2, 4, 5, 0,
        "Active format", NULL},
    {"ACT_P", DEV_CONF_MP, 0, 1, 3, 7, 8, 0,
        "Active partition", NULL},
    {"WOBFR", DEV_CONF_MP, 0, 1, 4, 7, 8, 0,
        "Write object buffer full ratio", NULL},
    {"ROBER", DEV_CONF_MP, 0, 1, 5, 7, 8, 0,
        "Read object buffer empty ratio", NULL},
    {"WDT", DEV_CONF_MP, 0, 1, 6, 7, 16, 0,
        "Write delay time (100 ms)", NULL},
    {"OBR", DEV_CONF_MP, 0, 1, 8, 7, 1, 0,
        "Object buffer recovery", NULL},
    {"LOIS", DEV_CONF_MP, 0, 1, 8, 6, 1, 0,
        "Logical object identifiers supported", NULL},
    {"RSMK", DEV_CONF_MP, 0, 1, 8, 5, 1, MF_COMMON,
        "Report setmarks (obsolete)", NULL},
    {"AVC", DEV_CONF_MP, 0, 1, 8, 4, 1, 0,
        "Automatic velocity control", NULL},
    {"SOCF", DEV_CONF_MP, 0, 1, 8, 3, 2, 0,
        "Stop on consecutive filemarks", NULL},
    {"ROBO", DEV_CONF_MP, 0, 1, 8, 1, 1, 0,
        "Recover object buffer order", NULL},
    {"REW", DEV_CONF_MP, 0, 1, 8, 0, 1, 0,
        "Report early warning", NULL},
    {"GAP_S", DEV_CONF_MP, 0, 1, 9, 7, 8, 0,
        "Gap size (obsolete)", NULL},
    {"EOD_D", DEV_CONF_MP, 0, 1, 10, 7, 3, 0,
        "EOD (end-of-data) defined",
        "0: default; 1: format defined; 2: SOCF; 3: not supported"},
    {"EEG", DEV_CONF_MP, 0, 1, 10, 4, 1, 0,
        "Enable EOD generation", NULL},
    {"SEW", DEV_CONF_MP, 0, 1, 10, 3, 1, MF_COMMON,
        "Synchronize early warning", NULL},
    {"SWP_T", DEV_CONF_MP, 0, 1, 10, 2, 1, 0,
        "Software write protect (tape)", NULL},
    {"BAML", DEV_CONF_MP, 0, 1, 10, 1, 1, 0,
        "Block address mode lock", NULL},
    {"BAM", DEV_CONF_MP, 0, 1, 10, 0, 1, 0,
        "Block address mode", NULL},
    {"OBSAEW", DEV_CONF_MP, 0, 1, 11, 7, 24, 0,
        "Object buffer size at early warning", NULL},
    {"SDCA", DEV_CONF_MP, 0, 1, 14, 7, 8, MF_COMMON,
        "Select data compression algorithm", NULL},
    {"WTRE", DEV_CONF_MP, 0, 1, 15, 7, 2, 0,
        "WORM tamper read enable", NULL},
    {"OIR", DEV_CONF_MP, 0, 1, 15, 5, 1, 0,
        "Only if reserved", NULL},
    {"ROR", DEV_CONF_MP, 0, 1, 15, 4, 2, 0,
        "Rewind on reset",
        "0: vendor specific; 1: to BOP 0 on lu reset\t"
        "2: hold position on lu reset"},
    {"ASOCWP", DEV_CONF_MP, 0, 1, 15, 2, 1, 0,
        "Associated write protection", NULL},
    {"PERSWP", DEV_CONF_MP, 0, 1, 15, 1, 1, 0,
        "Persistent write protection", NULL},
    {"PRMWP", DEV_CONF_MP, 0, 1, 15, 0, 1, 0,
        "Permanent write protection", NULL},

    /* Device configuration extension mode subpage [0x10,1 ] ssc3 */
    {"TARPF", DEV_CONF_MP, MSP_DEV_CONF_EXT, 1, 4, 3, 1, 0,
        "TapeAlert respect parameter fields", NULL},
    {"TASER", DEV_CONF_MP, MSP_DEV_CONF_EXT, 1, 4, 2, 1, 0,
        "TapeAlert select except reporting", NULL},
    {"TARPC", DEV_CONF_MP, MSP_DEV_CONF_EXT, 1, 4, 1, 1, 0,
        "TapeAlert respect page control", NULL},
    {"TAPLSD", DEV_CONF_MP, MSP_DEV_CONF_EXT, 1, 4, 0, 1, 0,
        "TapeAlert prevent log sense deactivation", NULL},
    {"SEM", DEV_CONF_MP, MSP_DEV_CONF_EXT, 1, 5, 3, 4, 0,
        "Short erase mode",
        "0: as per ssc-2; 1: erase has no effect; 2: record EOD indication"},

    /* Medium partition mode page [0x11] ssc3 */
    {"MAX_AP", MED_PART_MP, 0, 1, 2, 7, 8, 0,
        "Maximum additional partitions", NULL},
    {"APD", MED_PART_MP, 0, 1, 3, 7, 8, 0,
        "Additional partitions defined", NULL},
    {"FDP", MED_PART_MP, 0, 1, 4, 7, 1, 0,
        "Fixed data partitions", NULL},
    {"SDP", MED_PART_MP, 0, 1, 4, 6, 1, 0,
        "Select data partitions", NULL},
    {"IDP", MED_PART_MP, 0, 1, 4, 5, 1, 0,
        "Initiator defined partitions", NULL},
    {"PSUM", MED_PART_MP, 0, 1, 4, 4, 2, 0,
        "Partition size unit of measure",
        "0: bytes; 1: kilobytes; 2: megabytes; 3: 10**(partition_units)"},
    {"POFM", MED_PART_MP, 0, 1, 4, 2, 1, 0,
        "Partition on format", NULL},
    {"CLEAR", MED_PART_MP, 0, 1, 4, 1, 1, 0,
        "Erase partition(s) (in concert with ADDP)", NULL},
    {"ADDP", MED_PART_MP, 0, 1, 4, 0, 1, 0,
        "Additional partition bit (in concert with CLEAR)", NULL},
    {"MFR", MED_PART_MP, 0, 1, 5, 7, 8, 0,
        "Medium format recognition",
        "0: incapable; 1: format recognition; 2: partition recognition\t"
        "3: format and partition recognition"},
    {"PART_U", MED_PART_MP, 0, 1, 6, 3, 4, 0,
        "Partition units (exponent of 10, bytes)", NULL},
    {"P_SZ_0", MED_PART_MP, 0, 1, 8, 7, 16, 0,
        "Partition size (index 0)", NULL},
    {"P_SZ_1", MED_PART_MP, 0, 1, 10, 7, 16, 0,
        "Partition size (index 1)", NULL},
    {"P_SZ_2", MED_PART_MP, 0, 1, 12, 7, 16, 0,
        "Partition size (index 2)", NULL},

    /* Enclosure services management mode page [0x14] ses2 */
    {"ENBLTC", ES_MAN_MP, 0, 0xd, 5, 0, 1, MF_COMMON,
        "Enable timed completion", NULL},
    {"MTCT", ES_MAN_MP, 0, 0xd, 6, 7, 16, MF_COMMON,
        "Maximum task completion time (100ms)", NULL},

    /* Protocol specific logical unit control mode page [0x18] spc3 */
    {"LUPID", PROT_SPEC_LU_MP, 0, -1, 2, 3, 4, 0,
        "Logical unit's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi\t"
        "[try adding '-t <transport>' to get more fields]"},

    /* Protocol specific port control mode page [0x19] spc3 */
    {"PPID", PROT_SPEC_PORT_MP, 0, -1, 2, 3, 4, 0,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi\t"
        "[try adding '-t <transport>' to get more fields]"},

    /* Power condition mode page [0x1a] spc3 */
    {"IDLE", POWER_MP, 0, -1, 3, 1, 1, 0,
        "Idle timer active", NULL},
    {"STANDBY", POWER_MP, 0, -1, 3, 0, 1, 0,
        "Standby timer active", NULL},
    {"ICT", POWER_MP, 0, -1, 4, 7, 32, 0,
        "Idle condition timer (100 ms)", NULL},
    {"SCT", POWER_MP, 0, -1, 8, 7, 32, 0,
        "Standby condition timer (100 ms)", NULL},

    /* Informational exception control mode page [0x1c] spc3 */
    {"PERF", IEC_MP, 0, -1, 2, 7, 1, 0,
        "Performance (impact of ie operations)",
        "0: normal (some delays); 1: abridge ie operations"},
    {"EBF", IEC_MP, 0, -1, 2, 5, 1, 0,
        "Enable background function", NULL},
    {"EWASC", IEC_MP, 0, -1, 2, 4, 1, MF_COMMON,
        "Enable warning", NULL},
    {"DEXCPT", IEC_MP, 0, -1, 2, 3, 1, MF_COMMON,
        "Disable exceptions", NULL},
    {"TEST", IEC_MP, 0, -1, 2, 2, 1, 0,
        "Test (simulate device failure)", NULL},
    {"EBACKERR", IEC_MP, 0, -1, 2, 1, 1, 0,
        "Enable background (scan + self test) error reporting", NULL},
    {"LOGERR", IEC_MP, 0, -1, 2, 0, 1, 0,
        "Log informational exception errors", NULL},
    {"MRIE", IEC_MP, 0, -1, 3, 3, 4, MF_COMMON,
        "Method of reporting informational exceptions",
        "0: no reporting; 1: async reporting; 2: unit attention\t"
        "3: conditional recovered error; 4: recovered error\t"
        "5: check condition with no sense; 6: request sense only"},
    {"INTT", IEC_MP, 0, -1, 4, 7, 32, 0,
        "Interval timer (100 ms)", NULL},
    {"REPC", IEC_MP, 0, -1, 8, 7, 32, 0,
        "Report count", NULL},

    /* Background control mode subpage [0x1c,0x1] sbc3 */
    {"S_L_FULL", IEC_MP, MSP_BACK_CTL, 0, 4, 2, 1, 0,
        "Suspend on log full", NULL},
    {"LOWIR", IEC_MP, MSP_BACK_CTL, 0, 4, 1, 1, 0,
        "Log only when intervention required", NULL},
    {"EN_BMS", IEC_MP, MSP_BACK_CTL, 0, 4, 0, 1, 0,
        "Enable background medium scan", NULL},
    {"EN_PS", IEC_MP, MSP_BACK_CTL, 0, 5, 0, 1, 0,
        "Enable pre-scan", NULL},
    {"BMS_I", IEC_MP, MSP_BACK_CTL, 0, 6, 7, 16, 0,
        "Background medium scan interval time (hour)", NULL},
    {"BPS_TL", IEC_MP, MSP_BACK_CTL, 0, 8, 7, 16, 0,
        "Background pre-scan time limit (hour)", NULL},
    {"MIN_IDLE", IEC_MP, MSP_BACK_CTL, 0, 10, 7, 16, 0,
        "Minumum idle time before background scan (ms)", NULL},
    {"MAX_SUSP", IEC_MP, MSP_BACK_CTL, 0, 12, 7, 16, 0,
        "Maximum time to suspend background scan (ms)", NULL},

    /* Medium configuration mode page [0x1d] ssc3 */
    {"WORMM", MED_CONF_MP, 0, 1, 2, 0, 1, 0,
        "Worm mode", NULL},
    {"WMLR", MED_CONF_MP, 0, 1, 4, 7, 8, 0,
        "Worm mode label restrictions",
        "0: disallow overwrite; 1: disallow some format labels overwrite\t"
        "2: allow all format labels to be overwritten"},
    {"WMFR", MED_CONF_MP, 0, 1, 5, 7, 8, 0,
        "Worm mode filemark restrictions",
        "2: allow filemarks before EOD except closest to BOP\t"
        "3: allow any number of filemarks before EOD"},

    /* Timeout and protect mode page [0x1d] mmc5 */
    {"G3E", TIMEOUT_PROT_MP, 0, 5, 4, 3, 1, 0,
        "Group 3 timeout capability enable", NULL},
    {"TMOE", TIMEOUT_PROT_MP, 0, 5, 4, 2, 1, 0,
        "Timeout enable", NULL},
    {"DISP", TIMEOUT_PROT_MP, 0, 5, 4, 1, 1, 0,
        "Disable (unavailable) until power cycle", NULL},
    {"SWPP", TIMEOUT_PROT_MP, 0, 5, 4, 0, 1, 0,
        "Software write protect until power cycle", NULL},
    {"G1MT", TIMEOUT_PROT_MP, 0, 5, 6, 7, 16, 0,
        "Group 1 minimum timeout (sec)", NULL},
    {"G2MT", TIMEOUT_PROT_MP, 0, 5, 8, 7, 16, 0,
        "Group 2 minimum timeout (sec)", NULL},

    /* CD/DVD (MM) capabilities and mechanical status mode page */
    /* [0x2a] obsolete in mmc4 and mmc5, last valid in mmc3 */
    {"D_RAM_R", MMCMS_MP, 0, 5, 2, 5, 1, 0,
        "DVD-RAM read", NULL},
    {"D_R_R", MMCMS_MP, 0, 5, 2, 4, 1, 0,
        "DVD-R read", NULL},
    {"D_ROM_R", MMCMS_MP, 0, 5, 2, 3, 1, 0,
        "DVD-ROM read", NULL},
    {"METH2", MMCMS_MP, 0, 5, 2, 2, 1, 0,
        "Method 2", NULL},
    {"CD_RW_R", MMCMS_MP, 0, 5, 2, 1, 1, 0,
        "CD-RW read", NULL},
    {"CD_R_R", MMCMS_MP, 0, 5, 2, 0, 1, 0,
        "CD-R read", NULL},
    {"D_RAM_W", MMCMS_MP, 0, 5, 3, 5, 1, 0,
        "DVD-RAM write", NULL},
    {"D_R_W", MMCMS_MP, 0, 5, 3, 4, 1, 0,
        "DVD-R write", NULL},     /* was D_R_R, wrong, clashed with above */
    {"TST_WR", MMCMS_MP, 0, 5, 3, 2, 1, 0,
        "Test write", NULL},      /* was TST_W but clashed with page 0x5 */
    {"CD_RW_W", MMCMS_MP, 0, 5, 3, 1, 1, 0,
        "CD-RW write", NULL},
    {"CD_R_W", MMCMS_MP, 0, 5, 3, 0, 1, 0,
        "CD-R write", NULL},
    {"BUF", MMCMS_MP, 0, 5, 4, 7, 1, 0,
        "Buffer underrun free recording", NULL},
    {"MULT_S", MMCMS_MP, 0, 5, 4, 6, 1, 0,
        "Multi session", NULL},   /* was MULTI_S but clashed with page 0x5 */
    {"M2F2", MMCMS_MP, 0, 5, 4, 5, 1, 0,
        "Mode 2 form 2", NULL},
    {"M2F1", MMCMS_MP, 0, 5, 4, 4, 1, 0,
        "Mode 2 form 1", NULL},
    {"DP_2", MMCMS_MP, 0, 5, 4, 3, 1, 0,
        "Digital port 2", NULL},
    {"DP_1", MMCMS_MP, 0, 5, 4, 2, 1, 0,
        "Digital port 1", NULL},
    {"COMP", MMCMS_MP, 0, 5, 4, 1, 1, 0,
        "Composite", NULL},
    {"AUDIO_P", MMCMS_MP, 0, 5, 4, 0, 1, 0,
        "Audio play", NULL},
    {"RBC", MMCMS_MP, 0, 5, 5, 7, 1, 0,
        "Read bar code", NULL},
    {"UPC", MMCMS_MP, 0, 5, 5, 6, 1, 0,
        "Uniform product code", NULL},
    {"ISRC", MMCMS_MP, 0, 5, 5, 5, 1, 0,
        "International standard recording code", NULL},
    {"C2PS", MMCMS_MP, 0, 5, 5, 4, 1, 0,
        "C 2 pointers supported", NULL},
    {"RW_DC", MMCMS_MP, 0, 5, 5, 3, 1, 0,
        "R-W de-interleaved and corrected", NULL},
    {"RW_S", MMCMS_MP, 0, 5, 5, 2, 1, 0,
        "R-W supported", NULL},
    {"CDDA_SA", MMCMS_MP, 0, 5, 5, 1, 1, 0,
        "CD-DA stream accurate", NULL},
    {"CDDA_CS", MMCMS_MP, 0, 5, 5, 0, 1, 0,
        "CD-DA commands supported", NULL},
    {"LMT", MMCMS_MP, 0, 5, 6, 7, 3, 0,
        "Loading mechanism type", NULL},
    {"EJECT", MMCMS_MP, 0, 5, 6, 3, 1, 0,
        "Eject (individual or magazine)", NULL},
    {"PJ", MMCMS_MP, 0, 5, 6, 2, 1, 0,
        "Prevent jumper", NULL},
    {"LS", MMCMS_MP, 0, 5, 6, 1, 1, 0,
        "Lock state", NULL},
    {"LOCK", MMCMS_MP, 0, 5, 6, 0, 1, 0,
        "Lock (supported)", NULL},
    {"RWILI", MMCMS_MP, 0, 5, 7, 5, 1, 0,
        "R-W in lead in", NULL},
    {"SCC", MMCMS_MP, 0, 5, 7, 4, 1, 0,
        "Side change capable", NULL},
    {"SSS", MMCMS_MP, 0, 5, 7, 3, 1, 0,
        "Software slot selection", NULL},
    {"CSDP", MMCMS_MP, 0, 5, 7, 2, 1, 0,
        "Changer supports disc present", NULL},
    {"SCM", MMCMS_MP, 0, 5, 7, 1, 1, 0,
        "Separate channel mute", NULL},
    {"SVL", MMCMS_MP, 0, 5, 7, 0, 1, 0,
        "Separate volume levels", NULL},
    {"NVLS", MMCMS_MP, 0, 5, 10, 7, 16, 0,
        "Number of volume levels supported", NULL},
    {"BSS", MMCMS_MP, 0, 5, 12, 7, 16, 0,
        "Buffer size supported (1024 bytes)", NULL},
    {"LENGTH", MMCMS_MP, 0, 5, 17, 5, 2, 0,
        "Length (bit length of IEC958 words)", NULL},
    {"LSBF", MMCMS_MP, 0, 5, 17, 3, 1, 0,
        "LSB (least significant bit) first", NULL},
    {"RCK", MMCMS_MP, 0, 5, 17, 2, 1, 0,
        "High on LRCK indicates left channel", NULL},
    {"BCKF", MMCMS_MP, 0, 5, 17, 1, 1, 0,
        "BCK signal falling edge", NULL},
    {"CMRS", MMCMS_MP, 0, 5, 22, 7, 16, 0,
        "Copy management revision supported", NULL},
    {"RCS", MMCMS_MP, 0, 5, 27, 1, 2, 0,
        "Rotation control selected", NULL},
    {"CWSS", MMCMS_MP, 0, 5, 28, 7, 16, 0,
        "Current write speed selected", NULL},

    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL},
};


/* << Transport protocol specific mode page items follow >> */

static struct sdparm_mode_page_item sdparm_mitem_fcp_arr[] = {
    /* disconnect-reconnect mode page [0x2] fcp3 */
    {"BFR", DISCONNECT_MP, 0, -1, 2, 7, 8, 0,
        "Buffer full ratio", NULL},
    {"BER", DISCONNECT_MP, 0, -1, 3, 7, 8, 0,
        "Buffer empty ratio", NULL},
    {"BIL", DISCONNECT_MP, 0, -1, 4, 7, 16, MF_COMMON,
        "Bus inactivity limit (transmission words)", NULL},
    {"DTL", DISCONNECT_MP, 0, -1, 6, 7, 16, MF_COMMON,
        "Disconnect time limit (128 transmission words)", NULL},
    {"CTL", DISCONNECT_MP, 0, -1, 8, 7, 16, MF_COMMON,
        "Connect time limit (128 transmission words)", NULL},
    {"MBS", DISCONNECT_MP, 0, -1, 10, 7, 16, MF_COMMON,
        "Maximum burst size (512 bytes)", NULL},
    {"EMDP", DISCONNECT_MP, 0, -1, 12, 7, 1, 0,
        "Enable modify data pointers", NULL},
    {"FAA", DISCONNECT_MP, 0, -1, 12, 6, 1, 0,
        "Fairness access A [FCP_DATA]", NULL},
    {"FAB", DISCONNECT_MP, 0, -1, 12, 5, 1, 0,
        "Fairness access B [FCP_XFER]", NULL},
    {"FAC", DISCONNECT_MP, 0, -1, 12, 4, 1, 0,
        "Fairness access C [FCP_RSP]", NULL},
    {"FBS", DISCONNECT_MP, 0, -1, 14, 7, 16, 0,
        "First burst size (512 bytes)", NULL},

    /* protocol specific logical unit mode page [0x18] fcp3 */
    {"LUPID", PROT_SPEC_LU_MP, 0, -1, 2, 3, 4, MF_COMMON,
        "Logical unit's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"EPDC", PROT_SPEC_LU_MP, 0, -1, 3, 0, 1, MF_COMMON,
        "Enable precise delivery checking", NULL},

    /* protocol specific port control page [0x19] fcp3 */
    {"PPID", PROT_SPEC_PORT_MP, 0, -1, 2, 3, 4, MF_COMMON,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"DTFD", PROT_SPEC_PORT_MP, 0, -1, 3, 7, 1, MF_COMMON,
        "Disable target fabric discovery", NULL},
    {"PLPB", PROT_SPEC_PORT_MP, 0, -1, 3, 6, 1, MF_COMMON,
        "Prevent loop port bypass", NULL},
    {"DDIS", PROT_SPEC_PORT_MP, 0, -1, 3, 5, 1, 0,
        "Disable discovery", NULL},
    {"DLM", PROT_SPEC_PORT_MP, 0, -1, 3, 4, 1, 0,
        "Disable loop master", NULL},
    {"RHA", PROT_SPEC_PORT_MP, 0, -1, 3, 3, 1, 0,
        "Require hard address", NULL},
    {"ALWI", PROT_SPEC_PORT_MP, 0, -1, 3, 2, 1, 0,
        "Allow login without loop initialization", NULL},
    {"DTIPE", PROT_SPEC_PORT_MP, 0, -1, 3, 1, 1, 0,
        "Disable target initialized port enable", NULL},
    {"DTOLI", PROT_SPEC_PORT_MP, 0, -1, 3, 0, 1, 0,
        "Disable target originated loop initialization", NULL},
    {"RRTVU", PROT_SPEC_PORT_MP, 0, -1, 6, 2, 3, 0,
        "Resource recovery timeout value unit", NULL},
    {"SIRRTV", PROT_SPEC_PORT_MP, 0, -1, 7, 7, 8, 0,
        "Sequence initiative resource recovery timeout value", NULL},

    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_mode_page_item sdparm_mitem_spi_arr[] = {
    /* disconnect-reconnect mode page [0x2] spi4 */
    {"BFR", DISCONNECT_MP, 0, -1, 2, 7, 8, 0,
        "Buffer full ratio", NULL},
    {"BER", DISCONNECT_MP, 0, -1, 3, 7, 8, 0,
        "Buffer empty ratio", NULL},
    {"BIL", DISCONNECT_MP, 0, -1, 4, 7, 16, MF_COMMON,
        "Bus inactivity limit (100 us)", NULL},
    {"PDTL", DISCONNECT_MP, 0, -1, 6, 7, 16, MF_COMMON,
        "Physical disconnect time limit (100 us)", NULL},
    {"CTL", DISCONNECT_MP, 0, -1, 8, 7, 16, MF_COMMON,
        "Connect time limit (100 us)", NULL},
    {"MBS", DISCONNECT_MP, 0, -1, 10, 7, 16, MF_COMMON,
        "Maximum burst size (512 bytes)", NULL},
    {"EMDP", DISCONNECT_MP, 0, -1, 12, 7, 1, 0,
        "Enable modify data pointers", NULL},
    {"FA", DISCONNECT_MP, 0, -1, 12, 6, 3, 0,
        "Fair arbitration", NULL},
    {"DIMM", DISCONNECT_MP, 0, -1, 12, 3, 1, 0,
        "Disconnect immediate", NULL},
    {"DTDC", DISCONNECT_MP, 0, -1, 12, 2, 3, 0,
        "Data transfer disconnect control", NULL},

    /* protocol specific logical unit control mode page [0x18] spi4 */
    {"LUPID", PROT_SPEC_LU_MP, 0, -1, 2, 3, 4, MF_COMMON,
        "Logical unit's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},

    /* protocol specific port control page [0x19] spi4 */
    {"PPID", PROT_SPEC_PORT_MP, 0, -1, 2, 3, 4, MF_COMMON,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"STT", PROT_SPEC_PORT_MP, 0, -1, 4, 7, 16, MF_COMMON,
        "Synchronous transfer timeout (ms)", NULL},

    /* margin control subpage  [0x19,0x1] spi4 */
    {"PPID_1", PROT_SPEC_PORT_MP, MSP_SPI_MC, -1, 5, 3, 4, 0,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"DS", PROT_SPEC_PORT_MP, MSP_SPI_MC, -1, 7, 7, 4, 0,
        "Driver strength", NULL},
    {"DA", PROT_SPEC_PORT_MP, MSP_SPI_MC, -1, 8, 7, 4, 0,
        "Driver asymmetry", NULL},
    {"DP", PROT_SPEC_PORT_MP, MSP_SPI_MC, -1, 8, 3, 4, 0,
        "Driver precompensation", NULL},
    {"DSR", PROT_SPEC_PORT_MP, MSP_SPI_MC, -1, 9, 7, 4, 0,
        "Driver slew rate", NULL},

    /* saved training configuration subpage [0x19,0x2] spi4 */
    {"PPID_2", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 5, 3, 4, 0,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"DB0", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 10, 7, 32, MF_HEX,
        "DB(0) value", NULL},
    {"DB1", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 14, 7, 32, MF_HEX,
        "DB(1) value", NULL},
    {"DB2", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 18, 7, 32, MF_HEX,
        "DB(2) value", NULL},
    {"DB3", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 22, 7, 32, MF_HEX,
        "DB(3) value", NULL},
    {"DB4", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 26, 7, 32, MF_HEX,
        "DB(4) value", NULL},
    {"DB5", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 30, 7, 32, MF_HEX,
        "DB(5) value", NULL},
    {"DB6", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 34, 7, 32, MF_HEX,
        "DB(6) value", NULL},
    {"DB7", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 38, 7, 32, MF_HEX,
        "DB(7) value", NULL},
    {"DB8", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 42, 7, 32, MF_HEX,
        "DB(8) value", NULL},
    {"DB9", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 46, 7, 32, MF_HEX,
        "DB(9) value", NULL},
    {"DB10", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 50, 7, 32, MF_HEX,
        "DB(10) value", NULL},
    {"DB11", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 54, 7, 32, MF_HEX,
        "DB(11) value", NULL},
    {"DB12", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 58, 7, 32, MF_HEX,
        "DB(12) value", NULL},
    {"DB13", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 62, 7, 32, MF_HEX,
        "DB(13) value", NULL},
    {"DB14", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 66, 7, 32, MF_HEX,
        "DB(14) value", NULL},
    {"DB15", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 70, 7, 32, MF_HEX,
        "DB(15) value", NULL},
    {"P_CRCA", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 74, 7, 32, MF_HEX,
        "P_CRCA value", NULL},
    {"P1", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 78, 7, 32, MF_HEX,
        "P1 value", NULL},
    {"BSY", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 82, 7, 32, MF_HEX,
        "BSY value", NULL},
    {"SEL", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 86, 7, 32, MF_HEX,
        "SEL value", NULL},
    {"RST", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 90, 7, 32, MF_HEX,
        "RST value", NULL},
    {"REQ", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 94, 7, 32, MF_HEX,
        "REQ value", NULL},
    {"ACK", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 98, 7, 32, MF_HEX,
        "ACK value", NULL},
    {"ATN", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 102, 7, 32, MF_HEX,
        "ATN value", NULL},
    {"C_D", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 106, 7, 32, MF_HEX,
        "C/D value", NULL},
    {"I_O", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 110, 7, 32, MF_HEX,
        "I/O value", NULL},
    {"MSG", PROT_SPEC_PORT_MP, MSP_SPI_STC, -1, 114, 7, 32, MF_HEX,
        "MSG value", NULL},

    /* negotiated settings subpage [0x19,0x3] spi4 */
    {"PPID_3", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 5, 3, 4, 0,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"TPF", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 6, 7, 8, 0,
        "Transfer period factor", NULL},
    {"RAO", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 8, 7, 8, 0,
        "REQ/ACK offset", NULL},
    {"TWE", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 9, 7, 8, 0,
        "Transfer width exponent", NULL},
    {"POB", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 10, 6, 7, 0,
        "Protocol option bits", NULL},
    {"TM", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 11, 3, 2, 0,
        "Transceiver mode", NULL},
    {"SPE", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 11, 1, 1, 0,
        "Sent PCOMP_EN bit (for current I_T nexus)", NULL},
    {"RPE", PROT_SPEC_PORT_MP, MSP_SPI_NS, -1, 11, 0, 1, 0,
        "Received PCOMP_EN bit (for current I_T nexus)", NULL},

    /* report transfer capabilities subpage [0x19,0x4] spi4 */
    {"PPID_4", PROT_SPEC_PORT_MP, MSP_SPI_RTC, -1, 5, 3, 4, 0,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"MTPF", PROT_SPEC_PORT_MP, MSP_SPI_RTC, -1, 6, 7, 8, 0,
        "Minimum transfer period factor", NULL},
    {"MRAO", PROT_SPEC_PORT_MP, MSP_SPI_RTC, -1, 8, 7, 8, 0,
        "Maximum REQ/ACK offset", NULL},
    {"MTWE", PROT_SPEC_PORT_MP, MSP_SPI_RTC, -1, 9, 7, 8, 0,
        "Maximum transfer width exponent", NULL},
    {"POBS", PROT_SPEC_PORT_MP, MSP_SPI_RTC, -1, 10, 7, 8, 0,
        "Protocol option bits supported", NULL},

    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_mode_page_item sdparm_mitem_srp_arr[] = {
    /* disconnect-reconnect mode page [0x2] srp */
    {"MBS", DISCONNECT_MP, 0, -1, 10, 7, 16, MF_COMMON,
        "Maximum burst size (512 bytes)", NULL},
    {"EMDP", DISCONNECT_MP, 0, -1, 12, 7, 1, 0,
        "Enable modify data pointers", NULL},

    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_mode_page_item sdparm_mitem_sas_arr[] = {
    /* disconnect-reconnect mode page [0x2] sas1 */
    {"BITL", DISCONNECT_MP, 0, -1, 4, 7, 16, MF_COMMON,
        "Bus inactivity time limit (100us)", NULL},
    {"MCTL", DISCONNECT_MP, 0, -1, 8, 7, 16, MF_COMMON,
        "Maximum connect time limit (100us)", NULL},
    {"MBS", DISCONNECT_MP, 0, -1, 10, 7, 16, MF_COMMON,
        "Maximum burst size (512 bytes)", NULL},
    {"FBS", DISCONNECT_MP, 0, -1, 14, 7, 16, 0,
        "First burst size (512 bytes)", NULL},

    /* protocol specific logical unit control mode page [0x18] sas1 */
    {"LUPID", PROT_SPEC_LU_MP, 0, -1, 2, 3, 4, MF_COMMON,
        "Logical unit's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"TLR", PROT_SPEC_LU_MP, 0, -1, 2, 4, 1, 0,
        "Transport layer retries (supported)", NULL},

    /* protocol specific port control page - short format [0x19] sas1 */
    {"PPID", PROT_SPEC_PORT_MP, 0, -1, 2, 3, 4, MF_COMMON,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"BAE", PROT_SPEC_PORT_MP, 0, -1, 2, 5, 1, MF_COMMON,
        "Broadcast asynchronous event", NULL},
    {"RLM", PROT_SPEC_PORT_MP, 0, -1, 2, 4, 1, MF_COMMON, 
        "Ready LED meaning",
        "0: usually on, flash when command processing; off when stopped\t"
        "1: usually off, flash when command processing"},
    {"ITNLT", PROT_SPEC_PORT_MP, 0, -1, 4, 7, 16, MF_COMMON, 
        "I_T nexus loss time (ms)", NULL},
    {"IRT", PROT_SPEC_PORT_MP, 0, -1, 6, 7, 16, MF_COMMON, 
        "Initiator response timeout (ms)", NULL},

    /* phy control + discover subpage [0x19,0x1] sas1 */
    {"PPID_1", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 5, 3, 4, 0,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"NOP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 7, 7, 8, MF_COMMON, 
        "Number of phys", NULL},
    /* */
    {"PHID", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 9, 7, 8, 0, 
        "Phy identifier", NULL},
    {"ADT", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 12, 6, 3, 0, 
        "Attached device type",
        "0: no device attached; 1: end device\t"
        "2: edge expander device; 3: fanout expander device"},
    {"NPLR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 13, 3, 4, 0, 
        "Negotiated physical link rate",
        "0: unknown; 1: disabled; 2: phy reset problem; 3: spinup hold\t"
        "4: port selector; 8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"ASIP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 14, 3, 1, 0, 
        "Attached SSP initiator port", NULL},
    {"ATIP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 14, 2, 1, 0, 
        "Attached STP initiator port", NULL},
    {"AMIP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 14, 1, 1, 0, 
        "Attached SMP initiator port", NULL},
    {"ASTP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 15, 3, 1, 0, 
        "Attached SSP target port", NULL},
    {"ATTP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 15, 2, 1, 0, 
        "Attached STP target port", NULL},
    {"AMTP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 15, 1, 1, 0, 
        "Attached SMP target port", NULL},
    {"SASA", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 16, 7, 64, MF_HEX, 
        "SAS address", NULL},
    {"ASASA", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 24, 7, 64, MF_HEX, 
        "Attached SAS address", NULL},
    {"APHID", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 32, 7, 8, 0, 
        "Attached phy identifier", NULL},
    {"PMILR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 40, 7, 4, 0, 
        "Programmed minimum link rate",
        "0: not programmed; 8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"HMILR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 40, 3, 4, 0, 
        "Hardware minimum link rate",
        "8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"PMALR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 41, 7, 4, 0, 
        "Programmed maximum link rate",
        "0: not programmed; 8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"HMALR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 41, 3, 4, 0, 
        "Hardware maximum link rate",
        "8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    /* */
    {"2_PHID", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 57, 7, 8, 0, 
        "Phy identifier", NULL},
    {"2_ADT", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 60, 6, 3, 0, 
        "Attached device type",
        "0: no device attached; 1: end device\t"
        "2: edge expander device; 3: fanout expander device"},
    {"2_NPLR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 61, 3, 4, 0, 
        "Negotiated physical link rate",
        "0: unknown; 1: disabled; 2: phy reset problem; 3: spinup hold\t"
        "4: port selector; 8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"2_ASIP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 62, 3, 1, 0, 
        "Attached SSP initiator port", NULL},
    {"2_ATIP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 62, 2, 1, 0, 
        "Attached STP initiator port", NULL},
    {"2_AMIP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 62, 1, 1, 0, 
        "Attached SMP initiator port", NULL},
    {"2_ASTP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 63, 3, 1, 0, 
        "Attached SSP target port", NULL},
    {"2_ATTP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 63, 2, 1, 0, 
        "Attached STP target port", NULL},
    {"2_AMTP", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 63, 1, 1, 0, 
        "Attached SMP target port", NULL},
    {"2_SASA", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 64, 7, 64, MF_HEX, 
        "SAS address", NULL},
    {"2_ASASA", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 72, 7, 64, MF_HEX, 
        "Attached SAS address", NULL},
    {"2_APHID", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 80, 7, 8, 0, 
        "Attached phy identifier", NULL},
    {"2_PMILR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 88, 7, 4, 0, 
        "Programmed minimum link rate",
        "0: not programmed; 8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"2_HMILR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 88, 3, 4, 0, 
        "Hardware minimum link rate",
        "8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"2_PMALR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 89, 7, 4, 0, 
        "Programmed maximum link rate",
        "0: not programmed; 8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},
    {"2_HMALR", PROT_SPEC_PORT_MP, MSP_SAS_PCD, -1, 89, 3, 4, 0, 
        "Hardware maximum link rate",
        "8: 1.5 Gbps; 9: 3 Gbps; 0xa: 6 Gbps"},

    /* SSP shared protocol specific port subpage [0x19,0x2] sas2 */
    {"PPID_2", PROT_SPEC_PORT_MP, MSP_SAS_SHA, -1, 5, 3, 4, 0,
        "Port's (transport) protocol identifier",
        "0: fcp; 1: spi; 4: srp; 5: iscsi; 6: sas; 7: adt; 8: ata/atapi"},
    {"PLT", PROT_SPEC_PORT_MP, MSP_SAS_SHA, -1, 6, 7, 16, 0, 
        "Power loss timeout(ms)", NULL},

    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL},
};

/* fixed length, indexed by transport protocol number */
struct sdparm_transport_pair sdparm_transport_mp[] = {
    {sdparm_fcp_mode_pg, sdparm_mitem_fcp_arr}, /* 0 */
    {sdparm_spi_mode_pg, sdparm_mitem_spi_arr},
    {NULL, NULL},
    {NULL, NULL},
    {sdparm_srp_mode_pg, sdparm_mitem_srp_arr},
    {NULL, NULL},
    {sdparm_sas_mode_pg, sdparm_mitem_sas_arr},
    {NULL, NULL},
    {NULL, NULL},       /* 8 */
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},       /* 15 */
};


/* Vendor specific mode pages */
struct sdparm_values_name_t sdparm_vendor_id[] = {
    {VENDOR_SEAGATE, 0, -1, 0, "sea", "Seagate disk"},
    {VENDOR_HITACHI, 0, -1, 0, "hit", "Hitachi disk"},
    {VENDOR_MAXTOR, 0, -1, 0, "max", "Maxtor disk"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_values_name_t sdparm_v_seagate_mode_pg[] = {
    {UNIT_ATTENTION_MP, 0, 0, 0, "ua", "Unit attention (seagate)"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_mode_page_item sdparm_mitem_v_seagate_arr[] = {
    /* Unit attention page [0x0] Seagate */
    {"PM", UNIT_ATTENTION_MP, 0, 0, 2, 7, 1, MF_COMMON,
        "Performance Mode",
        "0: adaptive cache ('server mode')\t"
        "1: number of cache segments as per caching page ('desktop mode')"},
    {"SSM", UNIT_ATTENTION_MP, 0, 0, 2, 6, 1, 0,
        "Synchronous select mode (SPI)",
        "0: drive will not initiate WDTR or SDTR\t"
        "1: drive may initiate WDTR or SDTR"},
    {"IL", UNIT_ATTENTION_MP, 0, 0, 2, 5, 1, MF_COMMON,
        "Inquiry length",
        "0: more than 36 bytes in response\t"
        "1: 36 byte response as per SCSI-2"},
    {"UA", UNIT_ATTENTION_MP, 0, 0, 2, 4, 1, MF_COMMON,
        "Unit attention",
        "0: unit attention condition for all initiators after reset\t"
        "1: no check condition with unit attention after reset"},
    {"DFUA", UNIT_ATTENTION_MP, 0, 0, 2, 3, 1, 0,
        "Disable force unit access (FUA)",
        "0: honour FUA bit setting on READ and WRITE commands\t"
        "1: ignore FUA bit setting"},
    {"ROUND", UNIT_ATTENTION_MP, 0, 0, 2, 2, 1, 0,
        "Reporting of log parameter rounding (wrap around)",
        "0: do not report (silently round)\t"
        "1: report rounding (as per SPC-4)"},
    {"STRICT", UNIT_ATTENTION_MP, 0, 0, 2, 1, 1, MF_COMMON,
        "Strict when trying to alter unchangeable mode page fields",
        "0: silently ignore\t"
        "1: report as error"},
    {"SCSI2", UNIT_ATTENTION_MP, 0, 0, 2, 0, 1, MF_COMMON,
        "SCSI-2 lengths for control and caching mode pages",
        "0: as per recent standards\t"
        "1: SCSI-2 lengths: control, 6; caching, 10"},
    {"SSEEK", UNIT_ATTENTION_MP, 0, 0, 3, 6, 1, 0,
        "Self seek",
        "0: off (normal operating mode)\t"
        "1: enter self seek mode (test power dissipation, acoustics, etc)"},
    {"JIT3", UNIT_ATTENTION_MP, 0, 0, 4, 3, 1, 0,
        "Just in time 3, slowest seek type",
        "0: can not use this seek type in seek speed algorithm\t"
        "1: can use this seek type in seek speed algorithm"},
    {"JIT2", UNIT_ATTENTION_MP, 0, 0, 4, 2, 1, 0,
        "Just in time 2, second slowest seek type",
        "0: can not use this seek type in seek speed algorithm\t"
        "1: can use this seek type in seek speed algorithm"},
    {"JIT1", UNIT_ATTENTION_MP, 0, 0, 4, 1, 1, 0,
        "Just in time 1, second fastest seek type",
        "0: can not use this seek type in seek speed algorithm\t"
        "1: can use this seek type in seek speed algorithm"},
    {"JIT0", UNIT_ATTENTION_MP, 0, 0, 4, 0, 1, 0,
        "Just in time 0, fastest seek type",
        "0: can not use this seek type in seek speed algorithm\t"
        "1: can use this seek type in seek speed algorithm"},

    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_values_name_t sdparm_v_hitachi_mode_pg[] = {
    {UNIT_ATTENTION_MP, 0, 0, 0, "vup", "Vendor unique parameters (hitachi)"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_mode_page_item sdparm_mitem_v_hitachi_arr[] = {
    /* Vendor unique parameters page [0x0] Hitachi */
    {"MRG", UNIT_ATTENTION_MP, 0, 0, 2, 3, 1, 0,
        "Merge Glist into Plist (during format)", NULL},
    {"VGMDE", UNIT_ATTENTION_MP, 0, 0, 3, 6, 1, MF_COMMON,
        "Veggie mode (do random seeks when idle)", NULL},
    {"RRNDE", UNIT_ATTENTION_MP, 0, 0, 3, 1, 1, 0,
        "Report recovered non data errors (when PER set)", NULL},
    {"FDD", UNIT_ATTENTION_MP, 0, 0, 5, 4, 1, 0,
        "Format degraded disable (reporting for Test Unit Ready)", NULL},
    {"CAEN", UNIT_ATTENTION_MP, 0, 0, 5, 1, 1, MF_COMMON,
        "Command aging enable", NULL},
    {"IGRA", UNIT_ATTENTION_MP, 0, 0, 6, 7, 1, MF_COMMON,
        "Ignore reassigned LBA (when RC also set)", NULL},
    {"AVERP", UNIT_ATTENTION_MP, 0, 0, 6, 6, 1, MF_COMMON,
        "AV ERP mode (maximum retry count for read errors)",
        "0: use default (ignore RRC)\t"
        "1: use RRC field"},
    {"OCT", UNIT_ATTENTION_MP, 0, 0, 6, 3, 12, 0,
        "Overall command timer, 0 -> disabled (50 ms)", NULL},
    {"TT", UNIT_ATTENTION_MP, 0, 0, 9, 7, 8, 0,
        "Temperature threshold (celsius), 0 -> 85C", NULL},
    {"CAL", UNIT_ATTENTION_MP, 0, 0, 10, 7, 16, 0,
        "Command aging limit (50 ms), 0 -> 85C", NULL},
    {"RRT", UNIT_ATTENTION_MP, 0, 0, 12, 7, 8, 0,
        "Read reporting threshold for read recovered errors when PER set",
        NULL},
    {"WRT", UNIT_ATTENTION_MP, 0, 0, 13, 7, 8, 0,
        "Write reporting threshold for write recovered errors when PER set",
        NULL},
    {"DRRT", UNIT_ATTENTION_MP, 0, 0, 14, 7, 1, 0,
        "Disable restore reassign target",
        "0: REASSIGN attempts to recovery old data\t"
        "1: REASSIGN ignores old data"},
    {"FFMT", UNIT_ATTENTION_MP, 0, 0, 14, 3, 1, 0,
        "Fast format enable, format without writes to customer media", NULL},
    {"FCERT", UNIT_ATTENTION_MP, 0, 0, 15, 5, 1, 0,
        "Format certification (enable)", NULL},

    {NULL, 0, 0, 0, 0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_values_name_t sdparm_v_maxtor_mode_pg[] = {
    {UNIT_ATTENTION_MP, 0, 0, 0, "uac", "Unit attention condition (maxtor)"},
    {0, 0, 0, 0, NULL, NULL},
};

static struct sdparm_mode_page_item sdparm_mitem_v_maxtor_arr[] = {
    /* Unit attention page [0x0] Seagate */
    {"DUA", UNIT_ATTENTION_MP, 0, 0, 2, 4, 1, MF_COMMON,
        "Disable unit attention", NULL},
};

/* Indexed by VENDOR_* define */
struct sdparm_vendor_pair sdparm_vendor_mp[] = {
    {sdparm_v_seagate_mode_pg, sdparm_mitem_v_seagate_arr},
    {sdparm_v_hitachi_mode_pg, sdparm_mitem_v_hitachi_arr},
    {sdparm_v_maxtor_mode_pg, sdparm_mitem_v_maxtor_arr},
};

int sdparm_vendor_mp_len = 
        sizeof(sdparm_vendor_mp) / sizeof(sdparm_vendor_mp[0]);


const char * sdparm_pdt_doc_strs[] = {
    /* 0 */ "SBC-3",    /* disk */
    "SSC-3",            /* tape */
    "SSC",              /* printer */
    "SPC-2",            /* processor */
    "SBC",              /* write once optical disk */
    /* 5 */ "MMC-5",    /* cd/dvd */
    "SCSI-2",           /* scanner */
    "SBC-2",            /* optical memory device */
    "SMC-2",            /* medium changer */
    "SCSI-2",           /* communications */
    /* 0xa */ "SCSI-2", /* graphics [0xa] */
    "SCSI-2",           /* graphics [0xb] */
    "SCC-2",            /* storage array controller */
    "SES-2",            /* enclosure services device */
    "RBC",              /* simplified direct access device */
    "OCRW",             /* optical card reader/writer device */
    /* 0x10 */ "BCC",   /* bridge controller commands */
    "OSD-2",            /* object based storage */
    "ADC",              /* automation/driver interface */
    "unknown",          /* 0x13 */
    "unknown", "unknown", "unknown", "unknown", "unknown",
    "unknown", "unknown", "unknown", "unknown",
    "unknown",          /* 0x1d */
    "SPC-4",            /* well known logical unit */
    "SPC-4",            /* no physical device on this lu */
};

const char * sdparm_transport_proto_arr[] =
{
    "Fibre Channel (FCP-2)",
    "Parallel SCSI (SPI-4)",
    "SSA (SSA-S3P)",
    "IEEE 1394 (SBP-3)",
    "Remote Direct Memory Access (RDMA)",
    "Internet SCSI (iSCSI)",
    "Serial Attached SCSI (SAS)",
    "Automation/Drive Interface (ADT)",
    "ATA Packet Interface (ATA/ATAPI-7)",
    "Ox9", "Oxa", "Oxb", "Oxc", "Oxd", "Oxe",
    "No specific protocol"
};

const char * sdparm_code_set_arr[] =
{
    "Reserved [0x0]",
    "Binary",
    "ASCII",
    "UTF-8",
    "Reserved [0x4]", "Reserved [0x5]", "Reserved [0x6]", "Reserved [0x7]",
    "Reserved [0x8]", "Reserved [0x9]", "Reserved [0xa]", "Reserved [0xb]",
    "Reserved [0xc]", "Reserved [0xd]", "Reserved [0xe]", "Reserved [0xf]",
};

const char * sdparm_assoc_arr[] =
{
    "Addressed logical unit",
    "Target port",      /* that received request; unless SCSI ports VPD */
    "Target device that contains addressed lu",
    "Reserved [0x3]",
};

const char * sdparm_desig_type_arr[] =
{
    "vendor specific [0x0]",
    "T10 vendor identification",
    "EUI-64 based",
    "NAA",
    "Relative target port",
    "Target port group",
    "Logical unit group",
    "MD5 logical unit identifier",
    "SCSI name string",
    "Reserved [0x9]", "Reserved [0xa]", "Reserved [0xb]",
    "Reserved [0xc]", "Reserved [0xd]", "Reserved [0xe]", "Reserved [0xf]",
};

const char * sdparm_ansi_version_arr[] =
{
    "no conformance claimed",
    "SCSI-1",
    "SCSI-2",
    "SPC",
    "SPC-2",
    "SPC-3",
    "SPC-4",
    "ANSI version: 7",
};

const char * sdparm_network_service_type_arr[] =
{
    "unspecified",
    "storage configuration service",
    "diagnostics",
    "status",
    "logging",
    "code download",
    "reserved[0x6]", "reserved[0x7]", "reserved[0x8]", "reserved[0x9]",
    "reserved[0xa]", "reserved[0xb]", "reserved[0xc]", "reserved[0xd]",
    "reserved[0xe]", "reserved[0xf]", "reserved[0x10]", "reserved[0x11]",
    "reserved[0x12]", "reserved[0x13]", "reserved[0x14]", "reserved[0x15]",
    "reserved[0x16]", "reserved[0x17]", "reserved[0x18]", "reserved[0x19]",
    "reserved[0x1a]", "reserved[0x1b]", "reserved[0x1c]", "reserved[0x1d]",
    "reserved[0x1e]", "reserved[0x1f]",
};

const char * sdparm_mode_page_policy_arr[] =
{
    "shared",
    "per target port",
    "per initiator port (obsolete)",    /* obsoleted in SPC-4 */
    "per I_T nexus",
};

struct sdparm_command sdparm_command_arr[] =
{
    {CMD_CAPACITY, "capacity"},
    {CMD_EJECT, "eject"},
    {CMD_LOAD, "load"},
    {CMD_READY, "ready"},
    {CMD_SENSE, "sense"},
    {CMD_START, "start"},
    {CMD_STOP, "stop"},
    {CMD_SYNC, "sync"},
    {CMD_UNLOCK, "unlock"},
    {-1, NULL},
};
