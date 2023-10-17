/* FreeRTOS Libraries*/
#include "FreeRTOS.h"
#include "event_groups.h"
#include "queue.h"
#include "semphr.h"
#include "status.h"
#include "task.h"
#include "timers.h"

/* Component Libraries */
#include "comms_status.h"
#include "component_processor/component_processor.h"
#include "packet.h"
#include "packet_processor.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

TaskHandle_t handlePacketProcessor;
static xSemaphoreHandle packet_queue_mutex = 0;
static xSemaphoreHandle packet_processing_mutex = 0;
static QueueHandle_t packetQueue = NULL;

#define PACKET_PROCESSOR_PRIORITY (tskIDLE_PRIORITY)
#define PACKET_PROCESSOR_PERIOD_MS (10 / portTICK_PERIOD_MS)
#define PACKET_PROCESSOR_TASK_STACK_SIZE 256
#define PACKET_PROCESSOR_QUEUE_LENGTH (1)

void taskPacketProcessor(void *pvParameters) {
    (void)pvParameters;
    uint8_t packet[PACKET_BUFFER_SIZE];
    uint8_t tx_buffer[PACKET_BUFFER_SIZE];
    uint8_t tx_bytes_written = 0;
    status_t status = STATUS_SUCCESS;
    uint16_t first_row = 0;
    uint16_t last_row = 0;

    for (;;) {
        xQueueReceive(packetQueue, packet, portMAX_DELAY);
        /* packet has already been verified as part of comms
         * stack so it's considered safe to start processing
         */

        tx_bytes_written = 0;

        if (packet != NULL && xSemaphoreTake(packet_processing_mutex, PACKET_PROCESSOR_PERIOD_MS) != pdFAIL) {
            switch (packet[PACKET_BYTE_POS_TYPE]) {
                case PACKET_TYPE_READ_SINGLETON:
                    status = instance_read_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        0,
                        0,
                        tx_buffer,
                        PACKET_BUFFER_SIZE,
                        &tx_bytes_written
                    );
                    break;

                case PACKET_TYPE_READ_MULTI_ROW:
                    first_row = ((packet[PACKET_BYTE_POS_ROW_FIRST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_FIRST]);
                    last_row = ((packet[PACKET_BYTE_POS_ROW_LAST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_LAST]);

                    status = instance_read_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        first_row,
                        last_row,
                        tx_buffer,
                        PACKET_BUFFER_SIZE,
                        &tx_bytes_written
                    );
                    break;

                case PACKET_TYPE_READ_MULTI_ATTRIB:
                    status = instance_read_multiple_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE_LAST],
                        tx_buffer,
                        PACKET_BUFFER_SIZE,
                        &tx_bytes_written
                    );
                    break;

                case PACKET_TYPE_WRITE_SINGLETON:
                    status = instance_write_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        0,
                        0,
                        &packet[PACKET_BYTE_WRITE_SINGLETON_DATA],
                        packet[PACKET_BYTE_POS_LENGTH] - 2 /* instance and attr fields */
                    );
                    break;

                case PACKET_TYPE_WRITE_MULTI_ROW:
                    first_row = ((packet[PACKET_BYTE_POS_ROW_FIRST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_FIRST]);
                    last_row = ((packet[PACKET_BYTE_POS_ROW_LAST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_LAST]);

                    status = instance_write_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        first_row,
                        last_row,
                        &packet[PACKET_BYTE_WRITE_MULTI_ROW_DATA],
                        packet[PACKET_BYTE_POS_LENGTH] - 6 /* instance, attr and 4 row fields */
                    );
                    break;

                case PACKET_TYPE_EXECUTE:
                    status = instance_call_method(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_METHOD],
                        &packet[PACKET_BYTE_METHOD_DATA],
                        packet[PACKET_BYTE_POS_LENGTH] - 2 /* instance and method fields */
                    );
                    break;

                default:
                    break;
                    /* do nothing */
            }
        }

        comms_tx(status, tx_buffer, tx_bytes_written);

        xSemaphoreGive(packet_processing_mutex);
    }
}

void process_packet(uint8_t *packet) {
    if (xSemaphoreTake(packet_processing_mutex, PACKET_PROCESSOR_PERIOD_MS) != pdFAIL) {
        if (xSemaphoreTake(packet_queue_mutex, PACKET_PROCESSOR_PERIOD_MS) != pdFAIL) {
            xQueueSendToBack(packetQueue, packet, PACKET_PROCESSOR_PERIOD_MS);
        } else {
            /* Couldn't get semaphore for queue */
            DEV_ASSERT(0);
        }

        xSemaphoreGive(packet_queue_mutex);
    } else {
        /* Couldn't get semaphore for packet */
        DEV_ASSERT(0);
    }

    xSemaphoreGive(packet_processing_mutex);
}

void packet_processor_init() {
    /* Packet queue */
    packetQueue = xQueueCreate(PACKET_PROCESSOR_QUEUE_LENGTH, sizeof(uint8_t) * PACKET_BUFFER_SIZE);
    packet_queue_mutex = xSemaphoreCreateMutex();
    packet_processing_mutex = xSemaphoreCreateMutex();

    /* Tasks */
    xTaskCreate(
        taskPacketProcessor,
        "taskPacketProcessor",
        PACKET_PROCESSOR_TASK_STACK_SIZE,
        NULL,
        PACKET_PROCESSOR_PRIORITY,
        &handlePacketProcessor
    );
}
