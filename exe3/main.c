void process_task(void *p) {
    #define WINDOW_SIZE 5
    static int window[WINDOW_SIZE] = {0};

    static int idx = 0;

    // Soma corrente de todos os valores no buffer
    static int sum = 0;

    // Quantas amostras já recebemos (no início, menos de 5)
    static int samplesCount = 0;

    int data = 0;

    while (true) {
        if (xQueueReceive(xQueueData, &data, pdMS_TO_TICKS(100))) {
            
            sum -= window[idx];       
            sum += data;             
            window[idx] = data;     


            idx = (idx + 1) % WINDOW_SIZE;

 
            if (samplesCount < WINDOW_SIZE) {
                samplesCount++;
            }


            int filteredValue = sum / samplesCount;


            printf("%d \n", filteredValue);

            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}
