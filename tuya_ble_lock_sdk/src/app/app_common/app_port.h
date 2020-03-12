/**
****************************************************************************
* @file      app_port.h
* @brief     app_port
* @author    suding
* @version   V1.0.0
* @date      2019-09-11
* @note
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2019 Tuya </center></h2>
*/


#ifndef __APP_PORT_H__
#define __APP_PORT_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
//cpt
#include "cpt_math.h"
#include "cpt_string_op.h"
#include "easyflash.h"
#include "elog.h"
#include "sha1.h"
#include "hmac-sha1.h"
//tuya_ble_sdk
#include "tuya_ble_api.h"
#include "tuya_ble_mem.h"
#include "tuya_ble_mutli_tsf_protocol.h"
#include "tuya_ble_main.h" //tuya_ble_current_para
//nrfs
#include "nrfs_common.h"
//app
#include "app_test.h" //factory_test_process

/*********************************************************************
 * CONSTANTS
 */
/*********************************************************  tuya  *********************************************************/
#define TUYA_DEVICE_PID         "eq1ebzwt"
#define TUYA_DEVICE_DID         "tuya3c9983a10a0a"                 //16Byte 
#define TUYA_DEVICE_AUTH_KEY    "fYUftqd2K2mq1BuMs9dYr7tGWg4zloy5" //32Byte

#define TUYA_DEVICE_FIR_NAME    "tuya_ble_lock_common_nRF52832"    //�̼���ʶ��
#define TUYA_DEVICE_FVER_NUM    0x00000101                         //�̼��汾
#define TUYA_DEVICE_HVER_NUM    0x00000100                         //Ӳ���汾
#define TUYA_DEVICE_FVER_STR    "1.1"                              //�̼��汾str
#define TUYA_DEVICE_HVER_STR    "1.0"                              //Ӳ���汾str

/*********************************************************  ble  *********************************************************/
#define APP_PORT_DEFAULT_MAC_ADDR_STR    "DC234D08C8EF"

#define APP_PORT_ADV_INTERVAL            152.5 //(1022.5) //ms
#define APP_PORT_MIN_CONN_INTERVAL       NRFS_MIN_CONN_INTERVAL
#define APP_PORT_MAX_CONN_INTERVAL       NRFS_MAX_CONN_INTERVAL
#define APP_PORT_SLAVE_LATENCY           NRFS_SLAVE_LATENCY
#define APP_PORT_CONN_SUP_TIMEOUT        NRFS_CONN_SUP_TIMEOUT

/*********************************************************  app_port  *********************************************************/
#define APP_PORT_DEBUG_EN 1
#if (APP_PORT_DEBUG_EN)
    #define APP_DEBUG_PRINTF(...)  NRFS_PRINTF(__VA_ARGS__)
    #define APP_DEBUG_HEXDUMP      nrfs_log_hexdump
#else
    #define APP_DEBUG_PRINTF(...)
    #define APP_DEBUG_HEXDUMP      nrfs_log_hexdump_empty
#endif

//addr len
#define APP_PORT_BLE_ADDR_LEN        (6)
#define APP_PORT_BLE_ADDR_STR_LEN    (APP_PORT_BLE_ADDR_LEN*2)

//return value
typedef enum {
    APP_PORT_SUCCESS  = 0x00,
    APP_PORT_ERROR_COMMON  = 0x01,
} app_port_status_t;

/*********************************************************  tuya_ble_sdk  *********************************************************/
//pid len
#define APP_PORT_PID_LEN          8

//tuya_ble_sdk data type
#define APP_PORT_DT_RAW           DT_RAW    
#define APP_PORT_DT_BOOL          DT_BOOL   
#define APP_PORT_DT_VALUE         DT_VALUE  
#define APP_PORT_DT_INT           DT_INT    
#define APP_PORT_DT_STRING        DT_STRING 
#define APP_PORT_DT_ENUM          DT_ENUM   
#define APP_PORT_DT_BITMAP        DT_BITMAP 
#define APP_PORT_DT_CHAR          DT_CHAR   
#define APP_PORT_DT_UCHAR         DT_UCHAR  
#define APP_PORT_DT_SHORT         DT_SHORT  
#define APP_PORT_DT_USHORT        DT_USHORT 
#define APP_PORT_DT_LMT           DT_LMT    
//tuya_ble_sdk data type len
#define APP_PORT_DT_VALUE_LEN     DT_VALUE_LEN
#define APP_PORT_DT_BOOL_LEN      DT_BOOL_LEN
#define APP_PORT_DT_ENUM_LEN      DT_ENUM_LEN
#define APP_PORT_DT_BITMAP_MAX    DT_BITMAP_MAX
#define APP_PORT_DT_STR_MAX       DT_STR_MAX
#define APP_PORT_DT_RAW_MAX       DT_RAW_MAX
#define APP_PORT_DT_INT_LEN       DT_INT_LEN

/*********************************************************************
 * STRUCT
 */

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */
/*********************************************************  Storage  *********************************************************/
void *app_port_malloc(uint32_t size);
uint32_t app_port_free(void* buf);
uint32_t app_port_kv_init(void);
uint32_t app_port_kv_set(const char *key, const void *buf, size_t size);
uint32_t app_port_kv_get(const char *key, void *buf, size_t size);
uint32_t app_port_kv_del(const char *key);
uint32_t app_port_nv_write(uint32_t addr, const uint8_t* p_data, uint32_t size);
uint32_t app_port_nv_erase(uint32_t addr, uint32_t size);

/*********************************************************  timer  *********************************************************/
uint32_t app_port_timer_create(void** p_timer_id, uint32_t timeout_value_ms, tuya_ble_timer_mode mode, tuya_ble_timer_handler_t timeout_handler);
uint32_t app_port_timer_delete(void* timer_id);
uint32_t app_port_timer_start(void* timer_id);
uint32_t app_port_timer_stop(void* timer_id);
uint32_t app_port_update_timestamp(uint32_t app_timestamp);
uint32_t app_port_get_timestamp(void);
uint32_t app_port_get_old_timestamp(uint32_t old_local_timestamp);

/*********************************************************  ble  *********************************************************/
uint32_t app_port_dp_data_report(uint8_t *buf, uint32_t size);
uint32_t app_port_dp_data_with_time_report(uint32_t timestamp, uint8_t *buf, uint32_t size);
uint32_t app_port_ota_rsp(tuya_ble_ota_data_response_t *rsp);
tuya_ble_connect_status_t app_port_get_connect_status(void);
void app_port_set_bt_mac_addr(uint8_t* addr);
void app_port_get_bt_mac_addr(uint8_t* addr);
uint32_t app_port_conn_param_update(uint16_t cMin, uint16_t cMax, uint16_t latency, uint16_t timeout);
uint32_t app_port_ble_gap_disconnect(void);
uint32_t app_port_ble_conn_evt_ext(void);

/*********************************************************  device  *********************************************************/
uint32_t app_port_device_reset(void);
uint32_t app_port_local_clock_start(void);
uint32_t app_port_ble_sdk_init(tuya_ble_device_param_t * param_data);
uint32_t app_port_ble_callback_queue_register(tuya_ble_callback_t cb);
uint8_t app_port_ble_custom_event_send(tuya_ble_custom_evt_t evt);
uint32_t app_port_uart_send_data(const uint8_t* buf,uint16_t size);
void app_port_factory_test_process(uint8_t* p_in_data, uint16_t in_len, uint8_t* p_out_data, uint16_t* out_len);
uint32_t app_port_dfu_settings_init(bool sd_irq_initialized);
uint32_t app_port_dfu_settings_write_and_backup(nrf_dfu_flash_callback_t callback);
uint32_t app_port_tuya_ble_device_factory_reset(void);

/*********************************************************  check  *********************************************************/
uint8_t app_port_check_sum(uint8_t *buf, uint32_t size);
uint16_t app_port_check_sum_16(uint8_t *buf, uint32_t size);
uint16_t app_port_crc16_compute(uint8_t* buf, uint16_t size, uint16_t* p_crc);
uint32_t app_port_crc32_compute(uint8_t* buf, uint32_t size, uint32_t* p_crc);
void app_port_reverse_byte(void* buf, uint32_t size);

/*********************************************************  string  *********************************************************/
uint8_t app_port_string_op_hexstr2hex(uint8_t *hexstr, int len, uint8_t* hex);
uint8_t app_port_string_op_hex2hexstr(uint8_t *hex, int len, uint8_t* hexstr);


#ifdef __cplusplus
}
#endif

#endif //__APP_PORT_H__
