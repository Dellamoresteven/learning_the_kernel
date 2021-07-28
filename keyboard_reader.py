import struct

# struct input_event {
	# struct timeval time;
	# unsigned short type;
	# unsigned short code;
	# unsigned int value;
# };
f = open("/dev/input/by-id/usb-DELL_Dell_USB_Wired_Entry_Keyboard-event-kbd")
while 1:
    data = f.read(24) # read 24 bytes
    formated_data = struct.unpack('4IHHI',data)
    key = formated_data[5]
    value = "pressed" if formated_data[6] == 1 else "released"
    print(key, value)
