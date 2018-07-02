/**
******************************************************************************
* @file    			main.c
* @author  			WIZnet Software Team
* @version 			V1.0
* @date    			2015-02-14
* @brief   			用3.5.0版本库建的工程模板
* @attention  	实验平台：野火 iSO-MINI STM32 开发板 + 野火W5500网络适配板
*
*               默认使用野火开发板的SPI1接口，请断开“J10”A4与cs间的短接帽
*							
*               内网测试，请保证W5500的IP与测试PC机在同一网段内，且不冲突
*               如果是用网线跟PC机直连，请设置PC机本地连接地址IP为静态IP

*               测试本程序，请将w5500_conf.c文件中的local_port定义为测试
*               使用的监听端口,默认为5000
* 
* 实验平台:野火 iSO-MINI STM32 开发板 
* 论坛    :http://www.chuxue123.com
* 淘宝    :http://firestm32.taobao.com
******************************************************************************
*/ 
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "bsp_usart1.h"

#include "w5500.h"
#include "W5500_conf.h"
#include "socket.h"
#include "utility.h"
/*app函数头文件*/
#include "tcp_demo.h"
#include "dns.h"
#include "smtp.h"
//http webserver
#include "httputil.h"
#include "webpge.h"
#include "utility.h"
//ntp
#include "ntp.h"


uint8 reboot_flag = 0;

int main(void)
{ 	  
    systick_init(72);				            /*初始化Systick工作时钟*/
    USART2_Config(); 				            /*初始化串口通信:115200@8-n-1*/

    printf(" 野火网络适配版 TCP Server demo V1.0 \r\n");

    gpio_for_w5500_config();	         	/*初始化MCU相关引脚*/
    reset_w5500();					            /*硬复位W5500*/
    set_w5500_mac();                    /*配置MAC地址*/
    set_w5500_ip();                     /*配置IP地址*/

    socket_buf_init(txsize, rxsize);    /*初始化8个Socket的发送接收缓存大小*/

    printf(" 野火网络适配版作为TCP 服务器，建立侦听，等待PC作为TCP Client建立连接 \r\n");
    printf(" W5500监听端口为： %d \r\n",local_port);
    printf(" 连接成功后，TCP Client发送数据给W5500，W5500将返回对应数据 \r\n");

    ntp_client_init();                  /*NTP初始化*/
    while(1)                            /*循环执行的函数*/ 
    {
//       do_tcp_server();                  /*TCP_Client 数据回环测试程序*/
//       do_tcp_client();
        
//        do_udp();   //udp测试
//        do_dhcp();
//        do_dns();   delay_ms(1000); /*域名解析测试程序*/      
//        do_https(); if(reboot_flag==1)  reboot();   /*Web server测试程序*/
        do_ntp_client();    /* NTP测试程序 */
    }
}
