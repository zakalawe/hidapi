
#ifndef HIDPARSE_H__
#define HIDPARSE_H__

#include <stdint.h>

#include "hidapi.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct hid_item_s {

        /**
         * @brief next our sibling items
         */
        struct hid_item_s *next;

        /**
         * @brief collection our child items
         */
        struct hid_item_s *collection;

        /**
         * @brief parent our parent collection
         */
        struct hid_item_s *parent;

        #if 0
        /** Platform-specific device path */
        char *path;
        /** Device Vendor ID */
        unsigned short vendor_id;
        /** Device Product ID */
        unsigned short product_id;
        /** Serial Number */
        wchar_t *serial_number;
        /** Device Release Number in binary-coded decimal,
            also known as Device Version Number */
        unsigned short release_number;
        /** Manufacturer String */
        wchar_t *manufacturer_string;
        /** Product string */
        wchar_t *product_string;
        /** Usage Page for this Device/Interface
            (Windows/Mac only). */
        unsigned short usage_page;
        /** Usage for this Device/Interface
            (Windows/Mac only).*/
        unsigned short usage;
        /** The USB interface which this logical device
            represents. Valid on both Linux implementations
            in all cases, and valid on the Windows implementation
            only if the device contains more than one interface. */
        int interface_number;

        /** Pointer to the next device */
        struct hid_device_info *next;
        #endif

        uint32_t usage;
        uint8_t type;

        uint8_t report_size; /* in bits */
        uint8_t report_id;
        uint8_t flags;

        int32_t logical_min, logical_max, physical_min, physical_max;
        uint32_t unit, unit_exponent;
    } hid_item;

int HID_API_EXPORT HID_API_CALL hid_parse_report(uint8_t* rdesc_buf, uint32_t rdesc_size, hid_item** root);


#ifdef __cplusplus
}
#endif

#endif
