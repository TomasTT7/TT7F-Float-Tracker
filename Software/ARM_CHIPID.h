/*

*/

#ifndef ARM_CHIPID_H
#define ARM_CHIPID_H

// Variables
extern uint8_t CHIPID_version;
extern uint8_t CHIPID_eproc;
extern uint8_t CHIPID_nvpsiz;
extern uint8_t CHIPID_nvpsiz2;
extern uint8_t CHIPID_sramsiz;
extern uint8_t CHIPID_arch;
extern uint8_t CHIPID_nvptyp;
extern uint8_t CHIPID_ext;
extern uint32_t CHIPID_exid;

// Functions
void CHIPID_read_EXID(void);
void CHIPID_read_CIDR(void);

#endif // ARM_CHIPID_H_