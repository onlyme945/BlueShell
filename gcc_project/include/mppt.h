/* =================================================================================
File name:       MPPT.H  (IQ version)                  
                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2008		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/

typedef struct {  long  pv_v;  		/* 光伏阵列端电压  */
                  long  pv_v1;  		/* 光伏阵列前一时刻端电压  */
				  long  pv_i;			/* 光伏阵列输出电流  */
				  long  pv_i1;			//输出电流平均值，判断高于Voc
				  long  pv_p;			/* 当前时刻光伏阵列输出功率  */
				  long  pv_p1;			/* 前一时刻光伏阵列输出功率  */
				  _iq  deltu;         /* 电压调整方向  */
		 	 	  _iq  (*calc)();   	/* 指向MPPT算法的函数指针 */ 
				 } MPPT;	            

typedef MPPT *MPPT_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the MPPT object.
-----------------------------------------------------------------------------*/                     
#define MPPT_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0,\
						  0,\
						  0,\
              			  (_iq (*)(long))mppt_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in MPPT.C
------------------------------------------------------------------------------*/
_iq mppt_calc(MPPT_handle);
