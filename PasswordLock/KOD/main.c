#include <16F877.h>
#include <stdio.h>
#fuses xt,nowdt
#use delay(clock=4MHz)

// Define bit addresses for LEDs, LCD, and other components
#bit led = 0x05.0
#bit TRIS_led = 0x85.0
#byte lcd = 0x06
#byte TRIS_lcd = 0x86
#bit rs = 0x07.0
#bit TRIS_rs = 0x87.0
#bit en = 0x07.1
#bit TRIS_en = 0x87.1
#bit relay = 0x07.2
#bit TRIS_relay = 0x87.2
#bit C1 = 0x08.0
#bit C2 = 0x08.1
#bit C3 = 0x08.2
#bit R1 = 0x08.3
#bit R2 = 0x08.4
#bit R3 = 0x08.5
#bit R4 = 0x08.6
#bit TRIS_C1 = 0x88.0
#bit TRIS_C2 = 0x88.1
#bit TRIS_C3 = 0x88.2
#bit TRIS_R1 = 0x88.3
#bit TRIS_R2 = 0x88.4
#bit TRIS_R3 = 0x88.5
#bit TRIS_R4 = 0x88.6

// Function prototypes
void display(unsigned char a, int b);  // LCD subroutine
void debounce(); 
char keypad();                         // Keypad subroutine
void check();                          // Password check routine

// Predefined password
char password[5] = "0000";
char pswd[5];
unsigned char open_msg[15] = "Enter Password";
unsigned char welcome_msg[8] = "Welcome";
unsigned char close_msg[15] = "Wrong Password";
char c;
int flag, i, count, j;

void main() {
    // Set directions of the ports
    TRIS_lcd = 0;
    TRIS_en = 0;
    TRIS_rs = 0;
    TRIS_led = 0;
    TRIS_relay = 0;
    TRIS_R1 = 0;
    TRIS_R2 = 0;
    TRIS_R3 = 0;
    TRIS_R4 = 0;
    TRIS_C1 = 1;
    TRIS_C2 = 1;
    TRIS_C3 = 1;

    count = 0;
    flag = 0;

    while(TRUE) {
        c = keypad();
        if (c == '*') {  // Initialize condition
            flag = 1;  // Flag set to scan other keys
            count = 0;
            display(0x01, 0);
            display(0x38, 0);
            display(0x0f, 0);
            display(0x80, 0);
            for (i = 0; i <= 13; i++) {
                display(open_msg[i], 1);
            }
            display(0xc0, 0);
        } else if (c == '#') {  // Turning off condition
            count = 0;
            relay = 0;
            display(0x01, 0);
            display(0x0c, 0);
        } else {
            display('*', 1);
            pswd[count] = c;  // Storing input in new arrays
            count++;
            if (count > 3) {
                check();
            }
        }
    }
}

void display(unsigned char a, int b) {
    lcd = a;
    rs = b;
    en = 1;
    delay_ms(10);
    en = 0;
    delay_ms(10);
}

char keypad() {
    if (flag == 0) {  // Waiting for Initialization
        while(TRUE) {
            R4 = 1;
            R1 = R2 = R3 = 0;
            if (C1 == 1) {
                debounce();
                if (C1 == 1) {
                    while (C1 == 1);  // Wait for the key to be released
                    count = 0;
                    return '*';
                }
            }
            if (C3 == 1) {
                debounce();
                if (C3 == 1) {
                    while (C3 == 1);  // Wait for the key to be released
                    count = 0;
                    return '#';
                }
            }
        }
    } else if (flag == 1) {
        while(TRUE) {  // Keypad scan
            // Check row 1
            R1 = 1;
            R2 = R3 = R4 = 0;
            if (C1 == 1) {
                debounce();
                if (C1 == 1) {
                    while (C1 == 1);  // Wait for the key to be released
                    return '1';
                }
            }
            if (C2 == 1) {
                debounce();
                if (C2 == 1) {
                    while (C2 == 1);  // Wait for the key to be released
                    return '2';
                }
            }
            if (C3 == 1) {
                debounce();
                if (C3 == 1) {
                    while (C3 == 1);  // Wait for the key to be released
                    return '3';
                }
            }

            // Check row 2
            R2 = 1;
            R1 = R3 = R4 = 0;
            if (C1 == 1) {
                debounce();
                if (C1 == 1) {
                    while (C1 == 1);  // Wait for the key to be released
                    return '4';
                }
            }
            if (C2 == 1) {
                debounce();
                if (C2 == 1) {
                    while (C2 == 1);  // Wait for the key to be released
                    return '5';
                }
            }
            if (C3 == 1) {
                debounce();
                if (C3 == 1) {
                    while (C3 == 1);  // Wait for the key to be released
                    return '6';
                }
            }

            // Check row 3
            R3 = 1;
            R1 = R2 = R4 = 0;
            if (C1 == 1) {
                debounce();
                if (C1 == 1) {
                    while (C1 == 1);  // Wait for the key to be released
                    return '7';
                }
            }
            if (C2 == 1) {
                debounce();
                if (C2 == 1) {
                    while (C2 == 1);  // Wait for the key to be released
                    return '8';
                }
            }
            if (C3 == 1) {
                debounce();
                if (C3 == 1) {
                    while (C3 == 1);  // Wait for the key to be released
                    return '9';
                }
            }

            // Check row 4
            R4 = 1;
            R1 = R2 = R3 = 0;
            if (C1 == 1) {
                debounce();
                if (C1 == 1) {
                    while (C1 == 1);  // Wait for the key to be released
                    return '*';
                }
            }
            if (C2 == 1) {
                debounce();
                if (C2 == 1) {
                    while (C2 == 1);  // Wait for the key to be released
                    return '0';
                }
            }
            if (C3 == 1) {
                debounce();
                if (C3 == 1) {
                    while (C3 == 1);  // Wait for the key to be released
                    return '#';
                }
            }
        }
    }
    return '\0';  // Default return to avoid warning
}

void debounce() {
    delay_ms(50);  // Simple debounce delay, adjust as needed
}

void check() {
    flag = count = 0;
    j = strcmp(pswd, password);  // Comparison of input and predefined password
    if (j == 0) {
        //output_c(0b00000100);
       // relay = 1;  // Turning relay on
        display(0x01, 0);
        display(0x80, 0);
        for (i = 0; i <= 6; i++) {
            display(welcome_msg[i], 1);
            
        }
    } else {
        relay = 0;
        display(0x01, 0);
        display(0x80, 0);
        for (i = 0; i <= 13; i++) {
            display(close_msg[i], 1);
        }
    }
}

