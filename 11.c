#include <stdio.h>

typedef enum {player1, player2} turn;

/* returns number of 1s in number */
int get_beauty(int n) {
    int count = 0;
    while (n) {
        count += n&0x1;
        n >>= 1;
    }
    return count;
}

turn switch_players(turn current_player) {
    return current_player == player1 ? player2 : player1;
}

int get_next_beautiful_number(int n) {
    int two_to_k = 1;

    while (two_to_k < n) {
        if (get_beauty(n-two_to_k) == get_beauty(n)) {
            return n-two_to_k;
        }
        two_to_k *= 2;
    }
    return -1;
}

void start_game(int n) {
    turn current_player = player1;

    while ((n = get_next_beautiful_number(n)) != -1) {
        printf("Player %d: %d\n", current_player == player1 ? 1 : 2, n);
        current_player = switch_players(current_player);
    }
    printf("The winner is.... %s!\n", current_player == player1 ? "player 1" : "player2");
}

int main() {
    int n;
    printf("Enter N value:\n");
    scanf("%d", &n);

    start_game(n);
    return 0;
}
