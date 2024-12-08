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
    char destination[5] = {0};
    char previous, now; // 이전 목적지, 현재 목적지
    int workState;      // 프로그램 업무 상태
    int orderNum = 0;   // 처리한 주문 개수
    int err = 0;

    // init motor and sensor
    initMotor();
    initSensor();

    while (1)
    {
        orderNum = 0;
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
        while (1)
        {
            err = 0;
            memset(order, 0, sizeof(order));
            memset(destination, 0, sizeof(destination));

            // 주문 입력 문구 출력
            printf("------------------------------\n");
            printf("  주문을 공백으로 구분해 입력해주세요  \n");
            printf(" 형식: (주문 항목1) (주문 항목2)... \n");
            printf("------------------------------\n");

            // 주문 입력 및 처리
            fgets(order, sizeof(order), stdin);
            order[strcspn(order, "\n")] = '\0';

            if (strlen(order) > 8)
            {
                printf("다시 입력하세요. \n");
                err = 1;
            }
            else if (!err)
            {
                for (int i = 0; i < sizeof(order); i++)
                {
                    if (i % 2 == 0 && (order + i) != 0 && (*(order + i) != 'A' || *(order + i) != 'B' || *(order + i) != 'C' || *(order + i) != 'D'))
                    {
                        printf("다시 입력하세요. \n");
                        err = 1;
                    }
                    if (i % 2 == 1 && *(order) + i != 0)
                    {
                        printf("다시 입력하세요. \n");
                        err = 1;
                    }
                }
            }
            else
            {
                for (int i = 0, int j = 0; i < sizeof(order); i + 2)
                {
                    if (*(order + i) == 'A')
                        destination[0] = 'A';
                    else if (*(order + i) == 'B')
                        destination[2] = 'B';
                    else if (*(order + i) == 'C')
                        destination[1] = 'C';
                    else if (*(order + i) == 'D')
                        destination[3] = 'D';
                }
            }
        }

        // case 나누어 주행
        do
        {
            for (int i = 0; i < 5; i++)
            {
                // 현재 목적지, 다음 목적지 설정
                previous = now;
                now = 0;
                if (*(destination + i) != 0)
                {
                    now = destination[i];
                    destination[i] = 0;
                }

                if (previous == 0 && now != 0)
                    move(now);
                else if (previous != 0 && now != 0)
                    moveTo(previous, now);
                else if (previous != 0 && now == 0)
                    returnOrigin(previous);

                sleep(5);
            }
        } while (now != 0);

        // 주행 완료 후 돌아가기
        printf("%d 번째 주문 처리가 완료되었습니다.\n", ++orderNum);
    }

    disableSensor();

    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S", tm_info);
    printf("%s - 금일 운행이 중단되었습니다.");

    return 0;
}
