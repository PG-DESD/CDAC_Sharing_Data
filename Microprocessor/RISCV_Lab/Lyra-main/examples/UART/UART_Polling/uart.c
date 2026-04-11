#include <vega/hal.h>

#include <stdio.h>
#include <string.h>

int main()
{
    char buf[80];
    char rxdata;

    UART_Init(&huart0);

    while (1) {
        UART_Receive(&huart0, (char *)&rxdata, 1);
        
        sprintf(buf, "Received : %c \r\n", rxdata);

        UART_Transmit(&huart0, buf, strlen(buf));
    }
    
    return 0;
}

