#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"

#define SNSR_ADDR (0x44 << 1)

#define I2C_SDA (22U)
#define I2C_SCL (21U)


void i2c_master_init() {
    i2c_config_t conf;

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_SDA;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_SCL;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    conf.clk_flags = 0;
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0);
}

void read_temp() {
uint8_t  temp_data[2];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t ret;

    // Write command sequence
    ret = i2c_master_start(cmd);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_write_byte(cmd, SNSR_ADDR, true);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_write_byte(cmd, 0x2C, true);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_write_byte(cmd, 0x06, true);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, (2000 * configTICK_RATE_HZ) / 1000);
    ESP_ERROR_CHECK(ret);

    // Delete the old command sequence
    i2c_cmd_link_delete(cmd);

    // Create a new command sequence for reading
    cmd = i2c_cmd_link_create();

    // Read command sequence
    ret = i2c_master_start(cmd);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_write_byte(cmd, SNSR_ADDR | I2C_MASTER_READ, true);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_read_byte(cmd, &temp_data[0], I2C_MASTER_ACK);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_read_byte(cmd, &temp_data[1], I2C_MASTER_NACK);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(ret);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, (2000 * configTICK_RATE_HZ) / 1000);
    ESP_ERROR_CHECK(ret);

    // Parse data (adjust based on BME280 datasheet)
    int32_t tmp_raw = ((uint16_t)temp_data[0] << 8) | temp_data[1];
    float temperature = -45.0 + (175.0 * (tmp_raw / 65535.0));
    printf("Temperature: %.2f°C\n", temperature);

    i2c_cmd_link_delete(cmd);
}