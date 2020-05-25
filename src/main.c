#include "mgos.h"

int uart_no = 0;

static void timer_cb(void *arg)
{
    // Repeating code goes here.
    if(mgos_uart_write_avail(uart_no)) {
        mgos_uart_write(uart_no, "Hello World", 11);
    }
    (void)arg;
}

enum mgos_app_init_result mgos_app_init(void)
{
    LOG(LL_INFO, ("Preparing UART interface"));

    struct mgos_uart_config ucfg;
    mgos_uart_config_set_defaults(uart_no, &ucfg);

    ucfg.baud_rate = 9600;
    ucfg.rx_buf_size = 1500;
    ucfg.tx_buf_size = 1500;

    if (!mgos_uart_configure(uart_no, &ucfg))
    {
        LOG(LL_ERROR, ("Failed to configure UART%d", uart_no));
    }

    else {
        mgos_set_timer(1000 /* ms */, MGOS_TIMER_REPEAT, timer_cb, NULL);
        LOG(LL_INFO, ("Handler set for pushing data periodically via UART."));
    }
    return MGOS_APP_INIT_SUCCESS;
}
