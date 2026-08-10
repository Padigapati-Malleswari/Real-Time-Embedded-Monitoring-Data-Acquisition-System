/*
 * task.h
 *
 *  Created on: 26-Jul-2026
 *      Author: JAYASIMHA REDDY
 */

#ifndef SRC_TASK_H_
#define SRC_TASK_H_
void  schedule(void);
void Task1_ReadRTC_WriteLCD_1Sec(void);
void Task2_ReadLM35_WriteLCD_5Sec(void);
void Task3_WiFi_Tx(void);
void Task4_Check_InternetStatus(void);
void Task5_SWMS_Config(void);
void  GO_TO_config(void);


#endif /* SRC_TASK_H_ */
