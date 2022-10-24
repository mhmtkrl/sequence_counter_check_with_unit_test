#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#define testVectorLength    13

uint8_t testVector[testVectorLength] = {3, 4, 4, 9, 5, 5, 7, 8, 9, 13, 14, 15, 0};

typedef struct {
    uint8_t repetation;
    uint8_t loss;
}ERROR_COUNT_t;

ERROR_COUNT_t globalEC = {0, 0};

typedef ERROR_COUNT_t (*FsequenceCheckFunction)(uint8_t);

typedef enum {
    REPETATION_OF_INFORMATION,
    LOSS_OF_INFORMATION,
    NO_ERROR
}COMMUNICATION_FAULTS_t;

typedef struct {
    ERROR_COUNT_t errorCount;
    FsequenceCheckFunction checkSequenceFunction;
    COMMUNICATION_FAULTS_t fault_type;
}SEQUENCE_COUNTER_CHECK_t;

SEQUENCE_COUNTER_CHECK_t t_sequence_check;
SEQUENCE_COUNTER_CHECK_t *sequence_check_struct = &t_sequence_check;

ERROR_COUNT_t checkSequence(uint8_t testNumber) {
    static ERROR_COUNT_t ec;
    static uint8_t prevNumber;
    static int8_t isFirstTime = 1;
    if(isFirstTime) {
        prevNumber = testNumber-1;
        isFirstTime = 0;
    }
    uint8_t currentNumber = testNumber;
    printf("current Number: %d\r\n", currentNumber);
    printf("Previous Number: %d\r\n", prevNumber);
    int8_t diff = currentNumber - prevNumber;
    printf("diff: %d\r\n", diff);


    if(diff != 1 || diff != -15) {
            if(currentNumber == prevNumber) {
                sequence_check_struct->errorCount.repetation++;
                sequence_check_struct->fault_type = REPETATION_OF_INFORMATION;
            }else {
                sequence_check_struct->errorCount.loss++;
                sequence_check_struct->fault_type = LOSS_OF_INFORMATION;
            }
    }else {
        sequence_check_struct->fault_type = NO_ERROR;
    }

    prevNumber = currentNumber;
    printf("---------------------------\r\n");
    ec.loss = sequence_check_struct->errorCount.loss;
    ec.repetation = sequence_check_struct->errorCount.repetation;

    return ec;
}

void structInit(void) {
    sequence_check_struct->errorCount.loss = 0;
    sequence_check_struct->errorCount.repetation = 0;
    sequence_check_struct->checkSequenceFunction = &checkSequence;
}

int main() {
    structInit();


    for(int i = 0 ; i < testVectorLength ; i++) {
        globalEC = sequence_check_struct->checkSequenceFunction(testVector[i]);
    }

    printf("done!");
}
