#include "hmc5883.h"
#include "math.h"


HAL_StatusTypeDef HMC5883_Init(CLASS_HMC5883L *hmc)

{
    hmc ->Init.configA[0] = REG_A; // передача адресса регистра A
    hmc->Init.configB[0] = REG_B; // передача адресса регистра B
    hmc->Init.configMode[0] = MODE_REG; // передача адресса регистра Mode
    hmc -> Init.regA = hmc->Init.data_rate | hmc->Init.mode_averaging | hmc->Init.measurment;
    hmc->Init.regB = hmc->Init.range;
    hmc->Init.Mode_Reg = hmc->Init.registr | hmc->Init.Speed;
    hmc->Init.configA[1] = hmc->Init.regA;
    hmc->Init.configB[1] = hmc->Init.regB;
    hmc->Init.configMode[1] = hmc->Init.Mode_Reg;
    HAL_I2C_Master_Transmit(hmc->Init.hi2c, hmc->Init.I2c_address_hmc, hmc->Init.configA, 2, HAL_MAX_DELAY); // отправка данных регистра A
    HAL_I2C_Master_Transmit(hmc->Init.hi2c, hmc->Init.I2c_address_hmc, hmc->Init.configB, 2, HAL_MAX_DELAY); // отправка данных регистра B
    HAL_I2C_Master_Transmit(hmc->Init.hi2c, hmc->Init.I2c_address_hmc, hmc->Init.configMode, 2, HAL_MAX_DELAY); // отправка данных регистра Mode

    return HAL_OK;
}

HAL_StatusTypeDef HMC5883_Task(CLASS_HMC5883L *hmc)
{
    hmc->Values.regAddr = X_MSB;

    if (HAL_I2C_Master_Transmit(hmc->Init.hi2c, hmc->Init.I2c_address_hmc, &hmc->Values.regAddr, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        return HAL_ERROR;
    }
    if (HAL_I2C_Master_Receive(hmc->Init.hi2c, hmc->Init.I2c_address_hmc, hmc->Values.buffer, 6, HAL_MAX_DELAY) != HAL_OK)
    {
        return HAL_ERROR;
    }
    hmc->Values.x = (int16_t)(hmc->Values.buffer[0] << 8 | hmc->Values.buffer[1]); // объединение старших и младших битов оси X
    hmc->Values.z = (int16_t)(hmc->Values.buffer[2] << 8 | hmc->Values.buffer[3]); // объединение старших и младших битов оси Z
    hmc->Values.y = (int16_t)(hmc->Values.buffer[4] << 8 | hmc->Values.buffer[5]); // объединение старших и младших битов оси Y

if(hmc->Init.range == HMC5883L_RANGE_0_88GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_0_88GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_0_88GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_0_88GA;
}
else if(hmc->Init.range == HMC5883L_RANGE_1_3GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_1_3GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_1_3GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_1_3GA;
}
else if(hmc->Init.range == HMC5883L_RANGE_1_9GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_1_9GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_1_9GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_1_9GA;
}
else if(hmc->Init.range == HMC5883L_RANGE_2_5GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_2_5GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_2_5GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_2_5GA;
}
else if(hmc->Init.range == HMC5883L_RANGE_4GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_4GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_4GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_4GA;
}
else if(hmc->Init.range == HMC5883L_RANGE_4_7GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_4_7GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_4_7GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_4_7GA;
}
else if(hmc->Init.range == HMC5883L_RANGE_5_6GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_5_6GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_5_6GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_5_6GA;
}
else if(hmc->Init.range == HMC5883L_RANGE_8_1GA)
{
    hmc -> Values.normal_x = (float)hmc->Values.x * MILLIGAUSS_8_1GA;
    hmc -> Values.normal_y = (float)hmc->Values.y * MILLIGAUSS_8_1GA;
    hmc -> Values.normal_z = (float)hmc->Values.z * MILLIGAUSS_8_1GA;
}
    hmc->Values.azimuth = atan2f((float)hmc->Values.y, (float)hmc->Values.x) * 180.0 / PI;
    if (hmc->Values.azimuth < 0) {
        hmc->Values.azimuth += 360.0;
    }

    return HAL_OK;
}
