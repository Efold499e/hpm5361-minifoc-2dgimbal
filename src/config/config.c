#include "board.h"
#include "eeprom_emulation.h"
#include "hpm_nor_flash.h" /* pulls hpm_romapi.h -> HPM_XPI0 */

/* ported to hpm_sdk v1.12.1 eeprom_emulation: nor_flash_config_t is app-side now,
 * e2p_write/e2p_read dropped the e2p_t handle argument */

static nor_flash_config_t nor_config;
static e2p_t e2p_ctx;

static hpm_stat_t config_read(uint8_t *buf, uint32_t addr, uint32_t size)
{
    return nor_flash_read(&nor_config, buf, addr, size);
}

static hpm_stat_t config_write(const uint8_t *buf, uint32_t addr, uint32_t size)
{
    return nor_flash_write(&nor_config, buf, addr, size);
}

static hpm_stat_t config_erase(uint32_t start_addr, uint32_t size)
{
    return nor_flash_erase(&nor_config, start_addr, size);
}

void config_init(void)
{
    nor_config.xpi_base = BOARD_APP_XPI_NOR_XPI_BASE;
    nor_config.opt_header = BOARD_APP_XPI_NOR_CFG_OPT_HDR;
    nor_config.opt0 = BOARD_APP_XPI_NOR_CFG_OPT_OPT0;
    nor_config.opt1 = BOARD_APP_XPI_NOR_CFG_OPT_OPT1;
    nor_config.base_addr = 0x80000000;

    nor_flash_init(&nor_config);

    /* same layout as the 2024 firmware: manage the upper half of the 1MB flash */
    e2p_ctx.config.start_addr = 0x80080000;
    e2p_ctx.config.erase_size = 4096;
    e2p_ctx.config.sector_cnt = 128;
    e2p_ctx.config.version = 0x0001;
    e2p_ctx.config.flash_read = config_read;
    e2p_ctx.config.flash_write = config_write;
    e2p_ctx.config.flash_erase = config_erase;

    e2p_config(&e2p_ctx);
}

int config_set(const char *name, void *buf, size_t len)
{
    uint32_t block_id = e2p_generate_id(name);
    return e2p_write(block_id, (uint16_t)len, buf);
}

int config_get(const char *name, void *buf, size_t len)
{
    uint32_t block_id = e2p_generate_id(name);
    return e2p_read(block_id, (uint16_t)len, buf);
}
