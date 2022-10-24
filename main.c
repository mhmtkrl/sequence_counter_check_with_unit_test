#include <stdio.h>
#include <stdint.h>

uint8_t testVector[8] = {1, 2, 3, 4, 5, 6, 7, 8};

typedef void (*FsequenceCheckFunction)(uint8_t *);

typedef struct {
    uint8_t errorCount;
    FsequenceCheckFunction checkSequenceFunction;
}SEQUENCE_COUNTER_CHECK_t;

SEQUENCE_COUNTER_CHECK_t t_sequence_check;
SEQUENCE_COUNTER_CHECK_t *sequence_check_struct = &t_sequence_check;

void checkSequence(uint8_t *testVector) {

}

void structInit(void) {
    sequence_check_struct->errorCount = 0;
    sequence_check_struct->checkSequenceFunction = &checkSequence;
}

int main() {
    structInit();
    printf("Hi\r\n");
}
