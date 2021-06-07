/* 
 * Copyright (C) 2021 Infineon Technologies AG.
 *
 * Licensed under the EVAL_XMC47_PREDMAIN_AA Evaluation Software License
 * Agreement V1.0 (the "License"); you may not use this file except in
 * compliance with the License.
 *
 * For receiving a copy of the License, please refer to:
 *
 * https://github.com/Infineon/pred-main-xmc4700-kit/LICENSE.txt
 *
 * Licensee acknowledges that the Licensed Items are provided by Licensor free
 * of charge. Accordingly, without prejudice to Section 9 of the License, the
 * Licensed Items provided by Licensor under this Agreement are provided "AS IS"
 * without any warranty or liability of any kind and Licensor hereby expressly
 * disclaims any warranties or representations, whether express, implied,
 * statutory or otherwise, including but not limited to warranties of
 * workmanship, merchantability, fitness for a particular purpose, defects in
 * the Licensed Items, or non-infringement of third parties' intellectual
 * property rights.
 *
 */

#include "dps368.h"

#include "cmsis_gcc.h"

/* Meaningful Default Configuration */
#define     IFX_DPS368_TEMPERATURE_OSR                  OSR_2
#define     IFX_DPS368_PRESSURE_OSR                     OSR_64
#define     IFX_DPS368_TEMPERATURE_MR                   TMP_MR_4
#define     IFX_DPS368_PRESSURE_MR                      PM_MR_8


static dps368_scaling_coeffs_e dps368_get_scaling_coef( dps368_osr_e osr )
{
	dps368_scaling_coeffs_e scaling_coeff;

	switch( osr )
	{
		case OSR_1:
			scaling_coeff = OSR_SF_1;
			break;
	  case OSR_2:
			scaling_coeff = OSR_SF_2;
			break;
	  case OSR_4:
			scaling_coeff = OSR_SF_4;
			break;
	  case OSR_8:
			scaling_coeff = OSR_SF_8;
			break;
	  case OSR_16:
			scaling_coeff = OSR_SF_16;
			break;
	  case OSR_32:
			scaling_coeff = OSR_SF_32;
			break;
	  case OSR_64:
			scaling_coeff = OSR_SF_64;
			break;
	  case OSR_128:
			scaling_coeff = OSR_SF_128;
			break;
	  default:
			 scaling_coeff = OSR_SF_1;
			 break;
	}

	return scaling_coeff;
}


static int dps368_read_calib_coeffs( DPS368_t *drv_state )
{
	int32_t ret;
	uint8_t read_buffer[IFX_DPS368_COEF_LEN] = { 0 };

	if( drv_state == NULL)
	{
		return -EINVAL;
	}

	ret = drv_state->io->read_block( drv_state->io->bus_context, (uint8_t)IFX_DPS368_COEF_REG_ADDR,
							 (uint8_t)IFX_DPS368_COEF_LEN, read_buffer );

	if( ret != IFX_DPS368_COEF_LEN )
	{
		return ret;
	}

	drv_state->calib_coeffs.C0 = ( read_buffer[0] << 4 ) + ( ( read_buffer[1] >> 4 ) & 0x0F );

	if( drv_state->calib_coeffs.C0 > POW_2_11_MINUS_1 )
	{
		drv_state->calib_coeffs.C0 = drv_state->calib_coeffs.C0 - POW_2_12;
	}

	drv_state->calib_coeffs.C1 = ( read_buffer[2] + ( ( read_buffer[1] & 0x0F ) << 8 ) );

	if( drv_state->calib_coeffs.C1 > POW_2_11_MINUS_1 )
	{
		drv_state->calib_coeffs.C1 = drv_state->calib_coeffs.C1 - POW_2_12;
	}

	drv_state->calib_coeffs.C00 = ( ( read_buffer[4] << 4 ) + ( read_buffer[3] << 12 ) ) + ( ( read_buffer[5] >> 4 ) & 0x0F );

	if( drv_state->calib_coeffs.C00 > POW_2_19_MINUS_1 )
	{
		drv_state->calib_coeffs.C00 = drv_state->calib_coeffs.C00 -POW_2_20;
	}

	drv_state->calib_coeffs.C10 = ( ( read_buffer[5] & 0x0F ) << 16 ) + read_buffer[7] + ( read_buffer[6] << 8 );

	if( drv_state->calib_coeffs.C10 > POW_2_19_MINUS_1 )
	{
		drv_state->calib_coeffs.C10 = drv_state->calib_coeffs.C10 - POW_2_20;
	}

	drv_state->calib_coeffs.C01 = ( read_buffer[9] + ( read_buffer[8] << 8 ) );

	if( drv_state->calib_coeffs.C01 > POW_2_15_MINUS_1 )
	{
		drv_state->calib_coeffs.C01 = drv_state->calib_coeffs.C01 - POW_2_16;
	}

	drv_state->calib_coeffs.C11 = ( read_buffer[11] + ( read_buffer[10] << 8 ) );

	if( drv_state->calib_coeffs.C11 > POW_2_15_MINUS_1 )
	{
		drv_state->calib_coeffs.C11 = drv_state->calib_coeffs.C11 - POW_2_16;
	}

	drv_state->calib_coeffs.C20 = ( read_buffer[13] + ( read_buffer[12] << 8 ) );

	if( drv_state->calib_coeffs.C20 > POW_2_15_MINUS_1 )
	{
		drv_state->calib_coeffs.C20 = drv_state->calib_coeffs.C20 - POW_2_16;
	}

	drv_state->calib_coeffs.C21 = ( read_buffer[15] + ( read_buffer[14] << 8 ) );

	if( drv_state->calib_coeffs.C21 > POW_2_15_MINUS_1 )
	{
		drv_state->calib_coeffs.C21 = drv_state->calib_coeffs.C21 - POW_2_16;
	}

	drv_state->calib_coeffs.C30 = ( read_buffer[17] + ( read_buffer[16] << 8 ) );

	if( drv_state->calib_coeffs.C30 > POW_2_15_MINUS_1 )
	{
		drv_state->calib_coeffs.C30 = drv_state->calib_coeffs.C30 - POW_2_16;
	}

	/* Lets see which temperature diode is used for calibration and update state accordingly */
	ret = drv_state->io->read_byte( drv_state->io->bus_context, IFX_DPS368_TMP_COEF_SRCE_REG_ADDR );

	if( ret < 0 )
	{
			return -EIO;
	}

	if( ( ret >> IFX_DPS368_TMP_COEF_SRCE_REG_POS_MASK ) & 1 )
	{
		drv_state->tmp_ext = TMP_EXT_MEMS;
	}
	else
	{
		drv_state->tmp_ext = TMP_EXT_ASIC;
	}

	return 0;
}


int dps368_is_prs_tmp_rdy( DPS368_t *drv_state )
{
	int32_t ret;
	if( drv_state == NULL )
	{
		return -EINVAL;
	}

	ret = drv_state->io->read_byte( drv_state->io->bus_context, IFX_DPS368_MEAS_CFG_REG_ADDR );

	if( ret < 0 )
	{
		return -EIO;
	}

	if(  ( ret & IFX_DPS368_MEAS_PRS_RDY_POS) && (ret & IFX_DPS368_MEAS_TMP_RDY_POS) )
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


int dps368_resume( DPS368_t *drv_state )
{
	int32_t ret;
	if( drv_state == NULL )
	{
		return -EINVAL;
	}

	ret = drv_state->io->write_byte( drv_state->io->bus_context,
									IFX_DPS368_MEAS_CFG_REG_ADDR,
									(uint8_t)DPS368_MODE_BACKGROUND_ALL );
	if( ret < 0 )
	{
		return -EIO;
	}

	drv_state->dev_mode = DPS368_MODE_BACKGROUND_ALL;

	return 0;
}


int dps368_standby( DPS368_t *drv_state )
{
	int32_t ret;
	if( drv_state == NULL )
	{
		return -EINVAL;
	}

	ret = drv_state->io->write_byte( drv_state->io->bus_context,
									IFX_DPS368_MEAS_CFG_REG_ADDR,
								   (uint8_t)DPS368_MODE_IDLE );
	if( ret < 0 )
	{
		return -EIO;
	}

	drv_state->dev_mode = DPS368_MODE_IDLE;

	return 0;
}


int dps368_config( DPS368_t *drv_state,
                            dps368_osr_e osr_temp,
                            dps368_tmp_rate_e mr_temp,
                            dps368_osr_e osr_press,
                            dps368_pm_rate_e mr_press,
                            dps368_temperature_src_e temp_src )
{

	int32_t ret;
	uint8_t config;

	if( drv_state == NULL )
	{
		return -EINVAL;
	}

	/* Configure temperature measurements first */
	/* Prepare a configuration word for TMP_CFG register */
	config = (uint8_t)temp_src;

	/* First Set the TMP_RATE[2:0] -> 6:4 */
	config |= ((uint8_t)mr_temp);

	/* Set the TMP_PRC[3:0] -> 2:0 */
	config |= ((uint8_t)osr_temp);

	ret = drv_state->io->write_byte( drv_state->io->bus_context,
									IFX_DPS368_TMP_CFG_REG_ADDR,
									config );
	if( ret < 0 )
	{
		return -EIO;
	}

	/* Prepare a configuration word for PRS_CFG register */
	/* First Set the PM_RATE[2:0] -> 6:4 */
	config = (uint8_t)( 0x00 ) | ( (uint8_t)mr_press );

	/* Set the PM_PRC[3:0] -> 3:0 */
	config |= ((uint8_t)osr_press);

	ret = drv_state->io->write_byte( drv_state->io->bus_context,
									IFX_DPS368_PRS_CFG_REG_ADDR,
									config );
	if( ret < 0 )
	{
		return -EIO;
	}

	/* Always take configuration word from state */
	config = drv_state->cfg_word;

	/* If over sampling rate for temperature is greater than 8 times, then set TMP_SHIFT bit in CFG_REG */
	if( (uint8_t)osr_temp > (uint8_t)OSR_8 )
	{
		config |= (uint8_t) IFX_DPS368_CFG_TMP_SHIFT_EN_SET_VAL;
	}

	/* If over sampling rate for pressure is greater than 8 times, then set P_SHIFT bit in CFG_REG */
	if( (uint8_t)osr_press > (uint8_t) OSR_8 )
	{
		config |= (uint8_t) IFX_DPS368_CFG_PRS_SHIFT_EN_SET_VAL;
	}


	/* Write CFG_REG */
	ret = drv_state->io->write_byte( drv_state->io->bus_context,
									 IFX_DPS368_CFG_REG_ADDR,
									 config );
	if( ret < 0 )
	{
		return -EIO;
	}

	/* Update state accordingly with proper scaling factors based on over sampling rates */
	drv_state->tmp_osr_scale_coeff = dps368_get_scaling_coef( osr_temp );

	drv_state->prs_osr_scale_coeff = dps368_get_scaling_coef( osr_press );

	drv_state->press_mr = mr_press;

	drv_state->temp_mr = mr_temp;

	drv_state->temp_osr = osr_temp;

	drv_state->press_osr = osr_press;

	drv_state->tmp_ext = temp_src;

	return 0;
}


int32_t DPS368_lGetProcessedData( DPS368_t *drv_state, float *pressure, float *temperature )
{
	int32_t ret;
	uint8_t read_buffer[IFX_DPS368_PSR_TMP_READ_LEN] = { 0 };

	float press_raw;
	float temp_raw;

	float temp_scaled;
	float temp_final;
	float press_scaled;
	float press_final;

	if( drv_state == NULL )
	{
		return -EINVAL;
	}

	ret = drv_state->io->read_block( drv_state->io->bus_context,
						  IFX_DPS368_PSR_TMP_READ_REG_ADDR,
						  IFX_DPS368_PSR_TMP_READ_LEN,
						  read_buffer );

	if( ret < IFX_DPS368_PSR_TMP_READ_LEN )
	{
		return -EINVAL;
	}

	press_raw = ( read_buffer[2] ) + ( read_buffer[1] << 8 ) + ( read_buffer[0] << 16 );
	temp_raw  = ( read_buffer[5] ) + ( read_buffer[4] << 8 ) + ( read_buffer[3] << 16 );

	if( temp_raw > POW_2_23_MINUS_1 )
	{
		temp_raw = temp_raw - POW_2_24;
	}

	if( press_raw > POW_2_23_MINUS_1 )
	{
		press_raw = press_raw - POW_2_24;
	}

	temp_scaled = (float)temp_raw / (float)( drv_state->tmp_osr_scale_coeff );

	temp_final = ( drv_state->calib_coeffs.C0 / 2.0f ) + drv_state->calib_coeffs.C1 * temp_scaled;

	press_scaled = (float)press_raw / drv_state->prs_osr_scale_coeff;

	press_final = drv_state->calib_coeffs.C00 +
				  press_scaled * ( drv_state->calib_coeffs.C10 + press_scaled *
				  ( drv_state->calib_coeffs.C20 + press_scaled * drv_state->calib_coeffs.C30 ) ) +
				  temp_scaled * drv_state->calib_coeffs.C01 +
				  temp_scaled * press_scaled * ( drv_state->calib_coeffs.C11 +
												  press_scaled * drv_state->calib_coeffs.C21 );

	/* To convert it into mBar */
	press_final = press_final * 0.01f;

	*temperature = temp_final;
	*pressure    = press_final;

	return 0;
}


int16_t dps368_init( DPS368_t *drv_state, dps368_bus_connection *io )
{
	int32_t ret = 0;

    while( 1 )
    {
        if( !drv_state )
        {
            ret = -EINVAL;
            break;
        }

        if( !io )
        {
            ret = -EINVAL;
            break;
        }

        drv_state->cfg_word = 0;
        drv_state->enable = 0;
       
        if( io->init )
        {
            ret = io->init( io->bus_context );
            if( ret < 0)
            {
            	break;
            }
        }

        /* First verify chip by reading product and revision ID */
        ret = io->read_byte( io->bus_context, IFX_DPS368_PROD_REV_ID_REG_ADDR );
        if( ret < 0 )
        {
            ret = -EIO;
            break;
        }

        if( ret != IFX_DPS368_PROD_REV_ID_VAL )
        {
            ret = -EINVAL;
			break;
        }

        io->delayms( 40 );

        /* Attach bus connection instance to state */
        drv_state->io = io;

        /* From here wait for about 40ms till calibration coefficients become available */
        if( drv_state->io->delayms != NULL )
        {
        	drv_state->io->delayms( 40 );
        }

        /* Read now the calibration coefficients, temperature coefficient source and store in driver state */
        ret = dps368_read_calib_coeffs( drv_state );
        if( ret < 0 )
        {
        	break;
        }

        /* Now apply ADC Temperature gain settings */
        /* First write valid signature on 0x0e and 0x0f
         * to unlock address 0x62 */

        ret = drv_state->io->write_byte( drv_state->io->bus_context, (uint8_t)0x0e, (uint8_t)0xa5 );
        if( ret < 0 )
        {
        	break;
        }

        ret = drv_state->io->write_byte( drv_state->io->bus_context, (uint8_t)0x0f, (uint8_t)0x96 );
        if( ret < 0 )
        {
        	break;
        }

        /* Then update high gain value for Temperature */
        ret = drv_state->io->write_byte( drv_state->io->bus_context, (uint8_t)0x62, (uint8_t)0x02 );
        if( ret < 0 )
        {
        	break;
        }

        /* Finally lock back the location 0x62 */
        ret = drv_state->io->write_byte( drv_state->io->bus_context, (uint8_t)0x0e, (uint8_t)0x00 );
        if( ret < 0 )
        {
        	break;
        }

        ret = drv_state->io->write_byte( drv_state->io->bus_context, (uint8_t)0x0f, (uint8_t)0x00 );
        if( ret < 0 )
        {
        	break;
        }

        /* Configure sensor for default ODR settings */
        ret = dps368_config( drv_state,
                            IFX_DPS368_TEMPERATURE_OSR,
                            IFX_DPS368_TEMPERATURE_MR,
                            IFX_DPS368_PRESSURE_OSR,
                            IFX_DPS368_PRESSURE_MR,
                            drv_state->tmp_ext );
        if( ret < 0 )
        {
        	break;
        }

        /* Activate sensor */
        ret = dps368_resume( drv_state );
        if( ret < 0 )
        {
        	break;
        }

        ret = 0;
        break;

    } /* while */

    return ret;
}
