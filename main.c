#include <stdio.h>
#include <stdint.h>

#define testVectorLength    8

uint8_t testVector[8] = {1, 2, 3, 4, 5, 6, 7, 8};

typedef void (*FsequenceCheckFunction)(uint8_t);

typedef struct {
    uint8_t errorCount;
    FsequenceCheckFunction checkSequenceFunction;
}SEQUENCE_COUNTER_CHECK_t;

SEQUENCE_COUNTER_CHECK_t t_sequence_check;
SEQUENCE_COUNTER_CHECK_t *sequence_check_struct = &t_sequence_check;

void checkSequence(uint8_t testNumber) {
    static uint8_t prevNumber = 0;
    uint8_t currentNumber = testNumber;
    printf("current Number: %d\r\n", currentNumber);
    printf("Previous Number: %d\r\n", prevNumber);
    int8_t diff = currentNumber - prevNumber;
    printf("diff: %d\r\n", diff);

    prevNumber = currentNumber;
    printf("---------------------------\r\n");
}

void structInit(void) {
    sequence_check_struct->errorCount = 0;
    sequence_check_struct->checkSequenceFunction = &checkSequence;
}

int main() {
    structInit();


    for(int i = 0 ; i < testVectorLength ; i++) {
        sequence_check_struct->checkSequenceFunction(testVector[i]);
    }
}
