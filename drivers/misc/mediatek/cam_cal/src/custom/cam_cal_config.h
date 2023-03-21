/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef __CAM_CAL_LAYOUT_H
#define __CAM_CAL_LAYOUT_H

#include "eeprom_driver.h"
#include "kd_imgsensor.h"
#include "cam_cal_format.h"
#include "eeprom_utils.h"

/*****************************************************************************
 * Structures
 *****************************************************************************/

struct STRUCT_CALIBRATION_ITEM_STRUCT {
	unsigned short Include; //calibration layout include this item?
	unsigned int start_addr; // item Start Address
	unsigned int block_size;   //block_size
	unsigned int (*GetCalDataProcess)(struct EEPROM_DRV_FD_DATA *pdata,
			unsigned int start_addr, unsigned int block_size,
			unsigned int *pGetSensorCalData);
};

struct STRUCT_CALIBRATION_LAYOUT_STRUCT {
	unsigned int header_addr; //Header Address
	unsigned int header_id;   //Header ID
	unsigned int data_ver;
	struct STRUCT_CALIBRATION_ITEM_STRUCT cal_layout_tbl[CAMERA_CAM_CAL_DATA_LIST];
};

struct STRUCT_CAM_CAL_CONFIG_STRUCT {
	const char *name;
	sensor_type_t sensor_type;
	unsigned int (*check_layout_function)(struct EEPROM_DRV_FD_DATA *pdata,
				unsigned int sensorID);
	unsigned int (*read_function)(struct i2c_client *client, unsigned int addr,
				unsigned char *data, unsigned int size);
	unsigned int (*mot_do_factory_verify_function)(struct EEPROM_DRV_FD_DATA *pdata,
				unsigned int *pGetSensorCalData);
	struct STRUCT_CALIBRATION_LAYOUT_STRUCT *layout;
	unsigned int sensor_id;
	unsigned int i2c_write_id;
	unsigned int max_size;
	unsigned int serial_number_bit;
	unsigned int enable_preload;
	unsigned int preload_size;
	unsigned int has_stored_data;
};

unsigned int show_cmd_error_log(enum ENUM_CAMERA_CAM_CAL_TYPE_ENUM cmd);
int get_mtk_format_version(struct EEPROM_DRV_FD_DATA *pdata, unsigned int *pGetSensorCalData);

unsigned int layout_check(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int sensorID);
unsigned int layout_no_ck(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int sensorID);
unsigned int mot_layout_no_ck(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int sensorId);
unsigned int do_module_version(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_part_number(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_single_lsc(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_2a_gain(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_pdaf(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_stereo_data(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_dump_all(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_lens_id_base(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int do_lens_id(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int mot_do_manufacture_info(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int mot_do_single_lsc(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int mot_do_2a_gain(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int mot_do_awb_gain(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);
unsigned int mot_do_pdaf(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int start_addr, unsigned int block_size, unsigned int *pGetSensorCalData);

unsigned int get_is_need_power_on(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int *pGetNeedPowerOn);
unsigned int get_cal_data(struct EEPROM_DRV_FD_DATA *pdata, unsigned int *pGetSensorCalData);
unsigned int mot_get_cal_factory_data(struct EEPROM_DRV_FD_DATA *pdata, unsigned int *pGetSensorCalData);
int32_t check_crc16(uint8_t  *data, uint32_t size, uint32_t ref_crc);
int  mot_check_awb_data(unsigned char* awb_data, int  size);

int read_data(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned int sensor_id, unsigned int device_id,
		unsigned int offset, unsigned int length, unsigned char *data);
unsigned int read_data_region(struct EEPROM_DRV_FD_DATA *pdata,
		unsigned char *buf, unsigned int offset, unsigned int size);

#endif /* __CAM_CAL_LAYOUT_H */
