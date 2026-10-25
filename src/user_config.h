/*
 * user_config.h — required by hpm_sdk v1.12.1 eeprom_emulation component
 * (values copied from sdk samples/eeprom/eeprom_emulation/base defaults)
 */

#ifndef _USER_CONFIG_H
#define _USER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Debug level: TRACE(0) INFO(1) WARN(2) ERROR(3) NONE(4)
 */
#define E2P_DEBUG_LEVEL     (1)

/**
 * Maximum number of unique block_id entries tracked in RAM
 */
#define E2P_MAX_VAR_CNT     (100)

/**
 * Static buffer size used by flush and read operations.
 * Must be >= the largest single data entry written via e2p_write().
 */
#define E2P_FLUSH_BUF_SIZE  (512)

#ifdef __cplusplus
}
#endif

#endif /* _USER_CONFIG_H */
