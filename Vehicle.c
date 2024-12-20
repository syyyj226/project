#include "header.h"
#include "GPIO.h"
#include "sensor.h"
#include "PWM.h"
#include "motor.h"

int main()
{
    // 시간 출력
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // 필요한 변수
    char buffer[20] = {0};
    char order[5] = {0};
    char previous, now;       // 이전 목적지, 현재 목적지
    char workState;           // 프로그램 업무 상태
    int destination[3] = {0}; // 0: C, 1: B, 2: A
    int orderNum = 0;         // 처리한 주문 개수
    int err = 0;

    while (1)
    {
        strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S", tm_info);
        printf("%s - Vehicle is ready for operation \n", buffer);

        // 업무 유지 물어보기
        printf("Do you want to maintain the operational status? \n");
        printf("            y / n            \n");

        // 유효한 입력을 받을 때까지 반복
        while (1)
        {
            scanf("%c", &workState);
            getchar();
            if (workState == 'y' || workState == 'n')
                break;
            else
                printf("Invalid input: Enter again \n(y / n): ");
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
            printf("Enter the order without spaces\n");
            printf("------------------------------\n");

            // 주문 입력 및 처리
            fgets(order, sizeof(order), stdin);

            for (int i = 0; order[i] != '\n'; i++)
            {
                if (order[i] != 'A' && order[i] != 'B' && order[i] != 'C')
                {
                    printf("Invalid input: Enter again \n");
                    err = 1;
                    break;
                }
                else if (order[i] == 'A')
                    destination[2] = 1;
                else if (order[i] == 'B')
                    destination[1] = 1;
                else if (order[i] == 'C')
                    destination[0] = 1;
            }
            if (!err)
                break;
        }

        printf("%d %d %d\n", destination[0], destination[1], destination[2]);

        previous = 'N';
        now = 'N';
        // case 나누어 주행
        while (1)
        {
            // 현재 목적지, 다음 목적지 설정
            previous = now;
            now = 'N';
            for (int i = 0; i < 3; i++)
            {
                if (destination[i] == 1)
                {
                    if (i == 0)
                        now = 'C';
                    else if (i == 1)
                        now = 'B';
                    else if (i == 2)
                        now = 'A';

                    destination[i] = 0;
                    break;
                }
            }

            if (previous == 'N' && now != 'N')
                move(now);
            else if (previous != 'N' && now != 'N')
                moveTo(now);
            else if (previous != 'N' && now == 'N')
                moveRe();

            sleep(1);
            if (now == 'N')
                break;

            sleep(5);
        }

        // 주행 완료 후 돌아가기
        printf("%d: The order has been processed\n", ++orderNum);
    }

    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S", tm_info);
    printf("%s - The vehicle operation has ended for today\n", buffer);

    return 0;
}
