; ---------------------------------------------------------------------
; Boot Sector
; ---------------------------------------------------------------------
;
; When the computer is turned on, it starts executing a firmware
; pre-installed on the system board called BIOS (Basic Input/Output 
; System). The BIOS runs a "Power-On Self-Test" routine (POST) which 
; checks, identifies, and initializes the CPU, RAM, video display, 
; card, etc.
;
; Once all checks complete, the BIOS will go through each boot device
; (these devices and their priorities are usually configurable 
; through the BIOS menu) in an attempt to find the "boot loader" 
; software.
;
; In order to do so, the BIOS loads the first device's sector (the boot 
; sector) (Cylinder 0, Head 0, Sector 0), 512 bytes, into RAM. If the 
; read was successful, it checks the bytes 511 (offset 0x1FE) and 512 
; (offset 0x1FF) are 0x55 and 0xAA respectively. This is known as the 
; MBR signature. 
;
; If the BIOS recognised a valid boot loader software, it will transfer
; control by executing a jump instruction to the boot loader's first 
; byte in memory.
;
; The last 66 bytes of the 512-byte MBR are reserved for the  partition 
; table and other information, so the MBR boot sector program must be 
; small enough to fit within 446 bytes of memory or less. 

; Infinite loop (e9 fd ff)
loop:
    jmp loop 

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0

; Magic number
dw 0xaa55 