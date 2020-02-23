#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*
 * Project name: Blackjack
 * Author: Yongqi Jia
 *
 * Implement simplified blackjack game version where a user can play
 * against the computer who acts as dealer.
 *
 */


/*
 * compare function is to determine who win
 *
 * return: 0
 */
int compare(int player, int dealer){
    if(player > dealer || dealer > 21){
        printf("You win!");
    }else if (player < dealer && dealer <= 21){
        printf("Dealer win.");
    }else if (player == dealer){
        printf("Push.");
    }
    return 0;
}

/*
 * printdealer function is to print the dealer cards in given format.
 *
 * return: the total points that dealer gets
 */
int printdealer(int dealer[], int temp){
    int ttemp = 0;
    int last = 0;
    for(int i = 0; i < 22; i++){
        if(dealer[i] != 0){
            ttemp += dealer[i];
        }
        if(dealer[i] == 0){
            last = dealer[i-1];
            break;
        }
    }
    printf("The dealer:\n");
    printf("%d + %d = %d\n\n", temp, last, ttemp);
    return ttemp;
}

 /*
  * showplayer function is to print the player cards in given format.
  *
  * return: the total points that player gets
  */
int showplayer(int player[], int temp){
    int ttemp = 0;
    int last = 0;
    for(int i = 0; i < 22; i++){
        if(player[i] != 0){
            ttemp += player[i];
        }
        if(player[i] == 0){
            last = player[i-1];
            break;
        }
    }
    printf("You:\n");
    printf("%d + %d = %d", temp, last, ttemp);
    return ttemp;
}

 /*
  * showdealer function is to print the dealer cards at beginning in given format.
  *
  * return: 0
  */
int showdealer(int dealer[]){
    printf("The dealer:\n");
    printf("? + %d\n\n", dealer[1]);
    return 0;
}

/*
 * calculate function is to handle the total points that whether player or dealer gets.
 *
 * return: total points
 */
int calculate(int player[]){
    int total = 0;
    for(int i = 0; i < 22; i++){
        total += player[i];
    }
    
    // deal with multi aces
    if(total > 21){
        int index = 0;
        while(index <= 21){
            if(player[index] == 11){
                player[index] = 1;
                total -= 10;
            }
            if(total <= 21){
                break;
            }else{
                index += 1;
            }
        }
    }
    return total;
}

/*
 * onecard function using rand() to get a card from 1 to 13
 *
 * return: int card
 */
int onecard(){
    int card = rand() % (13 - 1 + 1) + 1;
    if(card > 10){
        card = 10;
    }else if(card == 1){
        card = 11;
    }
    return card;
}

int main() {
    srand((unsigned int)time(NULL));
    int dealer[22];
    int player[22];
    for (int i = 0; i < 22; i++) {
        dealer[i] = 0;
        player[i] = 0;
    }

    // When game begin, give dealer and player two cards.
    dealer[0] = onecard();
    dealer[1] = onecard();
    player[0] = onecard();
    player[1] = onecard();
    
    int total = 0;
    int temp = player[0] + player[1];
    showdealer(dealer);
    printf("You:\n");
    printf("%d + %d = %d\n\n", player[0], player[1], temp);
    
    // Using while loop ensures that game plays round by round.
    while (1) {
        char op[5];
        int result1;
        int result2;
        printf("Would you like to “hit” or “stand”? ");
        scanf("%s", op);
        printf("\n");
        
        // check user input
        result1 = strcmp(op, "hit");
        result2 = strcmp(op, "stand");
        if(result1 == 0){
            for(int i = 0; i < 22; i++){
                if(player[i] == 0){
                    player[i] = onecard();
                    temp = calculate(player) - player[i];
                    break;
                }
            }
            total = calculate(player);
            showdealer(dealer);
            temp = showplayer(player, temp);
            if(total >= 21){
                printf(" BUSTED!\n\n");
                printf("You busted. Dealer wins.");
                return 0;
            }
            printf("\n\n");
        }
        if(result2 == 0){
            break;
        }
        if(result1 != 0 && result2 != 0){
            printf("This is not an options.\n");
        }
    }
    int dealer_total = 0;
    int dealer_temp = 0;
    printf("The dealer:\n");
    printf("%d + %d = %d\n\n", dealer[0], dealer[1], dealer[0] + dealer[1]);
    while(1){
        dealer_total = calculate(dealer);
        if(dealer_total >= 17){
            break;
        }
        for(int i = 0; i < 22; i++){
            if(dealer[i] == 0){
                dealer[i] = onecard();
                dealer_temp = calculate(dealer) - dealer[i];
                break;
            }
        }
        dealer_temp = printdealer(dealer, dealer_temp);
        
    }
    int player_final = calculate(player);
    int dealer_final = calculate(dealer);
    compare(player_final, dealer_final);
    return 0;
}


