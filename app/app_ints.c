/*Archivo con la funciones de interrupcion del micrcontroladores, revisar archivo startup_stm32g0b1.S */
#include "app_bsp.h"


void NMI_Handler( void )
{

}

void HardFault_Handler( void )
{
    assert_param( 0u );
}

void SVC_Handler( void )
{

}

void PendSV_Handler( void )
{

}

void SysTick_Handler( void )
{
    HAL_IncTick( );
}
