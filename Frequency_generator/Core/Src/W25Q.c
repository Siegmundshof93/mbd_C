/*#include "W25Q.h"
#include "Boot.h"

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart2;


uint8_t rx_buf[1025];
uint8_t tx_buf[10];

char str1[130];
unsigned int addr=0;

typedef struct
{
  uint16_t  PageSize;
  uint32_t  PageCount;
  uint32_t  SectorSize;
  uint32_t  SectorCount;
  uint32_t  BlockSize;
  uint32_t  BlockCount;
  uint32_t  NumKB;
  uint8_t   SR1;
  uint8_t   SR2;
  uint8_t   SR3;
  uint8_t   high_cap;
}w25_info_t;
w25_info_t  w25_info;


void SPI1_Send (uint8_t *dt, uint16_t cnt)
{
  HAL_SPI_Transmit (&hspi1, dt, cnt, 5000);

}
//-------------------------------------------------------------
void SPI1_Recv (uint8_t *dt, uint16_t cnt)
{
  HAL_SPI_Receive (&hspi1, dt, cnt, 5000);
}

void W25_Reset (void)
{
  cs_set();
  tx_buf[0] = W25_ENABLE_RESET;
  tx_buf[1] = W25_RESET;
  SPI1_Send(tx_buf, 2);
  cs_reset();
}

void W25_Read_Data(uint32_t addr, uint8_t* data, uint32_t sz)
{
  cs_set();
  tx_buf[0] = W25_READ;
  tx_buf[1] = (addr >> 16) & 0xFF;
  tx_buf[2] = (addr >> 8) & 0xFF;
  tx_buf[3] = addr & 0xFF;
  SPI1_Send(tx_buf, 4);
  SPI1_Recv(data, sz);
  cs_reset();
}

uint32_t W25_Read_ID(void)
{
  uint8_t dt[4];
  tx_buf[0] = W25_GET_JEDEC_ID;
  cs_set();
  SPI1_Send(tx_buf, 1);
  SPI1_Recv(dt,3);
  cs_reset();
  return (dt[0] << 16) | (dt[1] << 8) | dt[2];
}

//-------------------------------------------------------------
void W25_Read_Page(uint8_t* data, uint32_t page_addr, uint32_t offset, uint32_t sz)
{
	if(sz > w25_info.PageSize)
	      sz=w25_info.PageSize;
	  if((offset+sz) > w25_info.PageSize)
	      sz = w25_info.PageSize - offset;
	  page_addr = page_addr * w25_info.PageSize + offset;
	  tx_buf[0] = W25_FAST_READ;
	  if(w25_info.high_cap)
	    {
	      tx_buf[1] = (page_addr >> 24) & 0xFF;
	      tx_buf[2] = (page_addr >> 16) & 0xFF;
	      tx_buf[3] = (page_addr >> 8) & 0xFF;
	      tx_buf[4] = page_addr & 0xFF;
	      tx_buf[5] = 0;
	      cs_set();
	      SPI1_Send(tx_buf, 6);
	    }
	    else
	    {
	      tx_buf[1] = (page_addr >> 16) & 0xFF;
	      tx_buf[2] = (page_addr >> 8) & 0xFF;
	      tx_buf[3] = page_addr & 0xFF;
	      tx_buf[4] = 0;
	      cs_set();
	      SPI1_Send(tx_buf, 5);
	    }
	  	  SPI1_Recv(data, sz);
	   cs_reset();
}
//-------------------------------------------------------------
void Erase(void)
{
	uint8_t we = 0x06; //write enable
	uint8_t erase = 0xc7; //erase chip all memory to 0xFF
	cs_set();
	SPI1_Send(&we,1);
	cs_reset();

	cs_set();
	SPI1_Send(&erase,1);
	cs_reset();
}

void Write_Flash(uint8_t data, uint32_t page_addr)
{

	//uint32_t page_addr = 256;
	uint8_t Tx_Data[1];
	Tx_Data[0] = data;
	//sprintf(str1,"second byte = 0x%X \r\n",Tx_Data[1]);
	//HAL_UART_Transmit(&huart2, str1, strlen((char*)str1), HAL_MAX_DELAY);

	//sprintf(str1,"first byte = 0x%X \r\n",Tx_Data[0]);
	//HAL_UART_Transmit(&huart2, str1, strlen((char*)str1), HAL_MAX_DELAY);
	uint8_t WriteEnable = 0x06; //write enable
	tx_buf[0] = 0x02;
	tx_buf[1] = (page_addr >> 16) & 0xFF;
	tx_buf[2] = (page_addr >> 8) & 0xFF;
    tx_buf[3] = page_addr & 0xFF;
    //----------------------------------------
    cs_set();
    SPI1_Send(&WriteEnable, 1);
    cs_reset();

    cs_set();
    SPI1_Send(tx_buf,4);
    SPI1_Send(Tx_Data,1);
    cs_reset();

}

void Read_Flash(void)
{

	uint32_t page_addr = 0;
	tx_buf[0] = 0x03;
	tx_buf[1] = (page_addr >> 16) & 0xFF;
	tx_buf[2] = (page_addr >> 8) & 0xFF;
    tx_buf[3] = page_addr & 0xFF;
	cs_set();
	SPI1_Send(tx_buf, 4);
	SPI1_Recv(rx_buf, 5);
	cs_reset();
}

void W25_Ini(void)
{
  HAL_Delay(100);
  W25_Reset();
  HAL_Delay(100);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, 1);
}

void W25_Display (void)
{
	 unsigned int id = W25_Read_ID();
	  HAL_UART_Transmit(&huart2,(uint8_t*)"\r\n",2,0x1000);
	  // sprintf(str1,"ID:0x%X\r\n",id);
	  // HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	   id &= 0x0000ffff;
	   w25_info.high_cap = 0;
	   switch(id)
	     {
	       case 0x401A:
	    	   w25_info.high_cap=1;
	         w25_info.BlockCount=1024;
	         sprintf(str1,"w25qxx Chip: w25q512\r\n");
	         break;
	       case 0x4019:
	    	   w25_info.high_cap=1;
	         w25_info.BlockCount=512;
	         sprintf(str1,"w25qxx Chip: w25q256\r\n");
	         break;
	       case 0x4018:
	         w25_info.BlockCount=256;
	         sprintf(str1,"w25qxx Chip: w25q128\r\n");
	         break;
	       case 0x4017:
	         w25_info.BlockCount=128;
	         sprintf(str1,"w25qxx Chip: w25q64\r\n");
	         break;
	       case 0x4016:
	         w25_info.BlockCount=64;
	         sprintf(str1,"w25qxx Chip: w25q32\r\n");
	         break;
	       case 0x4015:
	         w25_info.BlockCount=32;
	         sprintf(str1,"w25qxx Chip: w25q16\r\n");
	         break;
	       case 0x4014:
	         w25_info.BlockCount=16;
	         sprintf(str1,"w25qxx Chip: w25q80\r\n");
	         break;
	       case 0x4013:
	         w25_info.BlockCount=8;
	         sprintf(str1,"w25qxx Chip: w25q40\r\n");
	         break;
	       case 0x4012:
	         w25_info.BlockCount=4;
	         sprintf(str1,"w25qxx Chip: w25q20\r\n");
	         break;
	       case 0x4011:
	         w25_info.BlockCount=2;
	         sprintf(str1,"w25qxx Chip: w25q10\r\n");
	         break;
	       default:
	         sprintf(str1,"w25qxx Unknown ID\r\n");
	         HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	         return;
	     }
	   //  HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	     w25_info.PageSize=256;
	     w25_info.SectorSize=0x1000;
	     w25_info.SectorCount=w25_info.BlockCount*16;
	     w25_info.PageCount=(w25_info.SectorCount*w25_info.SectorSize)/w25_info.PageSize;
	     w25_info.BlockSize=w25_info.SectorSize*16;
	     w25_info.NumKB=(w25_info.SectorCount*w25_info.SectorSize)/1024;
	     sprintf(str1,"Page Size: %d Bytes\r\n",(unsigned int)w25_info.PageSize);
	    // HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	     sprintf(str1,"Page Count: %u\r\n",(unsigned int)w25_info.PageCount);
	    // HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	     sprintf(str1,"Sector Size: %u Bytes\r\n",(unsigned int)w25_info.SectorSize);
	    // HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	     sprintf(str1,"Sector Count: %u\r\n",(unsigned int)w25_info.SectorCount);
	    // HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	     sprintf(str1,"Block Size: %u Bytes\r\n",(unsigned int)w25_info.BlockSize);
	   //  HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	     sprintf(str1,"Block Count: %u\r\n",(unsigned int)w25_info.BlockCount);
	  //   HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);
	     sprintf(str1,"Capacity: %u KB\r\n",(unsigned int)w25_info.NumKB);
	  //   HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),0x1000);

		 for(uint16_t k=0; k<1; k++) //k<4
		  {
		   // W25_Read_Data(k*256, rx_buf, 256);
			 W25_Read_Page(rx_buf, k, 0, 256); //256
		    for(uint8_t i=0; i<16; i++)
		    {
		      addr = k*256 + i*16;
		      sprintf(str1,"%08X: ", addr);
		      HAL_UART_Transmit(&huart2,(uint8_t*)str1,10,0x1000);
		      for(uint8_t j=0; j<16; j++)
		      {
		        sprintf(str1,"%02X", rx_buf[(uint16_t)i*16 + (uint16_t)j]);
		        HAL_UART_Transmit(&huart2,(uint8_t*)str1,2,0x1000);
		        if(j==7) HAL_UART_Transmit(&huart2,(uint8_t*)"|",1,0x1000);
		        else HAL_UART_Transmit(&huart2,(uint8_t*)" ",1,0x1000);
		      }
		      HAL_UART_Transmit(&huart2,(uint8_t*)"| ",1,0x1000);
		      for(uint8_t j=0; j<16; j++)
		      {
		        if ((rx_buf[(uint16_t)i*16 + (uint16_t)j] == 0x0A) ||
		            (rx_buf[(uint16_t)i*16 + (uint16_t)j] == 0x0D))  sprintf(str1," ");
		         else  sprintf(str1,"%c", (char) rx_buf[(uint16_t)i*16 + (uint16_t)j]);
		        HAL_UART_Transmit(&huart2,(uint8_t*)str1,1,0x1000);
		      }
		      HAL_UART_Transmit(&huart2,(uint8_t*)"\r\n",2,0x1000);
		    }
		    HAL_UART_Transmit(&huart2,(uint8_t*)"\r\n",2,0x1000);
		  }
}
*/
