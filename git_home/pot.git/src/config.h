#ifndef __CONFIG_H_
#define __CONFIG_H_

#define POT_FILENAME		"/tmp/pot_value"

#define POT_MAX_VALUE	4320		/* 4320 minutes */
#define POT_RESOLUTION	1		/* minute */
#define POT_PORT	3333		/* potval listen this port */

#define NAND_FLASH_BLOCKSIZE	(124 * 1024)	/* bytes, 124KB */
#define NAND_FLASH_PAGESIZE	(2 * 1024)	/* bytes, 2KB */
#define POT_MTD_SIZE	(512 * 1024)	/* bytes, POT partition is 512KB(4 blocks) by default */
#define FIRST_NTP_TIME_OFFSET	(2 * NAND_FLASH_BLOCKSIZE)
#define FIRST_WIFISTATION_MAC_OFFSET	(FIRST_NTP_TIME_OFFSET + NAND_FLASH_PAGESIZE)

#endif
