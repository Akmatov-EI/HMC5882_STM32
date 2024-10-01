#ifndef hmc5883_H
#define hmc5883_H

#include "stm32f1xx_hal.h"
#include "stdlib.h"

// Адрес I2C для HMC5883
#define HMC5883_ADDRESS 0x1E << 1

// Регистры HMC5883
#define REG_A 0x00
#define REG_B 0x01
#define MODE_REG 0x02
#define X_MSB 0x03
#define X_LSB 0x04
#define Z_MSB 0x05
#define Z_LSB 0x06
#define Y_MSB 0x07
#define Y_LSB 0x08
#define STATUS_REG 0x09
#define IDENT_REG_A 0x0A
#define IDENT_REG_B 0x0B
#define IDENT_REG_C 0x0C
#define PI 3.141593
// Биты DO2, DO1, DO0: Настройка частоты данных
#define HMC5883L_DATARATE_0_75_HZ 0b00000000
#define HMC5883L_DATARATE_1_5HZparams 0b00000100
#define HMC5883L_DATARATE_75HZ 0b00011100
#define HMC5883L_DATARATE_30HZ 0b00010100
#define HMC5883L_DATARATE_15HZ 0b00010000
#define HMC5883L_DATARATE_7_5HZ 0b00001100
#define HMC5883L_DATARATE_3HZ 0b00001000

// Биты GN2, GN1, GN0: Настройка усиления
#define HMC5883L_RANGE_8_1GA 0b11100000
#define HMC5883L_RANGE_5_6GA 0b11000000
#define HMC5883L_RANGE_4_7GA 0b10100000
#define HMC5883L_RANGE_4GA 0b10000000
#define HMC5883L_RANGE_2_5GA 0b01100000
#define HMC5883L_RANGE_1_9GA 0b01000000
#define HMC5883L_RANGE_1_3GA 0b00100000
#define HMC5883L_RANGE_0_88GA 0b00000000

// Биты MS1, MS0: Режим измерения
#define HMC5883L_NEGATIV 0b00000010
#define HMC5883L_POSITIV 0b00000001
#define HMC5883L_DEFAULT 0b00000000

// Биты MA1, MA0: Настройка усреднения данных
#define HMC5883L_AVERAGING_8 0b01100000
#define HMC5883L_AVERAGING_4 0b01000000
#define HMC5883L_AVERAGING_2 0b00100000
#define HMC5883L_AVERAGING_1 0b00000000

// Биты MD1, MD0: Режим работы
#define HMC5883L_CONTINUOUS_MEASUREMENT 0b00000000
#define HMC5883L_SINGLE_MEASURMENT 0b00000001
#define HMC5883L_IDLE_MODE 0b00000010

// Бит HS: Режим скорости I2c
#define HMC5883L_SPEED_i2c_0 0b00000000
#define HMC5883L_SPEED_i2c_1 0b10000000

#define MILLIGAUSS_0_88GA 0.073f 
#define MILLIGAUSS_1_3GA 0.92f
#define MILLIGAUSS_1_9GA 1.22f
#define MILLIGAUSS_2_5GA 1.52f
#define MILLIGAUSS_4GA 2.27f
#define MILLIGAUSS_4_7GA 2.56f
#define MILLIGAUSS_5_6GA 3.03f
#define MILLIGAUSS_8_1GA 4.35f

typedef struct
{
    int I2c_address_hmc; // адресс I2c устройства
    I2C_HandleTypeDef *hi2c;
    uint8_t data_rate;     // Настройка частоты данных
    uint8_t mode_averaging;       // Настройка усреднения данных
    uint8_t measurment;    // Режим измерения
    uint8_t range;         // Настройка усиления
    uint8_t registr;       // Режим работы
    uint8_t Speed;         // Скорость I2c
    uint8_t regA;          // настройки для работы регистра A
    uint8_t regB;          // настройки для работы регистра B
    uint8_t Mode_Reg;      // настройки для работы регистра Mode
    uint8_t configA[2];    // буфер для битов регистра A
    uint8_t configB[2];    // буфер для битов регистра B
    uint8_t configMode[2]; // буфер для битов регистра Mode

} HMC5883L_Init_Reg;

typedef struct
{
    uint8_t buffer[6]; // буфер для чтения данных с осей X, Y, Z
    uint8_t regAddr;   // установка начального адреса регистра с которого будут считываться данные
    int16_t x;         // хранит в себе данные с оси X
    int16_t y;         // хранит в себе данные с оси Y
    int16_t z;         // хранит в себе данные с оси Z
    float normal_x;
    float normal_y;
    float normal_z;
    float azimuth;
} HMC5883L_ReadRaw;

typedef struct 
{
HMC5883L_Init_Reg Init;
HMC5883L_ReadRaw Values;
}CLASS_HMC5883L;


/// @brief функция для инициализации дачика HMC5883L
/// @param params указатель на структуру,в которой хранятся параметры функции для инициализации
HAL_StatusTypeDef HMC5883_Init(CLASS_HMC5883L *hmc);

/// @brief Эта функция HMC5883_ReadRaw используется для чтения сырых данных с датчика HMC5883L (магнитометр) по интерфейсу I2C. Результаты чтения сохраняются в структуре HMC5883L_ReadRaw.
/// @param Raw указатель на структуру, в которой хранятся переменные для хранения значений с датчика
HAL_StatusTypeDef HMC5883_Task(CLASS_HMC5883L *hmc);

#endif
