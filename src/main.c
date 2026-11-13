#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 17
#define MAX_READINGS 10
#define MIN_TEMP 68
#define MAX_TEMP 76

int main(void)
{
    double readings[MAX_READINGS];
    const char *statuses[MAX_READINGS];
    double temperature;
    double total = 0.0;
    int count = 0;
    int finished = 0;
    int result = 0;
    char input[100];
    char extra;
    FILE *logFile;

    if (gpioInitialise() < 0) 
    {
        printf("Could not start GPIO.\n");
        result = 1;
    } 
    else 
    {
        gpioSetMode(PIN, PI_OUTPUT);
        gpioWrite(PIN, 0);

        logFile = fopen("../data/classroom_temperature_log.txt", "w+");

        if (logFile == NULL) 
        {
            printf("Could not open classroom_temperature_log.txt.\n");
            result = 1;
        } 
        else 
        {
            fprintf(logFile, "\nClassroom Temperature Readings\n");

            while (count < MAX_READINGS && !finished) 
            {
                printf("Enter temperature %d in F, or q to finish:\n", count + 1);

                if (fgets(input, sizeof(input), stdin) == NULL || input[0] == 'q' || input[0] == 'Q') 
                {
                    finished = 1;
                } 
                else if (sscanf(input, "%lf %c", &temperature, &extra) == 1) 
                {
                    readings[count] = temperature;

                    if (temperature < MIN_TEMP || temperature > MAX_TEMP) 
                    {
                        statuses[count] = "WARNING";
                        gpioWrite(PIN, 1);
                    } 
                    else 
                    {
                        statuses[count] = "NORMAL";
                        gpioWrite(PIN, 0);
                    }

                    printf("Reading %d: %.1f F - %s\n", count + 1, temperature, statuses[count]);
                    
                    fprintf(logFile, "Reading %d: %.1f F - %s\n", count + 1, temperature, statuses[count]);

                    total += temperature;
                    count++;
                } 
                else 
                {
                    printf("Invalid reading. Enter a number like 72.5.\n");
                }
            }

            if (count > 0) 
            {
                printf("\nAll entered readings:\n");

                for (int i = 0; i < count; i++) 
                {
                    printf("Reading %d: %.1f F - %s\n",
                           i + 1, readings[i], statuses[i]);
                }

                printf("\nAverage: %.2f F\n\n", total / count);
                fprintf(logFile, "Average: %.2f F\n", total / count);
            } 
            else 
            {
                printf("No readings entered.\n");
                fprintf(logFile, "No readings entered.\n");
            }

            fclose(logFile);
            printf("Log saved to classroom_temperature_log.txt\n");

            if (count == MAX_READINGS) 
            {
                printf("10 readings complete. Press Enter to exit.\n");
                getchar();
            }
        }

        gpioWrite(PIN, 0);
        gpioTerminate();
    }

    return result;
}
