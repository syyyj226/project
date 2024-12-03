#include <wiringPi.h>
#include <pthread.h>
#include <signal.h>

#include "header.h"
#include "GPIO.h"
#include "sensor.h"
#include "PWM.h"
#include "motor.h"

#define IDLE 0    // 대기 중
#define STOPPED 1 // 운행 중지
#define RUNNING 2 // 운행 중
#define ARRIVED 3 // 구역 도착

int main()
{
    // 시간 출력
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // 필요한 변수
    char buffer[20] = {0};
    char order[20] = {0};
    char workState;   // 프로그램 업무 상태
    int runState = 0; // 운행 상태
    int orderNum = 0; // 처리한 주문 개수

    // init motor and sensor
    initMotor();
    initSensor();

    while (1)
    {
        strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S", tm_info);
        printf("%s - 운행 준비 완료\n", buffer);

        // 업무 유지 물어보기
        printf("\n    운행 상태를 유지하시겠습니까?    \n");
        printf("            y / n            \n");

        // 유효한 입력을 받을 때까지 반복
        while (1)
        {
            scanf("%c", &workState);
            if (workState == 'y' || workState == 'n')
                break;
            else
                printf("잘못된 입력입니다. 다시 입력해주세요.\n(y / n): ");
        }

        // 업무 상태 처리
        if (workState == 'y')
            printf("\n\n");
        else if (workState == 'n')
            break;

        // 주문 입력 문구 출력
        printf("------------------------------\n");
        printf("  주문을 공백으로 구분해 입력해주세요  \n");
        printf(" 형식: (주문 항목1) (주문 항목2)... \n");
        printf("------------------------------\n");

        // 주문 입력 및 처리
        fgets(order, sizeof(order), stdin);
        getchar();

        for (int i = 0; *(order + i) != 0; i + 2)
        {
        }

        // case 나누어 주행

        // 주행 완료 후 다시 처음으로 돌아가기
        printf("%d 번째 주문 처리가 완료되었습니다.\n", ++order);
    }
    disableSensor();

    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S", tm_info);
    printf("%s - 금일 운행이 중단되었습니다.");

    return 0;
}
