#include "tmc_4671_driver.h"

void initTmc4671(uint8_t motor) {

    // === Motor Type & PWM Configuration ===
    tmc4671_setPolePairs(motor, 10);
    tmc4671_setMotorType(motor, TMC4671_THREE_PHASE_BLDC);
    tmc4671_setPWMPolarity(motor, 0, 0);                                   // Low polarity for both high and low sides
    tmc4671_setPWMFreq(motor, 50000);                                      // 50 kHz PWM frequency
    tmc4671_setPWMBBM(motor, 25, 25);                                      // Deadtime for high and low sides
    tmc4671_setPWMMode(motor, TMC4671_PWM_CENTRE, 1);                      // Center-aligned PWM with SVM enabled

    // === ADC Configuration ===
    tmc4671_writeInt(motor, TMC4671_ADC_I_SELECT, 0x06000100);             // ADC current selection
    tmc4671_writeInt(motor, TMC4671_dsADC_MCFG_B_MCFG_A, 0x00100010);      // ADC MCFG for channels A and B
    tmc4671_writeInt(motor, TMC4671_dsADC_MCLK_A, 0x60000000);             // ADC MCLK for channel A
    tmc4671_writeInt(motor, TMC4671_dsADC_MCLK_B, 0x60000000);             // ADC MCLK for channel B
    tmc4671_writeInt(motor, TMC4671_dsADC_MDEC_B_MDEC_A, 0x01F201F2);      // ADC MDEC for channels A and B
    tmc4671_writeInt(motor, TMC4671_ADC_I0_SCALE_OFFSET, 0x010080DA);      // ADC I0 scale and offset
    tmc4671_writeInt(motor, TMC4671_ADC_I1_SCALE_OFFSET, 0x01008092);      // ADC I1 scale and offset

    // === Digital Hall Settings ===
    tmc4671_writeInt(motor, TMC4671_HALL_MODE, 0x00000001);                 // Enable digital hall sensors
    tmc4671_writeInt(motor, TMC4671_HALL_PHI_E_PHI_M_OFFSET, 0x00000000);   // Reset Phi_E and Phi_M offsets

    // === Feedback Selection ===
    tmc4671_writeInt(motor, TMC4671_PHI_E_SELECTION, 0x00000005);           // Select Phi_E feedback source (e.g., digital hall)
    tmc4671_writeInt(motor, TMC4671_VELOCITY_SELECTION, 0x0000000C);        // Select velocity feedback source

    // === Limits Configuration ===
    tmc4671_writeInt(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, 0x000003E8);    // Set PID torque and flux limits (1000 in decimal)

    // === PI Controller Settings ===
    tmc4671_writeInt(motor, TMC4671_PID_TORQUE_P_TORQUE_I, 0x02000200);     // PI settings for torque (P=512, I=512)
    tmc4671_writeInt(motor, TMC4671_PID_FLUX_P_FLUX_I, 0x02000200);         // PI settings for flux (P=512, I=512)

}