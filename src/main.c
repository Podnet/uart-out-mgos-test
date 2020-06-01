#include "mgos.h"

int uart_no = 1;



/*! \mainpage UART OUT doc
 *
 * \section Documentation
 *
 * This a test app that sends data over UART port for ESP32.
 */




/**> function write to UART. */
void timer_cb(void *arg)
{
    // Repeating code goes here.
    if(mgos_uart_write_avail(uart_no)) {
        mgos_uart_write(uart_no, "Hello World\n", 12);
    }
    (void)arg;
}

/**> MongooseOS initialization function to setup UART. */
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
