#include <vega/hal.h>

#include <stdio.h>
#include <string.h>

char buf[80] = {0};

int main()
{
    UART_Init(&huart0);
    
    while (1) {
        UART_Receive_IT(&huart0, buf, 5);
    }
    
    return 0;
}

void UART_RxCpltCallback(UART_Handle_t *huart)
{
    char msg[100];
    sprintf(msg, "\r\nReceived : %s",buf);
    UART_Transmit(&huart0, msg, strlen(msg));
}
