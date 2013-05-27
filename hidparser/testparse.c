#include "hidapi.h"
#include "hidparse.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	#define MAX_STR 255
	wchar_t wstr[MAX_STR];
    int res;
    
	if (hid_init())
		return -1;

    struct hid_device_info *devs, *cur_dev;
	devs = hid_enumerate(0x0, 0x0);
	cur_dev = devs;	
	while (cur_dev) {
		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		printf("  Product:      %ls\n", cur_dev->product_string);
		printf("  Release:      %hx\n", cur_dev->release_number);
		printf("  Interface:    %d\n",  cur_dev->interface_number);
		printf("\n");
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);
    
    hid_device *handle;
	handle = hid_open(0x09f3, 0x0064, NULL);
	if (!handle) {
		printf("unable to open device\n");
 		return 1;
	}
    
	wstr[0] = 0x0000;
	res = hid_get_product_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read product string\n");
	printf("Product String: %ls\n", wstr);
    
    
#if 0
	// Read Indexed String 1
	wstr[0] = 0x0000;
	res = hid_get_indexed_string(handle, 0, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read indexed string 1\n");
	printf("Indexed String 1: %ls\n", wstr);
#endif
    
	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);
    
    int i;
    unsigned char buf[2048];
	memset(buf,0,sizeof(buf));

	// Read a Feature Report from the device
	buf[0] = atoi(argv[1]);
	res = hid_get_feature_report(handle, buf, sizeof(buf));
	if (res < 0) {
		printf("Unable to get a feature report.\n");
		printf("%ls", hid_error(handle));
	}
	else {
		// Print out the returned buffer.
		printf("Feature Report (size=%d)\n   ", res);
		for (i = 0; i < res; i++)
			printf("%02hhx ", buf[i]);
		printf("\n");
	}
}