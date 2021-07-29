#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <unordered_map>
#include <linux/input-event-codes.h> //https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h

std::unordered_map<char, int> key_code_map({
    { 'a', KEY_A },{ 'b', KEY_B },{ 'c', KEY_C },{ 'd', KEY_D },
    { 'e', KEY_E },{ 'f', KEY_F },{ 'g', KEY_G },{ 'h', KEY_H },
    { 'i', KEY_I },{ 'j', KEY_J },{ 'k', KEY_K },{ 'l', KEY_L },
    { 'm', KEY_M },{ 'n', KEY_N },{ 'o', KEY_O },{ 'p', KEY_P },
    { 'q', KEY_Q },{ 'r', KEY_R },{ 's', KEY_S },{ 't', KEY_T },
    { 'u', KEY_U },{ 'v', KEY_V },{ 'w', KEY_W },{ 'x', KEY_X },
    { 'y', KEY_Y },{ 'z', KEY_Z },{ '1', KEY_1 },{ '2', KEY_2 },
    { '3', KEY_3 },{ '4', KEY_4 },{ '5', KEY_5 },{ '6', KEY_6 },
    { '7', KEY_7 },{ '8', KEY_8 },{ '9', KEY_9 },{ '0', KEY_0 },
});

void write_null_event(FILE * fout) {
    struct input_event null_press;
    null_press.type = 0;
    null_press.code = 0;
    null_press.value = 0;
    fwrite(&null_press, 24, 1, fout);
}

void write_press_key(FILE * fout, short key_code) {
    struct input_event inp_press;
    inp_press.type = EV_KEY;
    inp_press.code = key_code;
    inp_press.value = 1;
    fwrite(&inp_press, 24, 1, fout);
}

void write_release_key(FILE * fout, short key_code) {
    struct input_event inp_release;
    inp_release.type = EV_KEY;
    inp_release.code = key_code;
    inp_release.value = 0;
    fwrite(&inp_release, 24, 1, fout);
}

void write_weird_key(FILE *fout) {
    //(1627566407, 0, 784159, 0, 4, 4, 458756)
    struct input_event inp_release;
    inp_release.type = 4;
    inp_release.code = 4;
    inp_release.value = 458756;
    fwrite(&inp_release, 24, 1, fout);
}

void write_key(char letter) {
    short key_code = key_code_map[letter];
    FILE *fout = fopen("/dev/input/by-id/usb-DELL_Dell_USB_Wired_Entry_Keyboard-event-kbd", "w");
    write_weird_key(fout);
    write_press_key(fout, key_code);
    write_null_event(fout);
    usleep(500000);
    write_weird_key(fout);
    write_release_key(fout, key_code);
    write_null_event(fout);
    fclose(fout);
}

int main() {
    write_key('s');
    write_key('t');
    write_key('e');
    write_key('v');
    write_key('e');
    write_key('n');
}
