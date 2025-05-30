/*
 * Copyright : (C) 2024 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2024/6/26 first commit
 */
#ifndef CHERRYUSB_CONFIG_H
#define CHERRYUSB_CONFIG_H

#include "rtconfig.h"
#include <rtthread.h> 

/* ================ USB common Configuration ================ */

#define CONFIG_USB_PRINTF(...) rt_kprintf(__VA_ARGS__)

void *usb_sys_mem_malloc(size_t size);
void usb_sys_mem_free(void *ptr);
void *usb_sys_malloc_align(size_t align, size_t size);

#define usb_malloc(size)        usb_sys_mem_malloc(size)
#define usb_free(ptr)           usb_sys_mem_free(ptr)
#define usb_align(align, size)  usb_sys_malloc_align(align, size)

unsigned long usb_hc_get_register_base(uint32_t id);
unsigned long usb_dc_get_register_base(uint32_t id);

#define CONFIG_USB_DBG_LEVEL USB_DBG_ERROR

/* Enable print with color */
#define CONFIG_USB_PRINTF_COLOR_ENABLE

/* data align size when use dma */
#ifndef CONFIG_USB_ALIGN_SIZE
#define CONFIG_USB_ALIGN_SIZE 4
#endif

/* attribute data into no cache ram */
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".noncacheable")))

/* ================= USB Device Stack Configuration ================ */

/* Ep0 in and out transfer buffer */
#ifndef CONFIG_USBDEV_REQUEST_BUFFER_LEN
#define CONFIG_USBDEV_REQUEST_BUFFER_LEN 512
#endif

/* Setup packet log for debug */
// #define CONFIG_USBDEV_SETUP_LOG_PRINT

/* Send ep0 in data from user buffer instead of copying into ep0 reqdata
 * Please note that user buffer must be aligned with CONFIG_USB_ALIGN_SIZE
*/
// #define CONFIG_USBDEV_EP0_INDATA_NO_COPY

/* Check if the input descriptor is correct */
// #define CONFIG_USBDEV_DESC_CHECK

/* Enable test mode */
// #define CONFIG_USBDEV_TEST_MODE

#ifndef CONFIG_USBDEV_MSC_MAX_LUN
#define CONFIG_USBDEV_MSC_MAX_LUN 1
#endif

#ifndef CONFIG_USBDEV_MSC_MAX_BUFSIZE
#define CONFIG_USBDEV_MSC_MAX_BUFSIZE 4096
#endif

#ifndef CONFIG_USBDEV_MSC_MANUFACTURER_STRING
#define CONFIG_USBDEV_MSC_MANUFACTURER_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_PRODUCT_STRING
#define CONFIG_USBDEV_MSC_PRODUCT_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_VERSION_STRING
#define CONFIG_USBDEV_MSC_VERSION_STRING "0.01"
#endif

// #define CONFIG_USBDEV_MSC_THREAD

#ifndef CONFIG_USBDEV_MSC_PRIO
#define CONFIG_USBDEV_MSC_PRIO 4
#endif

#ifndef CONFIG_USBDEV_MSC_STACKSIZE
#define CONFIG_USBDEV_MSC_STACKSIZE 8192
#endif

#ifndef CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE
#define CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE 156
#endif

/* rndis transfer buffer size, must be a multiple of (1536 + 44)*/
#ifndef CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE
#define CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE 1580
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_ID
#define CONFIG_USBDEV_RNDIS_VENDOR_ID 0x0000ffff
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_DESC
#define CONFIG_USBDEV_RNDIS_VENDOR_DESC "CherryUSB"
#endif

#define CONFIG_USBDEV_RNDIS_USING_LWIP

/* ================ USB HOST Stack Configuration ================== */

#define CONFIG_USBHOST_MAX_RHPORTS          1
#define CONFIG_USBHOST_MAX_EXTHUBS          0
#define CONFIG_USBHOST_MAX_EHPORTS          8
#define CONFIG_USBHOST_MAX_INTERFACES       8
#define CONFIG_USBHOST_MAX_INTF_ALTSETTINGS 8
#define CONFIG_USBHOST_MAX_ENDPOINTS        8

#define CONFIG_USBHOST_MAX_CDC_ACM_CLASS 4
#define CONFIG_USBHOST_MAX_HID_CLASS     4
#define CONFIG_USBHOST_MAX_MSC_CLASS     2
#define CONFIG_USBHOST_MAX_AUDIO_CLASS   1
#define CONFIG_USBHOST_MAX_VIDEO_CLASS   1

#define CONFIG_USBHOST_DEV_NAMELEN 16

#ifndef CONFIG_USBHOST_PSC_PRIO
#define CONFIG_USBHOST_PSC_PRIO 0
#endif
#ifndef CONFIG_USBHOST_PSC_STACKSIZE
#define CONFIG_USBHOST_PSC_STACKSIZE 8192
#endif

//#define CONFIG_USBHOST_GET_STRING_DESC

// #define CONFIG_USBHOST_MSOS_ENABLE
#ifndef CONFIG_USBHOST_MSOS_VENDOR_CODE
#define CONFIG_USBHOST_MSOS_VENDOR_CODE 0x00
#endif

/* Ep0 max transfer buffer */
#ifndef CONFIG_USBHOST_REQUEST_BUFFER_LEN
#define CONFIG_USBHOST_REQUEST_BUFFER_LEN 512
#endif

#ifndef CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT
#define CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT 500
#endif

#ifndef CONFIG_USBHOST_MSC_TIMEOUT
#define CONFIG_USBHOST_MSC_TIMEOUT 5000
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE
#define CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE (2048)
#endif

/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE
#define CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_CDC_NCM_ETH_MAX_RX_SIZE
#define CONFIG_USBHOST_CDC_NCM_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_CDC_NCM_ETH_MAX_TX_SIZE
#define CONFIG_USBHOST_CDC_NCM_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE
#define CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_ASIX_ETH_MAX_TX_SIZE
#define CONFIG_USBHOST_ASIX_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE
#define CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE
#define CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE (2048)
#endif

#define CONFIG_USBHOST_BLUETOOTH_HCI_H4
// #define CONFIG_USBHOST_BLUETOOTH_HCI_LOG

#ifndef CONFIG_USBHOST_BLUETOOTH_TX_SIZE
#define CONFIG_USBHOST_BLUETOOTH_TX_SIZE 2048
#endif
#ifndef CONFIG_USBHOST_BLUETOOTH_RX_SIZE
#define CONFIG_USBHOST_BLUETOOTH_RX_SIZE 2048
#endif

/* ================ USB Device Port Configuration ================*/

#ifndef CONFIG_USBDEV_MAX_BUS
#define CONFIG_USBDEV_MAX_BUS 1 // for now, bus num must be 1 except hpm ip
#endif

#ifndef CONFIG_USBDEV_EP_NUM
#define CONFIG_USBDEV_EP_NUM 8
#endif

/* ---------------- FSDEV Configuration ---------------- */
//#define CONFIG_USBDEV_FSDEV_PMA_ACCESS 2 // maybe 1 or 2, many chips may have a difference

/* ---------------- DWC2 Configuration ---------------- */
/* (5 * number of control endpoints + 8) + ((largest USB packet used / 4) + 1 for
 * status information) + (2 * number of OUT endpoints) + 1 for Global NAK
 */
// #define CONFIG_USB_DWC2_RXALL_FIFO_SIZE (1024 / 4)
/* IN Endpoints Max packet Size / 4 */
// #define CONFIG_USB_DWC2_TX0_FIFO_SIZE (64 / 4)
// #define CONFIG_USB_DWC2_TX1_FIFO_SIZE (512 / 4)
// #define CONFIG_USB_DWC2_TX2_FIFO_SIZE (64 / 4)
// #define CONFIG_USB_DWC2_TX3_FIFO_SIZE (64 / 4)
// #define CONFIG_USB_DWC2_TX4_FIFO_SIZE (0 / 4)
// #define CONFIG_USB_DWC2_TX5_FIFO_SIZE (0 / 4)
// #define CONFIG_USB_DWC2_TX6_FIFO_SIZE (0 / 4)
// #define CONFIG_USB_DWC2_TX7_FIFO_SIZE (0 / 4)
// #define CONFIG_USB_DWC2_TX8_FIFO_SIZE (0 / 4)

/* ---------------- MUSB Configuration ---------------- */
// #define CONFIG_USB_MUSB_SUNXI

/* ================ USB Host Port Configuration ==================*/
#ifndef CONFIG_INPUT_MOUSE_WHEEL
#define CONFIG_INPUT_MOUSE_WHEEL
#endif

#ifndef CONFIG_USBHOST_MAX_BUS
#define CONFIG_USBHOST_MAX_BUS 3
#endif

#ifndef CONFIG_USBHOST_PIPE_NUM
#define CONFIG_USBHOST_PIPE_NUM 10
#endif

/* ---------------- XHCI Configuration ---------------- */
#define CONFIG_USB_XHCI_HCCR_OFFSET (0x0)

/* ---------------- PUSB2 Configuration ---------------- */
#define CONFIG_USB_PUSB2_BUS_NUM  3U
#define CONFIG_USB_PUSB2_BUS_ID   0U

#endif
