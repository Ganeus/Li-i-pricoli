#include <stdio.h>
#include <stdlib.h>

#define ROW 8
#define COL 8
#define INF 9999

struct Node {
    int row;
    int col;
    struct Node* next;
};

struct Queue {
    struct Node* front, * rear;
};

struct Node* createNode(int row, int col) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;
    return newNode;
}

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

void enqueue(struct Queue* queue, int row, int col) {
    struct Node* newNode = createNode(row, col);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

void dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return;
    }
    struct Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
}

int leeAlgorithm(int maze[ROW][COL]) {
    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    int distance[ROW][COL];
    struct Queue* queue = createQueue();

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            distance[i][j] = INF;
        }
    }

    int srcRow = 0, srcCol = 0;
    distance[srcRow][srcCol] = 0;
    enqueue(queue, srcRow, srcCol);

    while (!isEmpty(queue)) {
        int curRow = queue->front->row;
        int curCol = queue->front->col;
        dequeue(queue);

        for (int i = 0; i < 4; i++) {
            int nextRow = curRow + dr[i];
            int nextCol = curCol + dc[i];

            if (nextRow >= 0 && nextRow < ROW && nextCol >= 0 && nextCol < COL
                && maze[nextRow][nextCol] == 0 && distance[nextRow][nextCol] == INF) {
                distance[nextRow][nextCol] = distance[curRow][curCol] + 1;
                enqueue(queue, nextRow, nextCol);
            }
        }
    }

    int shortestPath = distance[ROW - 1][COL - 1];
    return shortestPath;
}

int main() {
    int maze[ROW][COL] = {
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0}
    };

    int shortestPath = leeAlgorithm(maze);

    if (shortestPath < INF) {
        printf("Shortest path length: %d\n", shortestPath);
    }
    else {
        printf("No path found to the destination.\n");
    }

    return 0;
}
