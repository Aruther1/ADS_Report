#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Enum to represent different moves
typedef enum {
ROCK,
PAPER,
SCISSORS
} Move
// Node structure for the linked list
typedef struct Node {
Move move;
struct Node* next;
} Node;
// Queue structure
typedef struct {
Node* front;
Node* rear;
} Queue;
// Function to initialize an empty queue
void initializeQueue(Queue* queue) {
queue->front = queue->rear = NULL
// Function to enqueue a move into the queue
void enqueue(Queue* queue, Move move) {
Node* newNode = (Node*)malloc(sizeof(Node));
if (newNode == NULL) {
fprintf(stderr, "Memory allocation error\n");
exit(EXIT_FAILURE);
}
newNode->move = move;
newNode->next = NULL;
if (queue->rear == NULL) {
queue->front = queue->rear = newNode;
6
} else {
queue->rear->next = newNode;
queue->rear = newNode;
}
}
// Function to dequeue a move from the queue
Move dequeue(Queue* queue) {
if (queue->front == NULL) {
fprintf(stderr, "Queue is empty\n");
exit(EXIT_FAILURE);
}
Node* temp = queue->front;
Move move = temp->move;
queue->front = temp->next;
free(temp);
if (queue->front == NULL) {
queue->rear = NULL;
}
return move;
}
// Function to determine the winner of the game
Move determineWinner(Move playerMove, Move computerMove) {
if (playerMove == computerMove) {
return ROCK; // Draw
}
if ((playerMove == ROCK && computerMove == SCISSORS) ||
(playerMove == PAPER && computerMove == ROCK) ||
(playerMove == SCISSORS && computerMove == PAPER)) {
return playerMove; // Player wins
}
return computerMove; // Computer wins
}
int main() {
srand(time(NULL));
Queue playerQueue;
7
Queue computerQueue;
initializeQueue(&playerQueue);
initializeQueue(&computerQueue);
// Generate random moves for the computer
for (int i = 0; i < 5; ++i) {
int randomMove = rand() % 3;
enqueue(&computerQueue, (Move)randomMove);
}
// Get moves from the player
printf("Enter your moves (0 for ROCK, 1 for PAPER, 2 for SCISSORS):\n");
for (int i = 0; i < 5; ++i) {
int playerMove;
scanf("%d", &playerMove);
enqueue(&playerQueue, (Move)playerMove);
}
// Play the game and display results
for (int i = 0; i < 5; ++i) {
Move playerMove = dequeue(&playerQueue);
Move computerMove = dequeue(&computerQueue);
printf("Round %d: ", i + 1);
printf("Player chooses %d, Computer chooses %d. ", playerMove, computerMove);
Move winner = determineWinner(playerMove, computerMove);
if (winner == ROCK) {
printf("It's a draw!\n");
} else if (winner == playerMove) {
printf("You win!\n");
} else {
printf("Computer wins!\n");
}
}
return 0;
}
