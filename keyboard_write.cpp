#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>


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

void write_key(short key_code) {
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
    for(int i = 0; i < 10; ++i) {
        write_key(30);
    }
}
