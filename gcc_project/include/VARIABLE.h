/*===================================================================================

File Name:       VARIABLE.H

Description:    Variable file for  VSC-HVDC control
          		
Originator:    XIAN yuneng dianli

==========================================================================================================  */

#ifndef VARIABLE_H
#define VARIABLE_H
/*==========================================================================
1        状态字           Grid_State    
2	     故障字 	      Grid_Faults
3	     报警字	          Grid_Alarm
===========================================================================*/

//---------------------------------------------------------------------------

//===============================================================//
#include "Solar_F.h"

CLARKE clarke1 = CLARKE_DEFAULTS;     //三相并网电流CLARKE变换
CLARKE clarke2 = CLARKE_DEFAULTS;     //三相交流电压CLARKE变换
iCLARKE_F iclarke1;                   // 三相并网电流正序CLARKE反变换
park_PN park1 = park_PN_DEFAULTS;     // 1#桥电流双旋转变换
park_PN park_pll = park_PN_DEFAULTS;  // 锁相环双旋转变换
IPARK ipark1 = IPARK_DEFAULTS;        // 三相并网电流正序PARK反变换
RAMPGEN rg1 = RAMPGEN_DEFAULTS;
SVGENDQ svgen_dq1 = SVGENDQ_DEFAULTS; // SVPWM调制方式
INTEGRAL integral1 = INTEGRAL_DEFAULTS;

CNTL_PI_F pi1_id;                     // d轴电流内环调节器
CNTL_PI_F pi1_iq;                     // q轴电流内环调节器
CNTL_PI_F pi1_Vdc;                    // 电压外环调节器
CNTL_PI_F pi1_pll;                    // 锁相环调节器 

//Sys_State_Type sys_state;

//=====模拟量采样======//
float Ia_Sample;
float Ib_Sample;
float Ic_Sample; 
float Vab_Sample;
float Vbc_Sample;
float Vca_Sample; 
float Vdc_Sample;
float Vdc_Sample_mid;
float Vdc_Sample_init;
int Vdc_Sample_counter;

float Grid_Va_Instant;
float Grid_Vb_Instant;
float Grid_Vc_Instant;
float Grid_Act_Power;
float Grid_React_Power;
int Avg_PQ_i = 0;
float Avg_P_Temp;
float Avg_Q_Temp;


//=====通讯输入遥控及遥调量=====//
unsigned int LEVEL;
unsigned int Run_Mode;
float Grid_m;
float Id_ref;
float Iq_ref;
float Udc_ref;
unsigned int Start_CMD = 0;
//unsigned int RemoteOrLocal = 0;
unsigned int Stop_CMD;
unsigned int Reset_CMD; 
//==============================//

//=====通讯输出遥测及遥信量=====//
unsigned int Grid_Ia;
unsigned int Grid_Ib;
unsigned int Grid_Ic;
unsigned int Grid_Vab;
unsigned int Grid_Vbc;
unsigned int Grid_Vca;
unsigned int Udc;
unsigned int Grid_Freq = 0;
int Grid_Pac;
int Grid_Qac;
int Frq_i = 0;
float Frq_Avg_Tmp = 0;
float Frq_Avg = 0;


//==============================//

//=========程序中间变量=========//
float Id_ref_init;
float Iq_ref_init;
float Id_ref_step;
float Iq_ref_step;
float Udc_ref_init;
float Udc_ref_step;
float theta;
float theta_line;
float theta_park;

unsigned int Sys_Run;
unsigned int Reset_onetime_flag = 0;

//==============================// 

//==============================//

// AC电流环d轴PI 
float pi1_id_Kp = 0.15;//0.4489              
float pi1_id_Ki = 0.0164;//0.00308
// AC电流环q轴PI
float pi1_iq_Kp = 0.15;//0.4489
float pi1_iq_Ki = 0.0164;//0.00308
// 电压环PI
float pi1_Vdc_Kp = 0.5;//0.5
float pi1_Vdc_Ki= 0.0033;//0.003

float Delay_Second;

long Delay_Second_i;

int Delay_End;

//==============================//

struct Grid_State_Bits
{                                              
   unsigned int        STOP:1;                  //正常停机
   unsigned int        FAULT:1;                 //故障
   unsigned int        START:1;                 //启动中
   unsigned int		   RUN:1;                   //运行
   unsigned int        VOLTS_MODE:1;            //恒压模式
   unsigned int        CURRENT_MODE:1;          //恒流模式
   unsigned int        SVG_MODE:1;            //SVG模式
   unsigned int        LOCAL_CTR:1;            //远程控制
   unsigned int        REMOTE_CTR:1;           //本地控制
   unsigned int        Q_SVG:1;            //恒无功功率
   unsigned int        Pn_SVG:1;            //恒功率因数
   unsigned int        Auto_SVG:1;           //自动无功补偿
   unsigned int		   Reserved_1:4;		    //备用
};

union Grid_State 
{
   unsigned int              all;
   struct Grid_State_Bits  bit;
};  

struct Grid_Faults_Bits
 {                                              
   unsigned int        Ia_OVER:1;                 //a相过流
   unsigned int        Ib_OVER:1;                 //b相过流
   unsigned int        Ic_OVER:1;                 //c相过流
   unsigned int		   Idc_OVER:1;                //直流过流
   unsigned int		   Uab_OVER:1;                //Uab过压
   unsigned int        Ubc_OVER:1;                //Ubc过压
   unsigned int        Uca_OVER:1;                //Uca过压
   unsigned int        Udc_Up_OVER:1;             //直流上母线过压
   unsigned int        Udc_Down_OVER:1;           //直流下母线过压
   unsigned int        A_Driv:1;                 //A桥驱动故障
   unsigned int        B_Driv:1;                //B桥驱动故障
   unsigned int        C_Driv:1;               //C桥驱动故障
   unsigned int        CONTACT_Fault:1;          //接触器异常
   unsigned int		   Reserved_1:3;	          //备用1   	  	
};

union Grid_Faults
{
   unsigned int                 all;
   struct Grid_Faults_Bits  bit;
};  
//Start Grid_S_Faults_1_Bits bit definitions:
struct Grid_S_Faults_1_Bits
 {                                              
   unsigned int        Ia:1;                  //a相过流
   unsigned int        Ib:1;                  //b相过流
   unsigned int        Ic:1;                  //c相过流
   unsigned int		   Idc1:1;                //直流输入过流
   unsigned int        solft_Fault:1;         //软启失败
   unsigned int        UNBALANCE_CURRENT:1;    //电流不平衡
   unsigned int        COM_Fault:1;            //通讯故障
   unsigned int        Heat_Fault:1;            //散热器故障
   unsigned int        Local_Emrgence:1;        //本地急停
   unsigned int		   Reserved_1:7;	        //备用1    	  	  	
};

union Grid_S_Faults_1
{
   unsigned int                 all;
   struct Grid_S_Faults_1_Bits  bit;
};  
//End Grid_S_Faults_1_Bits bit definitions.

//Start Grid_S_Faults_2_Bits bit definitions:
struct Grid_S_Faults_2_Bits
 {                                              
   unsigned int        OVER_FRQ:1;              //电网电压过频
   unsigned int        UNDER_FRQ:1;             //电网电压欠频
   unsigned int        OVER_Uab:1;              //uab过压
   unsigned int		   OVER_Ubc:1;              //Ubc过压
   unsigned int		   OVER_Uca:1;				//Uca过压
   unsigned int		   UNDER_Uab:1;	            //Uab欠压
   unsigned int        UNDER_Ubc:1;             //Ubc欠压
   unsigned int		   UNDER_Uca:1;             //Uca欠压
   unsigned int		   UNBALANCE_Volt:1;		//交流电压不平衡
   unsigned int		   UNBALANCE_Udc:1;         //直流母线不平衡
   unsigned int		   UNDER_Udc:1;	            //Udc欠压
   unsigned int        OVER_Udc_UP:1;            //直流上母线过压
   unsigned int		   OVER_Udc_DOWN:1;	    //直流下母线过压
   unsigned int		   OVER_POWVER:1;	    //过载
   unsigned int		   Udc_Reverse:1;	        //直流接反 
   unsigned int		   PHASE:1;	        //电网相序错误
};

union Grid_S_Faults_2
{
   unsigned int                 all;
   struct Grid_S_Faults_2_Bits  bit;
};  

struct Grid_Alarm_Bits
 {                                              
   unsigned int        LOAD:1;                  //逆变器过载
   unsigned int		   Reserved_1:15;	        //备用1   	  	
};

union Grid_Alarm
{
   unsigned int            all;
   struct Grid_Alarm_Bits  bit;
};  

struct INV15_States 
{
   union Grid_State       grid_state;
   union Grid_Faults      grid_faults;                   
   union Grid_Alarm       grid_alarm; 
   union Grid_S_Faults_1  grid_s_fault1; 
   union Grid_S_Faults_2  grid_s_fault2; 
};

volatile struct INV15_States SYS_Info; //Info: Information

typedef enum _Sys_State
{
	State_Stopping = 10,                // 停机动作状态
	State_Stopped,                      // 正常停机刺?
	State_Starting,                     // 启动髯刺�
	State_Reset,                        // 复位状态
	State_SoloStage_Running,            // 行状态
	State_DualStage_Running,            // 双级运行状态
	State_Error,                        // 故障停机状态
	State_Standby,                      // 待机状态
    State_Running                       //正常运行状态
}Sys_State_Type;   

Sys_State_Type sys_state;

//=====================//

#endif 
//===========================================================================
// No more.
//===========================================================================
