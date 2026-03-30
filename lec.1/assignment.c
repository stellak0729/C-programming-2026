#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PLAYER_COUNT 8
#define ROUND8_MATCHES 4
#define ROUND4_MATCHES 2

void flushInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void waitEnter(const char *message) {
    printf("\n%s", message);
    fflush(stdout);
    getchar();
}

int getWinnerRPS(int p1, int p2) {
    if (p1 == p2) return 0;

    if ((p1 == 1 && p2 == 3) ||
        (p1 == 2 && p2 == 1) ||
        (p1 == 3 && p2 == 2)) {
        return 1;
    }

    return 2;
}

const char* getChoiceName(int choice) {
    switch (choice) {
        case 1: return "가위";
        case 2: return "바위";
        case 3: return "보";
        default: return "알 수 없음";
    }
}

void shuffle(const char *arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        const char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

const char* autoMatch(const char *player1, const char *player2) {
    while (1) {
        int p1 = rand() % 3 + 1;
        int p2 = rand() % 3 + 1;
        int result = getWinnerRPS(p1, p2);

        if (result == 1) return player1;
        if (result == 2) return player2;
    }
}

const char* playUserMatch(const char *opponent, int *userLost) {
    while (1) {
        int userChoice, computerChoice, result;

        printf("가위(1), 바위(2), 보(3) 중 선택하세요 : ");

        if (scanf("%d", &userChoice) != 1) {
            printf("잘못된 입력입니다. 숫자 1, 2, 3 중 하나를 입력하세요.\n");
            flushInput();
            continue;
        }
        flushInput();

        if (userChoice < 1 || userChoice > 3) {
            printf("잘못된 입력입니다. 숫자 1, 2, 3 중 하나를 입력하세요.\n");
            continue;
        }

        computerChoice = rand() % 3 + 1;

        printf("\n가위! 바위! 보!\n");
        waitEnter("엔터를 누르면 경기 결과를 확인합니다...");

        printf("\n당신의 선택 : %s\n", getChoiceName(userChoice));
        printf("%s의 선택 : %s\n", opponent, getChoiceName(computerChoice));

        result = getWinnerRPS(userChoice, computerChoice);

        if (result == 0) {
            printf("비겼습니다! 재경기합니다.\n\n");
            continue;
        } else if (result == 1) {
            printf("이겼습니다!\n");
            *userLost = 0;
            return "1플레이어(당신)";
        } else {
            printf("졌습니다!\n");
            *userLost = 1;
            return opponent;
        }
    }
}

int main(void) {
    const char *userName = "1플레이어(당신)";
    srand((unsigned int)time(NULL));

    const char *others[7] = {
        "민지", "태양", "지수", "준호", "서연", "현우", "유나"
    };
    const char *players[PLAYER_COUNT];
    const char *winners8[ROUND8_MATCHES];
    const char *winners4[ROUND4_MATCHES];
    const char *finalWinner;
    int userLost = 0;

    shuffle(others, 7);

    players[0] = userName;
    players[1] = others[0];
    players[2] = others[1];
    players[3] = others[2];
    players[4] = others[3];
    players[5] = others[4];
    players[6] = others[5];
    players[7] = others[6];

    printf("=====================================\n");
    printf("      토너먼트 가위바위보 경기\n");
    printf("=====================================\n\n");

    printf("[8강 대진표]\n");
    printf("1경기 : %s vs %s\n", players[0], players[1]);
    printf("2경기 : %s vs %s\n", players[2], players[3]);
    printf("3경기 : %s vs %s\n", players[4], players[5]);
    printf("4경기 : %s vs %s\n", players[6], players[7]);

    printf("\n당신은 1플레이어입니다.\n");
    waitEnter("엔터를 누르면 8강 경기를 시작합니다...");

    printf("\n=====================================\n");
    printf("             8강 경기 시작\n");
    printf("=====================================\n");

    for (int i = 0; i < ROUND8_MATCHES; i++) {
        const char *p1 = players[i * 2];
        const char *p2 = players[i * 2 + 1];

        printf("\n-------------------------------------\n");
        printf("%d경기 : %s vs %s\n", i + 1, p1, p2);
        printf("-------------------------------------\n");

        if (i == 0) {
            winners8[i] = playUserMatch(p2, &userLost);

            if (userLost) {
                printf("\n아쉽게도 8강에서 탈락했습니다.\n");
                printf("게임을 종료합니다.\n");
                return 0;
            } else {
                printf("%s 4강 진출!\n", winners8[i]);
                waitEnter("엔터를 누르면 다른 경기 결과를 확인합니다...");
            }
        } else {
            winners8[i] = autoMatch(p1, p2);
            printf("%s 승! 4강 진출\n", winners8[i]);
        }
    }

    waitEnter("엔터를 누르면 4강 대진표를 확인합니다...");

    printf("\n=====================================\n");
    printf("             4강 대진표\n");
    printf("=====================================\n");
    printf("1경기 : %s vs %s\n", winners8[0], winners8[1]);
    printf("2경기 : %s vs %s\n", winners8[2], winners8[3]);

    waitEnter("엔터를 누르면 4강 경기를 시작합니다...");

    printf("\n=====================================\n");
    printf("             4강 경기 시작\n");
    printf("=====================================\n");

    for (int i = 0; i < ROUND4_MATCHES; i++) {
        const char *p1 = winners8[i * 2];
        const char *p2 = winners8[i * 2 + 1];

        printf("\n-------------------------------------\n");
        printf("%d경기 : %s vs %s\n", i + 1, p1, p2);
        printf("-------------------------------------\n");

        if (p1 == userName || p2 == userName) {
            const char *opponent = (p1 == userName) ? p2 : p1;
            winners4[i] = playUserMatch(opponent, &userLost);

            if (userLost) {
                printf("\n아쉽게도 4강에서 탈락했습니다.\n");
                printf("게임을 종료합니다.\n");
                return 0;
            } else {
                printf("%s 결승 진출!\n", winners4[i]);
                waitEnter("엔터를 누르면 다른 경기 결과를 확인합니다...");
            }
        } else {
            winners4[i] = autoMatch(p1, p2);
            printf("%s 승! 결승 진출\n", winners4[i]);
        }
    }

    waitEnter("엔터를 누르면 결승 대진표를 확인합니다...");

    printf("\n=====================================\n");
    printf("              결승 대진표\n");
    printf("=====================================\n");
    printf("%s vs %s\n", winners4[0], winners4[1]);

    waitEnter("엔터를 누르면 결승 경기를 시작합니다...");

    printf("\n=====================================\n");
    printf("              결승 경기 시작\n");
    printf("=====================================\n");

    printf("\n-------------------------------------\n");
    printf("결승전 : %s vs %s\n", winners4[0], winners4[1]);
    printf("-------------------------------------\n");

    if (winners4[0] == userName || winners4[1] == userName) {
        const char *opponent = (winners4[0] == userName) ? winners4[1] : winners4[0];
        finalWinner = playUserMatch(opponent, &userLost);

        if (userLost) {
            printf("\n아쉽게도 결승에서 패배했습니다.\n");
            printf("게임을 종료합니다.\n");
            return 0;
        } else {
            waitEnter("엔터를 누르면 최종 결과를 확인합니다...");
        }
    } else {
        finalWinner = autoMatch(winners4[0], winners4[1]);
        printf("%s 승! 우승\n", finalWinner);
    }

    printf("\n=====================================\n");
    printf("              최종 우승자\n");
    printf("=====================================\n");
    printf("%s\n", finalWinner);

    if (finalWinner == userName) {
        printf("\n축하합니다! 토너먼트 우승입니다!\n");
    } else {
        printf("\n아쉽지만 우승자는 %s 입니다.\n", finalWinner);
    }

    return 0;
}